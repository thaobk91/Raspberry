/*
 * SS_PH.c
 *
 *  Created on: Mar 22, 2019
 *      Author: thaonm1
 */
#include "SS_PH.h"
#include "../Interface/ADC.h"
#include "../main.h"


#define ADC_PH_VOUT_CHANNEL				ADC_CHANNEL_1
#define ADC_PH_VCOM_CHANNEL				ADC_CHANNEL_2

#define ADC_PH_REF						2048	//mV


//calib: y = ax2 + bx + c (y la gia tri thuc)
#define CALIB_PH_A_PARAM				(-0.12165)
#define CALIB_PH_B_PARAM				(3.5821)
#define CALIB_PH_C_PARAM				(-12.244816)



ADC_HandleTypeDef ADC_PH_Handle;




void SS_PH_Init( void )
{
	ADC_Init( &ADC_PH_Handle );
}



float SS_PH_Read( void )
{
	float pH = 0;
	uint32_t PH_VOut = 0, PH_VCom = 0;

	for(uint8_t ui = 0; ui < 5; ui++)
	{
		float pH_value = 0;
		ADC_SetChannel( &ADC_PH_Handle, ADC_PH_VOUT_CHANNEL );
		ADC_ReadValue( &ADC_PH_Handle, &PH_VOut );

		ADC_SetChannel( &ADC_PH_Handle, ADC_PH_VCOM_CHANNEL );
		ADC_ReadValue( &ADC_PH_Handle, &PH_VCom );

		APP_DEBUG("--- SS_PH: PH_Vout = %ld [mV], PH_VCom = %ld [mV]\r\n", PH_VOut, PH_VCom);

		int32_t value = PH_VOut - PH_VCom;
		pH_value = (float)(7 - ((value * 2048 / 4096) / (59.16)));
		pH += pH_value;
		osDelay(100);
	}
	pH /= 5;
	pH = (CALIB_PH_A_PARAM * pH * pH) + (CALIB_PH_B_PARAM * pH) +  CALIB_PH_C_PARAM;

	return pH;
}



























