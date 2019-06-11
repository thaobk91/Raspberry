/*
 * HW_Flash_Driver.h
 *
 *  Created on: Mar 13, 2019
 *      Author: Thao
 */

#ifndef DEVICE_HWDRIVER_HW_FLASH_DRIVER_H_
#define DEVICE_HWDRIVER_HW_FLASH_DRIVER_H_

#include <stdint.h>



/******************************************************************************
 * Function		: void HW_Flash_Driver_setOutput_Dir( void *Port, uint16_t Pin )
 * Description	: set gpio output pullup
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_setOutput_Dir( void *Port, uint16_t Pin );



/******************************************************************************
 * Function		: void HW_Flash_Driver_setOutput_HighLevel( void *Port, uint16_t Pin )
 * Description	: set output high level
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_setOutput_HighLevel( void *Port, uint16_t Pin );



/******************************************************************************
 * Function		: void HW_Flash_Driver_setOutput_LowLevel( void *Port, uint16_t Pin )
 * Description	: set gpio low level
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_setOutput_LowLevel( void *Port, uint16_t Pin );



/******************************************************************************
 * Function		: void HW_Flash_Driver_SPI_Init( void )
 * Description	: spi init
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_SPI_Init( void );



/******************************************************************************
 * Function		: bool HW_Flash_Driver_SPI_Ready( void )
 * Description	: spi ready
 * Param		: None
 * Return		: None
 * ***************************************************************************/
bool HW_Flash_Driver_SPI_Ready( void );



/******************************************************************************
 * Function		: void HW_Flash_Driver_SPI_Write_Bytes( uint8_t *txBuffer, uint16_t txLenght )
 * Description	: spi write bytes
 * Param		:
 * 				+ txBuffer - tx buffer
 * 				+ txLenght - tx lenght
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_SPI_Write_Bytes( uint8_t *txBuffer, uint16_t txLenght );



/******************************************************************************
 * Function		: void HW_Flash_Driver_SPI_Read_Bytes( uint8_t Addr, uint8_t *rxBuffer, uint16_t rxLenght )
 * Description	: spi read bytes
 * Param		:
 * 				+ Addr - address to read
 * 				+ rxBuffer - rx buffer
 * 				+ rxLenght - rx lenght
 * Return		: None
 * ***************************************************************************/
void HW_Flash_Driver_SPI_Read_Bytes( uint8_t *rxBuffer, uint16_t rxLenght );

#endif /* DEVICE_HWDRIVER_HW_FLASH_DRIVER_H_ */










