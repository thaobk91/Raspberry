/*
 * MQTTClient.h
 *
 *  Created on: Feb 23, 2018
 *      Author: thaohuyen
 */

#ifndef SOURCE_MQTTCLIENT_H_
#define SOURCE_MQTTCLIENT_H_


typedef enum
{
	eEVENT_MQTT_IDLE = 0,
	eEVENT_MQTT_CONNECTED,
	eEVENT_MQTT_DISCONNECTED,
	eEVENT_MQTT_RECEIVED,
	eEVENT_MQTT_PUBLISH_OK,
	eEVENT_MQTT_PUBLISH_NOK,
}Enum_MQTT_EVENT;





/******************************************************************************
 * Function	: int iMQTTClient_Connect( void (*_mqttCallback) ( void *, int ) )
 * Desc		: MQTT client Connect to host
 * Param	: none
 * Return	: none
 * ***************************************************************************/
int iMQTTClient_Connect( void (*_mqttCallback) ( void *, int ) );





/******************************************************************************
 * Function	: void vMQTTClient_Publish( char *uMessage )
 * Desc		: send data to broker
 * Param	: none
 * Return	: none
 * ***************************************************************************/
void vMQTTClient_Publish( char *uMessage );



#endif /* SOURCE_MQTTCLIENT_H_ */












