/*
 * SHT1x.h
 *
 *  Created on: Mar 22, 2019
 *      Author: thaonm1
 */

#ifndef SENSOR_DEVICE_SHT1X_H_
#define SENSOR_DEVICE_SHT1X_H_

#include <stdint.h>



typedef struct
{
	void (*Delay_ms)( uint32_t );
	void (*I2C1_SS_Write)( uint16_t DevAddress, uint8_t *txBuffer, uint16_t txLenght );
	void (*I2C1_SS_Read)( uint16_t DevAddress, uint8_t *rxBuffer, uint16_t rxLenght );
	void (*I2C1_SS_Ready)( uint16_t DevAddress );

	float (*SHT1x_ReadTemp)( void );
	float (*SHT1xReadHumi)( void );
}SHT1x_t;


void SHT1x_Init( SHT1x_t *_SHT1x );


#endif /* SENSOR_DEVICE_SHT1X_H_ */
