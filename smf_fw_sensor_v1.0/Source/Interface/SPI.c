/*
 * SPI.c
 *
 *  Created on: Mar 10, 2019
 *      Author: Thao
 */
#include <stdlib.h>
#include "stm32l4xx_hal.h"

#include "SPI.h"
#include "../main.h"



/******************************************************************************
 * Function		: bool SPI_Init( SPI_HandleTypeDef *_SPIHandle, SPI_TypeDef *_SPIBase )
 * Description	: SPI Initialization Function
 * Param		:
 * 				+ _SPIHandle - SPI handle
 * 				+ _SPIBase - spi base
 * Return		:
 * 				+ true - successfully
 * 				+ false - failture
 * ***************************************************************************/
bool SPI_Init( SPI_HandleTypeDef *_SPIHandle, SPI_TypeDef *_SPIBase )
{
	/* SPI1 parameter configuration*/
	_SPIHandle->Instance 				= _SPIBase;
	_SPIHandle->Init.Mode 				= SPI_MODE_MASTER;
	_SPIHandle->Init.Direction 			= SPI_DIRECTION_2LINES;
	_SPIHandle->Init.DataSize 			= SPI_DATASIZE_8BIT;
	_SPIHandle->Init.CLKPolarity 		= SPI_POLARITY_LOW; //high
	_SPIHandle->Init.CLKPhase 			= SPI_PHASE_1EDGE;
	_SPIHandle->Init.NSS 				= SPI_NSS_SOFT;
	_SPIHandle->Init.BaudRatePrescaler 	= SPI_BAUDRATEPRESCALER_4;
	_SPIHandle->Init.FirstBit 			= SPI_FIRSTBIT_MSB;
	_SPIHandle->Init.TIMode 			= SPI_TIMODE_DISABLE;
	_SPIHandle->Init.CRCCalculation 	= SPI_CRCCALCULATION_DISABLE;
	_SPIHandle->Init.CRCPolynomial 		= 10;
//	_SPIHandle->Init.CRCLength 			= SPI_CRC_LENGTH_DATASIZE;
//	_SPIHandle->Init.NSSPMode 			= SPI_NSS_PULSE_ENABLE;
	if (HAL_SPI_Init( _SPIHandle ) != HAL_OK)
	{
		APP_DEBUG("--- SPI: init spi failture: line %d\r\n", __LINE__);
		return false;
	}
	__HAL_SPI_ENABLE(_SPIHandle);
	return true;
}




/******************************************************************************
 * Function		: bool SPI_State_Ready( SPI_HandleTypeDef *_SPIHandle )
 * Description	: SPI state ready
 * Param		: _SPIHandle - spi handle
 * Return		:
 * 				+ true - spi ready
 * 				+ false - spi busy
 * ***************************************************************************/
bool SPI_State_Ready( SPI_HandleTypeDef *_SPIHandle )
{
	if(HAL_SPI_GetState( _SPIHandle ) == HAL_SPI_STATE_READY)
		return true;
	else
		return false;
}



/******************************************************************************
 * Function		: bool SPI_WriteByte( SPI_HandleTypeDef *_SPIHandle, uint8_t txBuff, uint32_t Timeout )
 * Description	: spi write byte
 * Param		: txBuff - byte send
 * Return		: None
 * ***************************************************************************/
bool SPI_WriteByte( SPI_HandleTypeDef *_SPIHandle, uint8_t txBuff, uint32_t Timeout )
{
	if( HAL_SPI_Transmit( _SPIHandle, &txBuff, 1, Timeout) == HAL_OK )
		return true;
	APP_DEBUG("--- SPI: tx error, line: %d\r\n", __LINE__);
	return false;
}




/******************************************************************************
 * Function		: uint8_t SPI_ReadByte( SPI_HandleTypeDef *_SPIHandle, uint8_t Addr, uint32_t Timeout )
 * Description	: spi read byte
 * Param		: None
 * Return		: byte read
 * ***************************************************************************/
uint8_t SPI_ReadByte( SPI_HandleTypeDef *_SPIHandle, uint8_t Addr, uint32_t Timeout )
{
	uint8_t txByte = Addr;
	uint8_t rxByte = 0;

	if( HAL_SPI_TransmitReceive( _SPIHandle, &txByte, &rxByte, 1, Timeout) != HAL_OK )
		APP_DEBUG("--- SPI: rx error, line: %d\r\n", __LINE__);

	return rxByte;
}




/******************************************************************************
 * Function		: bool SPI_WriteBytes( SPI_HandleTypeDef *_SPIHandle, uint8_t txBuff, uint32_t Timeout )
 * Description	: spi write byte
 * Param		: txBuff - byte send
 * Return		: None
 * ***************************************************************************/
bool SPI_WriteBytes( SPI_HandleTypeDef *_SPIHandle, uint8_t *txBuff, uint16_t txLenght, uint32_t Timeout )
{
	if( HAL_SPI_Transmit( _SPIHandle, txBuff, txLenght, Timeout) == HAL_OK )
		return true;
	APP_DEBUG("--- SPI: tx error, line: %d\r\n", __LINE__);
	return false;
}




/******************************************************************************
 * Function		: void SPI_ReadBytes( SPI_HandleTypeDef *_SPIHandle, uint8_t *rxBuffer, uint16_t rxLenght, uint32_t Timeout )
 * Description	: spi read byte
 * Param		: None
 * Return		: byte read
 * ***************************************************************************/
void SPI_ReadBytes( SPI_HandleTypeDef *_SPIHandle, uint8_t *rxBuffer, uint16_t rxLenght, uint32_t Timeout )
{
	if( HAL_SPI_Receive( _SPIHandle, rxBuffer, rxLenght, Timeout) != HAL_OK )
		APP_DEBUG("--- SPI: rx error, line: %d\r\n", __LINE__);
}





















