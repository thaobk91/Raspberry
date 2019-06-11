/*
 * HW_Lora_Driver.c
 *
 *  Created on: Mar 13, 2019
 *      Author: Thao
 */
#include "../../Interface/SPI.h"
#include "../../Interface/GPIO.h"


SPI_HandleTypeDef _SPI1_Lora;



/******************************************************************************
 * Function		: void HW_Lora_Driver_Delay_ms( uint32_t ms )
 * Description	: delay ms
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void HW_Lora_Driver_Delay_ms( uint32_t ms )
{
	HAL_Delay(ms);
}



/******************************************************************************
 * Function		: void HW_Lora_Driver_Pin_Output( void *Port, uint16 Pin )
 * Description	: gpio set pin output
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void HW_Lora_Driver_setPin_Output( void *Port, uint16_t Pin )
{
	GPIO_setOutput_Pullup( (GPIO_TypeDef *)Port, Pin );
}



/******************************************************************************
 * Function		: void HW_Lora_Driver_setPin_Input( void *Port, uint16 Pin )
 * Description	: gpio set pin input
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void HW_Lora_Driver_setPin_Input( void *Port, uint16_t Pin )
{
	GPIO_setInput( (GPIO_TypeDef *)Port, Pin );
}



/******************************************************************************
 * Function		: int HW_Lora_Driver_ReadPin( void *Port, uint16 Pin )
 * Description	: gpio read pin
 * Param		: None
 * Return		: None
 * ***************************************************************************/
int HW_Lora_Driver_ReadPin( void *Port, uint16_t Pin )
{
	return GPIO_getlevel( (GPIO_TypeDef *)Port, Pin );
}



/******************************************************************************
 * Function		: void HW_Lora_Driver_setPin_High( void *Port, uint16_t Pin )
 * Description	: gpio set pin high level
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void HW_Lora_Driver_setPin_High( void *Port, uint16_t Pin )
{
	GPIO_setHighlevel( (GPIO_TypeDef *)Port, Pin );
}



/******************************************************************************
 * Function		: void HW_Lora_Driver_setPin_Low( void *Port, uint16_t Pin )
 * Description	: gpio set pin low level
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void HW_Lora_Driver_setPin_Low( void *Port, uint16_t Pin )
{
	GPIO_setLowlevel( (GPIO_TypeDef *)Port, Pin );
}




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
bool HW_Lora_Driver_SPI_Init( void )
{
	return SPI_Init( &_SPI1_Lora, SPI1 );
}



/******************************************************************************
 * Function		: bool HW_Lora_Driver_SPI_Ready( void )
 * Description	: SPI state ready
 * Param		: None
 * Return		:
 * 				+ true - spi ready
 * 				+ false - spi busy
 * ***************************************************************************/
bool HW_Lora_Driver_SPI_Ready( void )
{
	return SPI_State_Ready( &_SPI1_Lora );
}




/******************************************************************************
 * Function		: bool HW_Lora_Driver_SPI_WriteByte( uint8_t txBuff, uint32_t Timeout )
 * Description	: spi write byte
 * Param		: txBuff - byte send
 * Return		: None
 * ***************************************************************************/
bool HW_Lora_Driver_SPI_WriteByte( uint8_t txBuff, uint32_t Timeout )
{
	return SPI_WriteByte( &_SPI1_Lora, txBuff, Timeout );
}



/******************************************************************************
 * Function		: uint8_t HW_Lora_Driver_SPI_ReadByte( uint32_t Timeout )
 * Description	: spi read byte
 * Param		: None
 * Return		: byte read
 * ***************************************************************************/
uint8_t HW_Lora_Driver_SPI_ReadByte( uint32_t Timeout )
{
	return SPI_ReadByte( &_SPI1_Lora, 0x00, Timeout );
}



















