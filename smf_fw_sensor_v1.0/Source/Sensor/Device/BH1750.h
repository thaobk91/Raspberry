/*
 * BH1750.h
 *
 *  Created on: Mar 22, 2019
 *      Author: thaonm1
 */

#ifndef SENSOR_DEVICE_BH1750_H_
#define SENSOR_DEVICE_BH1750_H_

#include <stdint.h>


typedef struct
{
	void *CS_Port;
	uint16_t CS_Pin;

	void (*CS_Pin_setOutput)( void *Port, uint16_t Pin );
	void (*CS_Pin_setActiveLow)( void *Port, uint16_t Pin );

	void (*Delay_ms)( uint32_t );
	void (*I2C1_SS_Write)( uint16_t DevAddress, uint8_t *txBuffer, uint16_t txLenght );
	void (*I2C1_SS_Read)( uint16_t DevAddress, uint8_t *rxBuffer, uint16_t rxLenght );
	void (*I2C1_SS_Ready)( uint16_t DevAddress );
}BH1750_t;


void BH1750_Init( BH1750_t *_BH1750 );



/******************************************************************************/
uint16_t BH1750_GetLux( BH1750_t *_BH1750 );



#endif /* SENSOR_DEVICE_BH1750_H_ */





