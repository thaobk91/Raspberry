/*
 * SS_Light.c
 *
 *  Created on: Mar 22, 2019
 *      Author: thaonm1
 */
#include "SS_Light.h"
#include "../Interface/I2C.h"
#include "../Interface/GPIO.h"

#define LIGHT_BH1750



#ifdef LIGHT_BH1750
#include "Device/BH1750.h"
BH1750_t __BH1750;
#define BH1750_ENABLE_PORT				GPIOB
#define BH1750_ENABLE_PIN				GPIO_PIN_10
#endif



/*******************************************************************************
 * Function		: void SS_Light_Init( void )
 * Description	: light sensor init
 * Param		: None
 * Return		: None
 * ****************************************************************************/
void SS_Light_Init( void )
{
	__BH1750.CS_Port				= BH1750_ENABLE_PORT;
	__BH1750.CS_Pin					= BH1750_ENABLE_PIN;
	__BH1750.CS_Pin_setOutput		= GPIO_setOutput_Pullup;
	__BH1750.CS_Pin_setActiveLow	= GPIO_setLowlevel;

	BH1750_Init( &__BH1750 );
	I2C1_SS_AddDevice( __BH1750.I2C1_SS_Write, __BH1750.I2C1_SS_Read, NULL );
}




/*******************************************************************************
 * Function		: uint16_t SS_Light_Read( void )
 * Description	: read light value (lux)
 * Param		: None
 * Return		: lux value
 * ****************************************************************************/
uint16_t SS_Light_Read( void )
{
	return BH1750_GetLux( &__BH1750 );
}















