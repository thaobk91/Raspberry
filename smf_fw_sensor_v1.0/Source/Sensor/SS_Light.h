/*
 * SS_Light.h
 *
 *  Created on: Mar 22, 2019
 *      Author: thaonm1
 */

#ifndef SENSOR_SS_LIGHT_H_
#define SENSOR_SS_LIGHT_H_

#include <stdint.h>




/*******************************************************************************
 * Function		: void SS_Light_Init( void )
 * Description	: light sensor init
 * Param		: None
 * Return		: None
 * ****************************************************************************/
void SS_Light_Init( void );




/*******************************************************************************
 * Function		: uint16_t SS_Light_Read( void )
 * Description	: read light value (lux)
 * Param		: None
 * Return		: lux value
 * ****************************************************************************/
uint16_t SS_Light_Read( void );

#endif /* SENSOR_SS_LIGHT_H_ */





