/*
 * Flash.h
 *
 *  Created on: Mar 13, 2019
 *      Author: Thao
 */

#ifndef DEVICE_FLASH_FLASH_H_
#define DEVICE_FLASH_FLASH_H_

#include <stdint.h>
#include <stdbool.h>



/******************************************************************************
 * Function		: bool Flash_Init( void )
 * Description	: external flash init
 * Param		: None
 * Return		:
 * 				+ true - successfully
 * 				+ false - failture
*******************************************************************************/
bool Flash_Init( void );



/******************************************************************************
 * Function		: void Flash_Read( uint32_t addr, uint8_t *uBuffer, uint16_t Lenght )
 * Description	: flash read data
 * Param		:
 * 				+ addr - address start to read
 * 				+ uBuffer - read buffer
 * 				+ Lenght - read lenght
 * Return		:
 * 				+ true - successfully
 * 				+ false - failture
*******************************************************************************/
void Flash_Read( uint32_t addr, uint8_t *uBuffer, uint16_t Lenght );




/******************************************************************************
 * Function		: void Flash_Write_to_Page( uint32_t addr, uint8_t *txBuffer, uint16_t Lenght )
 * Description	: flash write data to sector
 * Param		:
 * 				+ addr - address start to write
 * 				+ uBuffer - write buffer
 * 				+ Lenght - write lenght
 * Return		:
 * 				+ true - successfully
 * 				+ false - failture
*******************************************************************************/
void Flash_Write_to_Page( uint32_t addr, uint8_t *txBuffer, uint16_t Lenght );




/******************************************************************************
 * Function		: void Flash_Write_to_Block( uint32_t addr, uint8_t *txBuffer, uint16_t Lenght )
 * Description	: flash write data to block
 * Param		:
 * 				+ addr - address start to write
 * 				+ uBuffer - write buffer
 * 				+ Lenght - write lenght
 * Return		:
 * 				+ true - successfully
 * 				+ false - failture
*******************************************************************************/
void Flash_Write_to_Block( uint32_t addr, uint8_t *txBuffer, uint16_t Lenght );


#endif /* DEVICE_FLASH_FLASH_H_ */












