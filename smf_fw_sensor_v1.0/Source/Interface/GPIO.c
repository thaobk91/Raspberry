/*
 * GPIO.c
 *
 *  Created on: Mar 11, 2019
 *      Author: Thao
 */
#include "GPIO.h"




/******************************************************************************
 * Function		: void GPIO_Init( void )
 * Description	: init gpio
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void GPIO_Init( void )
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
}




/******************************************************************************
 * Function		: void GPIO_setOutput_Pullup( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio output pullup
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * 				+ Pullup - true: pullup, false: pulldown
 * Return		: None
 * ***************************************************************************/
void GPIO_setOutput_Pullup( GPIO_TypeDef *Port, uint16_t Pin )
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pin*/
	GPIO_InitStruct.Pin = Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(Port, &GPIO_InitStruct);
}




/******************************************************************************
 * Function		: void GPIO_setOutput_Pulldown( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio output pulldown
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * 				+ Pullup - true: pullup, false: pulldown
 * Return		: None
 * ***************************************************************************/
void GPIO_setOutput_Pulldown( GPIO_TypeDef *Port, uint16_t Pin )
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pin*/
	GPIO_InitStruct.Pin = Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(Port, &GPIO_InitStruct);
}



/******************************************************************************
 * Function		: void GPIO_setOutput_NoPull( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio output no pull
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * 				+ Pullup - true: pullup, false: pulldown
 * Return		: None
 * ***************************************************************************/
void GPIO_setOutput_NoPull( GPIO_TypeDef *Port, uint16_t Pin )
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pin*/
	GPIO_InitStruct.Pin = Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(Port, &GPIO_InitStruct);
}




/******************************************************************************
 * Function		: void GPIO_setInput( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio input
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void GPIO_setInput( GPIO_TypeDef *Port, uint16_t Pin )
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pin*/
	GPIO_InitStruct.Pin = Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(Port, &GPIO_InitStruct);
}




/******************************************************************************
 * Function		: void GPIO_setHighlevel( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio high level
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void GPIO_setHighlevel( GPIO_TypeDef *Port, uint16_t Pin )
{
	HAL_GPIO_WritePin( Port, Pin, GPIO_PIN_SET );
}



/******************************************************************************
 * Function		: void GPIO_setLowlevel( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio low level
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void GPIO_setLowlevel( GPIO_TypeDef *Port, uint16_t Pin )
{
	HAL_GPIO_WritePin( Port, Pin, GPIO_PIN_RESET );
}


/******************************************************************************
 * Function		: void GPIO_setToggle( GPIO_TypeDef *Port, uint16_t Pin )
 * Description	: set gpio toggle
 * Param		:
 * 				+ Port - gpio port
 * 				+ Pin  -gpio Pin
 * Return		: None
 * ***************************************************************************/
void GPIO_setToggle( GPIO_TypeDef *Port, uint16_t Pin )
{
	HAL_GPIO_TogglePin( Port, Pin );
}



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
bool GPIO_getlevel( GPIO_TypeDef *Port, uint16_t Pin )
{
	return HAL_GPIO_ReadPin( Port, Pin );
}





















