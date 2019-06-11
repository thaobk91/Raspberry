/*
 * ProcessTask.c
 *
 *  Created on: Mar 11, 2019
 *      Author: Thao
 */
#include <stdlib.h>
#include <string.h>

#include "cmsis_os.h"

#include "ProcessTask.h"
#include "OTATask.h"

#include "../Interface/Uart.h"
#include "../fileData.h"
#include "../IOControl.h"
#include "../Message/Message.h"
#include "../fileData.h"


#define PROCESS_TASK_DELAY				10	//ms
#define LED_STATUS_TIME_OFF				3000 //ms
#define LED_STATUS_TIME_ON				30	//ms


#define LED_STATUS_PORT					GPIOB
#define LED_STATUS_PIN					GPIO_PIN_11

#define LED_STATUS_TOGGLE()				HAL_GPIO_TogglePin( LED_STATUS_PORT, LED_STATUS_PIN )
#define LED_STATUS_HIGH()				GPIO_setHighlevel( LED_STATUS_PORT, LED_STATUS_PIN )
#define LED_STATUS_LOW()				GPIO_setLowlevel( LED_STATUS_PORT, LED_STATUS_PIN )

#define SEND_DATA_TIMEOUT				10 //second


extern Task_t _TaskHandle;
extern fileData_t __fileData;
extern OTA_State_t OTA_State;


uint16_t Led_Counter = 0;
uint32_t SendData_Counter = 0;


static void ProcessTask_sendData_Callback( void );




/******************************************************************************
 * Function		: void ProcessTask( void const *arg )
 * Description	: process task
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void ProcessTask( void const *arg )
{
	APP_DEBUG( "--- ProcessTask: running...\r\n" );

	//init led status
	GPIO_setOutput_Pullup( LED_STATUS_PORT, LED_STATUS_PIN );		//led status

	//set message callback
	Message_set_sendData_Callback( ProcessTask_sendData_Callback );

	for(;;)
	{
		osDelay(PROCESS_TASK_DELAY);
		Led_Counter++;

		//led status
		if( Led_Counter <= (LED_STATUS_TIME_OFF / PROCESS_TASK_DELAY) )
			LED_STATUS_HIGH();
		else if( Led_Counter <= ((LED_STATUS_TIME_OFF + LED_STATUS_TIME_ON) / PROCESS_TASK_DELAY) )
			LED_STATUS_LOW();
		else
		{
			Led_Counter = 0;
			IOControl_WDT_Done();	//WDT refresh
		}

		//OTA is off
		if(OTA_State == OTA_STOP)
		{
			SendData_Counter++;
			//send data sensor
			if( SendData_Counter == (__fileData.DataUT * 1000 / PROCESS_TASK_DELAY) )
			{
				Message_SendData_Sensor();
			}
			else if(SendData_Counter >= ((__fileData.DataUT + SEND_DATA_TIMEOUT) * 1000 / PROCESS_TASK_DELAY)) //send timeout
			{
				APP_DEBUG("--- ProcessTask: gw not feedback. resending...\r\n");
				SendData_Counter = __fileData.DataUT * 1000 / PROCESS_TASK_DELAY - 1;
			}
		}
		else if(OTA_State == OTA_START)
		{
			vTaskResume( _TaskHandle.OTATask_Handle );
		}


		//check task
		if( _TaskHandle.LoraTask_Finish >= 1 )
			_TaskHandle.LoraTask_Finish++;
		if( _TaskHandle.SensorTask_Finish >= 1 )
			_TaskHandle.SensorTask_Finish++;
		if( _TaskHandle.OTATask_Finish >= 1 )
			_TaskHandle.OTATask_Finish++;

		if( ( _TaskHandle.LoraTask_Finish >= (90 * 1000 / PROCESS_TASK_DELAY) ) || \
			( _TaskHandle.SensorTask_Finish >= (90 * 1000 / PROCESS_TASK_DELAY) ) || \
			( _TaskHandle.OTATask_Finish >= (300 * 1000 / PROCESS_TASK_DELAY) ) \
			)
		{
			APP_DEBUG("--- ProcessTask: task is died. reseting...\r\n");
			osDelay(1000);
			NVIC_SystemReset();
		}
	}
}




static void ProcessTask_sendData_Callback( void )
{
	SendData_Counter = 0;
	APP_DEBUG("--- ProcessTask: send data to gw successfully\r\n\r\n");
}














