/*
 * Parse.h
 *
 *  Created on: Mar 16, 2019
 *      Author: thaonm1
 */

#ifndef MESSAGE_PARSE_H_
#define MESSAGE_PARSE_H_

#include <stdint.h>

#include "MessageData.h"



typedef struct
{
	uint8_t Array[MSG_MAX_FIELD][MSG_FIELD_MAX_LENGHT + 1];
}Array_t;

typedef struct
{
	uint8_t msgsTring[MSG_MAX_FIELD*MSG_FIELD_MAX_LENGHT + 1];
}string_msg_t;



/*******************************************************************************
 * Function		: msgData_t Parse_getMsgData( uint8_t *Message, uint16_t Lenght )
 * Description	: assign field message to message data struct
 * Param		: Message - input string
 * Return		:
 * 				+ message data struct
 * 				+ if data struct = NULL - failture
 * ****************************************************************************/
msgData_t Parse_getMsgData( uint8_t *Message, uint16_t Lenght );




/*******************************************************************************
 * Function		: string_msg_t Parse_setMsgData( msgData_t *_msgData, uint16_t *Lenght )
 * Description	: set message data
 * Param		: _msgData - message data srtuct
 * Return		: message output
 * ****************************************************************************/
string_msg_t Parse_setMsgData( msgData_t *_msgData, uint16_t *Lenght );

#endif /* MESSAGE_PARSE_H_ */









