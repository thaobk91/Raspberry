/*
 * ClientConfig.h
 *
 *  Created on: Feb 28, 2018
 *      Author: thaohuyen
 */

#ifndef INTERFACE_CLIENTCONFIG_H_
#define INTERFACE_CLIENTCONFIG_H_



struct Client_Config
{
	char 	*ClientId;
	int 	Protocol_version;
	int 	Keepalive;
	char 	*Host;
	int 	Port;
	char 	*username;
	char 	*password;
	int 	Qos;
	bool 	Retain;
	char 	*TopicPub; /* pub */
	char	*TopicSub;
	char 	*bind_address;
	int 	max_inflight;
	char 	*will_topic;
	char 	*will_payload;
	long 	will_payloadlen;
	int 	will_qos;
	bool 	will_retain;
	bool 	clean_session;
};




/******************************************************************************
 * Function	: int iClient_Config_Load(struct Client_Config *cfg)
 * Desc		: client config load from file
 * Param	:
 * 			+ cfg - config struct
 * Return	:
 * 			+ MOSQ_ERR_SUCCESS: successfully
 * 			+ others: false
 * ***************************************************************************/
int iClient_Config_Load(struct Client_Config *cfg);





/******************************************************************************
 * Function	: int iClient_Config_Save(struct Client_Config *cfg)
 * Desc		: client config save to file
 * Param	:
 * 			+ cfg - config struct
 * Return	:
 * 			+ MOSQ_ERR_SUCCESS: successfully
 * 			+ others: false
 * ***************************************************************************/
int iClient_Config_Save(struct Client_Config *cfg);





/******************************************************************************
 * Function	: void vClient_Cleanup_Config(struct Client_Config *cfg)
 * Desc		: clear config of client
 * Param	: cfg - config struct
 * Return	: none
 * ***************************************************************************/
void vClient_Cleanup_Config(struct Client_Config *cfg);





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
int iClient_Opts_Set(struct mosquitto *mosq, struct Client_Config *cfg);






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
int iClient_Id_Generate(struct Client_Config *cfg, const char *id_base);






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
int iClient_Connect(struct mosquitto *mosq, struct Client_Config *cfg);



#endif /* INTERFACE_CLIENTCONFIG_H_ */

















