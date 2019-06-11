/*
 * Flash.c
 *
 *  Created on: Mar 13, 2019
 *      Author: Thao
 */
#include "../../main.h"

#include "HW_Flash_Driver.h"
#include "W25Q64JVS.h"


#define CHIP_SELECT_PORT						GPIOB
#define CHIP_SELECT_PIN							GPIO_PIN_12


W25Q64JVS_Data_t __W25Q64JVS_Data;




/******************************************************************************
 * Function		: bool Flash_Init( void )
 * Description	: external flash init
 * Param		: None
 * Return		:
 * 				+ true - successfully
 * 				+ false - failture
*******************************************************************************/
bool Flash_Init( void )
{
	__W25Q64JVS_Data.CS_Port					= CHIP_SELECT_PORT;
	__W25Q64JVS_Data.CS_Pin						= CHIP_SELECT_PIN;

	__W25Q64JVS_Data.debug						= APP_DEBUG;
	__W25Q64JVS_Data.Delay_ms					= HAL_Delay;

	__W25Q64JVS_Data.GPIO_setOutput_Dir			= HW_Flash_Driver_setOutput_Dir;
	__W25Q64JVS_Data.GPIO_setOutput_HighLevel	= HW_Flash_Driver_setOutput_HighLevel;
	__W25Q64JVS_Data.GPIO_setOutput_LowLevel	= HW_Flash_Driver_setOutput_LowLevel;

	__W25Q64JVS_Data.SPI_Init					= HW_Flash_Driver_SPI_Init;
	__W25Q64JVS_Data.SPI_Ready					= HW_Flash_Driver_SPI_Ready;
	__W25Q64JVS_Data.SPI_Write_Bytes			= HW_Flash_Driver_SPI_Write_Bytes;
	__W25Q64JVS_Data.SPI_Read_Bytes				= HW_Flash_Driver_SPI_Read_Bytes;

	//HAL_Delay(1000);
	W25Q64JVS_Init( &__W25Q64JVS_Data );

	while( W25Q64JVS_CheckConnection( &__W25Q64JVS_Data ) != true )
	{
		APP_DEBUG("--- Flash: flash init nok\r\n");
		osDelay(1000);
	}
	return true;
}




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
void Flash_Read( uint32_t addr, uint8_t *uBuffer, uint16_t Lenght )
{
	W25Q64JVS_Read( &__W25Q64JVS_Data, addr, uBuffer, Lenght );
}




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
void Flash_Write_to_Page( uint32_t addr, uint8_t *txBuffer, uint16_t Lenght )
{
	W25Q64JVS_EraseSector( &__W25Q64JVS_Data, addr );
	W25Q64JVS_Write( &__W25Q64JVS_Data, addr, txBuffer, Lenght );
}



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
void Flash_Write_to_Block( uint32_t addr, uint8_t *txBuffer, uint16_t Lenght )
{
	W25Q64JVS_EraseBlock( &__W25Q64JVS_Data, addr );
	W25Q64JVS_Write( &__W25Q64JVS_Data, addr, txBuffer, Lenght );
}
























