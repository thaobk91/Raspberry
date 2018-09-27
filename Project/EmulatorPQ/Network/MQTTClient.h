/*
 * MQTTClient.h
 *
 *  Created on: Feb 23, 2018
 *      Author: thaohuyen
 */

#ifndef SOURCE_MQTTCLIENT_H_
#define SOURCE_MQTTCLIENT_H_


#define macroMQTT_RX_BUFFER_LENGHT				512
#define macroRX_TX_BUFFER_LENGHT				512

typedef struct
{
	char 	uMQTT_RX_Buffer[macroRX_TX_BUFFER_LENGHT];
	bool	MessageReceived;
	bool	Connected;
	bool	Disconnected;
	int		SendOK;
}MqttStatus;



/******************************************************************************
 * Function	: int iMQTTClient_Connect( void )
 * Desc		: MQTT client Connect to host
 * Param	: none
 * Return	: none
 * ***************************************************************************/
int iMQTTClient_Connect( void );




/******************************************************************************
 * Function	: void vMQTTClient_Reconnect( void )
 * Desc		: MQTT client reconnect to host
 * Param	: none
 * Return	: none
 * ***************************************************************************/
void vMQTTClient_Reconnect( void );





/******************************************************************************
 * Function	: void vMQTTClient_Publish( char *uMessage )
 * Desc		: send data to broker
 * Param	: none
 * Return	: none
 * ***************************************************************************/
void vMQTTClient_Publish( char *uMessage );




/******************************************************************************
 * Function	: void vMQTTClient_Save_Config(char *Host, int Port, char *User, char *Pwd, int KeepAlive, char *Pub, char *Sub)
 * Desc		: save config
 * Param	: none
 * Return	: none
 * ***************************************************************************/
void vMQTTClient_Save_Config(char *Host, int Port, char *User, char *Pwd, int KeepAlive, char *Pub, char *Sub);



#endif /* SOURCE_MQTTCLIENT_H_ */












