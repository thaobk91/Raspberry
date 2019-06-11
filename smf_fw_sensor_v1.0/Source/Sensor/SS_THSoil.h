/*
 * THMoisture.h
 *
 *  Created on: Mar 22, 2019
 *      Author: thaonm1
 */

#ifndef __SS_TH_SOIL_H_
#define __SS_TH_SOIL_H_

#include <stdint.h>



/******************************************************************************
 * Function		: void SS_THSoil_Read( float *Temp, float *Humi )
 * Description	: read temp and humi soil
 * Parameter	:
 * 				+ Temp: temperature
 * 				+ Humi: humidity
 * Return		: None
 *****************************************************************************/
void SS_THSoil_Read( float *Temp, float *Humi );


#endif /* __SS_TH_SOIL_H_ */
