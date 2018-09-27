/*
 * MqttThread.h
 *
 *  Created on: May 11, 2018
 *      Author: thaohuyen
 */

#ifndef THREAD_MQTTTHREAD_H_
#define THREAD_MQTTTHREAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netinet/in.h>


/******************************************************************************
 * Function	: int iMqttThread_SendToCloud(char *pData)
 * Desc		: mqtt client send data
 * Param	: none
 * Return	: none
 * ***************************************************************************/
int iMqttThread_SendToCloud(char *pData);


#endif /* THREAD_MQTTTHREAD_H_ */
