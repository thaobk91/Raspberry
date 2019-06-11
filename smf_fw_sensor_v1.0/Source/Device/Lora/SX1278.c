
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "SX1278.h"




static void SX1278_HW_Init( Lora_SX1278_t *__Lora_SX1278 );
static void SX1278_HW_SetNSS( Lora_SX1278_t *__Lora_SX1278, int Value );
static void SX1278_HW_Reset( Lora_SX1278_t *__Lora_SX1278 );
static int SX1278_HW_GetDIO0( Lora_SX1278_t *__Lora_SX1278 );
static bool SX1278_Wait_SPIReady( Lora_SX1278_t *__Lora_SX1278, uint32_t Timeout_ms );
static uint8_t SX1278_SPIReadByte( Lora_SX1278_t *__Lora_SX1278, uint8_t addr);
static void SX1278_SPIWrite( Lora_SX1278_t *__Lora_SX1278, uint8_t addr, uint8_t cmd );
static void SX1278_SPIBurstRead( Lora_SX1278_t *__Lora_SX1278, uint8_t addr, uint8_t* rxBuf, uint8_t length );
static void SX1278_SPIBurstWrite( Lora_SX1278_t *__Lora_SX1278, uint8_t addr, uint8_t* txBuf, uint8_t length );
static void SX1278_defaultConfig( Lora_SX1278_t *__Lora_SX1278 );


void SX1278_Standby( Lora_SX1278_t *__Lora_SX1278 );
void SX1278_Sleep( Lora_SX1278_t *__Lora_SX1278 );
void SX1278_entryLoRa( Lora_SX1278_t *__Lora_SX1278 ) ;




static void SX1278_HW_Init( Lora_SX1278_t *__Lora_SX1278 ) 
{
	SX1278_HW_SetNSS( __Lora_SX1278, 1 );
	__Lora_SX1278->HW_GPIO_Set_Pin( __Lora_SX1278->HW.Reset.Port, __Lora_SX1278->HW.Reset.Pin );
}



static void SX1278_HW_SetNSS( Lora_SX1278_t *__Lora_SX1278, int Value ) 
{
	if(Value == 1)
		__Lora_SX1278->HW_GPIO_Set_Pin( __Lora_SX1278->HW.NSS.Port, __Lora_SX1278->HW.NSS.Pin );
	else
		__Lora_SX1278->HW_GPIO_Reset_Pin( __Lora_SX1278->HW.NSS.Port, __Lora_SX1278->HW.NSS.Pin );
}



static void SX1278_HW_Reset( Lora_SX1278_t *__Lora_SX1278 ) 
{
	SX1278_HW_SetNSS( __Lora_SX1278, 1 );
	__Lora_SX1278->HW_GPIO_Reset_Pin( __Lora_SX1278->HW.Reset.Port, __Lora_SX1278->HW.Reset.Pin );
	__Lora_SX1278->SX1278_Delay_ms(100);
	__Lora_SX1278->HW_GPIO_Set_Pin( __Lora_SX1278->HW.Reset.Port, __Lora_SX1278->HW.Reset.Pin );
	__Lora_SX1278->SX1278_Delay_ms(100);
}



static int SX1278_HW_GetDIO0( Lora_SX1278_t *__Lora_SX1278 ) 
{
	return __Lora_SX1278->HW_GPIO_Read_Pin( __Lora_SX1278->HW.DIO_0.Port, __Lora_SX1278->HW.DIO_0.Pin );
}



static bool SX1278_Wait_SPIReady( Lora_SX1278_t *__Lora_SX1278, uint32_t Timeout_ms )
{
	uint32_t TimeCount = 0;

	while( TimeCount < (Timeout_ms * 1000) )
	{
		TimeCount++;
		if( __Lora_SX1278->HW_SPI_State_Ready() == true )
			return true;
		__Lora_SX1278->SX1278_Delay_us(1);
	}
	return false;
}



static uint8_t SX1278_SPIReadByte( Lora_SX1278_t *__Lora_SX1278, uint8_t addr) 
{
	uint8_t tmp;
	
	SX1278_HW_SetNSS( __Lora_SX1278, 0 );
	__Lora_SX1278->HW_SPI_WriteByte( addr, 0xffff );
	SX1278_Wait_SPIReady( __Lora_SX1278, 3000 );
	tmp = __Lora_SX1278->HW_SPI_ReadByte( 0xffff );
	SX1278_Wait_SPIReady( __Lora_SX1278, 3000 );
	SX1278_HW_SetNSS( __Lora_SX1278, 1);
	return tmp;
}



static void SX1278_SPIWrite( Lora_SX1278_t *__Lora_SX1278, uint8_t addr, uint8_t cmd ) 
{
	SX1278_HW_SetNSS( __Lora_SX1278, 0 );
	
	__Lora_SX1278->HW_SPI_WriteByte( addr | 0x80, 0xffff );
	SX1278_Wait_SPIReady( __Lora_SX1278, 3000 );
	__Lora_SX1278->HW_SPI_WriteByte( cmd, 0xffff );
	SX1278_Wait_SPIReady( __Lora_SX1278, 3000 );
	
	SX1278_HW_SetNSS( __Lora_SX1278, 1);
}



static void SX1278_SPIBurstRead( Lora_SX1278_t *__Lora_SX1278, uint8_t addr, uint8_t* rxBuf, uint8_t length ) 
{
	uint8_t i;
	
	if (length <= 1) 
	{
		return;
	} 
	else 
	{
		SX1278_HW_SetNSS( __Lora_SX1278, 0 );
		__Lora_SX1278->HW_SPI_WriteByte( addr, 0xffff );
		SX1278_Wait_SPIReady( __Lora_SX1278, 3000 );
		
		for (i = 0; i < length; i++) 
			*(rxBuf + i) = __Lora_SX1278->HW_SPI_ReadByte( 0xffff );
		SX1278_HW_SetNSS( __Lora_SX1278, 1 );
	}
}



static void SX1278_SPIBurstWrite( Lora_SX1278_t *__Lora_SX1278, uint8_t addr, uint8_t* txBuf, uint8_t length ) 
{
	unsigned char i;
	
	if (length <= 1) 
	{
		return;
	} 
	else 
	{
		SX1278_HW_SetNSS( __Lora_SX1278, 0 );
		__Lora_SX1278->HW_SPI_WriteByte( addr | 0x80, 0xffff );
		SX1278_Wait_SPIReady( __Lora_SX1278, 3000 );

		for (i = 0; i < length; i++) 
		{
			__Lora_SX1278->HW_SPI_WriteByte( *(txBuf + i), 0xffff );
			SX1278_Wait_SPIReady( __Lora_SX1278, 3000 );
		}
		SX1278_HW_SetNSS( __Lora_SX1278, 1 );
	}
}



//////////////////////////////////
// logic
//////////////////////////////////
void SX1278_defaultConfig( Lora_SX1278_t *__Lora_SX1278 )
{
	SX1278_Sleep( __Lora_SX1278 ); //Change modem mode Must in Sleep mode
	__Lora_SX1278->SX1278_Delay_ms(15);
	SX1278_entryLoRa( __Lora_SX1278 );

	//setting  frequency parameter
	SX1278_SPIBurstWrite( __Lora_SX1278, LR_RegFrMsb, (uint8_t *)SX1278_Frequency[__Lora_SX1278->Cfg.Frequency], 3 );

	//setting base parameter
	SX1278_SPIWrite( __Lora_SX1278, LR_RegPaConfig, SX1278_Power[__Lora_SX1278->Cfg.Power] );	//Setting output power parameter
	SX1278_SPIWrite( __Lora_SX1278, LR_RegOcp, 0x0B );			//RegOcp,Close Ocp
	SX1278_SPIWrite( __Lora_SX1278, LR_RegLna, 0x23 );			//RegLNA,High & LNA Enable
	
	if (SX1278_SpreadFactor[__Lora_SX1278->Cfg.LoRa_Rate] == 6)	//SFactor=6
	{	
		uint8_t tmp;
		SX1278_SPIWrite( __Lora_SX1278, LR_RegModemConfig1, \
						((SX1278_LoRaBandwidth[__Lora_SX1278->Cfg.LoRa_BW] << 4) + (SX1278_CR << 1) + 0x01) );//Implicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
		SX1278_SPIWrite( __Lora_SX1278, LR_RegModemConfig2, \
						((SX1278_SpreadFactor[__Lora_SX1278->Cfg.LoRa_Rate] << 4) + (SX1278_CRC << 2) + 0x03) );

		tmp = SX1278_SPIReadByte( __Lora_SX1278, 0x31);
		tmp &= 0xF8;
		tmp |= 0x05;
		SX1278_SPIWrite( __Lora_SX1278, 0x31, tmp );
		SX1278_SPIWrite( __Lora_SX1278, 0x37, 0x0C );
	} 
	else 
	{
		SX1278_SPIWrite( __Lora_SX1278, LR_RegModemConfig1, \
						((SX1278_LoRaBandwidth[__Lora_SX1278->Cfg.LoRa_BW] << 4) + (SX1278_CR << 1) + 0x00) );//Explicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
		SX1278_SPIWrite( __Lora_SX1278, LR_RegModemConfig2, \
						((SX1278_SpreadFactor[__Lora_SX1278->Cfg.LoRa_Rate] << 4) + (SX1278_CRC << 2) + 0x03) );//SFactor &  LNA gain set by the internal AGC loop
	}

	SX1278_SPIWrite( __Lora_SX1278, LR_RegSymbTimeoutLsb, 0xFF );		//RegSymbTimeoutLsb Timeout = 0x3FF(Max)
	SX1278_SPIWrite( __Lora_SX1278, LR_RegPreambleMsb, 0x00 );			//RegPreambleMsb
	SX1278_SPIWrite( __Lora_SX1278, LR_RegPreambleLsb, 12 );			//RegPreambleLsb 8+4=12byte Preamble
	SX1278_SPIWrite( __Lora_SX1278, REG_LR_DIOMAPPING2, 0x01 );			//RegDioMapping2 DIO5=00, DIO4=01
	__Lora_SX1278->Cfg.rxBuffer_Lenght = 0;
	SX1278_Standby( __Lora_SX1278 ); //Entry standby mode
}




void SX1278_Init( Lora_SX1278_t *__Lora_SX1278 ) 
{
	__Lora_SX1278->HW_GPIO_Init_Pin_Output( __Lora_SX1278->HW.Reset.Port, __Lora_SX1278->HW.Reset.Pin );
	__Lora_SX1278->HW_GPIO_Init_Pin_Output( __Lora_SX1278->HW.NSS.Port, __Lora_SX1278->HW.NSS.Pin );
	__Lora_SX1278->HW_GPIO_Init_Pin_Input( __Lora_SX1278->HW.DIO_0.Port, __Lora_SX1278->HW.DIO_0.Pin );
	SX1278_HW_Init( __Lora_SX1278 );
	__Lora_SX1278->HW_SPI_Init();
	SX1278_defaultConfig( __Lora_SX1278 );
}



void SX1278_Standby( Lora_SX1278_t *__Lora_SX1278 ) 
{
	SX1278_SPIWrite( __Lora_SX1278, LR_RegOpMode, 0x09 );
	__Lora_SX1278->Cfg.Status = STANDBY;
}



void SX1278_Sleep( Lora_SX1278_t *__Lora_SX1278 ) 
{
	SX1278_SPIWrite( __Lora_SX1278, LR_RegOpMode, 0x08 );
	__Lora_SX1278->Cfg.Status = SLEEP;
}



void SX1278_entryLoRa( Lora_SX1278_t *__Lora_SX1278 ) 
{
	SX1278_SPIWrite( __Lora_SX1278, LR_RegOpMode, 0x88 );
}



void SX1278_ClearLoRaIrq( Lora_SX1278_t *__Lora_SX1278 )
{
	SX1278_SPIWrite( __Lora_SX1278, LR_RegIrqFlags, 0xFF );
}



bool SX1278_LoRaEntryRx( Lora_SX1278_t *__Lora_SX1278, uint16_t Length, uint32_t Timeout) 
{
	uint8_t addr;

	__Lora_SX1278->Cfg.packetLength = Length;

	//SX1278_defaultConfig( __Lora_SX1278 );		//Setting base parameter
	SX1278_SPIWrite( __Lora_SX1278, REG_LR_PADAC, 0x84 );		//Normal and RX
	SX1278_SPIWrite( __Lora_SX1278, LR_RegHopPeriod, 0xFF );	//No FHSS
	SX1278_SPIWrite( __Lora_SX1278, REG_LR_DIOMAPPING1, 0x01 );	//DIO=00,DIO1=00,DIO2=00, DIO3=01
	SX1278_SPIWrite( __Lora_SX1278, LR_RegIrqFlagsMask, 0x3F );	//Open RxDone interrupt & Timeout
	SX1278_ClearLoRaIrq( __Lora_SX1278 );
	SX1278_SPIWrite( __Lora_SX1278, LR_RegPayloadLength, LR_RegPayloadLength );//Payload Length 21byte(this register must difine when the data long of one byte in SF is 6)
	
	addr = SX1278_SPIReadByte( __Lora_SX1278, LR_RegFifoRxBaseAddr);//Read RxBaseAddr
	SX1278_SPIWrite( __Lora_SX1278, LR_RegFifoAddrPtr, addr );		//RxBaseAddr->FiFoAddrPtr
	SX1278_SPIWrite( __Lora_SX1278, LR_RegOpMode, 0x8d );			//Mode//Low Frequency Mode
	//SX1278_SPIWrite(module, LR_RegOpMode,0x05);	//Continuous Rx Mode //High Frequency Mode
	__Lora_SX1278->Cfg.rxBuffer_Lenght = 0;

	while (1) 
	{
		if( (SX1278_SPIReadByte( __Lora_SX1278, LR_RegModemStat) & 0x04) == 0x04 ) //Rx-on going RegModemStat
		{	
			__Lora_SX1278->Cfg.Status = RX;
			return true;
		}
		
		if(--Timeout == 0) 
		{
			SX1278_HW_Reset( __Lora_SX1278 );
			SX1278_defaultConfig( __Lora_SX1278 );
			return false;
		}
		__Lora_SX1278->SX1278_Delay_ms(1);
	}
}



uint16_t SX1278_LoRaRxPacket( Lora_SX1278_t *__Lora_SX1278 ) 
{
	unsigned char addr;
	unsigned char packet_size;

	if( SX1278_HW_GetDIO0( __Lora_SX1278 ) ) 
	{
		memset( __Lora_SX1278->Cfg.rxBuffer, 0x00, __Lora_SX1278->Cfg.rxBuffer_Lenght);

		addr = SX1278_SPIReadByte( __Lora_SX1278, LR_RegFifoRxCurrentaddr);//last packet addr
		SX1278_SPIWrite( __Lora_SX1278, LR_RegFifoAddrPtr, addr );		//RxBaseAddr -> FiFoAddrPtr

		if( __Lora_SX1278->Cfg.LoRa_Rate == SX1278_LORA_SF_6 ) //When SpreadFactor is six,will used Implicit Header mode(Excluding internal packet length)
			packet_size = __Lora_SX1278->Cfg.packetLength;
		else 
			packet_size = SX1278_SPIReadByte( __Lora_SX1278, LR_RegRxNbBytes);	//Number for received bytes
		
		SX1278_SPIBurstRead( __Lora_SX1278, 0x00, __Lora_SX1278->Cfg.rxBuffer, packet_size );
		__Lora_SX1278->Cfg.rxBuffer_Lenght = packet_size;
		SX1278_ClearLoRaIrq( __Lora_SX1278 );
	}
	return __Lora_SX1278->Cfg.rxBuffer_Lenght;
}



bool SX1278_LoRaEntryTx( Lora_SX1278_t *__Lora_SX1278, uint16_t Length, uint32_t Timeout ) 
{
	uint8_t addr;
	uint8_t temp;

	__Lora_SX1278->Cfg.packetLength = Length;

//	SX1278_defaultConfig( __Lora_SX1278 ); //setting base parameter
	SX1278_SPIWrite( __Lora_SX1278, REG_LR_PADAC, 0x87 );		//Tx for 20dBm
	SX1278_SPIWrite( __Lora_SX1278, LR_RegHopPeriod, 0x00 );	//RegHopPeriod NO FHSS
	SX1278_SPIWrite( __Lora_SX1278, REG_LR_DIOMAPPING1, 0x41 );	//DIO0=01, DIO1=00,DIO2=00, DIO3=01
	SX1278_ClearLoRaIrq( __Lora_SX1278 );
	SX1278_SPIWrite( __Lora_SX1278, LR_RegIrqFlagsMask, 0xF7 );	//Open TxDone interrupt
	SX1278_SPIWrite( __Lora_SX1278, LR_RegPayloadLength, Length );//RegPayloadLength 21byte
	
	addr = SX1278_SPIReadByte( __Lora_SX1278, LR_RegFifoTxBaseAddr);//RegFiFoTxBaseAddr
	SX1278_SPIWrite( __Lora_SX1278, LR_RegFifoAddrPtr, addr );	//RegFifoAddrPtr

	while (1) 
	{
		temp = SX1278_SPIReadByte( __Lora_SX1278, LR_RegPayloadLength);
		if (temp == Length) 
		{
			__Lora_SX1278->Cfg.Status = TX;
			return true;
		}

		if (--Timeout == 0) 
		{
			SX1278_HW_Reset( __Lora_SX1278 );
			SX1278_defaultConfig( __Lora_SX1278 );
			return false;
		}
	}
}



bool SX1278_LoRaTxPacket( Lora_SX1278_t *__Lora_SX1278, uint8_t* txBuffer, uint16_t Length, uint32_t Timeout ) 
{ 
	SX1278_SPIBurstWrite( __Lora_SX1278, 0x00, txBuffer, Length );
	SX1278_SPIWrite( __Lora_SX1278, LR_RegOpMode, 0x8b );		//Tx Mode
	
	while (1)
	{
		if ( SX1278_HW_GetDIO0( __Lora_SX1278 ) ) //Packet send over
		{ 
			SX1278_SPIReadByte( __Lora_SX1278, LR_RegIrqFlags);
			SX1278_ClearLoRaIrq( __Lora_SX1278 ); //Clear irq
			SX1278_Standby( __Lora_SX1278 ); //Entry Standby mode
			return true;
		}

		if (--Timeout == 0) 
		{
			SX1278_HW_Reset( __Lora_SX1278 );
			SX1278_defaultConfig( __Lora_SX1278 );
			return false;
		}
		__Lora_SX1278->SX1278_Delay_ms(1);
	}
}



bool SX1278_Transmit( Lora_SX1278_t *__Lora_SX1278, uint8_t* txBuf, uint16_t Length, uint32_t Timeout) 
{
	if( SX1278_LoRaEntryTx( __Lora_SX1278, Length, Timeout) == true )
		return SX1278_LoRaTxPacket( __Lora_SX1278, txBuf, Length, Timeout );

	return false;
}



bool SX1278_Receive( Lora_SX1278_t *__Lora_SX1278, uint8_t* rxBuf, uint16_t *RXBuffer_Lenght )
{
	__Lora_SX1278->Cfg.rxBuffer_Lenght = 0;
	if( (*RXBuffer_Lenght = SX1278_LoRaRxPacket( __Lora_SX1278 )) > 0 )
	{
		//memset(rxBuf, 0, strlen((char *)rxBuf));
		if (*RXBuffer_Lenght != __Lora_SX1278->Cfg.rxBuffer_Lenght)
			*RXBuffer_Lenght = __Lora_SX1278->Cfg.rxBuffer_Lenght;
		memcpy(rxBuf, __Lora_SX1278->Cfg.rxBuffer, *RXBuffer_Lenght);
		rxBuf[*RXBuffer_Lenght] = '\0';
		//__Lora_SX1278->Cfg.rxBuffer_Lenght = 0;
		return true;
	}
	return false;
}



uint8_t SX1278_RSSI_LoRa( Lora_SX1278_t *__Lora_SX1278 ) 
{
	uint32_t temp = 10;
	
	temp = SX1278_SPIReadByte( __Lora_SX1278, LR_RegRssiValue); //Read RegRssiValue, Rssi value
	temp = temp + 127 - 137; //127:Max RSSI, 137:RSSI offset
	return (uint8_t) temp;
}



uint8_t SX1278_RSSI( Lora_SX1278_t *__Lora_SX1278 ) 
{
	uint8_t temp = 0xff;
	temp = SX1278_SPIReadByte( __Lora_SX1278, 0x11);
	temp = 127 - (temp >> 1);	//127:Max RSSI
	return temp;
}













