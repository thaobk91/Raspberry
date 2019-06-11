/*
 * SHT1x.c
 *
 *  Created on: Mar 22, 2019
 *      Author: thaonm1
 */
#include "SHT1x.h"


/* Define of Sensor */
#define macroTEMP_READ_CMD  			0x03
#define macroHUMI_READ_CMD    			0x05

#define D1      						-39.7
#define D2      						0.01

#define C1      						-4.0
#define C2       						0.0405
#define C3       						-0.0000028
#define T1       						0.01
#define T2       						0.00008



static uint16_t SHT1x_ReadRaw( SHT1x_t *_SHT1x, uint8_t cmd )
{
	uint8_t rxBuff[3] = {0};

	// send start
	_SHT1x->I2C1_SS_Read( cmd, rxBuff, 2 );

	return ((rxBuff[0] << 8) | rxBuff[1]);
}



float fSHT1x_ReadTemp( SHT1x_t *_SHT1x )
{
	uint16_t raw = SHT1x_ReadRaw( _SHT1x, macroTEMP_READ_CMD );
	float _temp = D2*raw + D1;
	return _temp;
}



float fSHT1x_ReadHumi( SHT1x_t *_SHT1x )
{
	float _linear_humi, temp, _correct_humi;
	uint16_t raw;
	raw = SHT1x_ReadRaw( _SHT1x, macroHUMI_READ_CMD );
	_linear_humi = C1 + C2 * raw + C3 * raw * raw;
	temp = fSHT1x_ReadTemp( _SHT1x );
	_correct_humi = (temp - 25.0 ) * (T1 + T2 * raw) + _linear_humi;
	return _correct_humi;
}



void SHT1x_Read( SHT1x_t *_SHT1x, float *_fTemp, float *_fHumi )
{
	int Temp_raw = SHT1x_ReadRaw( _SHT1x, macroTEMP_READ_CMD );
	int Humi_raw = SHT1x_ReadRaw( _SHT1x, macroHUMI_READ_CMD );

	*_fTemp = D2 * Temp_raw + D1;
	*_fHumi = (*_fTemp - 25.0) * (T1 + T2 * Humi_raw) + C1 + C2 * Humi_raw + C3 * Humi_raw * Humi_raw;
}

















