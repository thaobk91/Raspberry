/*
 * EDC.h
 *
 *  Created on: Jan 21, 2019
 *      Author: ThaoHuyen
 */

#ifndef SOURCE_MESSAGE_EDC_H_
#define SOURCE_MESSAGE_EDC_H_

#include <stdint.h>



/*******************************************************************************
 * Function		: uint8_t *EDC_Encode( uint8_t *Ptr_In, uint16_t *Lenght )
 * Description	: Encode string
 * Param		:
 * 				+ Ptr_In - string input
 * 				+ Lenght - lenght of string decode
 * Return		: string output
 * ****************************************************************************/
uint8_t *EDC_Encode( uint8_t *Ptr_In, uint16_t *Lenght );




/*******************************************************************************
 * Function		: uint8_t *EDC_Decode( uint8_t *Ptr_In, uint16_t *Lenght )
 * Description	: Decode string
 * Param		:
 * 				+ Ptr_In - string input
 * 				+ Lenght - lenght of string decode
 * Return		: string output
 * ****************************************************************************/
uint8_t *EDC_Decode( uint8_t *Ptr_In, uint16_t *Lenght );


#endif /* SOURCE_MESSAGE_EDC_H_ */


















