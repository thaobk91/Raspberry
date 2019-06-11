/*
 * IOControl.c
 *
 *  Created on: Apr 24, 2019
 *      Author: Thao
 */
#include "IOControl.h"
#include "Interface/GPIO.h"


/******************************** WDT ********************************/
#define WDT_POWER_CONTROL_PIN				GPIO_PIN_1
#define WDT_POWER_CONTROL_PORT				GPIOA


/******************************* Power *******************************/
//input charger
#define CHRG_CHARGER_CONTROL_PIN			GPIO_PIN_8
#define CHRG_CHARGER_CONTROL_PORT			GPIOA

#define FAULT_CHARGER_CONTROL_PIN			GPIO_PIN_9
#define FAULT_CHARGER_CONTROL_PORT			GPIOC

//on/off battery charger
#define BATTERY_CHARGER_CONTROL_PIN			GPIO_PIN_8
#define BATTERY_CHARGER_CONTROL_PORT		GPIOC


/******************************* Lora ********************************/
#define LR_POWER_CONTROL_PIN				GPIO_PIN_10
#define LR_POWER_CONTROL_PORT				GPIOB


/****************************** Sensor *******************************/
//temp and humi soil sensor
#define SS_THS_POWER_CONTROL_PIN			GPIO_PIN_4
#define SS_THS_POWER_CONTROL_PORT			GPIOB

//EC
#define SS_EC_POWER_CONTROL_PIN				GPIO_PIN_13
#define SS_EC_POWER_CONTROL_PORT			GPIOC

//PH
#define SS_PH_POWER_CONTROL_PIN				GPIO_PIN_14
#define SS_PH_POWER_CONTROL_PORT			GPIOC

//CO2
#define SS_CO2_POWER_CONTROL_PIN			GPIO_PIN_6
#define SS_CO2_POWER_CONTROL_PORT			GPIOB

//Temp Anh humi + light
#define SS_THL_POWER_CONTROL_PIN			GPIO_PIN_7
#define SS_THL_POWER_CONTROL_PORT			GPIOB



/******************************** WDT ********************************/
void IOControl_WDT_Done( void )
{
	GPIO_setToggle( WDT_POWER_CONTROL_PORT, WDT_POWER_CONTROL_PIN );
}



/******************************* Power *******************************/
void IOControl_Battery_Charger_ON( void )
{
	GPIO_setLowlevel( BATTERY_CHARGER_CONTROL_PORT, BATTERY_CHARGER_CONTROL_PIN );
}


void IOControl_Battery_Charger_OFF( void )
{
	GPIO_setHighlevel( BATTERY_CHARGER_CONTROL_PORT, BATTERY_CHARGER_CONTROL_PIN );
}



/******************************* Lora ********************************/
void IOControl_Lora_ON( void )
{
	GPIO_setHighlevel( LR_POWER_CONTROL_PORT, LR_POWER_CONTROL_PIN );
}


void IOControl_Lora_OFF( void )
{
	GPIO_setLowlevel( LR_POWER_CONTROL_PORT, LR_POWER_CONTROL_PIN );
}



/****************************** Sensor *******************************/
//temp and humi soil sensor
void IOControl_SS_TH_Soil_ON( void )
{
	GPIO_setHighlevel( SS_THS_POWER_CONTROL_PORT, SS_THS_POWER_CONTROL_PIN );
}

void IOControl_SS_TH_Soil_OFF( void )
{
	GPIO_setLowlevel( SS_THS_POWER_CONTROL_PORT, SS_THS_POWER_CONTROL_PIN );
}


//EC
void IOControl_SS_EC_ON( void )
{
	GPIO_setHighlevel( SS_EC_POWER_CONTROL_PORT, SS_EC_POWER_CONTROL_PIN );
}

void IOControl_SS_EC_OFF( void )
{
	GPIO_setLowlevel( SS_EC_POWER_CONTROL_PORT, SS_EC_POWER_CONTROL_PIN );
}


//PH
void IOControl_SS_PH_ON( void )
{
	GPIO_setHighlevel( SS_PH_POWER_CONTROL_PORT, SS_PH_POWER_CONTROL_PIN );
}

void IOControl_SS_PH_OFF( void )
{
	GPIO_setLowlevel( SS_PH_POWER_CONTROL_PORT, SS_PH_POWER_CONTROL_PIN );
}


//CO2
void IOControl_SS_CO2_ON( void )
{
	GPIO_setHighlevel( SS_CO2_POWER_CONTROL_PORT, SS_CO2_POWER_CONTROL_PIN );
}

void IOControl_SS_CO2_OFF( void )
{
	GPIO_setLowlevel( SS_CO2_POWER_CONTROL_PORT, SS_CO2_POWER_CONTROL_PIN );
}


//Temp Anh humi + light
void IOControl_SS_THL_ON( void )
{
	GPIO_setHighlevel( SS_THL_POWER_CONTROL_PORT, SS_THL_POWER_CONTROL_PIN );
}

void IOControl_SS_THL_OFF( void )
{
	GPIO_setLowlevel( SS_THL_POWER_CONTROL_PORT, SS_THL_POWER_CONTROL_PIN );
}



void IOControl_Init( void )
{
	/******************************** WDT ********************************/
	GPIO_setOutput_Pulldown( WDT_POWER_CONTROL_PORT, WDT_POWER_CONTROL_PIN );

	/******************************* Power *******************************/
	//input charger
	GPIO_setInput( CHRG_CHARGER_CONTROL_PORT, CHRG_CHARGER_CONTROL_PIN );
	GPIO_setInput( FAULT_CHARGER_CONTROL_PORT, FAULT_CHARGER_CONTROL_PIN );

	//on/off battery charger
	IOControl_Battery_Charger_ON();


	/******************************* Lora ********************************/
	GPIO_setOutput_Pulldown( LR_POWER_CONTROL_PORT, LR_POWER_CONTROL_PIN );
	IOControl_Lora_ON();

	/****************************** Sensor *******************************/
	//temp and humi soil sensor
	GPIO_setOutput_Pulldown( SS_THS_POWER_CONTROL_PORT, SS_THS_POWER_CONTROL_PIN );
	IOControl_SS_TH_Soil_OFF();

	//EC
	GPIO_setOutput_Pulldown( SS_EC_POWER_CONTROL_PORT, SS_EC_POWER_CONTROL_PIN );
	IOControl_SS_EC_OFF();

	//PH
	GPIO_setOutput_Pulldown( SS_PH_POWER_CONTROL_PORT, SS_PH_POWER_CONTROL_PIN );
	IOControl_SS_PH_OFF();

	//CO2
	GPIO_setOutput_Pulldown( SS_CO2_POWER_CONTROL_PORT, SS_CO2_POWER_CONTROL_PIN );
	IOControl_SS_CO2_OFF();

	//Temp Anh humi + light
	GPIO_setOutput_Pulldown( SS_THL_POWER_CONTROL_PORT, SS_THL_POWER_CONTROL_PIN );
	IOControl_SS_THL_OFF();
}















