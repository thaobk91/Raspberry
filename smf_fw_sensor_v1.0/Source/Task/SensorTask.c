/*
 * SensorTask.c
 *
 *  Created on: Mar 11, 2019
 *      Author: Thao
 */
#include "cmsis_os.h"

#include "SensorTask.h"
#include "../fileData.h"
#include "../main.h"
#include "../IOControl.h"
#include "../Sensor/SS_THSoil.h"
#include "../Sensor/SS_PH.h"
#include "../Sensor/SS_EC.h"
#include "../Message/Message.h"


extern fileData_t __fileData;
extern Task_t _TaskHandle;


#define TIME_READ_SENSOR				30 //60s

#define SENSOR_ERROR_COUNT				10

SensorData_t __SensorData = {0};
Sensor_Error_t __Sensor_Error = {0};



static void SensorTask_SS_Power_Control( void );
static void SensorTask_CheckError( void );




/******************************************************************************
 * Function		: void SensorTask( void const *arg )
 * Description	: sensor task
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void SensorTask( void const *arg )
{
	APP_DEBUG("--- SensorTask: running...\r\n");

	osDelay(1000);
	Message_set_Typesensor_Callback( SensorTask_SS_Power_Control );
	SensorTask_SS_Power_Control();

	for(;;)
	{
		osDelay(TIME_READ_SENSOR * 1000);
		_TaskHandle.SensorTask_Finish = 1;
		APP_DEBUG("--- SensorTask: reading...\r\n");

		//read sensor
		//read temp and humi air
		if( (__fileData.SensorCfg & SS_TempA) == SS_TempA )
		{

		}

		//read temp and humi soil
		if( (__fileData.SensorCfg & SS_TempS) == SS_TempS )
		{
			float Temp = 0;
			float Humi = 0;

			SS_THSoil_Read( &Temp, &Humi );

			if( (Temp > __fileData.Threshold_TempS.Low) && (Temp < __fileData.Threshold_TempS.High) && \
				(Humi > __fileData.Threshold_HumiS.Low) && (Humi < __fileData.Threshold_HumiS.High) \
				)
			{
				__SensorData.TempS = Temp;
				__SensorData.HumiS = Humi;
				APP_DEBUG("--- SensorTask: Temp soil = %.2f, Humi soil = %.2f\r\n", __SensorData.TempS, __SensorData.HumiS);
			}
			else
			{
				APP_DEBUG("--- SensorTask: read temp & humi soil error, Temp = %.2f, Humi = %.2f\r\n", Temp, Humi);
			}

			//check loop data error
			if( (__Sensor_Error.TempS_error.value == __SensorData.TempS) && \
				(__Sensor_Error.HumiS_error.value == __SensorData.HumiS) \
				)
			{
				__Sensor_Error.TempS_error.Count++;
				__Sensor_Error.HumiS_error.Count++;
			}
			else
			{
				__Sensor_Error.TempS_error.Count = 0;
				__Sensor_Error.HumiS_error.Count = 0;
				__Sensor_Error.TempS_error.value = Temp;
				__Sensor_Error.HumiS_error.value = Humi;
			}
		}

		//read pH
		if( (__fileData.SensorCfg & SS_pH) == SS_pH )
		{
			float pH_value = SS_PH_Read();
			if( (pH_value >= __fileData.Threshold_pH.Low) && (pH_value <= __fileData.Threshold_pH.High) )
			{
				__SensorData.PH = pH_value;
				APP_DEBUG("--- SensorTask: pH = %.2f\r\n", __SensorData.PH);
			}
			else
			{
				APP_DEBUG("--- SensorTask: read pH error, value = %.2f\r\n", pH_value);
			}

			//check loop data error
			if( __Sensor_Error.pH_error.value == __SensorData.PH )
			{
				__Sensor_Error.pH_error.Count++;
			}
			else
			{
				__Sensor_Error.pH_error.Count = 0;
				__Sensor_Error.pH_error.value = pH_value;
			}
		}

		//read EC
		if( (__fileData.SensorCfg & SS_EC) == SS_EC )
		{
			float EC_Value = 0;
			EC_Value = SS_EC_Read();

			if( (EC_Value >= __fileData.Threshold_EC.Low) && (EC_Value <= __fileData.Threshold_EC.High) )
			{
				__SensorData.EC = EC_Value;
				APP_DEBUG("--- SensorTask: EC = %.2f\r\n", __SensorData.EC);
			}
			else
			{
				APP_DEBUG("--- SensorTask: read EC error, value = %.2f\r\n", EC_Value);
			}

			//check loop data error
			if( __Sensor_Error.EC_error.value == __SensorData.EC )
			{
				__Sensor_Error.EC_error.Count = 0;
				__Sensor_Error.EC_error.value = EC_Value;
			}
		}

		//read light
		if( (__fileData.SensorCfg & SS_Light) == SS_Light )
		{

		}

		//read CO2
		if( (__fileData.SensorCfg & SS_CO2) == SS_CO2 )
		{

		}

		//check sensor read error
		SensorTask_CheckError();

		_TaskHandle.SensorTask_Finish = 0;
	}
}




/******************************************************************************
 * Function		: void SensorTask_SS_Power_Control( void )
 * Description	: sensor read control
 * Param		: None
 * Return		: None
 * ***************************************************************************/
static void SensorTask_SS_Power_Control( void )
{
	//read temp and humi air
	if( (((__fileData.SensorCfg & SS_TempA) == SS_TempA) && ((__fileData.SensorCfg & SS_HumiA) == SS_HumiA )) || \
		((__fileData.SensorCfg & SS_Light) == SS_Light) )
	{
		IOControl_SS_THL_ON();
	}
	else
	{
		IOControl_SS_THL_OFF();
	}

	//read temp and humi soil
	if( ((__fileData.SensorCfg & SS_TempS) == SS_TempS) && ((__fileData.SensorCfg & SS_HumiS) == SS_HumiS) )
	{
		IOControl_SS_TH_Soil_ON();
	}
	else
	{
		IOControl_SS_TH_Soil_OFF();
	}

	//read pH
	if( (__fileData.SensorCfg & SS_pH) == SS_pH )
	{
		IOControl_SS_PH_ON();
		SS_PH_Init();
	}
	else
	{
		IOControl_SS_PH_OFF();
	}

	//read EC
	if( (__fileData.SensorCfg & SS_EC) == SS_EC )
	{
		IOControl_SS_EC_ON();
		SS_EC_Init();
	}
	else
	{
		IOControl_SS_EC_OFF();
	}

	//read CO2
	if( (__fileData.SensorCfg & SS_CO2) == SS_CO2 )
	{
		IOControl_SS_CO2_ON();
	}
	else
	{
		IOControl_SS_CO2_OFF();
	}
}




/******************************************************************************
 * Function		: void SensorTask_CheckError( void )
 * Description	: check sensor error
 * Param		: None
 * Return		: None
 * ***************************************************************************/
static void SensorTask_CheckError( void )
{
	//if data read after SENSOR_ERROR_COUNT --> reset sensor

	if( (__Sensor_Error.TempA_error.Count >= SENSOR_ERROR_COUNT) || \
		(__Sensor_Error.HumiA_error.Count >= SENSOR_ERROR_COUNT) \
		)
	{
		__Sensor_Error.TempA_error.Count = 0;
		__Sensor_Error.HumiA_error.Count = 0;
		APP_DEBUG("--- SensorTask: temp & humi air sensor error \"read count\". Reseting sensor\r\n");
		IOControl_SS_THL_OFF();
		osDelay(200);
		IOControl_SS_THL_ON();
	}

	if( (__Sensor_Error.TempS_error.Count >= SENSOR_ERROR_COUNT) || \
		(__Sensor_Error.HumiS_error.Count >= SENSOR_ERROR_COUNT) \
		)
	{
		__Sensor_Error.TempS_error.Count = 0;
		__Sensor_Error.HumiS_error.Count = 0;
		APP_DEBUG("--- SensorTask: temp & humi soil sensor error \"read count\". Reseting sensor\r\n");
		IOControl_SS_TH_Soil_OFF();
		osDelay(200);
		IOControl_SS_TH_Soil_ON();
	}

	if(__Sensor_Error.pH_error.Count >= SENSOR_ERROR_COUNT)
	{
		__Sensor_Error.pH_error.Count = 0;
		APP_DEBUG("--- SensorTask: pH sensor error \"read count\". Reseting sensor\r\n");
		IOControl_SS_PH_OFF();
		osDelay(200);
		IOControl_SS_PH_ON();
	}

	if(__Sensor_Error.EC_error.Count >= SENSOR_ERROR_COUNT)
	{
		__Sensor_Error.EC_error.Count = 0;
		APP_DEBUG("--- SensorTask: EC sensor error \"read count\". Reseting sensor\r\n");
		IOControl_SS_EC_OFF();
		osDelay(200);
		IOControl_SS_EC_ON();
	}

	if(__Sensor_Error.Light_error.Count >= SENSOR_ERROR_COUNT)
	{
		__Sensor_Error.Light_error.Count = 0;
		APP_DEBUG("--- SensorTask: Light sensor error \"read count\". Reseting sensor\r\n");
		IOControl_SS_THL_OFF();
		osDelay(200);
		IOControl_SS_THL_ON();
	}

	if(__Sensor_Error.CO2_error.Count >= SENSOR_ERROR_COUNT)
	{
		__Sensor_Error.CO2_error.Count = 0;
		APP_DEBUG("--- SensorTask: CO2 sensor error \"read count\". Reseting sensor\r\n");
		IOControl_SS_CO2_OFF();
		osDelay(200);
		IOControl_SS_CO2_ON();
	}
}






















