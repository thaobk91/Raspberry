/*
 * ADC.c
 *
 *  Created on: Mar 16, 2019
 *      Author: thaonm1
 */
#include "../main.h"




/*******************************************************************************
 * Function		: void ADC_Init( ADC_HandleTypeDef *__ADC_Handle )
 * Description	: init adc
 * Param		: __ADC_Handle - adc handle
 * Return		: None
 * ****************************************************************************/
void ADC_Init( ADC_HandleTypeDef *__ADC_Handle )
{
	__ADC_Handle->Instance = ADC1;
	__ADC_Handle->Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	__ADC_Handle->Init.Resolution = ADC_RESOLUTION_12B;
	__ADC_Handle->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	__ADC_Handle->Init.ScanConvMode = ADC_SCAN_DISABLE;
	__ADC_Handle->Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	__ADC_Handle->Init.LowPowerAutoWait = DISABLE;
	__ADC_Handle->Init.ContinuousConvMode = DISABLE;
	__ADC_Handle->Init.NbrOfConversion = 1;
	__ADC_Handle->Init.DiscontinuousConvMode = DISABLE;
	__ADC_Handle->Init.ExternalTrigConv = ADC_SOFTWARE_START;
	__ADC_Handle->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	__ADC_Handle->Init.DMAContinuousRequests = DISABLE;
	__ADC_Handle->Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	__ADC_Handle->Init.OversamplingMode = DISABLE;

	if (HAL_ADC_Init( __ADC_Handle ) != HAL_OK)
		APP_DEBUG("--- ADC: init fail\r\n");

	/*##-3- Calibrate ADC then Start the conversion process ####################*/
	if (HAL_ADCEx_Calibration_Start( __ADC_Handle, ADC_SINGLE_ENDED ) !=  HAL_OK)
		APP_DEBUG("--- ADC: calibration start error\r\n");

}




/*******************************************************************************
 * Function		: void ADC_SetChannel( ADC_HandleTypeDef *__ADC_Handle, uint32_t Channel )
 * Description	: adc set channel
 * Param		:
 * 				+ __ADC_Handle: adc handle
 * 				+ Channel: adc channel
 * Return		: None
 * ****************************************************************************/
void ADC_SetChannel( ADC_HandleTypeDef *__ADC_Handle, uint32_t Channel )
{
	ADC_ChannelConfTypeDef sConfig = {0};

	//Configure Regular Channel
	sConfig.Channel = Channel;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;

	if (HAL_ADC_ConfigChannel( __ADC_Handle, &sConfig ) != HAL_OK)
		APP_DEBUG("--- ADC: config channel fail\r\n");
}




/*******************************************************************************
 * Function		: void ADC_ReadValue( ADC_HandleTypeDef *__ADC_Handle, uint32_t *VOut )
 * Description	: read adc
 * Param		:
 * 				+ __ADC_Handle: adc handle
 * 				+ VOut: adc voltage output
 * Return		: None
 * ****************************************************************************/
void ADC_ReadValue( ADC_HandleTypeDef *__ADC_Handle, uint32_t *VOut )
{
	if (HAL_ADC_Start( __ADC_Handle ) != HAL_OK)
		APP_DEBUG("--- ADC: hal adc start error\r\n");

	if (HAL_ADC_PollForConversion( __ADC_Handle, 100 ) != HAL_OK)
		APP_DEBUG("--- ADC: HAL_ADC_PollForConversion error\r\n");

	/* Check if the continous conversion of regular channel is finished */
	if ((HAL_ADC_GetState( __ADC_Handle ) & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC)
		*VOut = HAL_ADC_GetValue( __ADC_Handle );

	HAL_ADC_Stop( __ADC_Handle );
}




















