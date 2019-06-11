/*
 * I2C.h
 *
 *  Created on: Mar 16, 2019
 *      Author: thaonm1
 */

#ifndef INTERFACE_I2C_H_
#define INTERFACE_I2C_H_

#include <stdbool.h>
#include <stdint.h>


/*******************************************************************************
 * Function		: void I2C1_SS_Init( void )
 * Description	: i2c init
 * Param		: NOne
 * Return		: None
 * ****************************************************************************/
void I2C1_SS_Init( void );



/*******************************************************************************
 * Function		: void I2C1_SS_AddDevice
 * Description	: i2c init
 * Param		:
 * 				+ write - write data call back
 * 				+ read - read data callback
 * 				+ ready - device ready
 * Return		: None
 * ****************************************************************************/
void I2C1_SS_AddDevice( void (*write)( uint16_t /*slave addr*/, uint8_t */*data write*/, uint16_t /*data lenght*/ ), \
					void (*read)( uint16_t /*slave addr*/, uint8_t */*data read*/, uint16_t /*data lenght*/ ), \
					bool (*ready) ( uint16_t /*slave addr*/ ) \
					);

#endif /* INTERFACE_I2C_H_ */





