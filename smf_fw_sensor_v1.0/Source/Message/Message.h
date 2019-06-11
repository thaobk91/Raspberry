/*
 * Message.h
 *
 *  Created on: Mar 16, 2019
 *      Author: thaonm1
 */

#ifndef MESSAGE_MESSAGE_H_
#define MESSAGE_MESSAGE_H_

#include <stdbool.h>


/*******************************************************************************
 * Function		: void Message_Process( uint8_t *Message, uint16_t Lenght )
 * Description	: process message
 * Param		:
 * 				+ Message - message data
 * Return		: None
 * ****************************************************************************/
bool Message_Process( uint8_t *Message, uint16_t Lenght );



/******************************************************************************
 * Function		: void Message_SendData_Sensor( void )
 * Description	: sensor set data
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void Message_SendData_Sensor( void );



/********************************** Call back ***************************/
//OTA callback
void Message_set_OTA_Callback( void ota_start_cb( void ), \
							   void ota_data_cb( uint8_t *, uint16_t ), void ota_data_done_cb( void ) );


//send data callback
void Message_set_sendData_Callback( void send_data_cb( void ) );


//lora transmit callback
void Message_set_Lora_Transmit_Callback( bool Lora_Transmit_cb( uint8_t *, uint16_t ) );


//set type sensor call back
void Message_set_Typesensor_Callback( void set_typesensor_cb( void ) );




#endif /* MESSAGE_MESSAGE_H_ */















