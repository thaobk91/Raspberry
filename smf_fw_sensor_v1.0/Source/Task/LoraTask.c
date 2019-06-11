/*
 * LoraTask.c
 *
 *  Created on: Mar 11, 2019
 *      Author: Thao
 */
#include "cmsis_os.h"

#include "LoraTask.h"
#include "../Message/Message.h"
#include "Device/Lora/Lora.h"
#include "../main.h"



extern Task_t _TaskHandle;


uint8_t Lora_RX_Buffer[LORA_MAX_LENGHT + 1] = {0};
uint16_t Lora_RX_Lenght = 0;




/******************************************************************************
 * Function		: void LoraTask( void const *agr )
 * Description	: lora task
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void LoraTask( void const *agr )
{
	APP_DEBUG("--- LoraTask: running...\r\n");
	osDelay(1000);
	Lora_Init( LORA_MAX_LENGHT );
	Message_set_Lora_Transmit_Callback( Lora_Transmit );

	for(;;)
	{
		osDelay(50);
		_TaskHandle.LoraTask_Finish = 1;
		if( (Lora_RX_Lenght = Lora_Receive( Lora_RX_Buffer )) > 0 )
			Message_Process( Lora_RX_Buffer, Lora_RX_Lenght );
		_TaskHandle.LoraTask_Finish = 0;
	}
}




















