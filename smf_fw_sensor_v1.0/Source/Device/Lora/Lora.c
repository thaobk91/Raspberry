/*
 * Lora.c
 *
 *  Created on: Feb 24, 2019
 *      Author: Thao
 */
#include "HW_Lora_Driver.h"
#include "SX1278.h"
#include "../../main.h"
#include "Lora.h"


#define macroLR_DIO_0_PORT						GPIOB
#define macroLR_DIO_0_PIN 						GPIO_PIN_1
#define macroLR_RESET_PORT						GPIOB
#define macroLR_RESET_PIN						GPIO_PIN_0
#define macroLR_NSS_PORT						GPIOA
#define macroLR_NSS_PIN							GPIO_PIN_4


Lora_SX1278_t __Lora_SX1278;
uint16_t LR_MSG_Max_Lenght = 0;




/*******************************************************************************
 * Function		: void Lora_Init( uint16_t Message_maxLenght )
 * Description	: Lora Init
 * Param		: Message_maxLenght - message max lenght
 * Return		: None
 * ****************************************************************************/
void Lora_Init( uint16_t Message_maxLenght )
{
	//initialize LoRa module
	LR_MSG_Max_Lenght = Message_maxLenght;
	__Lora_SX1278.HW.DIO_0.Port				= macroLR_DIO_0_PORT;
	__Lora_SX1278.HW.DIO_0.Pin 				= macroLR_DIO_0_PIN;
	__Lora_SX1278.HW.Reset.Port				= macroLR_RESET_PORT;
	__Lora_SX1278.HW.Reset.Pin				= macroLR_RESET_PIN;
	__Lora_SX1278.HW.NSS.Port				= macroLR_NSS_PORT;
	__Lora_SX1278.HW.NSS.Pin				= macroLR_NSS_PIN;

	__Lora_SX1278.Cfg.Frequency				= SX1278_433MHZ;
	__Lora_SX1278.Cfg.Power					= SX1278_POWER_20DBM;
	__Lora_SX1278.Cfg.LoRa_Rate				= SX1278_LORA_SF_8;
	__Lora_SX1278.Cfg.LoRa_BW				= SX1278_LORA_BW_500KHZ;
	__Lora_SX1278.Cfg.packetLength			= LR_MSG_Max_Lenght;

	__Lora_SX1278.SX1278_Delay_ms			= HW_Lora_Driver_Delay_ms;
	//__Lora_SX1278.SX1278_Delay_us			= LR_HW_Driver_Delay_us;
	__Lora_SX1278.HW_GPIO_Init_Pin_Output	= HW_Lora_Driver_setPin_Output;
	__Lora_SX1278.HW_GPIO_Init_Pin_Input	= HW_Lora_Driver_setPin_Input;
	__Lora_SX1278.HW_GPIO_Set_Pin			= HW_Lora_Driver_setPin_High;
	__Lora_SX1278.HW_GPIO_Reset_Pin			= HW_Lora_Driver_setPin_Low;
	__Lora_SX1278.HW_GPIO_Read_Pin			= HW_Lora_Driver_ReadPin;
	__Lora_SX1278.HW_SPI_Init				= HW_Lora_Driver_SPI_Init;
	__Lora_SX1278.HW_SPI_State_Ready		= HW_Lora_Driver_SPI_Ready;
	__Lora_SX1278.HW_SPI_ReadByte			= HW_Lora_Driver_SPI_ReadByte;
	__Lora_SX1278.HW_SPI_WriteByte			= HW_Lora_Driver_SPI_WriteByte;
	__Lora_SX1278.debug						= APP_DEBUG;

	SX1278_Init( &__Lora_SX1278 );

	SX1278_LoRaEntryRx( &__Lora_SX1278, LR_MSG_Max_Lenght, 0xffff );
	APP_DEBUG("\r\n--- Lora: Lora RX Start\r\n");
}




/*******************************************************************************
 * Function		: bool Lora_Transmit( uint8_t *TXBuffer, uint16_t TXLenght )
 * Description	: Lora transmit data
 * Param		:
 * 				+ TXBuffer - TX Buffer
 * 				+ TXLenght - TX buffer lenght
 * Return		:
 * 				+ true - successfully
 * 				+ false - failture
 * ****************************************************************************/
bool Lora_Transmit( uint8_t *TXBuffer, uint16_t TXLenght )
{
//	char Hex[17] = "0123456789ABCDEF";
//	__Lora_SX1278.debug("--- Lora: sending message ");
//	for(uint16_t ui = 0; ui < TXLenght; ui++)
//		__Lora_SX1278.debug("%c%c", Hex[TXBuffer[ui] / 16], Hex[TXBuffer[ui] % 16]);
//	__Lora_SX1278.debug(", lenght = %d\r\n", TXLenght);
	bool Result = SX1278_Transmit( &__Lora_SX1278, TXBuffer, TXLenght, 0xffff );
	SX1278_LoRaEntryRx( &__Lora_SX1278, LR_MSG_Max_Lenght, 0xffff );	//goto rx mode

	if(Result == true)
		__Lora_SX1278.debug("--- Lora: sent message successfully. \"%s\", lenght = %d\r\n", TXBuffer, TXLenght);
	else
		__Lora_SX1278.debug("--- Lora: sent message failture\r\n");
	return Result;
}




/*******************************************************************************
 * Function		: uint16_t Lora_Receive( uint8_t *RX_Buffer )
 * Description	: Lora receive data
 * Param		: RX_Buffer - RX Buffer
 * Return		:
 * 				+ >0 - successfully
 * 				+ 0 - failture
 * ****************************************************************************/
uint16_t Lora_Receive( uint8_t *RX_Buffer )
{
	uint16_t len = 0;
	SX1278_Receive( &__Lora_SX1278, RX_Buffer, &len );
	return len;
}



















