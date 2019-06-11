/*
 * Uart.c
 *
 *  Created on: Feb 27, 2019
 *      Author: Thao
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stm32l4xx_hal.h"
#include "Uart.h"
#include "../main.h"



static bool Uart_Write( UART_HandleTypeDef *_UartHandle, uint8_t *TXBuffer, uint16_t TXLenght );
static uint16_t Uart_Read( UART_HandleTypeDef *_UartHandle, uint8_t *RXBuffer, uint16_t RXLenght );





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
bool Uart_Open( Uart_Handle_t *_Uart_Handle, USART_TypeDef *_UartInstance, uint32_t Baudrate )
{
	_Uart_Handle->_UartHandle.Instance 						= _UartInstance;
	_Uart_Handle->_UartHandle.Init.BaudRate 				= Baudrate;
	_Uart_Handle->_UartHandle.Init.WordLength 				= UART_WORDLENGTH_8B;
	_Uart_Handle->_UartHandle.Init.StopBits 				= UART_STOPBITS_1;
	_Uart_Handle->_UartHandle.Init.Parity 					= UART_PARITY_NONE;
	_Uart_Handle->_UartHandle.Init.Mode 					= UART_MODE_TX_RX;
	_Uart_Handle->_UartHandle.Init.HwFlowCtl 				= UART_HWCONTROL_NONE;
	_Uart_Handle->_UartHandle.Init.OverSampling 			= UART_OVERSAMPLING_16;
	_Uart_Handle->_UartHandle.Init.OneBitSampling 			= UART_ONE_BIT_SAMPLE_DISABLE;
//	_Uart_Handle->_UartHandle.AdvancedInit.AdvFeatureInit 	= UART_ADVFEATURE_NO_INIT;

	if (HAL_UART_Init( &_Uart_Handle->_UartHandle ) != HAL_OK)
		return false;

	_Uart_Handle->Uart_Transmit = Uart_Write;
	_Uart_Handle->Uart_Receive	= Uart_Read;
	return true;
}




/******************************************************************************
 * Function		: bool Uart_Write( UART_HandleTypeDef *_UartHandle, uint8_t *TXBuffer, uint16_t TXLenght )
 * Description	: uart write data
 * Parameter	:
 * 				+ _UartHandle: uart handle
 * 				+ TXBuffer: data to write
 * 				+ TXLenght - lenght of buffer
 * Return		:
 * 				+ true: successfully
 * 				+ false: failture
 *****************************************************************************/
static bool Uart_Write( UART_HandleTypeDef *_UartHandle, uint8_t *TXBuffer, uint16_t TXLenght )
{
//	uint16_t len = 0;
//
//	APP_DEBUG("sent = ");
//	while( len < TXLenght )
//	{
//		if( HAL_UART_Transmit( _UartHandle, &TXBuffer[len], 1, 0xffff ) != HAL_OK )
//			return false;
//		APP_DEBUG("%.2x", TXBuffer[len]);
//		len++;
//	}
//	APP_DEBUG("\r\n");

	if( HAL_UART_Transmit( _UartHandle, TXBuffer, TXLenght, 0xffff ) == HAL_OK )
		return true;
	return false;
}




/******************************************************************************
 * Function		: uint16_t Uart_Read( UART_HandleTypeDef *_UartHandle, uint8_t *RXBuffer )
 * Description	: uart receive data
 * Parameter	:
 * 				+ _UartHandle: uart handle
 * 				+ RXBuffer - received buffer
 * Return		: return data lenght
 *****************************************************************************/
static uint16_t Uart_Read( UART_HandleTypeDef *_UartHandle, uint8_t *RXBuffer, uint16_t RXLenght )
{
	uint16_t RX_Lenght = 0;
	uint8_t c;

	while(RX_Lenght < RXLenght)
	{
		if( HAL_UART_Receive( _UartHandle, &c, 1, 0xff) != HAL_OK )
			return RX_Lenght;
		RXBuffer[RX_Lenght++] = c;
	}
	return RX_Lenght;
}




























