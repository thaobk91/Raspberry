/*
 * HW_Flash_Driver.c
 *
 *  Created on: Mar 13, 2019
 *      Author: Thao
 */
#include "../../Interface/SPI.h"
#include "../../Interface/GPIO.h"

SPI_HandleTypeDef __SPI2_Flash;




/******************************************************************************
 * Function		: void HW_Flash_Driver_setOutput_Dir( void *Port, uint16_t Pin )
 * Description	: set gpio output pullup
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_setOutput_Dir( void *Port, uint16_t Pin )
{
	GPIO_setOutput_NoPull( Port, Pin );
}



/******************************************************************************
 * Function		: void HW_Flash_Driver_setOutput_HighLevel( void *Port, uint16_t Pin )
 * Description	: set output high level
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_setOutput_HighLevel( void *Port, uint16_t Pin )
{
	GPIO_setHighlevel( Port, Pin );
}



/******************************************************************************
 * Function		: void HW_Flash_Driver_setOutput_LowLevel( void *Port, uint16_t Pin )
 * Description	: set gpio low level
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_setOutput_LowLevel( void *Port, uint16_t Pin )
{
	GPIO_setLowlevel( Port, Pin );
}



/******************************************************************************
 * Function		: void HW_Flash_Driver_SPI_Init( void )
 * Description	: spi init
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_SPI_Init( void )
{
	SPI_Init( &__SPI2_Flash, SPI2 );
}



/******************************************************************************
 * Function		: bool HW_Flash_Driver_SPI_Ready( void )
 * Description	: spi ready
 * Param		: None
 * Return		: None
 * ***************************************************************************/
bool HW_Flash_Driver_SPI_Ready( void )
{
	return SPI_State_Ready( &__SPI2_Flash );
}



/******************************************************************************
 * Function		: void HW_Flash_Driver_SPI_Write_Bytes( uint8_t *txBuffer, uint16_t txLenght )
 * Description	: spi write bytes
 * Param		:
 * 				+ txBuffer - tx buffer
 * 				+ txLenght - tx lenght
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_SPI_Write_Bytes( uint8_t *txBuffer, uint16_t txLenght )
{
	SPI_WriteBytes( &__SPI2_Flash, txBuffer, txLenght, 0xffff );
}



/******************************************************************************
 * Function		: void HW_Flash_Driver_SPI_Read_Bytes( uint8_t *rxBuffer, uint16_t rxLenght )
 * Description	: spi read bytes
 * Param		:
 * 				+ rxBuffer - rx buffer
 * 				+ rxLenght - rx lenght
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_SPI_Read_Bytes( uint8_t *rxBuffer, uint16_t rxLenght )
{
	SPI_ReadBytes( &__SPI2_Flash, rxBuffer, rxLenght, 0xffff );
}



















