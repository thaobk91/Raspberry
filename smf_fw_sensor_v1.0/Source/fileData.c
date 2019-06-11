/*
 * fileData.c
 *
 *  Created on: Mar 19, 2019
 *      Author: thaonm1
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Device/Flash/Flash.h"
#include "fileData.h"
#include "main.h"


#define PAGE_SIZE							4*1024 //4K
#define BLOCK_SIZE							64*1024 //64K

//address mapping
enum
{
	//address = page size * page num + address if page
	address_reset				= PAGE_SIZE * 24 + 0,	//page 24
	address_flags				= PAGE_SIZE * 0 + 0,	//page 0
	address_sensor_cfg			= PAGE_SIZE * 1 + 0,	//page 1
	address_dataut 				= PAGE_SIZE * 2 + 0,	//page 2
	address_threshold_temp_a	= PAGE_SIZE * 3 + 0,	//page 3
	address_threshold_humi_a	= PAGE_SIZE * 4 + 0,	//page 4
	address_threshold_temp_s	= PAGE_SIZE * 5 + 0,	//page 5
	address_threshold_humi_s	= PAGE_SIZE * 6 + 0,	//page 6
	address_threshold_ph		= PAGE_SIZE * 7 + 0,	//page 7
	address_threshold_ec		= PAGE_SIZE * 8 + 0,	//page 8
	address_threshold_light		= PAGE_SIZE * 9 + 0,	//page 9
	address_threshold_co2		= PAGE_SIZE * 10 + 0,	//page 10
};


#define RESET_LENGHT						2
#define FLAGS_FLASH_LENGHT					1
#define SENSOR_CFG_FLASH_LENGHT				2
#define DATA_UT_FLASH_LENGHT				2
#define TEMP_A_FLASH_LENGHT					8
#define HUMI_A_FLASH_LENGHT					8
#define TEMP_S_FLASH_LENGHT					8
#define HUMI_S_FLASH_LENGHT					8
#define PH_FLASH_LENGHT						8
#define EC_FLASH_LENGHT						8
#define LIGHT_FLASH_LENGHT					8
#define CO2_FLASH_LENGHT					8



fileData_t __fileData =
{
	.ResetCount			= 0,
	.SensorCfg			= SS_TempS | SS_HumiS | SS_pH | SS_EC,
	.DataUT				= 30,
	.Threshold_TempA	= {0, 50},
	.Threshold_HumiA 	= {0, 100},
	.Threshold_TempS 	= {0, 50},
	.Threshold_HumiS 	= {0, 100},
	.Threshold_pH	 	= {0, 14},
	.Threshold_EC		= {0, 200},
	.Threshold_Light	= {0, 65535},
	.Threshold_CO2		= {0, 1000},
};



//threshold temp air
static void fileData_Write_Threshold_Component( uint32_t addr, uint8_t Lenght, float Threshold_Low, float Threshold_High );
static void fileData_Read_Threshold_Component( uint32_t addr, uint8_t Lenght, float *Threshold_Low, float *Threshold_High );

static void fileData_Write_Flags( void );
static uint8_t fileData_Read_Flags( void );
static void fileData_Write_Reset( void );
static void fileData_Read_Reset( void );



/*******************************************************************************
 * Function		: void fileData_Init( void )
 * Description	: init data storage
 * Param		: None
 * Return		: None
 * ****************************************************************************/
void fileData_Init( void )
{
	Flash_Init();
}



/*******************************************************************************
 * Function		: void fileData_ReadAll( void )
 * Description	: read all data from flash
 * Param		: None
 * Return		: None
 * ****************************************************************************/
void fileData_ReadAll( void )
{
//	fileData_WriteAll();
	if( fileData_Read_Flags() != 1 )
	{
		fileData_WriteAll();
	}

	fileData_Read_Reset();
	fileData_Write_Reset();
	fileData_Read_Sensor_CFG();
	fileData_Read_DataUT();

	APP_DEBUG("\r\n--- fileData: reset count         = %d\r\n", __fileData.ResetCount);
	APP_DEBUG("--- fileData: Sensor cfg          = 0x%.4x\r\n", __fileData.SensorCfg);
	APP_DEBUG("--- fileData: Data UT             = %d\r\n", __fileData.DataUT);

	if( (__fileData.SensorCfg & SS_TempA) == SS_TempA )
	{
		fileData_Read_Threshold_TempA();
		APP_DEBUG("--- fileData: Threshold Temp Air  = %f - %f\r\n", \
					__fileData.Threshold_TempA.Low, __fileData.Threshold_TempA.High);
	}
	if( (__fileData.SensorCfg & SS_HumiA) == SS_HumiA )
	{
		fileData_Read_Threshold_HumiA();
		APP_DEBUG("--- fileData: Threshold Humi Air  = %f - %f\r\n", \
					__fileData.Threshold_HumiA.Low, __fileData.Threshold_HumiA.High);
	}
	if( (__fileData.SensorCfg & SS_TempS) == SS_TempS )
	{
		fileData_Read_Threshold_TempS();
		APP_DEBUG("--- fileData: Threshold Temp Soil = %f - %f\r\n", \
					__fileData.Threshold_TempS.Low, __fileData.Threshold_TempS.High);
	}
	if( (__fileData.SensorCfg & SS_HumiS) == SS_HumiS )
	{
		fileData_Read_Threshold_HumiS();
		APP_DEBUG("--- fileData: Threshold Humi Soil = %f - %f\r\n", \
					__fileData.Threshold_HumiS.Low, __fileData.Threshold_HumiS.High);
	}
	if( (__fileData.SensorCfg & SS_pH) == SS_pH )
	{
		fileData_Read_Threshold_PH();
		APP_DEBUG("--- fileData: Threshold PH        = %f - %f\r\n", \
					__fileData.Threshold_pH.Low, __fileData.Threshold_pH.High);
	}
	if( (__fileData.SensorCfg & SS_EC) == SS_EC )
	{
		fileData_Read_Threshold_EC();
		APP_DEBUG("--- fileData: Threshold EC        = %f - %f\r\n", \
					__fileData.Threshold_EC.Low, __fileData.Threshold_EC.High);
	}
	if( (__fileData.SensorCfg & SS_Light) == SS_Light )
	{
		fileData_Read_Threshold_Light();
		APP_DEBUG("--- fileData: Threshold Light     = %f - %f\r\n", \
					__fileData.Threshold_Light.Low, __fileData.Threshold_Light.High);
	}
	if( (__fileData.SensorCfg & SS_CO2) == SS_CO2 )
	{
		fileData_Read_Threshold_CO2();
		APP_DEBUG("--- fileData: Threshold CO2       = %f - %f\r\n", \
					__fileData.Threshold_CO2.Low, __fileData.Threshold_CO2.High);
	}
}



/*******************************************************************************
 * Function		: void fileData_WriteAll( void )
 * Description	: write all data to flash
 * Param		: None
 * Return		: None
 * ****************************************************************************/
void fileData_WriteAll( void )
{
	APP_DEBUG("--- fileData: write all data\r\n");
	fileData_Write_Reset();
	fileData_Write_Flags();
	fileData_Write_SensorCFG();
	fileData_Write_DataUT();
	fileData_Write_Threshold_TempA();
	fileData_Write_Threshold_HumiA();
	fileData_Write_Threshold_TempS();
	fileData_Write_Threshold_HumiS();
	fileData_Write_Threshold_PH();
	fileData_Write_Threshold_EC();
	fileData_Write_Threshold_Light();
	fileData_Write_Threshold_CO2();
}



//write reset
static void fileData_Write_Reset( void )
{
	uint8_t Buffwrite[RESET_LENGHT + 1] = {0};
	uint16_t value = __fileData.ResetCount + 1;
	Buffwrite[0] = (value >> 8) & 0xFF;
	Buffwrite[1] = (value >> 0) & 0xFF;

	Flash_Write_to_Page( address_reset, Buffwrite, RESET_LENGHT );
}



static void fileData_Read_Reset( void )
{
	uint8_t Buffread[RESET_LENGHT + 1] = {0};
	Flash_Read( address_reset, Buffread, RESET_LENGHT );
	__fileData.ResetCount = (Buffread[0] << 8) | Buffread[1];
}



//write flags
static void fileData_Write_Flags( void )
{
	uint8_t Buffwrite[FLAGS_FLASH_LENGHT + 1] = {0};
	Buffwrite[0] = 1;

	Flash_Write_to_Page( address_flags, Buffwrite, FLAGS_FLASH_LENGHT );
}



static uint8_t fileData_Read_Flags( void )
{
	uint8_t Buffread[FLAGS_FLASH_LENGHT + 1] = {0};
	Flash_Read( address_flags, Buffread, FLAGS_FLASH_LENGHT );
	return Buffread[0];
}




//write sensor config
void fileData_Write_SensorCFG( void )
{
	uint8_t Buffwrite[SENSOR_CFG_FLASH_LENGHT + 1] = {0};
	Buffwrite[0] = (__fileData.SensorCfg >> 8) & 0xFF;
	Buffwrite[1] = __fileData.SensorCfg & 0xFF;

	Flash_Write_to_Page( address_sensor_cfg, Buffwrite, SENSOR_CFG_FLASH_LENGHT );
}



void fileData_Read_Sensor_CFG( void )
{
	uint8_t Buffread[SENSOR_CFG_FLASH_LENGHT + 1] = {0};
	Flash_Read( address_sensor_cfg, Buffread, SENSOR_CFG_FLASH_LENGHT );
	__fileData.SensorCfg = ((Buffread[0] << 8) | Buffread[1]);
}




//data update time
void fileData_Write_DataUT( void )
{
	uint8_t Buffwrite[DATA_UT_FLASH_LENGHT + 1] = {0};
	Buffwrite[0] = (__fileData.DataUT >> 8) & 0xFF;
	Buffwrite[1] = __fileData.DataUT & 0xFF;

	Flash_Write_to_Page( address_dataut, Buffwrite, DATA_UT_FLASH_LENGHT );
}


void fileData_Read_DataUT( void )
{
	uint8_t Buffread[DATA_UT_FLASH_LENGHT + 1] = {0};
	Flash_Read( address_dataut, Buffread, DATA_UT_FLASH_LENGHT );
	__fileData.DataUT = ((Buffread[0] << 8) | Buffread[1]);
}



//threshold temp air
void fileData_Write_Threshold_TempA( void )
{
	fileData_Write_Threshold_Component(address_threshold_temp_a, TEMP_A_FLASH_LENGHT, \
										__fileData.Threshold_TempA.Low, __fileData.Threshold_TempA.High);
}


void fileData_Read_Threshold_TempA( void )
{
	fileData_Read_Threshold_Component( address_threshold_temp_a, TEMP_A_FLASH_LENGHT, \
										&__fileData.Threshold_TempA.Low, &__fileData.Threshold_TempA.High );
}



//threshold humi air
void fileData_Write_Threshold_HumiA( void )
{
	fileData_Write_Threshold_Component(address_threshold_humi_a, HUMI_A_FLASH_LENGHT, \
										__fileData.Threshold_HumiA.Low, __fileData.Threshold_HumiA.High);
}


void fileData_Read_Threshold_HumiA( void )
{
	fileData_Read_Threshold_Component( address_threshold_humi_a, HUMI_A_FLASH_LENGHT, \
										&__fileData.Threshold_HumiA.Low, &__fileData.Threshold_HumiA.High );
}



//threshold temp soil
void fileData_Write_Threshold_TempS( void )
{
	fileData_Write_Threshold_Component(address_threshold_temp_s, TEMP_S_FLASH_LENGHT, \
										__fileData.Threshold_TempS.Low, __fileData.Threshold_TempS.High);
}


void fileData_Read_Threshold_TempS( void )
{
	fileData_Read_Threshold_Component( address_threshold_temp_s, TEMP_S_FLASH_LENGHT, \
										&__fileData.Threshold_TempS.Low, &__fileData.Threshold_TempS.High );
}



//threshold humi soil
void fileData_Write_Threshold_HumiS( void )
{
	fileData_Write_Threshold_Component(address_threshold_humi_s, HUMI_S_FLASH_LENGHT, \
										__fileData.Threshold_HumiS.Low, __fileData.Threshold_HumiS.High);
}


void fileData_Read_Threshold_HumiS( void )
{
	fileData_Read_Threshold_Component( address_threshold_humi_s, HUMI_S_FLASH_LENGHT, \
										&__fileData.Threshold_HumiS.Low, &__fileData.Threshold_HumiS.High );
}



//threshold pH
void fileData_Write_Threshold_PH( void )
{
	fileData_Write_Threshold_Component(address_threshold_ph, PH_FLASH_LENGHT, \
										__fileData.Threshold_pH.Low, __fileData.Threshold_pH.High);
}


void fileData_Read_Threshold_PH( void )
{
	fileData_Read_Threshold_Component( address_threshold_ph, PH_FLASH_LENGHT, \
										&__fileData.Threshold_pH.Low, &__fileData.Threshold_pH.High );
}



//threshold EC
void fileData_Write_Threshold_EC( void )
{
	fileData_Write_Threshold_Component(address_threshold_ec, EC_FLASH_LENGHT, \
										__fileData.Threshold_EC.Low, __fileData.Threshold_EC.High);
}


void fileData_Read_Threshold_EC( void )
{
	fileData_Read_Threshold_Component( address_threshold_ec, EC_FLASH_LENGHT, \
										&__fileData.Threshold_EC.Low, &__fileData.Threshold_EC.High );
}



//threshold light
void fileData_Write_Threshold_Light( void )
{
	fileData_Write_Threshold_Component(address_threshold_light, LIGHT_FLASH_LENGHT, \
										__fileData.Threshold_Light.Low, __fileData.Threshold_Light.High);
}


void fileData_Read_Threshold_Light( void )
{
	fileData_Read_Threshold_Component( address_threshold_light, LIGHT_FLASH_LENGHT, \
										&__fileData.Threshold_Light.Low, &__fileData.Threshold_Light.High );
}



//threshold CO2
void fileData_Write_Threshold_CO2( void )
{
	fileData_Write_Threshold_Component(address_threshold_co2, CO2_FLASH_LENGHT, \
										__fileData.Threshold_CO2.Low, __fileData.Threshold_CO2.High);
}


void fileData_Read_Threshold_CO2( void )
{
	fileData_Read_Threshold_Component( address_threshold_co2, CO2_FLASH_LENGHT, \
										&__fileData.Threshold_CO2.Low, &__fileData.Threshold_CO2.High );
}




static void fileData_Write_Threshold_Component( uint32_t addr, uint8_t Lenght, float Threshold_Low, float Threshold_High )
{
	uint8_t Buffwrite[24] = {0};
	Buffwrite[0] = ((uint32_t)Threshold_Low 	>> 24	) & 0xFF;
	Buffwrite[1] = ((uint32_t)Threshold_Low 	>> 16	) & 0xFF;
	Buffwrite[2] = ((uint32_t)Threshold_Low 	>> 8	) & 0xFF;
	Buffwrite[3] = ((uint32_t)Threshold_Low				) & 0xFF;
	Buffwrite[4] = ((uint32_t)Threshold_High 	>> 24	) & 0xFF;
	Buffwrite[5] = ((uint32_t)Threshold_High 	>> 16	) & 0xFF;
	Buffwrite[6] = ((uint32_t)Threshold_High 	>> 8	) & 0xFF;
	Buffwrite[7] = ((uint32_t)Threshold_High			) & 0xFF;

	Flash_Write_to_Page( addr, Buffwrite, Lenght );
}




static void fileData_Read_Threshold_Component( uint32_t addr, uint8_t Lenght, float *Threshold_Low, float *Threshold_High )
{
	uint8_t Buffread[24] = {0};
	Flash_Read( addr, Buffread, Lenght );
	*Threshold_High = (float)( (Buffread[0] << 24) | (Buffread[1] << 16) | (Buffread[2] << 8) | Buffread[3] );
	*Threshold_Low = (float)( (Buffread[4] << 24) | (Buffread[5] << 16) | (Buffread[6] << 8) | Buffread[7] );
}
























