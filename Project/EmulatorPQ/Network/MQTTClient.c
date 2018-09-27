/*
 * MQTTClient.c
 *
 *  Created on: Feb 23, 2018
 *      Author: thaohuyen
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <assert.h>
#include <errno.h>
#include <unistd.h>

#include "mqttlib_mosquitto/mosquitto.h"
#include "mqttlib_mosquitto/Client.h"
#include "MQTTClient.h"


unsigned char uIDGW[17] = "4E4543801003002A";


struct mosquitto *xMQTTClient = NULL;


struct Client_Config xMQTTClient_Config =
{
	.Host		= "thingxyz.net",
	.Port		= 1883,
	.username	= "",
	.password	= "",
	.Keepalive	= 60,
	.TopicPub	= "123456",
	.TopicSub	= "123456",
};

unsigned long ulSendCounter = 0;


MqttStatus _MqttStatus =
{
	.uMQTT_RX_Buffer	= {0},
	.MessageReceived	= false,
	.Connected			= false,
	.Disconnected		= true,
	.SendOK				= -1,
};





/******************************************************************************
 * Function	: void vMQTTClient_Message_Callback( struct mosquitto *xMosq, void *vUserData, const struct mosquitto_message *xMessage )
 * Desc		: Callback when received message
 * Param	:
 * 			+ xMosq: mosquitto object
 * 			+ vUserData: none
 * 			+ xMessage: Message received
 * Return	: none
 * ***************************************************************************/
static void vMQTTClient_Message_Callback( struct mosquitto *xMosq, void *vUserData, const struct mosquitto_message *xMessage )
{
	if(xMessage->payloadlen)
	{
		printf( "\n--- MQTTClient: Receive message \"%s\" at topic \"%s\"\n", (char *)xMessage->payload, xMessage->topic );
		while(_MqttStatus.MessageReceived); //wait for data process done
		memset(_MqttStatus.uMQTT_RX_Buffer, 0, strlen(_MqttStatus.uMQTT_RX_Buffer));
		strcpy(_MqttStatus.uMQTT_RX_Buffer, (char *)xMessage->payload);
		_MqttStatus.MessageReceived = true;
	}
	else
	{
		printf( "--- MQTTClient: Received at topic \"%s\" is (null)\n", xMessage->topic );
	}
}




/******************************************************************************
 * Function	: void vMQTTClient_Connect_Callback(struct mosquitto *xMosq, void *vUserData, int iResult)
 * Desc		: Callback when connect to host
 * Param	:
 * 			+ xMosq: mosquitto object
 * 			+ vUserData: none
 * 			+ siResult: Ket qua tra ve
 * Return	: none
 * ***************************************************************************/
static void vMQTTClient_Connect_Callback(struct mosquitto *xMosq, void *vUserData, int iResult)
{
	struct Client_Config *cfg;
	assert(vUserData);
	cfg = (struct Client_Config *)vUserData;

	if(!iResult)
	{
		printf("--- MQTTClient: Client connect to host successfully!\r\n");
		printf("--- MQTTClient: Subcribing...\r\n");
		/* Subscribe to broker information topics on successful connect. */
		_MqttStatus.Connected = true;
		_MqttStatus.Disconnected = false;
		mosquitto_subscribe(xMosq, NULL, cfg->TopicSub, cfg->Qos);
	}
	else
	{
		_MqttStatus.Connected = false;
		_MqttStatus.Disconnected = true;
		printf("--- MQTTClient: Connect failed\n");
		if(iResult)
		{
			printf("--- MQTTClient: %s\n", mosquitto_connack_string(iResult));
		}
	}
}




/******************************************************************************
 * Function	: void vMQTTClient_Disconnect_Callback( struct mosquitto *xMosq, void *vUserData, int iResult )
 * Desc		: Callback when disconnect from host
 * Param	:
 * 			+ xMosq: mosquitto object
 * 			+ vUserData: none
 * 			+ iResult: Ket qua tra ve
 * Return	: none
 * ***************************************************************************/
static void vMQTTClient_Disconnect_Callback( struct mosquitto *xMosq, void *vUserData, int iResult )
{
	printf("\r\n--- MQTTClient: Client disconnected\r\n\n");
	_MqttStatus.Connected = false;
	_MqttStatus.Disconnected = true;
}




/******************************************************************************
 * Function	: void vMQTTClient_Subscribe_Callback( struct mosquitto *xMosq, void *vUserData, int siMid, int siQos_Count, const int *siGranted_qos )
 * Desc		: Callback when subcribe topic
 * Param	:
 * 			+ xMosq: mosquitto object
 * 			+ vUserData: none
 * 			+ siMid: none
 * 			+ siQos_Count: none
 * 			+ siGranted_qos: none
 * Return	: none
 * ***************************************************************************/
static void vMQTTClient_Subscribe_Callback( struct mosquitto *xMosq, void *vUserData, int iMid, int siQos_Count, const int *iGranted_qos )
{
	int sii;
	assert(vUserData);

	printf("--- MQTTClient: Subscribed (mid: %d): %d", iMid, iGranted_qos[0]);

	for( sii = 1; sii < siQos_Count; sii++)
	{
		printf(", %d", iGranted_qos[sii]);
	}
	printf(" successfully\n");
}




/******************************************************************************
 * Function	: void vMQTTClient_Publish_Callback( struct mosquitto *xMosq, void *vUserData, int iResult )
 * Desc		: Callback when publish topic
 * Param	:
 * 			+ xMosq: mosquitto object
 * 			+ vUserData: none
 * 			+ iResult: result
 * Return	: none
 * ***************************************************************************/
static void vMQTTClient_Publish_Callback( struct mosquitto *xMosq, void *vUserData, int iResult )
{
	if(iResult != -1)
	{
		_MqttStatus.SendOK = 1;
		printf("--- MQTTClient: Publish data successfully\r\n");
	}
	else
	{
		_MqttStatus.SendOK = 0;
		printf("--- MQTTClient: Publish data fail\r\n");
	}
}




/******************************************************************************
 * Function	: void vMQTTClient_Log_Callback( struct mosquitto *xMosq, void *vUserData, int iLevel, const char *cStr )
 * Desc		: Callback log data
 * Param	:
 * 			+ xMosq: mosquitto object
 * 			+ vUserData: none
 * 			+ iLevel: none#define macroMQTT_HOST					"thingxyz.net"
#define macroMQTT_PORT					1993
#define macroMQTT_USER					""
#define macroMQTT_PWD					""
#define macroMQTT_KEEPALIVE				60
 * 			+ cStr: message to log
 * Return	: none
 * ***************************************************************************/
void vMQTTClient_Log_Callback( struct mosquitto *xMosq, void *vUserData, int iLevel, const char *cStr )
{
	/* Pring all log messages regardless of level. */
	//printf("--- MQTTClient: Log - %s\n", cStr);
}





/******************************************************************************
 * Function	: int iMQTTClient_Connect( void )
 * Desc		: MQTT client Connect to host
 * Param	: none
 * Return	: none
 * ***************************************************************************/
int iMQTTClient_Connect( void )
{
	char cClientID[32] = {0};
	char cStr1[128] = {0};
	char cStr2[128] = {0};

	sprintf(cClientID, "SMH-%s", (char *)uIDGW);

//	if(iClient_Config_Load(&xMQTTClient_Config) != MOSQ_ERR_SUCCESS)
//		return 1;

	sprintf(cStr1, "/SCPCloud/DEVICE/%s", (char *)uIDGW);
	xMQTTClient_Config.TopicPub = cStr1;
	sprintf(cStr2, "/IN-CSB1/command/%s", (char *)uIDGW);
	xMQTTClient_Config.TopicSub = cStr2;
	printf("--- MQTTClient: Pub = %s\r\n", xMQTTClient_Config.TopicPub);
	printf("--- MQTTClient: Sub = %s\r\n\r\n", xMQTTClient_Config.TopicSub);

	mosquitto_lib_init();

	if(iClient_Id_Generate(&xMQTTClient_Config, cClientID))
		return 1;
	printf("--- MQTTClient: Client ID = \"%s\"\r\n", xMQTTClient_Config.ClientId);

	xMQTTClient = mosquitto_new( xMQTTClient_Config.ClientId, xMQTTClient_Config.clean_session, &xMQTTClient_Config );
	if( !xMQTTClient )
	{
		switch(errno)
		{
			case ENOMEM:
				printf("--- MQTTClient: Error - Out of memory.\n");
				break;
			case EINVAL:
				printf("--- MQTTClient: Error - Invalid id and/or clean_session.\n");
				break;
		}
		mosquitto_lib_cleanup();
		return 1;
	}

	if(iClient_Opts_Set(xMQTTClient, &xMQTTClient_Config))
		return 1;

	mosquitto_connect_callback_set( xMQTTClient, vMQTTClient_Connect_Callback );
	mosquitto_disconnect_callback_set( xMQTTClient,  vMQTTClient_Disconnect_Callback );
	mosquitto_message_callback_set( xMQTTClient, vMQTTClient_Message_Callback );
	mosquitto_publish_callback_set( xMQTTClient, vMQTTClient_Publish_Callback );
	mosquitto_log_callback_set(xMQTTClient, vMQTTClient_Log_Callback);
	mosquitto_subscribe_callback_set(xMQTTClient, vMQTTClient_Subscribe_Callback);

	while( iClient_Connect(xMQTTClient, &xMQTTClient_Config) )
	{
		//usleep(1000000);
		sleep(10);
	}

	mosquitto_loop_forever(xMQTTClient, -1, 1);

	mosquitto_destroy(xMQTTClient);
	mosquitto_lib_cleanup();

	return 1;
}





/******************************************************************************
 * Function	: void vMQTTClient_Reconnect( void )
 * Desc		: MQTT client reconnect to host
 * Param	: none
 * Return	: none
 * ***************************************************************************/
void vMQTTClient_Reconnect( void )
{
	printf("--- MQTTClient: mqtt reconnecting...\r\n");
	mosquitto_reconnect(xMQTTClient);
}





/******************************************************************************
 * Function	: void vMQTTClient_Publish( char *uMessage )
 * Desc		: send data to broker
 * Param	: none
 * Return	: none
 * ***************************************************************************/
void vMQTTClient_Publish( char *uMessage )
{
	if(_MqttStatus.Connected == true)
	{
		ulSendCounter++;
		printf("--- MQTTClient: send \"%s\" lenght = %d to Cloud. Send counter = %ld\r\n", uMessage, (int)strlen(uMessage), ulSendCounter);
		mosquitto_publish( xMQTTClient, NULL, xMQTTClient_Config.TopicPub, strlen(uMessage), uMessage, 0, false);
	}
	else
	{
		_MqttStatus.SendOK = 0;
		printf("--- MQTTClient: Can't publish because mqtt client is disconnected\r\n");
	}
}




/******************************************************************************
 * Function	: void vMQTTClient_Save_Config(char *Host, int Port, char *User, char *Pwd, int KeepAlive, char *Pub, char *Sub)
 * Desc		: save config
 * Param	: none
 * Return	: none
 * ***************************************************************************/
void vMQTTClient_Save_Config(char *Host, int Port, char *User, char *Pwd, int KeepAlive, char *Pub, char *Sub)
{
	xMQTTClient_Config.Host = Host;
	xMQTTClient_Config.Port = Port;
	xMQTTClient_Config.username = User;
	xMQTTClient_Config.password = Pwd;
	xMQTTClient_Config.Keepalive = KeepAlive;
	xMQTTClient_Config.TopicPub = Pub;
	xMQTTClient_Config.TopicSub = Sub;
	if(iClient_Config_Save(&xMQTTClient_Config) == MOSQ_ERR_SUCCESS)
		printf("--- MQTTClient: mqtt param config successfully\r\n");
	else
		printf("--- MQTTClient: mqtt param config failture\r\n");
}














