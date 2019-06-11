/*
 * EDC.c
 *
 *  Created on: Jan 21, 2019
 *      Author: ThaoHuyen
 */
#include <stdlib.h>
#include "EDC.h"


const char Key[9] = "123@!xyz";



static void EDC_EncodeByKey( uint8_t In, uint8_t *Out, uint8_t KeyBit1, uint8_t KeyBit2 )
{
	int8_t Value = 0;
	*Out = 0;

	if( KeyBit1 == 1 )
	{
		Value = ((In >> 4) & 0xF) + 1;
		if(Value > 15)
			Value = 0;
		*Out |= (Value << 4);
	}
	else
	{
		Value = ((In >> 4) & 0xF) - 1;
		if(Value < 0)
			Value = 15;
		*Out |= (Value << 4);
	}

	if( KeyBit2 == 1 )
	{
		Value = (In & 0xF) + 1;
		if(Value > 15)
			Value = 0;
		*Out |= (Value & 0xF);
	}
	else
	{
		Value = (In & 0xF) - 1;
		if(Value < 0)
			Value = 15;
		*Out |= (Value & 0xF);
	}
}




static void EDC_DecodeByKey( uint8_t In, uint8_t *Out, uint8_t KeyBit1, uint8_t KeyBit2 )
{
	int8_t Value = 0;
	*Out = 0;

	if( KeyBit1 == 1 )
	{
		Value = (In >> 4) & 0xF;
		if(Value == 0)
			Value = 15;
		else
			Value = Value - 1;
		*Out |= (Value << 4);
	}
	else
	{
		Value = (In >> 4) & 0xF;
		if(Value == 15)
			Value = 0;
		else
			Value = Value + 1;
		*Out |= (Value << 4);
	}

	if( KeyBit2 == 1 )
	{
		Value = In & 0xF;
		if(Value == 0)
			Value = 15;
		else
			Value = Value - 1;
		*Out |= (Value & 0xF);
	}
	else
	{
		Value = In & 0xF;
		if(Value == 15)
			Value = 0;
		else
			Value = Value + 1;
		*Out |= (Value & 0xF);
	}
}





/*******************************************************************************
 * Function		: uint8_t *EDC_Encode( uint8_t *Ptr_In, uint16_t *Lenght )
 * Description	: Encode string
 * Param		:
 * 				+ Ptr_In - string input
 * 				+ Lenght - lenght of string decode
 * Return		: string output
 * ****************************************************************************/
uint8_t *EDC_Encode( uint8_t *Ptr_In, uint16_t *Lenght )
{
	uint16_t Char_Count = 0;
	uint16_t Key_Count = 0;
	uint8_t *ptr = malloc(*Lenght + 1);
	uint8_t Out_Value = 0;
	uint16_t sLenght = 0;

	for( sLenght = 0; sLenght < *Lenght; sLenght += 4 )
	{
		for( uint8_t ui = 0; ui < 8; ui+=2 )
		{
			EDC_EncodeByKey( *Ptr_In++, &Out_Value, (Key[Key_Count] >> (7 - ui)) & 0x01, (Key[Key_Count] >> (7 - ui - 1)) & 0x01 );
				ptr[Char_Count++] = Out_Value;
			if(Char_Count >= *Lenght)
				goto EndEndcode;
		}

		Key_Count++;
		if(Key_Count >= 8)
			Key_Count = 0;
	}
	EndEndcode:;
	*Lenght = Char_Count;
	ptr[Char_Count] = '\0';

	return ptr;
}




/*******************************************************************************
 * Function		: uint8_t *EDC_Decode( uint8_t *Ptr_In, uint16_t *Lenght )
 * Description	: Decode string
 * Param		:
 * 				+ Ptr_In - string input
 * 				+ Lenght - lenght of string decode
 * Return		: string output
 * ****************************************************************************/
uint8_t *EDC_Decode( uint8_t *Ptr_In, uint16_t *Lenght )
{
	uint16_t Char_Count = 0;
	uint16_t Key_Count = 0;
	uint8_t *ptr = malloc(*Lenght + 1);
	uint8_t Out_Value = 0;
	uint16_t sLenght = 0;

	for( sLenght = 0; sLenght < *Lenght; sLenght += 4 )
	{
		for( uint8_t ui = 0; ui < 8; ui+=2 )
		{
			EDC_DecodeByKey( *Ptr_In++, &Out_Value, (Key[Key_Count] >> (7 - ui)) & 0x01, (Key[Key_Count] >> (7 - ui - 1)) & 0x01 );
				ptr[Char_Count++] = Out_Value;
			if(Char_Count >= *Lenght)
				goto EndDedcode;
		}

		Key_Count++;
		if(Key_Count >= 8)
			Key_Count = 0;
	}
	EndDedcode:;
	*Lenght = Char_Count;
	ptr[Char_Count] = '\0';

	return ptr;
}























