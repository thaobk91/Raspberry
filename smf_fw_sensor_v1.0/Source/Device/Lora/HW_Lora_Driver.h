/*
 * HW_Lora_Driver.h
 *
 *  Created on: Mar 13, 2019
 *      Author: Thao
 */

#ifndef DEVICE_HWDRIVER_HW_LORA_DRIVER_H_
#define DEVICE_HWDRIVER_HW_LORA_DRIVER_H_

#include <stdbool.h>
#include <stdint.h>



/******************************************************************************
 * Function		: void HW_Lora_Driver_Delay_ms( uint32_t ms )
 * Description	: delay ms
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void HW_Lora_Driver_Delay_ms( uint32_t ms );



/******************************************************************************
 * Function		: void HW_Lora_Driver_Pin_Output( void *Port, uint16 Pin )
 * Description	: gpio set pin output
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void HW_Lora_Driver_setPin_Output( void *Port, uint16_t Pin );



/******************************************************************************
 * Function		: void HW_Lora_Driver_setPin_Input( void *Port, uint16 Pin )
 * Description	: gpio set pin input
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void HW_Lora_Driver_setPin_Input( void *Port, uint16_t Pin );



/******************************************************************************
 * Function		: int HW_Lora_Driver_ReadPin( void *Port, uint16 Pin )
 * Description	: gpio read pin
 * Param		: None
 * Return		: None
 * ***************************************************************************/
int HW_Lora_Driver_ReadPin( void *Port, uint16_t Pin );



/******************************************************************************
 * Function		: void HW_Lora_Driver_setPin_High( void *Port, uint16_t Pin )
 * Description	: gpio set pin high level
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void HW_Lora_Driver_setPin_High( void *Port, uint16_t Pin );



/******************************************************************************
 * Function		: void HW_Lora_Driver_setPin_Low( void *Port, uint16_t Pin )
 * Description	: gpio set pin low level
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void HW_Lora_Driver_setPin_Low( void *Port, uint16_t Pin );




//SPI

/******************************************************************************
 * Function		: bool HW_Lora_Driver_SPI_Init( void )
 * Description	: SPI Initialization Function
 * Param		:
 * 				+ _SPIHandle - SPI handle
 * 				+ _SPIBase - spi base
 * Return		:
 * 				+ true - successfully
 * 				+ false - failture
 * ***************************************************************************/
bool HW_Lora_Driver_SPI_Init( void );



/******************************************************************************
 * Function		: bool HW_Lora_Driver_SPI_Ready( void )
 * Description	: SPI state ready
 * Param		: None
 * Return		:
 * 				+ true - spi ready
 * 				+ false - spi busy
 * ***************************************************************************/
bool HW_Lora_Driver_SPI_Ready( void );




/******************************************************************************
 * Function		: bool HW_Lora_Driver_SPI_WriteByte( uint8_t txBuff, uint32_t Timeout )
 * Description	: spi write byte
 * Param		: txBuff - byte send
 * Return		: None
 * ***************************************************************************/
bool HW_Lora_Driver_SPI_WriteByte( uint8_t txBuff, uint32_t Timeout );



/******************************************************************************
 * Function		: uint8_t HW_Lora_Driver_SPI_ReadByte( uint32_t Timeout )
 * Description	: spi read byte
 * Param		: None
 * Return		: byte read
 * ***************************************************************************/
uint8_t HW_Lora_Driver_SPI_ReadByte( uint32_t Timeout );


#endif /* DEVICE_HWDRIVER_HW_LORA_DRIVER_H_ */







