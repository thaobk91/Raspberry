/*
 * THMoisture.c
 *
 *  Created on: Mar 22, 2019
 *      Author: thaonm1
 */
#include <stdlib.h>
#include <string.h>

#include "Sensor/SS_THSoil.h"
#include "../Interface/Uart.h"
#include "../main.h"

extern Uart_Handle_t _Uart3_SOIL;

#define CMD_READ_TH_LENGHT				8
#define DATA_TH_LENGHT					9
uint8_t Cmd_Read_TH[9] = {0xFE, 0x03, 0x00, 0x00, 0x00, 0x02, 0xD0, 0x04};




/******************************************************************************
 * Function		: void SS_THSoil_Read( float *Temp, float *Humi )
 * Description	: read temp and humi soil
 * Parameter	:
 * 				+ Temp: temperature
 * 				+ Humi: humidity
 * Return		: None
 *****************************************************************************/
void SS_THSoil_Read( float *Temp, float *Humi )
{
	#define RX_BUFF_LENGHT			32
	uint8_t rxBuff[RX_BUFF_LENGHT + 1] = {0};
	uint8_t Count = 0;

	do
	{
		HAL_Delay(10);
		memset(rxBuff, 0, RX_BUFF_LENGHT);
		_Uart3_SOIL.Uart_Transmit( &_Uart3_SOIL._UartHandle, Cmd_Read_TH, CMD_READ_TH_LENGHT );
		_Uart3_SOIL.Uart_Receive( &_Uart3_SOIL._UartHandle, rxBuff, RX_BUFF_LENGHT);

		if( (rxBuff[0] == 0xFE) && (rxBuff[1] == 0x03) && (rxBuff[2] == 0x04) )
		{
			if( ((rxBuff[3] | rxBuff[4]) > 0) && ((rxBuff[5] | rxBuff[6]) > 0) )
				break;
		}

		Count++;
		if(Count > 20)
			break;
	}while(1);

//	APP_DEBUG("rxBuff = ");
//	for(uint8_t ui = 0; ui <= 8; ui++)
//		APP_DEBUG("%.2x-", rxBuff[ui]);
//	APP_DEBUG("\r\n");
	*Humi = (float)((rxBuff[3] << 8) | rxBuff[4]) / 10;
	*Temp = (float)((rxBuff[5] << 8) | rxBuff[6]) / 10;

//	APP_DEBUG("temp = %f, humi = %f\r\n", *Temp, *Humi);
}



















