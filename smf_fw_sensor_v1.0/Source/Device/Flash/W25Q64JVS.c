
#include <stdlib.h>
#include <string.h>

#include "W25Q64JVS.h"


static void W25Q64JVS_SetWriteEnable( W25Q64JVS_Data_t *__W25Q64JVS_Data );
static bool W25Q64JVS_IsBusy( W25Q64JVS_Data_t *__W25Q64JVS_Data );



/******************************************************************************
 * Function		: void W25Q64JVS_Init( W25Q64JVS_Data_t *__W25Q64JVS_Data )
 * Description	: flash init
 * Param		:
 * Return		: None
*******************************************************************************/
void W25Q64JVS_Init( W25Q64JVS_Data_t *__W25Q64JVS_Data )
{
	__W25Q64JVS_Data->GPIO_setOutput_Dir( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
	__W25Q64JVS_Data->SPI_Init();
	while(__W25Q64JVS_Data->SPI_Ready() == false)
	{
		//__W25Q64JVS_Data->debug("--- W25Q64JVS: spi not ready\r\n");
		__W25Q64JVS_Data->Delay_ms(1000);
	}

	__W25Q64JVS_Data->GPIO_setOutput_LowLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
	__W25Q64JVS_Data->Delay_ms(100);
	__W25Q64JVS_Data->GPIO_setOutput_HighLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
}




/******************************************************************************
 * Function		: bool W25Q64JVS_CheckConnection( W25Q64JVS_Data_t *__W25Q64JVS_Data )
 * Description	: Ham kiem tra ket noi den flash
 * Param		: 
 * Return		: 
 *				+ true: connection ok
 *				+ false: connection fail
*******************************************************************************/
bool W25Q64JVS_CheckConnection( W25Q64JVS_Data_t *__W25Q64JVS_Data )
{
	uint8_t uBuffer[4] = {0};

	__W25Q64JVS_Data->GPIO_setOutput_LowLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
	uint8_t value = macroW25Q64JVS_JEDECID;
	__W25Q64JVS_Data->SPI_Write_Bytes( &value, 1 );
	__W25Q64JVS_Data->SPI_Read_Bytes( uBuffer, 3 );
	__W25Q64JVS_Data->GPIO_setOutput_HighLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );

	__W25Q64JVS_Data->debug("--- %s: flash id = %x%x\r\n", __FILE__, uBuffer[1], uBuffer[2]);
    
	if ((uBuffer[1] == 0x40) && (uBuffer[2] == 0x17))
        return true;
    return false;
}

		


/******************************************************************************
 * Function		: void W25Q64JVS_Read( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t addr, uint8_t *uBuffer, uint16_t Lenght )
 * Description	: Ham doc du lieu tu flash
 * Param		: 
 *				+ addr: Dia chi du lieu
 *				+ uBuffer: Bo dem chua du lieu duoc doc
 *				+ Length: do dai du lieu doc ra
 * Return		: none
*******************************************************************************/
void W25Q64JVS_Read( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t addr, uint8_t *uBuffer, uint16_t Lenght )
{
	uint8_t txBuffer[5] = {0};

	__W25Q64JVS_Data->GPIO_setOutput_LowLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
	//Truyen lenh doc va 24bit dia chi can doc du lieu
	txBuffer[0] = macroW25Q64JVS_READ;
	txBuffer[1] = (addr >> 16	) & 0xff;
	txBuffer[2] = (addr >> 8	) & 0xff;
	txBuffer[3] = (addr			) & 0xff;
	__W25Q64JVS_Data->SPI_Write_Bytes( txBuffer, 4 );
	//doc du lieu
	__W25Q64JVS_Data->SPI_Read_Bytes( uBuffer, Lenght );
    __W25Q64JVS_Data->GPIO_setOutput_HighLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
}





/******************************************************************************
 * Function		: void W25Q64JVS_Write( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t addr, uint8_t *pBuffer, uint16_t Lenght )
 * Description	: Ham ghi du lieu toi flash
 * Param		: 
 *				+ addr: address in page
 *				+ pBuffer: Bo dem chua du lieu duoc ghi
 *				+ Length: do dai du lieu ghi vao
 * Return		: none
*******************************************************************************/
void W25Q64JVS_Write( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t addr, uint8_t *pBuffer, uint16_t Lenght )
{
	uint8_t data[64] = {0};

    W25Q64JVS_SetWriteEnable(__W25Q64JVS_Data);
    __W25Q64JVS_Data->GPIO_setOutput_LowLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );

	//Truyen lenh ghi va 24bit dia chi can ghi du lieu
    data[0] = macroW25Q64JVS_WRITE;
    data[1] = (addr >> 16	) & 0xff;
    data[2] = (addr >> 8	) & 0xff;
    data[3] = (addr			) & 0xff;

    uint8_t ui = 0;
    while(ui < Lenght)
    {
    	data[ui+4] = pBuffer[ui];
    	ui++;
    }
	//ghi du lieu
	__W25Q64JVS_Data->SPI_Write_Bytes( data, Lenght + 4 );
	__W25Q64JVS_Data->GPIO_setOutput_HighLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
    
    while(W25Q64JVS_IsBusy(__W25Q64JVS_Data));
}




/******************************************************************************
 * Function		: void W25Q64JVS_EraseSector( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t ulAddress )
 * Description	: Ham xoa sector trong flash
 * Param		: 
 *				+ ulAddress: Dia chi du lieu
 * Return		: none
*******************************************************************************/
void W25Q64JVS_EraseSector( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t ulAddress )
{
	uint8_t txBuffer[5] = {0};

    W25Q64JVS_SetWriteEnable(__W25Q64JVS_Data);
    __W25Q64JVS_Data->GPIO_setOutput_LowLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
	//Truyen lenh xoa sector va 24bit dia chi can xoa du lieu
	txBuffer[0] = macroW25Q64JVS_SECTOR_ERASE;
	txBuffer[1] = (ulAddress >> 16	) & 0xff;
	txBuffer[2] = (ulAddress >> 8	) & 0xff;
	txBuffer[3] = (ulAddress		) & 0xff;
	__W25Q64JVS_Data->SPI_Write_Bytes( txBuffer, 4 );
	__W25Q64JVS_Data->GPIO_setOutput_HighLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
    
    while(W25Q64JVS_IsBusy(__W25Q64JVS_Data));
}




/******************************************************************************
 * Function		: void W25Q64JVS_EraseBlock( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t ulAddress )
 * Description	: Ham xoa block trong flash
 * Param		: 
 *				+ ulAddress: Dia chi du lieu
==
 * Return		: none
*******************************************************************************/
void W25Q64JVS_EraseBlock( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t ulAddress )
{
	uint8_t txBuffer[5] = {0};

    W25Q64JVS_SetWriteEnable(__W25Q64JVS_Data);
    __W25Q64JVS_Data->GPIO_setOutput_LowLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
	//Truyen lenh xoa block va 24bit dia chi can xoa du lieu
    txBuffer[0] = macroW25Q64JVS_BLOCK_ERASE;
	txBuffer[1] = (ulAddress >> 16	) & 0xff;
	txBuffer[2] = (ulAddress >> 8	) & 0xff;
	txBuffer[3] = (ulAddress		) & 0xff;
	__W25Q64JVS_Data->SPI_Write_Bytes( txBuffer, 4 );
	__W25Q64JVS_Data->GPIO_setOutput_HighLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
    
    while(W25Q64JVS_IsBusy(__W25Q64JVS_Data));
}




/******************************************************************************
 * Function		: void W25Q64JVS_EraseChip( W25Q64JVS_Data_t *__W25Q64JVS_Data )
 * Description	: Ham xoa block trong flash
 * Param		: 
 *				+ true (default) to block until chip is finished 
 * Return		: none
*******************************************************************************/
void W25Q64JVS_EraseChip( W25Q64JVS_Data_t *__W25Q64JVS_Data )
{
	uint8_t txBuffer[2] = {0};

    W25Q64JVS_SetWriteEnable( __W25Q64JVS_Data );
    __W25Q64JVS_Data->GPIO_setOutput_LowLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
	//Truyen lenh xoa chip
    txBuffer[0] = macroW25Q64JVS_CHIP_ERASE;
	__W25Q64JVS_Data->SPI_Write_Bytes( txBuffer, 1 );
	__W25Q64JVS_Data->GPIO_setOutput_HighLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
    
	while(W25Q64JVS_IsBusy(__W25Q64JVS_Data));
}



/******************************************************************************
 * Function		: void W25Q64JVS_SetWriteEnable( W25Q64JVS_Data_t *__W25Q64JVS_Data  )
 * Description	: Ham enable che do ghi
 * Param		: none
 * Return		: none
*******************************************************************************/
void W25Q64JVS_SetWriteEnable( W25Q64JVS_Data_t *__W25Q64JVS_Data  )
{
	uint8_t txBuffer[2] = {0};

	__W25Q64JVS_Data->GPIO_setOutput_LowLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
    //Truyen lenh write enable
	txBuffer[0] = macroW25Q64JVS_WRITE_ENABLE;
	__W25Q64JVS_Data->SPI_Write_Bytes( txBuffer, 1 );
	__W25Q64JVS_Data->GPIO_setOutput_HighLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
}

	

/******************************************************************************
 * Function		: uint8_t W25Q64JVS_GetStatus( W25Q64JVS_Data_t *__W25Q64JVS_Data  )
 * Description	: Ham lay trang thai cua flash
 * Param		: none
 * Return		: none
*******************************************************************************/
uint8_t W25Q64JVS_GetStatus( W25Q64JVS_Data_t *__W25Q64JVS_Data  )
{
	//uint8_t txBuffer[2] = {0};
	uint8_t rxBuffer[2] = {0};

	__W25Q64JVS_Data->GPIO_setOutput_LowLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
    //Truyen lenh write
	uint8_t value = macroW25Q64JVS_READ_STATUS;
	__W25Q64JVS_Data->SPI_Write_Bytes( &value, 1 );
	__W25Q64JVS_Data->SPI_Read_Bytes( rxBuffer, 1 );
	__W25Q64JVS_Data->GPIO_setOutput_HighLevel( __W25Q64JVS_Data->CS_Port, __W25Q64JVS_Data->CS_Pin );
    return rxBuffer[0];
}



/******************************************************************************
 * Function		: bool W25Q64JVS_IsBusy( W25Q64JVS_Data_t *__W25Q64JVS_Data  )
 * Description	: Ham kiem tra flash co doi hay khong
 * Param		: none
 * Return		: none
*******************************************************************************/
bool W25Q64JVS_IsBusy( W25Q64JVS_Data_t *__W25Q64JVS_Data  )
{
    uint8_t retval = W25Q64JVS_GetStatus(__W25Q64JVS_Data);
    retval = retval & 0x01;
    return retval;
}















