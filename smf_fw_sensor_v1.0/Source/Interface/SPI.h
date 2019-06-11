/*
 * SPI.h
 *
 *  Created on: Mar 10, 2019
 *      Author: Thao
 */

#ifndef INTERFACE_SPI_H_
#define INTERFACE_SPI_H_

#include <stdbool.h>
#include <stdint.h>

#include "stm32l4xx_hal.h"



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
bool SPI_Init( SPI_HandleTypeDef *_SPIHandle, SPI_TypeDef *_SPIBase );




/******************************************************************************
 * Function		: bool SPI_State_Ready( SPI_HandleTypeDef *_SPIHandle )
 * Description	: SPI state ready
 * Param		: _SPIHandle - spi handle
 * Return		:
 * 				+ true - spi ready
 * 				+ false - spi busy
 * ***************************************************************************/
bool SPI_State_Ready( SPI_HandleTypeDef *_SPIHandle );



/******************************************************************************
 * Function		: bool SPI_WriteByte( SPI_HandleTypeDef *_SPIHandle, uint8_t txBuff, uint32_t Timeout )
 * Description	: spi write byte
 * Param		: txBuff - byte send
 * Return		: None
 * ***************************************************************************/
bool SPI_WriteByte( SPI_HandleTypeDef *_SPIHandle, uint8_t txBuff, uint32_t Timeout );




/******************************************************************************
 * Function		: uint8_t SPI_ReadByte( SPI_HandleTypeDef *_SPIHandle, uint8_t Addr, uint32_t Timeout )
 * Description	: spi read byte
 * Param		: None
 * Return		: byte read
 * ***************************************************************************/
uint8_t SPI_ReadByte( SPI_HandleTypeDef *_SPIHandle, uint8_t Addr, uint32_t Timeout );





/******************************************************************************
 * Function		: bool SPI_WriteBytes( SPI_HandleTypeDef *_SPIHandle, uint8_t txBuff, uint32_t Timeout )
 * Description	: spi write byte
 * Param		: txBuff - byte send
 * Return		: None
 * ***************************************************************************/
bool SPI_WriteBytes( SPI_HandleTypeDef *_SPIHandle, uint8_t *txBuff, uint16_t txLenght, uint32_t Timeout );




/******************************************************************************
 * Function		: void SPI_ReadBytes( SPI_HandleTypeDef *_SPIHandle, uint8_t *rxBuffer, uint16_t rxLenght, uint32_t Timeout )
 * Description	: spi read byte
 * Param		: None
 * Return		: byte read
 * ***************************************************************************/
void SPI_ReadBytes( SPI_HandleTypeDef *_SPIHandle, uint8_t *rxBuffer, uint16_t rxLenght, uint32_t Timeout );


#endif /* INTERFACE_SPI_H_ */















