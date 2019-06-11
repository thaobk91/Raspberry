/*
 * ADC.h
 *
 *  Created on: Mar 16, 2019
 *      Author: thaonm1
 */

#ifndef INTERFACE_ADC_H_
#define INTERFACE_ADC_H_

#include "stm32l4xx_hal.h"




/*******************************************************************************
 * Function		: void ADC_Init( ADC_HandleTypeDef *__ADC_Handle )
 * Description	: init adc
 * Param		: __ADC_Handle - adc handle
 * Return		: None
 * ****************************************************************************/
void ADC_Init( ADC_HandleTypeDef *__ADC_Handle );




/*******************************************************************************
 * Function		: void ADC_SetChannel( ADC_HandleTypeDef *__ADC_Handle, uint32_t Channel )
 * Description	: adc set channel
 * Param		:
 * 				+ __ADC_Handle: adc handle
 * 				+ Channel: adc channel
 * Return		: None
 * ****************************************************************************/
void ADC_SetChannel( ADC_HandleTypeDef *__ADC_Handle, uint32_t Channel );




/*******************************************************************************
 * Function		: void ADC_ReadValue( ADC_HandleTypeDef *__ADC_Handle, uint32_t *VOut )
 * Description	: read adc
 * Param		:
 * 				+ __ADC_Handle: adc handle
 * 				+ VOut: adc voltage output
 * Return		: None
 * ****************************************************************************/
void ADC_ReadValue( ADC_HandleTypeDef *__ADC_Handle, uint32_t *VOut );


#endif /* INTERFACE_ADC_H_ */












