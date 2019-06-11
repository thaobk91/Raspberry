/*
 * BH1750.c
 *
 *  Created on: Mar 22, 2019
 *      Author: thaonm1
 */

#include "BH1750.h"


/*Recommend to use H Res Mode*/
#define BH1750_Address_L 					0x23 // Device address when address pin LOW, this is default val
#define BH1750_Address_H 					0x5C // Device address when address pin HIGH


#define BH1750_POWER_DOWN        			0x00
#define BH1750_POWER_ON          			0x01
#define BH1750_DATA_REG_RESET    			0x07

//BH1750 Mode
#define BH1750_CONT_1LX_HRES       			0x10
#define BH1750_CONT_05LX_HRES    			0x11
#define BH1750_CONT_4LX_LRES       			0x13
#define BH1750_ONETIME_1LX_HRES        		0x20
#define BH1750_ONETIME_05LX_HRES     		0x21
#define BH1750_ONETIME_4LX_LRES        		0x23



/******************************************************************************/
static void BH1750_WriteCmd( BH1750_t *_BH1750, uint8_t cmd )
{
	_BH1750->I2C1_SS_Write( BH1750_Address_L, &cmd, 1 );
}



/******************************************************************************/
void BH1750_Begin( BH1750_t *_BH1750 )
{
	BH1750_WriteCmd( _BH1750, BH1750_POWER_ON );
}



/******************************************************************************/
void BH1750_SetMode( BH1750_t *_BH1750, uint8_t Mode )
{
	BH1750_WriteCmd( _BH1750, Mode );
}



/******************************************************************************/
void BH1750_SetAddr( BH1750_t *_BH1750, uint8_t Addr)
{
	BH1750_WriteCmd( _BH1750, Addr );
}



/******************************************************************************/
void BH1750_Init( BH1750_t *_BH1750 )
{
	_BH1750->CS_Pin_setOutput( _BH1750->CS_Port, _BH1750->CS_Pin );
	_BH1750->CS_Pin_setActiveLow( _BH1750->CS_Port, _BH1750->CS_Pin );
}




/******************************************************************************/
uint16_t BH1750_GetLux( BH1750_t *_BH1750 )
{
	uint8_t rxBuff[3] = {0};
	uint16_t ui16Lux_val = 0;

	BH1750_Begin( _BH1750 );
	BH1750_SetMode( _BH1750, BH1750_ONETIME_1LX_HRES );
	//read value
	_BH1750->I2C1_SS_Read( BH1750_Address_L, rxBuff, 2 );

	ui16Lux_val = (rxBuff[0] << 8) | rxBuff[1];
	ui16Lux_val = (uint16_t)(ui16Lux_val / 1.2);

	return ui16Lux_val;
}







