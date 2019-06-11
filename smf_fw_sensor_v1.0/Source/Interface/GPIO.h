/*
 * GPIO.h
 *
 *  Created on: Mar 11, 2019
 *      Author: Thao
 */

#ifndef INTERFACE_GPIO_H_
#define INTERFACE_GPIO_H_

#include <stdbool.h>
#include "stm32l4xx_hal.h"




/******************************************************************************
 * Function		: void GPIO_Init( void )
 * Description	: init gpio
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void GPIO_Init( void );




/******************************************************************************
 * Function		: void GPIO_setOutput_Pullup( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio output pullup
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void GPIO_setOutput_Pullup( GPIO_TypeDef *Port, uint16_t Pin );




/******************************************************************************
 * Function		: void GPIO_setOutput_Pulldown( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio output pulldown
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void GPIO_setOutput_Pulldown( GPIO_TypeDef *Port, uint16_t Pin );




/******************************************************************************
 * Function		: void GPIO_setOutput_NoPull( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio output no pull
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * 				+ Pullup - true: pullup, false: pulldown
 * Return		: None
 * ***************************************************************************/
void GPIO_setOutput_NoPull( GPIO_TypeDef *Port, uint16_t Pin );




/******************************************************************************
 * Function		: void GPIO_setInput( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio input
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void GPIO_setInput( GPIO_TypeDef *Port, uint16_t Pin );




/******************************************************************************
 * Function		: void GPIO_setHighlevel( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio high level
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void GPIO_setHighlevel( GPIO_TypeDef *Port, uint16_t Pin );



/******************************************************************************
 * Function		: void GPIO_setLowlevel( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio low level
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void GPIO_setLowlevel( GPIO_TypeDef *Port, uint16_t Pin );



/******************************************************************************
 * Function		: void GPIO_setToggle( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio toggle
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void GPIO_setToggle( GPIO_TypeDef *Port, uint16_t Pin );



/******************************************************************************
 * Function		: bool GPIO_getlevel( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: get gpio level
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		:
 * 				+ 1 - pin high level
 * 				+ 0 - pin low level
 * ***************************************************************************/
bool GPIO_getlevel( GPIO_TypeDef *Port, uint16_t Pin );


#endif /* INTERFACE_GPIO_H_ */
