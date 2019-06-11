/*
 * Lora.h
 *
 *  Created on: Feb 24, 2019
 *      Author: Thao
 */

#ifndef SOURCE_LORA_LORA_H_
#define SOURCE_LORA_LORA_H_

#include <stdbool.h>
#include <stdint.h>




/*******************************************************************************
 * Function		: void Lora_Init( uint16_t Message_maxLenght )
 * Description	: Lora Init
 * Param		: Message_maxLenght - message max lenght
 * Return		: None
 * ****************************************************************************/
void Lora_Init( uint16_t Message_maxLenght );




/*******************************************************************************
 * Function		: bool Lora_Transmit( uint8_t *TXBuffer, uint16_t TXLenght )
 * Description	: Lora transmit data
 * Param		:
 * 				+ TXBuffer - TX Buffer
 * 				+ TXLenght - TX buffer lenght
 * Return		:
 * 				+ true - successfully
 * 				+ false - failture
 * ****************************************************************************/
bool Lora_Transmit( uint8_t *TXBuffer, uint16_t TXLenght );




/*******************************************************************************
 * Function		: uint16_t Lora_Receive( uint8_t *RX_Buffer )
 * Description	: Lora receive data
 * Param		: RX_Buffer - RX Buffer
 * Return		:
 * 				+ >0 - successfully
 * 				+ 0 - failture
 * ****************************************************************************/
uint16_t Lora_Receive( uint8_t *RX_Buffer );


#endif /* SOURCE_LORA_LORA_H_ */














