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


extern MqttStatus _MqttStatus;

typedef enum
{
	eEVENT_IDLE = 0,
	eEVENT_BUSY,
	eEVENT_RECEIVED,
	eEVENT_SEND,
	eEVENT_CONNECTED,
	eEVENT_DISCONNECTED,
}MQTT_EVENT;

MQTT_EVENT Enum_Mqtt_Event = eEVENT_DISCONNECTED;


typedef struct
{
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char day;
}User_DateTime;


User_DateTime _DateTime;

char HAQI[512] = {0};
char DAQI[512] = {0};
bool sendHAQI = false;
bool sendDAQI = false;



void getDateTime(User_DateTime *_DT)
{
	time_t     now;
	struct tm *ts;
	char       buf[80];

	/* Get the current time */
	now = time(NULL);

	/* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
	ts = localtime(&now);
//	strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", ts);
	strftime(buf, sizeof(buf), "%S", ts);
	_DT->second = atoi(buf);
	strftime(buf, sizeof(buf), "%M", ts);
	_DT->minute = atoi(buf);
	strftime(buf, sizeof(buf), "%H", ts);
	_DT->hour = atoi(buf);
//	if(_DT->hour > 23)
//		_DT->hour -= 24;
	strftime(buf, sizeof(buf), "%d", ts);
	_DT->day = atoi(buf);
	//printf("Time D - H:M:S = %d - %d:%d:%d\r\n", _DT->day, _DT->hour, _DT->minute, _DT->second);
}






/******************************************************************************
 * Function	: void *vMQTTThread_EventLoop( void *vPtr )
 * Desc		: mqtt thread event loop
 * Param	: None
 * Return	: None
 * ***************************************************************************/
void *vMQTTThread_EventLoop( void *vPtr )
{
	while(1)
	{
		switch(Enum_Mqtt_Event)
		{
			case eEVENT_BUSY:

				break;

			case eEVENT_CONNECTED:
			case eEVENT_IDLE:
				getDateTime(&_DateTime);

				if( ((_DateTime.minute == 8) || (_DateTime.minute == 52)) && (_DateTime.second == 0) )
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
				sendHAQI = false;
				sendDAQI = false;
				break;
		}

		usleep(100000);
	}
}






/******************************************************************************
 * Function	: int main( void )
 * Desc		: main
 * Param	: none
 * Return	: none
 * ***************************************************************************/
int main( void )
{
	getDateTime(&_DateTime);
	vFileData_getHAQI( HAQI, _DateTime.day, _DateTime.hour );

	printf("--- MqttThread: my mqtt client thread\r\n");
	pthread_t xPthread_MqttEventLoop;

	int iResult = pthread_create( &xPthread_MqttEventLoop, NULL, vMQTTThread_EventLoop, (void*)"vMQTTThread_EventLoop" );
	if( iResult )
	{
		printf("--- Main: mqtt event loop thread return code: %d\n", iResult );
		return 0;
	}

	iMQTTClient_Connect();

	return 0;
}





/******************************************************************************
 * Function	: int iMqttThread_SendToCloud(char *pData)
 * Desc		: mqtt client send data
 * Param	: none
 * Return	: none
 * ***************************************************************************/
int iMqttThread_SendToCloud(char *pData)
{
	unsigned long count = 0;
	_MqttStatus.SendOK = -1;
	vMQTTClient_Publish(pData);
	while( (_MqttStatus.SendOK == -1) && (count < 3000) && (_MqttStatus.Connected) )
	{
		usleep(1000);
		count++;
	}

	Enum_Mqtt_Event = eEVENT_IDLE;

	return _MqttStatus.SendOK;
}














