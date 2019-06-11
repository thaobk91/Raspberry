
#ifndef __MAIN_H
#define __MAIN_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "cmsis_os.h"

#include "Interface/GPIO.h"


#define DEBUG

#ifdef DEBUG
#define APP_DEBUG						printf
#else
#define APP_DEBUG
#endif




typedef struct
{
	osThreadId	ProcessTask_Handle;
	osThreadId	LoraTask_Handle;
	osThreadId	SensorTask_Handle;
	osThreadId	OTATask_Handle;

	uint32_t	LoraTask_Finish;
	uint32_t	SensorTask_Finish;
	uint32_t	OTATask_Finish;
}Task_t;




#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */















