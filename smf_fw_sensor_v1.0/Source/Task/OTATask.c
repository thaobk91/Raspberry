/*
 * OTATask.c
 *
 *  Created on: Jun 5, 2019
 *      Author: Thao
 */
#include "OTATask.h"
#include "../main.h"
#include "../Message/Message.h"


#define OTA_LOOP_TIME							2//ms
#define OTA_TIMEOUT								300//s

extern Task_t _TaskHandle;

OTA_State_t OTA_State = OTA_STOP;
uint32_t OTA_Timeout_Count = 0;


//OTA start call back
static void OTATask_Start_Callback( void );
//OTA data call back
static void OTATask_Data_Callback( uint8_t *RXBuffer, uint16_t RXLenght );
//OTA data done call back
static void OTATask_data_done_Callback( void );





/******************************************************************************
 * Function		: void OTATask( void const *arg )
 * Description	: OTA task
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void OTATask( void const *arg )
{
	APP_DEBUG("--- OTATask: running...\r\n");
	osDelay(1000);

	Message_set_OTA_Callback( OTATask_Start_Callback, OTATask_Data_Callback, OTATask_data_done_Callback );

	for(;;)
	{
		osDelay(OTA_LOOP_TIME);
		_TaskHandle.OTATask_Finish = 1;
		OTA_Timeout_Count++;

		if(OTA_Timeout_Count >= (OTA_TIMEOUT * 1000 / OTA_LOOP_TIME))
		{
			APP_DEBUG("\r\n--- OTATask: OTA time out --> stop\r\n");
			OTA_Timeout_Count = 0;
			OTA_State = OTA_STOP;
		}

		switch(OTA_State)
		{
			case OTA_START:
				APP_DEBUG("\r\n--- OTATask: OTA started\r\n");
				OTA_Timeout_Count = 0;
				OTA_State = OTA_RECV_FW;
				break;

			case OTA_RECV_FW:
				APP_DEBUG("\r\n--- OTATask: OTA receiving data\r\n");
				break;

			case OTA_REV_DONE:
				APP_DEBUG("\r\n--- OTATask: OTA receive done\r\n");
				break;

			case OTA_UPGRADE:
				APP_DEBUG("\r\n--- OTATask: OTA upgrade\r\n");
				break;

			case OTA_STOP:
				APP_DEBUG("\r\n--- OTATask: OTA stopped\r\n");
				OTA_Timeout_Count = 0;
				_TaskHandle.OTATask_Finish = 0;
				vTaskSuspend(NULL);
				break;
		}
		_TaskHandle.OTATask_Finish = 0;
	}
}




//OTA start call back
static void OTATask_Start_Callback( void )
{
	OTA_State = OTA_START;
}



//OTA data call back
static void OTATask_Data_Callback( uint8_t *RXBuffer, uint16_t RXLenght )
{
	if(OTA_State == OTA_RECV_FW)
	{
		//write data to flash
	}
}



//OTA data done call back
static void OTATask_data_done_Callback( void )
{
	OTA_State = OTA_REV_DONE;
}


























