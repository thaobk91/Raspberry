/*
 * I2C.c
 *
 *  Created on: Mar 16, 2019
 *      Author: thaonm1
 */
#include "stm32l4xx_hal.h"
#include "I2C.h"


I2C_HandleTypeDef __I2C1_SS_Handle;


void I2C1_SS_Write( uint16_t DevAddress, uint8_t *txBuffer, uint16_t txLenght );
void I2C1_SS_Read( uint16_t DevAddress, uint8_t *rxBuffer, uint16_t rxLenght );
bool I2C1_SS_Ready( uint16_t DevAddress );




/*******************************************************************************
 * Function		: void I2C1_SS_Init( void )
 * Description	: i2c init
 * Param		: NOne
 * Return		: None
 * ****************************************************************************/
void I2C1_SS_Init( void )
{
	__I2C1_SS_Handle.Instance 				= I2C1;
	__I2C1_SS_Handle.Init.Timing 			= 0x00000E14;
	__I2C1_SS_Handle.Init.OwnAddress1 		= 0;
	__I2C1_SS_Handle.Init.AddressingMode 	= I2C_ADDRESSINGMODE_7BIT;
	__I2C1_SS_Handle.Init.DualAddressMode 	= I2C_DUALADDRESS_DISABLE;
	__I2C1_SS_Handle.Init.OwnAddress2 		= 0;
	__I2C1_SS_Handle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	__I2C1_SS_Handle.Init.GeneralCallMode 	= I2C_GENERALCALL_DISABLE;
	__I2C1_SS_Handle.Init.NoStretchMode 	= I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init( &__I2C1_SS_Handle ) != HAL_OK)
	{

	}

	//Configure Analogue filter
	if (HAL_I2CEx_ConfigAnalogFilter( &__I2C1_SS_Handle, I2C_ANALOGFILTER_ENABLE ) != HAL_OK);

	//Configure Digital filter
	if (HAL_I2CEx_ConfigDigitalFilter( &__I2C1_SS_Handle, 0 ) != HAL_OK);
}



/*******************************************************************************
 * Function		: void I2C1_SS_AddDevice
 * Description	: i2c init
 * Param		:
 * 				+ write - write data call back
 * 				+ read - read data callback
 * 				+ ready - device ready
 * Return		: None
 * ****************************************************************************/
void I2C1_SS_AddDevice( void (*write)( uint16_t /*slave addr*/, uint8_t */*data write*/, uint16_t /*data lenght*/ ),
					void (*read)( uint16_t /*slave addr*/, uint8_t */*data read*/, uint16_t /*data lenght*/ ),
					bool (*ready) ( uint16_t /*slave addr*/ )
					)
{
	if(write != NULL)
		write = I2C1_SS_Write;
	if(read != NULL)
		read = I2C1_SS_Read;
	if(ready != NULL)
		ready = I2C1_SS_Ready;
}



/*******************************************************************************
 * Function		: void I2C1_SS_Write( uint16_t DevAddress, uint8_t *txBuffer, uint16_t txLenght )
 * Description	: i2c write data
 * Param		:
 * 				+ DevAddress - adress of slave
 * 				+ txBuffer - write buffer
 * 				+ txLenght - buffer lenght
 * Return		: None
 * ****************************************************************************/
void I2C1_SS_Write( uint16_t DevAddress, uint8_t *txBuffer, uint16_t txLenght )
{
	HAL_I2C_Master_Transmit( &__I2C1_SS_Handle, DevAddress, txBuffer, txLenght, 0xffff );
}



/*******************************************************************************
 * Function		: void I2C1_SS_Read( uint16_t DevAddress, uint8_t *rxBuffer, uint16_t rxLenght )
 * Description	: i2c read data
 * Param		:
 * 				+ DevAddress - adress of slave
 * 				+ rxBuffer - read buffer
 * 				+ rxLenght - buffer lenght
 * Return		: None
 * ****************************************************************************/
void I2C1_SS_Read( uint16_t DevAddress, uint8_t *rxBuffer, uint16_t rxLenght )
{
	HAL_I2C_Master_Receive( &__I2C1_SS_Handle, DevAddress, rxBuffer, rxLenght, 0xffff );
}



/*******************************************************************************
 * Function		: void I2C1_SS_Ready( uint16_t DevAddress )
 * Description	: check device ready
 * Param		: DevAddress - device address
 * Return		:
 * 				+ true -  ready
 * 				+ false - busy
 * ****************************************************************************/
bool I2C1_SS_Ready( uint16_t DevAddress )
{
	return HAL_I2C_IsDeviceReady( &__I2C1_SS_Handle, DevAddress, 1, 0xffff );
}














