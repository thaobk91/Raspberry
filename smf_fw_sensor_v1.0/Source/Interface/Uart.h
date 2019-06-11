/*
 * Uart.h
 *
 *  Created on: Feb 27, 2019
 *      Author: Thao
 */

#ifndef INTERFACE_UART_H_
#define INTERFACE_UART_H_

#include <stdbool.h>
#include "stm32l4xx_hal.h"


typedef struct
{
	UART_HandleTypeDef 	_UartHandle;
	uint8_t				*UartRX_Buffer;
	uint8_t				UartRX_Lenght;

	bool				(*Uart_Transmit) ( UART_HandleTypeDef *_UartHandle, uint8_t *TXBuffer, uint16_t TXLenght );
	uint16_t			(*Uart_Receive) ( UART_HandleTypeDef *_UartHandle, uint8_t *RXBuffer, uint16_t RXLenght );
}Uart_Handle_t;




/******************************************************************************
 * Function		: bool Uart_Open( Uart_Handle_t *_Uart_Handle, USART_TypeDef *_UartInstance, uint32_t Baudrate )
 * Description	: uart open
 * Parameter	:
 * 				+ _UartHandle: uart handle
 * 				+ _UartInstance: uart data struct
 * 				+ Baudrate - bit rate per second
 * Return		:
 * 				+ true - successfully
 * 				+ false - failture
 *****************************************************************************/
bool Uart_Open( Uart_Handle_t *_Uart_Handle, USART_TypeDef *_UartInstance, uint32_t Baudrate );



#endif /* INTERFACE_UART_H_ */



















