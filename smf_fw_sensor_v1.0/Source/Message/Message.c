/*
 * Message.c
 *
 *  Created on: Mar 16, 2019
 *      Author: thaonm1
 */
#include <stdlib.h>
#include <string.h>

#include "Parse.h"
#include "MessageData.h"
#include "Message.h"
#include "../main.h"
//#include "EDC.h"
#include "../fileData.h"
#include "../Task/SensorTask.h"



extern uint8_t SerialNumber[17];;
extern fileData_t __fileData;
extern SensorData_t __SensorData;

uint32_t msgID = 0;



static void Message_isData( msgData_t *_msgData );
static void Message_isConfig( msgData_t *_msgData );
static void Message_isRequest( msgData_t *_msgData );
static void Message_isControl( msgData_t *_msgData );
static void Message_isResponse( msgData_t *_msgData );
static void Message_sendData( msgData_t *_msgData );


//send data callback
void (*Message_sendData_Callback)( void );
//OTA call back
void (*Message_OTA_Start_Callback)( void );
void (*Message_OTA_DataDone_Callback)( void );
//OTA call back
void (*Message_OTA_Data_Callback)( uint8_t *, uint16_t );
//send data
bool (*Message_Lora_Transmit) ( uint8_t */*Data*/, uint16_t /*Lenght*/ );
//set type sensor
void (*Message_setTypeSensor)( void );




/*******************************************************************************
 * Function		: void Message_Process( uint8_t *Message, uint16_t Lenght )
 * Description	: process message
 * Param		:
 * 				+ Message - message data
 * Return		: None
 * ****************************************************************************/
bool Message_Process( uint8_t *Message, uint16_t Lenght )
{
	//uint8_t *msgDecode = EDC_Decode( Message, &Lenght );
	APP_DEBUG("--- Message: Received = \"%s\", lenght = %d\r\n", Message, Lenght);
	msgData_t _msgData = Parse_getMsgData( Message, Lenght );
	//free(msgDecode);

//	if(_msgData == NULL)
//	{
//		APP_DEBUG("--- Message: message error\r\n");
//		free(_msgData);
//		return false;
//	}

	if( strcmp((char *)_msgData.IDEd, (char *)SerialNumber) != 0 )
	{
		APP_DEBUG("--- Message: IDEd not found\r\n");
//		free(_msgData);
		return false;
	}

	if( strcmp((char *)_msgData.TypePacket, macroTYPE_PACKET_DATA) == 0 )	//data
		Message_isData( &_msgData );
	else if( strcmp((char *)_msgData.TypePacket, macroTYPE_PACKET_CONF) == 0 )	//config
		Message_isConfig( &_msgData );
	else if( strcmp((char *)_msgData.TypePacket, macroTYPE_PACKET_CTRL) == 0 )	//request
		Message_isRequest( &_msgData );
	else if( strcmp((char *)_msgData.TypePacket, macroTYPE_PACKET_REQS) == 0 )	//control
		Message_isControl( &_msgData );
	else if( strcmp((char *)_msgData.TypePacket, macroTYPE_PACKET_RESP) == 0 )	//response
		Message_isResponse( &_msgData );

//	free(_msgData);
	return true;
}




/*******************************************************************************
 * Function		: void Message_isData( msgData_t *_msgData )
 * Description	: process message is data type
 * Param		: _msgData - message data struct
 * Return		: None
 * ****************************************************************************/
static void Message_isData( msgData_t *_msgData )
{
	APP_DEBUG("--- Message: type packet data not except\r\n");
}




/*******************************************************************************
 * Function		: void Message_isConfig( msgData_t *_msgData )
 * Description	: process message is config type
 * Param		:
 * 				+ _msgData - message data struct
 * 				+ msgIsJson - message is json
 * Return		: None
 * ****************************************************************************/
static void Message_isConfig( msgData_t *_msgData )
{
	uint8_t index = 0;

	for(index = 0; index < _msgData->NameIndex; index++)
	{
		if( strcmp((char *)_msgData->Data[index].Name, macroID_CONF_DATA_UT) == 0 )	//data UT
		{
			uint16_t value = atoi((char *)_msgData->Data[index].Info);
			if( (value > 10) && (value < 60*60*24) )
			{
				APP_DEBUG("--- Message: rewrite data update time\r\n");
				__fileData.DataUT = value;
				fileData_Write_DataUT();
			}
			else
				APP_DEBUG("--- Message: dataUT not found\r\n");
			break;
		}
		else if( strcmp((char *)_msgData->Data[index].Name, macroID_CONF_RESET ) == 0 )	//reset
		{
			APP_DEBUG("--- Message: device reseting...\r\n");
			HAL_Delay(1000);
			NVIC_SystemReset();
		}
		else if( strcmp((char *)_msgData->Data[index].Name, macroID_CONF_OTA ) == 0 )	//OTA
		{
			Message_OTA_Start_Callback();
		}
		else if( strcmp((char *)_msgData->Data[index].Name, macroID_CONF_SENSOR ) == 0 )	//config sensor
		{
			uint16_t value = atoi((char *)_msgData->Data[index].Info);
			if( ( value>= 0) && (value < 0xffff) )
			{
				__fileData.SensorCfg &= value;
				APP_DEBUG("--- Message: config sensor type = 0x%.4x\r\n", __fileData.SensorCfg);
				fileData_Write_SensorCFG();
				Message_setTypeSensor();
				break;
			}
		}
	}
}




/*******************************************************************************
 * Function		: void Message_isRequest( msgData_t *_msgData )
 * Description	: process message is request type
 * Param		:
 * 				+ _msgData - message data struct
 * 				+ msgIsJson - message is json
 * Return		: None
 * ****************************************************************************/
static void Message_isRequest( msgData_t *_msgData )
{
	uint8_t index = 0;

	for(index = 0; index < _msgData->NameIndex; index++)
	{
		if( strcmp((char *)_msgData->Data[index].Name, macroID_REQS_ALL ) == 0 )
		{

//			Message_sendData( _msgData );
			Message_SendData_Sensor();
			break;
		}
		else if( strcmp((char *)_msgData->Data[index].Name, macroID_REQS_D_STATE ) == 0 )
		{
			APP_DEBUG("--- Message: request is D State\r\n");
			strcpy((char *)_msgData->TypePacket, macroTYPE_PACKET_DATA);
			strcpy((char *)_msgData->Data[0].Name, macroID_DATA_DEVICE_STATE);
			strcpy((char *)_msgData->Data[0].Info, "OK");
			_msgData->NameIndex		= 1;
			_msgData->InfoIndex		= 1;

			Message_sendData( _msgData );
			break;
		}
	}
}




/*******************************************************************************
 * Function		: void Message_isControl( msgData_t *_msgData )
 * Description	: process message is control type
 * Param		:
 * 				+ _msgData - message data struct
 * 				+ msgIsJson - message is json
 * Return		: None
 * ****************************************************************************/
static void Message_isControl( msgData_t *_msgData )
{
	APP_DEBUG("--- Message: type packet control not except\r\n");
}




/*******************************************************************************
 * Function		: void Message_isResponse( msgData_t *_msgData )
 * Description	: process message is response type
 * Param		:
 * 				+ _msgData - message data struct
 * 				+ msgIsJson - message is json
 * Return		: None
 * ****************************************************************************/
static void Message_isResponse( msgData_t *_msgData )
{
	APP_DEBUG("--- Message: message is response\r\n");
	if(_msgData->msgID == msgID)
	{
		Message_sendData_Callback();
	}
}



/*******************************************************************************
 * Function		: void Message_sendData( msgData_t *_msgData )
 * Description	: send data
 * Param		:
 * 				+ _msgData - message data struct
 * Return		: None
 * ****************************************************************************/
static void Message_sendData( msgData_t *_msgData )
{
	uint16_t msgLenght = 0;
	string_msg_t msg_string = Parse_setMsgData(_msgData, &msgLenght);
	//APP_DEBUG("--- Message: preparing packet = \"%s\", lenght = %d\r\n", msg, msgLenght);
	//msg = EDC_Encode( msg, &msgLenght );
	Message_Lora_Transmit( msg_string.msgsTring, msgLenght );
//	free(msg_string);
}



/******************************************************************************
 * Function		: void Message_SendData_Sensor( void )
 * Description	: sensor set data
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void Message_SendData_Sensor( void )
{
	uint8_t index = 0;
	msgData_t __msgData = {0};

	APP_DEBUG("\r\n--- Message: set sensor data\r\n");

	strcpy((char *)__msgData.TypePacket, macroTYPE_PACKET_DATA);
	__msgData.msgID = ++msgID;
	strcpy((char *)__msgData.IDEd, (char *)SerialNumber);

	//temp soil
	if((__fileData.SensorCfg & SS_TempS) == SS_TempS)
	{
		strcpy((char *)__msgData.Data[index].Name, macroID_DATA_TEMP_S);
		sprintf((char *)__msgData.Data[index].Info, "%.2f", __SensorData.TempS);
		index++;
	}

	//humi soil
	if((__fileData.SensorCfg & SS_HumiS) == SS_HumiS )
	{
		strcpy((char *)__msgData.Data[index].Name, macroID_DATA_HUMI_S);
		sprintf((char *)__msgData.Data[index].Info, "%.2f", __SensorData.HumiS);
		index++;
	}

	//temp air
	if((__fileData.SensorCfg & SS_TempA) == SS_TempA)
	{
		strcpy((char *)__msgData.Data[index].Name, macroID_DATA_TEMP_A);
		sprintf((char *)__msgData.Data[index].Info, "%.2f", __SensorData.TempA);
		index++;
	}

	//humi air
	if((__fileData.SensorCfg & SS_HumiA) == SS_HumiA )
	{
		strcpy((char *)__msgData.Data[index].Name, macroID_DATA_HUMI_A);
		sprintf((char *)__msgData.Data[index].Info, "%.2f", __SensorData.HumiA);
		index++;
	}

	//Light
	if((__fileData.SensorCfg & SS_Light) == SS_Light )
	{
		strcpy((char *)__msgData.Data[index].Name, macroID_DATA_LIGHT);
		sprintf((char *)__msgData.Data[index].Info, "%.2f", __SensorData.Light);
		index++;
	}

	//PH
	if((__fileData.SensorCfg & SS_pH) == SS_pH )
	{
		strcpy((char *)__msgData.Data[index].Name, macroID_DATA_PH);
		sprintf((char *)__msgData.Data[index].Info, "%.2f", __SensorData.PH);
		index++;
	}

	//EC
	if((__fileData.SensorCfg & SS_EC) == SS_EC )
	{
		strcpy((char *)__msgData.Data[index].Name, macroID_DATA_EC);
		sprintf((char *)__msgData.Data[index].Info, "%.2f", __SensorData.EC);
		index++;
	}

	//CO2
	if((__fileData.SensorCfg & SS_CO2) == SS_CO2 )
	{
		strcpy((char *)__msgData.Data[index].Name, macroID_DATA_CO2);
		sprintf((char *)__msgData.Data[index].Info, "%.2f", __SensorData.CO2);
		index++;
	}

	__msgData.NameIndex = __msgData.InfoIndex = index;

	Message_sendData(&__msgData);
	//free(__msgData);
}




/********************************** Call back ***************************/
//OTA callback
void Message_set_OTA_Callback( void ota_start_cb( void ), \
							   void ota_data_cb( uint8_t *, uint16_t ), void ota_data_done_cb( void ) )
{
	Message_OTA_Start_Callback		= ota_start_cb;
	Message_OTA_Data_Callback		= ota_data_cb;
	Message_OTA_DataDone_Callback	= ota_data_done_cb;
}



//send data callback
void Message_set_sendData_Callback( void send_data_cb( void ) )
{
	Message_sendData_Callback = send_data_cb;
}



//lora transmit callback
void Message_set_Lora_Transmit_Callback( bool Lora_Transmit_cb( uint8_t *, uint16_t ) )
{
	Message_Lora_Transmit = Lora_Transmit_cb;
}



//set type sensor call back
void Message_set_Typesensor_Callback( void set_typesensor_cb( void ) )
{
	Message_setTypeSensor = set_typesensor_cb;
}




















