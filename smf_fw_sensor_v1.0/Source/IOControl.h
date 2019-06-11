/*
 * IOControl.h
 *
 *  Created on: Apr 24, 2019
 *      Author: Thao
 */

#ifndef IOCONTROL_H_
#define IOCONTROL_H_



void IOControl_Init( void );


/******************************** WDT ********************************/
void IOControl_WDT_Done( void );


/******************************* Power *******************************/
void IOControl_Battery_Charger_ON( void );
void IOControl_Battery_Charger_OFF( void );


/******************************* Lora ********************************/
void IOControl_Lora_ON( void );
void IOControl_Lora_OFF( void );


/****************************** Sensor *******************************/
//temp and humi soil sensor
void IOControl_SS_TH_Soil_ON( void );
void IOControl_SS_TH_Soil_OFF( void );


//EC
void IOControl_SS_EC_ON( void );
void IOControl_SS_EC_OFF( void );


//PH
void IOControl_SS_PH_ON( void );
void IOControl_SS_PH_OFF( void );


//CO2
void IOControl_SS_CO2_ON( void );
void IOControl_SS_CO2_OFF( void );


//Temp Anh humi + light
void IOControl_SS_THL_ON( void );
void IOControl_SS_THL_OFF( void );


#endif /* IOCONTROL_H_ */









