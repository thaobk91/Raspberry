/*
 * fileData.h
 *
 *  Created on: Mar 19, 2019
 *      Author: thaonm1
 */

#ifndef FILEDATA_H_
#define FILEDATA_H_



enum
{
	SS_TempA	= 0x0001,
	SS_HumiA	= 0x0002,
	SS_TempS	= 0x0004,
	SS_HumiS	= 0x0008,
	SS_pH		= 0x0010,
	SS_EC		= 0x0020,
	SS_Light	= 0x0040,
	SS_CO2		= 0x0080,
}SensorType;


typedef struct
{
	float High;
	float Low;
}SS_Threshold_t;


typedef struct
{
	uint16_t		ResetCount;

	uint16_t		SensorCfg; //0b00000000 00000000 (co2 <- light <- EC <- pH <- humiS <- tempS <- humiA <- tempA)

	uint16_t		DataUT;		//ms

	SS_Threshold_t	Threshold_TempA;
	SS_Threshold_t	Threshold_HumiA;
	SS_Threshold_t	Threshold_TempS;
	SS_Threshold_t	Threshold_HumiS;
	SS_Threshold_t	Threshold_pH;
	SS_Threshold_t	Threshold_EC;
	SS_Threshold_t	Threshold_Light;
	SS_Threshold_t	Threshold_CO2;
}fileData_t;



/*******************************************************************************
 * Function		: void fileData_Init( void )
 * Description	: init data storage
 * Param		: None
 * Return		: None
 * ****************************************************************************/
void fileData_Init( void );



/*******************************************************************************
 * Function		: void fileData_ReadAll( void )
 * Description	: read all data from flash
 * Param		: None
 * Return		: None
 * ****************************************************************************/
void fileData_ReadAll( void );



/*******************************************************************************
 * Function		: void fileData_WriteAll( void )
 * Description	: write all data to flash
 * Param		: None
 * Return		: None
 * ****************************************************************************/
void fileData_WriteAll( void );



//write sensor config
void fileData_Write_SensorCFG( void );
void fileData_Read_Sensor_CFG( void );



//data update time
void fileData_Write_DataUT( void );
void fileData_Read_DataUT( void );



//threshold temp air
void fileData_Write_Threshold_TempA( void );
void fileData_Read_Threshold_TempA( void );



//threshold humi air
void fileData_Write_Threshold_HumiA( void );
void fileData_Read_Threshold_HumiA( void );



//threshold temp soil
void fileData_Write_Threshold_TempS( void );
void fileData_Read_Threshold_TempS( void );



//threshold humi soil
void fileData_Write_Threshold_HumiS( void );
void fileData_Read_Threshold_HumiS( void );



//threshold pH
void fileData_Write_Threshold_PH( void );
void fileData_Read_Threshold_PH( void );



//threshold EC
void fileData_Write_Threshold_EC( void );
void fileData_Read_Threshold_EC( void );



//threshold light
void fileData_Write_Threshold_Light( void );
void fileData_Read_Threshold_Light( void );



//threshold CO2
void fileData_Write_Threshold_CO2( void );
void fileData_Read_Threshold_CO2( void );




#endif /* FILEDATA_H_ */













