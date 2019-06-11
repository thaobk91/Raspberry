/*
 * Parse.c
 *
 *  Created on: Mar 16, 2019
 *      Author: thaonm1
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Parse.h"
#include "../main.h"




//static void Parse_resetData( msgData_t *_msgData )
//{
//	_msgData->TypePacket 	= '\0';
//	_msgData->msgID 		= 0;
//	_msgData->IDEd 			= '\0';
//	for(uint8_t ui = 0; ui < _msgData->NameIndex; ui++)
//	{
//		_msgData->Data[ui].Name = '\0';
//		if(ui < _msgData->InfoIndex)
//			_msgData->Data[ui].Info = '\0';
//	}
//	_msgData->NameIndex 	= 0;
//	_msgData->InfoIndex 	= 0;
//}




/******************************************************************************
 * Function		: Array_t Parse_UnParking( uint8_t *msg, uint16_t Lenght )
 * Description	: unparking message
 * Param		: None
 * Return		: Array data
 * ***************************************************************************/
static Array_t Parse_UnParking( uint8_t *msg, uint16_t Lenght )
{
	Array_t Array = {0};
	uint8_t index = 0;
	uint8_t Len = 0;
	uint16_t Count = 0;

	while(Count < Lenght)
	{
		if((*msg == ',') || (*msg == ':') || (*msg == '!'))
		{
			index++;
			Len = 0;
			if(*msg == '!')
				break;

			if(index >= MSG_MAX_FIELD)
				return Array;
		}
		else
		{
			Array.Array[index][Len++] = *msg;
			if(Len >= MSG_FIELD_MAX_LENGHT)
				return Array;
		}
		msg++;
		Count++;
	}

	return Array;
}




/*******************************************************************************
 * Function		: msgData_t Parse_getMsgData( uint8_t *Message, uint16_t Lenght )
 * Description	: assign field message to message data struct
 * Param		: Message - input string
 * Return		:
 * 				+ message data struct
 * 				+ if data struct = NULL - failture
 * ****************************************************************************/
msgData_t Parse_getMsgData( uint8_t *Message, uint16_t Lenght )
{
//	uint8_t Array[MSG_MAX_FIELD][MSG_FIELD_MAX_LENGHT + 1] = {0};

	Array_t Array = Parse_UnParking( Message, Lenght );
	msgData_t _msgData = {0};// = malloc(Lenght + 32);
	uint8_t index = 0;

//	for(uint8_t ui = 0; Array.Array[ui][0] > 0; ui++)
//		APP_DEBUG("Array[%d] = %s\r\n", ui, Array.Array[ui]);

	//Parse_resetData(_msgData);

	while(Array.Array[index][0] > 0)
	{
		switch(index)
		{
			case 0:
				strcpy((char *)_msgData.TypePacket, (char *)Array.Array[0]);
				break;
			case 1:
				_msgData.msgID = atoi((char *)Array.Array[1]);
				break;
			case 2:
				strcpy((char *)_msgData.IDEd, (char *)Array.Array[2]);
				break;
			default:
				if(index % 2 == 1)
					strcpy((char *)_msgData.Data[_msgData.NameIndex++].Name, (char *)Array.Array[index]);
				else
					strcpy((char *)_msgData.Data[_msgData.InfoIndex++].Info, (char *)Array.Array[index]);
				break;
		}
		index++;
	}

	return _msgData;
}




/*******************************************************************************
 * Function		: string_msg_t Parse_setMsgData( msgData_t *_msgData, uint16_t *Lenght )
 * Description	: set message data
 * Param		: _msgData - message data srtuct
 * Return		: message output
 * ****************************************************************************/
string_msg_t Parse_setMsgData( msgData_t *_msgData, uint16_t *Lenght )
{
	string_msg_t string_msg = {0};

	sprintf((char *)string_msg.msgsTring, "%s,%ld,%s", (char *)_msgData->TypePacket, _msgData->msgID, (char *)_msgData->IDEd);
	for(uint8_t ui = 0; ui < _msgData->NameIndex; ui++)
	{
		sprintf((char *)string_msg.msgsTring, "%s,%s", string_msg.msgsTring, (char *)_msgData->Data[ui].Name);
		if(ui < _msgData->InfoIndex)
			sprintf((char *)string_msg.msgsTring, "%s:%s", string_msg.msgsTring, (char *)_msgData->Data[ui].Info);
	}
	string_msg.msgsTring[strlen((char *)string_msg.msgsTring)] = '!';
	*Lenght = strlen((char *)string_msg.msgsTring);

	return string_msg;
}



















