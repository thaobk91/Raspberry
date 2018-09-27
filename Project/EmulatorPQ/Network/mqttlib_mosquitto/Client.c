/*
 * ClientConfig.c
 *
 *  Created on: Feb 28, 2018
 *      Author: thaohuyen
 */
//#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <mosquitto.h>
//#include "../../AppData.h"
#include "Client.h"
#include "../../main.h"



#if (USER_PROFILE == 0)
#define macroMQTT_FILE_CONFIG					"mqttclient.conf"
#elif (USER_PROFILE == 1)
#define macroMQTT_FILE_CONFIG					"/data/mqttclient.conf"
#endif




/******************************************************************************
 * Function	: void vClient_Init_Config(struct Client_Config *cfg)
 * Desc		: Init config parameter basic of client
 * Param	: cfg - config struct
 * Return	: none
 * ***************************************************************************/
static void vClient_Init_Config(struct Client_Config *cfg)
{
	//memset(cfg, 0, sizeof(*cfg));
	cfg->max_inflight = 20;
	cfg->clean_session = true;
	cfg->Protocol_version = MQTT_PROTOCOL_V31;
}




/******************************************************************************
 * Function	: int iClient_Config_Load(struct Client_Config *cfg)
 * Desc		: client config load from file
 * Param	:
 * 			+ cfg - config struct
 * Return	:
 * 			+ MOSQ_ERR_SUCCESS: successfully
 * 			+ others: false
 * ***************************************************************************/
int iClient_Config_Load(struct Client_Config *cfg)
{
	int file;
	char cBuffer[1024] = {0};
	int ui = 0;

	vClient_Init_Config(cfg);

	file = open(macroMQTT_FILE_CONFIG, O_RDONLY);
	if(file < 0)
	{
		printf("--- Client: Config load - can't open file\r\n");
		return 1;
	}

	for(;;)
	{
		char c;

		if(read(file, (char *)&c, 1) != 1)
			break;
		else
			cBuffer[ui++] = c;
	}

	if(cBuffer[0] == '\0')
	{
		printf("--- Client: file config is empty\r\n");
		return 1;
	}

	ui = 0;
	char Array[15][64];
	memset(Array, 0, sizeof(Array));
	unsigned char uj = 0, uk = 0;
	for(ui = 0; cBuffer[ui] > 0; ui++)
	{
		if((cBuffer[ui] == '=') || (cBuffer[ui] == '\n'))
		{
			uj++;
			uk = 0;
		}
		else if(cBuffer[ui] == '\r')
		{
			continue;
		}
		else
		{
			Array[uj][uk++] = cBuffer[ui];
		}
	}

	if(strcmp(Array[0], "MQTTAddr") == 0)
		cfg->Host = strdup(Array[1]);
	if(strcmp(Array[2], "MQTTPort") == 0)
		cfg->Port = atoi(Array[3]);
	if(strcmp(Array[4], "MQTTUser") == 0)
		cfg->username = strdup(Array[5]);
	if(strcmp(Array[6], "MQTTPwd") == 0)
		cfg->password = strdup(Array[7]);
	if(strcmp(Array[8], "MQTTKeepAlive") == 0)
		cfg->Keepalive = atoi(Array[9]);
	if(strcmp(Array[10], "MQTTPub") == 0)
		cfg->TopicPub = strdup(Array[11]);
	if(strcmp(Array[12], "MQTTSub") == 0)
		cfg->TopicSub = strdup(Array[13]);

	printf("********** mqtt load config ************\r\n");
	printf("--- Client: Addr = %s\r\n", cfg->Host);
	printf("--- Client: Port = %d\r\n", cfg->Port);
	printf("--- Client: User = %s\r\n", cfg->username);
	printf("--- Client: Pwd = %s\r\n", cfg->password);
	printf("--- Client: KeepAlive = %d\r\n", cfg->Keepalive);

	return MOSQ_ERR_SUCCESS;
}





/******************************************************************************
 * Function	: int iClient_Config_Save(struct Client_Config *cfg)
 * Desc		: client config save to file
 * Param	:
 * 			+ cfg - config struct
 * Return	:
 * 			+ MOSQ_ERR_SUCCESS: successfully
 * 			+ others: false
 * ***************************************************************************/
int iClient_Config_Save(struct Client_Config *cfg)
{
	int file = open(macroMQTT_FILE_CONFIG, O_WRONLY | O_APPEND | O_TRUNC | O_CREAT);
	if(file < 0)
	{
		printf("--- Client: Config save - cann't open file\r\n");
		return 1;
	}

	char cStr[512] = {0};

	sprintf(cStr, "MQTTAddr=%s\r\nMQTTPort=%d\r\nMQTTUser=%s\r\nMQTTPwd=%s\r\nMQTTKeepAlive=%d\r\nMQTTPub=%s\r\nMQTTSub=%s\r\n", \
					cfg->Host, cfg->Port, cfg->username, cfg->password, cfg->Keepalive, cfg->TopicPub, cfg->TopicSub);
	write(file, cStr, strlen(cStr));
	close(file);

	return MOSQ_ERR_SUCCESS;
}





/******************************************************************************
 * Function	: void vClient_Cleanup_Config(struct Client_Config *cfg)
 * Desc		: clear config of client
 * Param	: cfg - config struct
 * Return	: none
 * ***************************************************************************/
void vClient_Cleanup_Config(struct Client_Config *cfg)
{
	printf("--- Client: Clean up client config\r\n");
	free(cfg->ClientId);
	free(cfg->Host);
	free(cfg->TopicPub);
	free(cfg->TopicSub);
	free(cfg->bind_address);
	free(cfg->username);
	free(cfg->password);
	free(cfg->will_topic);
	free(cfg->will_payload);
}





/******************************************************************************
 * Function	: int iClient_Opts_Set(struct mosquitto *mosq, struct Client_Config *cfg)
 * Desc		: client option setting
 * Param	:
 * 			+ mosq - mosquitto client struct
 * 			+ cfg - config struct
 * Return	:
 * 			+ MOSQ_ERR_SUCCESS: successfully
 * 			+ others: false
 * ***************************************************************************/
int iClient_Opts_Set(struct mosquitto *mosq, struct Client_Config *cfg)
{
	if(cfg->will_topic && mosquitto_will_set(mosq, cfg->will_topic, cfg->will_payloadlen, cfg->will_payload, cfg->will_qos, cfg->will_retain))
	{
		printf("--- Client: Error - Problem setting will.\n");
		mosquitto_lib_cleanup();
		return 1;
	}

	if(cfg->username && mosquitto_username_pw_set(mosq, cfg->username, cfg->password))
	{
		printf("--- Client: Error - Problem setting username and password.\n");
		mosquitto_lib_cleanup();
		return 1;
	}

	mosquitto_max_inflight_messages_set(mosq, cfg->max_inflight);

	mosquitto_opts_set(mosq, MOSQ_OPT_PROTOCOL_VERSION, &(cfg->Protocol_version));
	return MOSQ_ERR_SUCCESS;
}





/******************************************************************************
 * Function	: int iClient_Id_Generate(struct Client_Config *cfg, const char *id_base)
 * Desc		: client generate id
 * Param	:
 * 			+ cfg - config struct
 * 			+ id_base - id random input
 * Return	:
 * 			+ MOSQ_ERR_SUCCESS: successfully
 * 			+ others: false
 * ***************************************************************************/
int iClient_Id_Generate(struct Client_Config *cfg, const char *id_base)
{
	int len;
	char hostname[256];

	if(!cfg->ClientId)
	{
		hostname[0] = '\0';
		gethostname(hostname, 256);
		hostname[255] = '\0';
		len = strlen(id_base) + strlen("|-") + 6 + strlen(hostname);
		cfg->ClientId = malloc(len);

		if(!cfg->ClientId)
		{
			printf("--- Client: Error - Out of memory.\n");
			mosquitto_lib_cleanup();
			return 1;
		}
		snprintf(cfg->ClientId, len, "%s|%d-%s", id_base, getpid(), hostname);
		if(strlen(cfg->ClientId) > MOSQ_MQTT_ID_MAX_LENGTH)
		{
			/* Enforce maximum client id length of 23 characters */
			cfg->ClientId[MOSQ_MQTT_ID_MAX_LENGTH] = '\0';
		}
	}

	return MOSQ_ERR_SUCCESS;
}





/******************************************************************************
 * Function	: int iClient_Connect(struct mosquitto *mosq, struct Client_Config *cfg)
 * Desc		: client connect
 * Param	:
 * 			+ cfg - config struct
 * 			+ mosq - mosquitto client struct
 * Return	:
 * 			+ MOSQ_ERR_SUCCESS: successfully
 * 			+ others: false
 * ***************************************************************************/
int iClient_Connect(struct mosquitto *mosq, struct Client_Config *cfg)
{
	char err[1024];
	int rc;

	rc = mosquitto_connect( mosq, cfg->Host, cfg->Port, cfg->Keepalive );

	if(rc > 0)
	{
		if(rc == MOSQ_ERR_ERRNO)
		{
#ifndef WIN32
			strerror_r(errno, err, 1024);
#else
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errno, 0, (LPTSTR)&err, 1024, NULL);
#endif
			printf("--- Client: Error - %s\n", err);
		}
		else
		{
			printf("--- Client: Error -Unable to connect (%s).\n", mosquitto_strerror(rc));
		}
		//mosquitto_lib_cleanup();
		return rc;
	}
	return MOSQ_ERR_SUCCESS;
}

















