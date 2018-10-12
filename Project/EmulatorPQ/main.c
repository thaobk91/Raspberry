/*
 * MqttThread.c
 *
 *  Created on: May 11, 2018
 *      Author: thaohuyen
 */
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "MQTTClient.h"
#include "main.h"
#include "FileData.h"

#define macroTIME_MAIN_LOOP					10000		//us


unsigned char uIDGW[17] = "4E4543801003002A";



typedef struct
{
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char day;
	unsigned char month;
	unsigned char year;
}User_DateTime;


User_DateTime _DateTime;
char HAQI[512] = {0};
char DAQI[512] = {0};
bool sendHAQI = false;
bool sendDAQI = false;
bool isClientConnected = false;





void getDateTime(User_DateTime *_DT)
{
	time_t     now;
	struct tm *ts;
	char       buf[16];

	/* Get the current time */
	now = time(NULL);
	/* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
	ts = localtime(&now);

	strftime(buf, sizeof(buf), "%S", ts);
	_DT->second = atoi(buf);
	strftime(buf, sizeof(buf), "%M", ts);
	_DT->minute = atoi(buf);
	strftime(buf, sizeof(buf), "%H", ts);
	_DT->hour = atoi(buf);
	strftime(buf, sizeof(buf), "%d", ts);
	_DT->day = atoi(buf);
	strftime(buf, sizeof(buf), "%m", ts);
	_DT->month = atoi(buf);
	strftime(buf, sizeof(buf), "%Y", ts);
	_DT->year = atoi(buf);
	//printf("Time D - H:M:S = %d - %d:%d:%d\r\n", _DT->day, _DT->hour, _DT->minute, _DT->second);
}




/******************************************************************************
 * Function	: void *vMQTTThread_EventLoop( void *vPtr )
 * Desc		: mqtt thread event loop
 * Param	: None
 * Return	: None
 * ***************************************************************************/
static void vMQTTThread_Event_Callback( void *Buffer, int Event )
{
	switch(Event)
	{
<<<<<<< HEAD
		case eEVENT_MQTT_IDLE:
			break;

		case eEVENT_MQTT_CONNECTED:
			printf("--- Main: MQTT Client is connected\r\n");
			isClientConnected = true;
			break;

		case eEVENT_MQTT_DISCONNECTED:
			printf("--- Main: MQTT Client is disconnected\r\n");
			isClientConnected = false;
			break;

		case eEVENT_MQTT_RECEIVED:
			printf("--- Main: MQTT Client received data = %s\r\n", (char *)Buffer);
			break;

		case eEVENT_MQTT_PUBLISH_OK:
			if(sendHAQI == true)
			{
=======
		switch(Enum_Mqtt_Event)
		{
			case eEVENT_BUSY:

				break;

			case eEVENT_CONNECTED:
			case eEVENT_IDLE:
				getDateTime(&_DateTime);

				if( ((_DateTime.minute == 17) || (_DateTime.minute == 45)) && (_DateTime.second == 0) )
				{
					vFileData_getHAQI( HAQI, _DateTime.day, _DateTime.hour );
					printf("HAQI = %s\r\n", HAQI);
					sendHAQI = true;
					Enum_Mqtt_Event = eEVENT_SEND;
				}
				if( ((_DateTime.hour == 0) || (_DateTime.hour == 9) || (_DateTime.hour == 18)) && \
					(_DateTime.minute == 3) && (_DateTime.minute == 0) \
					)
				{
					vFileData_getDAQI( DAQI, _DateTime.day, _DateTime.hour );
					printf("HAQI = %s\r\n", DAQI);
					sendDAQI = true;
					Enum_Mqtt_Event = eEVENT_SEND;
				}

				if(_MqttStatus.MessageReceived == true)
					Enum_Mqtt_Event = eEVENT_RECEIVED;
				else if(_MqttStatus.Disconnected == true)
					Enum_Mqtt_Event = eEVENT_DISCONNECTED;
				break;

			case eEVENT_DISCONNECTED:
				if(_MqttStatus.Connected == true)
					Enum_Mqtt_Event = eEVENT_CONNECTED;
				else
					sleep(1);
				break;

			case eEVENT_RECEIVED:
				printf(" MQTT Client received data = %s\r\n", _MqttStatus.uMQTT_RX_Buffer);
				_MqttStatus.MessageReceived = false;
				break;

			case eEVENT_SEND:
				Enum_Mqtt_Event = eEVENT_BUSY;

				if(sendHAQI == true)
					iMqttThread_SendToCloud(HAQI);
				else if(sendDAQI == true)
					iMqttThread_SendToCloud(DAQI);
>>>>>>> 40d920c04caaa12060106f89d3df13bf9c9725c5
				sendHAQI = false;
			}
			else if(sendDAQI == true)
			{
				sendDAQI = false;
			}
			break;

		case eEVENT_MQTT_PUBLISH_NOK:

			break;
	}
}






/******************************************************************************
 * Function	: void *vMqttThread_Run( void *vPtr )
 * Desc		: Thread for mqtt client
 * Param	: none
 * Return	: none
 * ***************************************************************************/
void *vMqttThread_Run( void *vPtr )
{
	printf("--- MqttThread: my mqtt client thread\r\n");
	iMQTTClient_Connect( vMQTTThread_Event_Callback );

	return 0;
}







/******************************************************************************
 * Function	: int main( void )
 * Desc		: main
 * Param	: none
 * Return	: none
 * ***************************************************************************/
int main( void )
{
<<<<<<< HEAD
	unsigned int uiSendCounter = 0;
	int iResult = -1;

	pthread_t xPthread_MqttClient;
	//mqtt thread
	iResult = pthread_create( &xPthread_MqttClient, NULL, vMqttThread_Run, (void*)"vMqttThread_Run");
	if( iResult )
	{
		printf("--- Main: mqtt client thread return code: %d\n", iResult );
		return 0;
=======
	unsigned long count = 0;
	_MqttStatus.SendOK = -1;
	vMQTTClient_Publish(pData);
	while( (_MqttStatus.SendOK == -1) && (count < (3000000 / 100000)) && (_MqttStatus.Connected) )
	{
		usleep(100000);
		count++;
>>>>>>> 40d920c04caaa12060106f89d3df13bf9c9725c5
	}

	while(1)
	{
		if(isClientConnected == true)
		{
			uiSendCounter++;
			getDateTime(&_DateTime);

			if( ((_DateTime.minute == 5) || (_DateTime.minute == 35)) && (_DateTime.second == 0) && (sendHAQI == false) )
			{
				vFileData_getHAQI( HAQI, _DateTime.day, _DateTime.hour );
				printf("HAQI = %s\r\n", HAQI);
				sendHAQI = true;
			}

			if( ((_DateTime.hour == 0) || (_DateTime.hour == 12)) && (_DateTime.minute == 3) && (_DateTime.second == 0) && (sendDAQI == false) )
			{
				vFileData_getDAQI( DAQI, _DateTime.day, _DateTime.hour );
				printf("HAQI = %s\r\n", DAQI);
				sendDAQI = true;
			}

			if(uiSendCounter >= (1000000 / macroTIME_MAIN_LOOP))
			{
				printf("DateTime = %d:%d:%d - %d/%d/%d\r\n", _DateTime.hour, _DateTime.minute, _DateTime.second, _DateTime.day, _DateTime.month, _DateTime.year);

				if(sendHAQI == true)
					vMQTTClient_Publish(HAQI);
				else if(sendDAQI == true)
					vMQTTClient_Publish(DAQI);

				uiSendCounter = 0;
			}
		}
		else
		{
			printf("--- Main: Client is disconneced\r\n");
			usleep( 1000000 - macroTIME_MAIN_LOOP );
		}

		usleep( macroTIME_MAIN_LOOP );
	}

	return 0;
}

















