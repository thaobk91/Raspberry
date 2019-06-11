
#ifndef W25Q64JVS_H
#define W25Q64JVS_H

#include <stdbool.h>
#include <stdint.h>


#define macroW25Q64JVS_WRITE_STATUS      				0x01
#define macroW25Q64JVS_WRITE         					0x02
#define macroW25Q64JVS_READ          					0x03
#define macroW25Q64JVS_READ_STATUS     					0x05
#define macroW25Q64JVS_WRITE_ENABLE    					0x06
#define macroW25Q64JVS_SECTOR_ERASE  					0x20
#define macroW25Q64JVS_CHIP_ERASE    					0xC7
#define macroW25Q64JVS_BLOCK_ERASE   					0xD8
#define macroW25Q64JVS_JEDECID		         			0x9F



typedef struct
{
	void *CS_Port;
	uint16_t CS_Pin;

	void (*debug)( const char *, ...);
	void (*Delay_ms)( uint32_t ms );

	void (*GPIO_setOutput_Dir)( void *Port, uint16_t Pin );
	void (*GPIO_setOutput_HighLevel)( void *Port, uint16_t Pin );
	void (*GPIO_setOutput_LowLevel)( void *Port, uint16_t Pin );

	void (*SPI_Init)( void );
	bool (*SPI_Ready)(void);
	void (*SPI_Write_Bytes)( uint8_t *txBuffer, uint16_t txLenght );
	void (*SPI_Read_Bytes)( uint8_t *rxBuffer, uint16_t rxLenght );
}W25Q64JVS_Data_t;


/******************************************************************************
 * Function		: void W25Q64JVS_Init( W25Q64JVS_Data_t *__W25Q64JVS_Data )
 * Description	: flash init
 * Param		:
 * Return		: None
*******************************************************************************/
void W25Q64JVS_Init( W25Q64JVS_Data_t *__W25Q64JVS_Data );



/******************************************************************************
 * Function		: bool W25Q64JVS_CheckConnection( W25Q64JVS_Data_t *__W25Q64JVS_Data )
 * Description	: Ham kiem tra ket noi den flash
 * Param		:
 * Return		:
 *				+ true: connection ok
 *				+ false: connection fail
*******************************************************************************/
bool W25Q64JVS_CheckConnection( W25Q64JVS_Data_t *__W25Q64JVS_Data );




/******************************************************************************
 * Function		: void W25Q64JVS_Read( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t addr, uint8_t *uBuffer, uint16_t Lenght )
 * Description	: Ham doc du lieu tu flash
 * Param		:
 *				+ addr: Dia chi du lieu
 *				+ uBuffer: Bo dem chua du lieu duoc doc
 *				+ Length: do dai du lieu doc ra
 * Return		: none
*******************************************************************************/
void W25Q64JVS_Read( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t addr, uint8_t *uBuffer, uint16_t Lenght );





/******************************************************************************
 * Function		: void W25Q64JVS_Write( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t addr, uint8_t *pBuffer, uint16_t Lenght )
 * Description	: Ham ghi du lieu toi flash
 * Param		:
 *				+ addr: address in page
 *				+ pBuffer: Bo dem chua du lieu duoc ghi
 *				+ Length: do dai du lieu ghi vao
 * Return		: none
*******************************************************************************/
void W25Q64JVS_Write( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t addr, uint8_t *pBuffer, uint16_t Lenght );




/******************************************************************************
 * Function		: void W25Q64JVS_EraseSector( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t ulAddress )
 * Description	: Ham xoa sector trong flash
 * Param		:
 *				+ ulAddress: Dia chi du lieu
 * Return		: none
*******************************************************************************/
void W25Q64JVS_EraseSector( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t ulAddress );




/******************************************************************************
 * Function		: void W25Q64JVS_EraseBlock( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t ulAddress )
 * Description	: Ham xoa block trong flash
 * Param		:
 *				+ ulAddress: Dia chi du lieu
==
 * Return		: none
*******************************************************************************/
void W25Q64JVS_EraseBlock( W25Q64JVS_Data_t *__W25Q64JVS_Data, uint32_t ulAddress );




/******************************************************************************
 * Function		: void W25Q64JVS_EraseChip( W25Q64JVS_Data_t *__W25Q64JVS_Data )
 * Description	: Ham xoa block trong flash
 * Param		:
 *				+ true (default) to block until chip is finished
 * Return		: none
*******************************************************************************/
void W25Q64JVS_EraseChip( W25Q64JVS_Data_t *__W25Q64JVS_Data );



#endif














