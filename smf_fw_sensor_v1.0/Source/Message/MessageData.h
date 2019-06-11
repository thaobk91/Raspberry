/*
 * MessageData.h
 *
 *  Created on: Mar 16, 2019
 *      Author: thaonm1
 */

#ifndef MESSAGE_MESSAGEDATA_H_
#define MESSAGE_MESSAGEDATA_H_

#include <stdbool.h>
#include <stdint.h>


//Type packet
#define macroTYPE_PACKET_DATA					"DATA"
#define macroTYPE_PACKET_CONF					"CONF"
#define macroTYPE_PACKET_REQS					"REQS"
#define macroTYPE_PACKET_CTRL					"CTRL"
#define macroTYPE_PACKET_RESP					"RESP"

//ID Data
#define macroID_DATA_PH							"PH"
#define macroID_DATA_EC							"EC"
#define macroID_DATA_TEMP_S						"TempS"
#define macroID_DATA_HUMI_S						"HumiS"
#define macroID_DATA_TEMP_A						"TempA"
#define macroID_DATA_HUMI_A						"HumiA"
#define macroID_DATA_LIGHT						"Light"
#define macroID_DATA_CO2						"CO2"
#define macroID_DATA_DEVICE_STATE				"D_State"
#define macroID_DATA_TIME						"Time"

//ID Config
#define macroID_CONF_DATA_UT					"DataUT"
#define macroID_CONF_RESET						"Reset"
#define macroID_CONF_OTA						"OTA"
#define macroID_CONF_SENSOR						"SS_CFG"

//ID Request
#define macroID_REQS_ALL						"ALL"
#define macroID_REQS_D_STATE					"R_DState"


#define MSG_MAX_FIELD							23
#define MSG_FIELD_MAX_LENGHT					17




typedef struct
{
	uint8_t		TypePacket[MSG_FIELD_MAX_LENGHT / 2];
	uint32_t	msgID;
	uint8_t		IDEd[MSG_FIELD_MAX_LENGHT];

	uint8_t		NameIndex;
	uint8_t		InfoIndex;
	struct
	{
		uint8_t	Name[MSG_FIELD_MAX_LENGHT / 2];
		uint8_t	Info[MSG_FIELD_MAX_LENGHT];
	}Data[(MSG_MAX_FIELD - 3) / 2];
}msgData_t;


#endif /* MESSAGE_MESSAGEDATA_H_ */












