/*
 * SS_EC.c
 *
 *  Created on: Mar 22, 2019
 *      Author: thaonm1
 */
#include "stm32l4xx_hal.h"
#include "../main.h"
#include "SS_EC.h"
#include "../Interface/ADC.h"


/* Private typedef -----------------------------------------------------------*/
#define  PERIOD_VALUE       			500  /* Period Value  */

#define ADC_EC_VOUT_CHANNEL				ADC_CHANNEL_3
#define ADC_EC_REF						3300	//mV


ADC_HandleTypeDef ADC_EC_Handle;

TIM_HandleTypeDef htim1;




static void SS_EC_Init_PWM( void )
{
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
//	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**TIM1 GPIO Configuration
	PA11     ------> TIM1_CH4
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 400-1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 9999-1;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
	{

	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{

	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	{

	}

//	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
//	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
//	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
//	sBreakDeadTimeConfig.DeadTime = 0;
//	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
//	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
//	sBreakDeadTimeConfig.BreakFilter = 0;
//	sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
//	sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
//	sBreakDeadTimeConfig.Break2Filter = 0;
//	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
//	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
//	{
//
//	}

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
}



static void SS_EC_Init_ADC( void )
{
	ADC_Init( &ADC_EC_Handle );
}



void SS_EC_Init( void )
{
	SS_EC_Init_PWM();
	SS_EC_Init_ADC();
}



float SS_EC_Read( void )
{
	uint32_t EC_VOut = 0;

	ADC_SetChannel( &ADC_EC_Handle, ADC_EC_VOUT_CHANNEL );
	ADC_ReadValue( &ADC_EC_Handle, &EC_VOut );

	APP_DEBUG("--- SS_EC: EC_Vout = %ld [mV]\r\n", EC_VOut);

	float EC = (float)(EC_VOut / 0.14 / (ADC_EC_REF / 2));

	return EC;
}



















