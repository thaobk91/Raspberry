/*
 * SensorTask.h
 *
 *  Created on: Mar 11, 2019
 *      Author: Thao
 */

#ifndef TASK_SENSORTASK_H_
#define TASK_SENSORTASK_H_


typedef struct
{
	float	TempA;
	float	HumiA;
	float	TempS;
	float	HumiS;
	float	PH;
	float	EC;
	float	Light;
	float	CO2;
}SensorData_t;


typedef struct
{
	float	value;
	uint8_t	Count;
}Sensor_Old_Count_t;


typedef struct
{
	Sensor_Old_Count_t	TempA_error;
	Sensor_Old_Count_t	HumiA_error;
	Sensor_Old_Count_t	TempS_error;
	Sensor_Old_Count_t	HumiS_error;
	Sensor_Old_Count_t	pH_error;
	Sensor_Old_Count_t	EC_error;
	Sensor_Old_Count_t	Light_error;
	Sensor_Old_Count_t	CO2_error;
}Sensor_Error_t;



/******************************************************************************
 * Function		: void SensorTask( void const *arg )
 * Description	: sensor task
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void SensorTask( void const *arg );

#endif /* TASK_SENSORTASK_H_ */
