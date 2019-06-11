
#include <string.h>
#include <stdlib.h>

#include "main.h"

#include "Interface/Uart.h"
#include "Interface/GPIO.h"
#include "Interface/I2C.h"

#include "fileData.h"
#include "IOControl.h"

//task
#include "Task/ProcessTask.h"
#include "Task/LoraTask.h"
#include "Task/SensorTask.h"
#include "Task/OTATask.h"


/* Private variables ---------------------------------------------------------*/
Uart_Handle_t _Uart1_Debug;
Uart_Handle_t _Uart3_SOIL;
Uart_Handle_t _Uart5_CO2;


Task_t _TaskHandle;

uint8_t SerialNumber[17] = {0};


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Main_getUID( uint8_t *UID );




/******************************************************************************
 * Function		: int main( void )
 * Description	: main task
 * Param		: None
 * Return		: None
 * ***************************************************************************/
int main( void )
{
	HAL_Init();
	SystemClock_Config();

	//Init gpio
	GPIO_Init();

	//Uart debug
	Uart_Open( &_Uart1_Debug, USART1, 115200 );
	//uart for temperature and moisture sensor
	Uart_Open( &_Uart3_SOIL, USART3, 9600 );
	//uart for CO2 sensor
	//Uart_Open( &_Uart5_CO2, UART5, 9600 );

	//I2c for sensor
	I2C1_SS_Init();

	//device init
	IOControl_Init();

	/******************** func pointer assign ******************/



	APP_DEBUG("\r\n****************** smartfarm sensor v%.1f ******************\r\n", 1.0);
	//get serial number
	Main_getUID( SerialNumber );
	APP_DEBUG("--- Main: serial number = %s\r\n", SerialNumber);

	//read data flash
	fileData_Init();
	fileData_ReadAll();

	//Process task
	osThreadDef(ProcessTask, ProcessTask, osPriorityHigh, 0, 1500);
	_TaskHandle.ProcessTask_Handle = osThreadCreate(osThread(ProcessTask), NULL);
	//Lora task
	osThreadDef(LoraTask, LoraTask, osPriorityNormal, 0, 1200);
	_TaskHandle.LoraTask_Handle = osThreadCreate(osThread(LoraTask), NULL);
	//Sensor task
	osThreadDef(SensorTask, SensorTask, osPriorityNormal, 0, 512);
	_TaskHandle.SensorTask_Handle = osThreadCreate(osThread(SensorTask), NULL);
	//Sensor task
	osThreadDef(OTATask, OTATask, osPriorityAboveNormal, 0, 1024);
	_TaskHandle.OTATask_Handle = osThreadCreate(osThread(OTATask), NULL);

	/* Start scheduler */
	osKernelStart();

	for(;;);
}





/******************************************************************************
 * Function		: void SystemClock_Config(void)
 * Description	: System Clock Configuration
 * Param		: None
 * Return		: None
 * ***************************************************************************/
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	/**Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
	RCC_OscInitStruct.MSIState = RCC_MSI_ON;
	RCC_OscInitStruct.MSICalibrationValue = 0;
	RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		APP_DEBUG("--- Main: HAL_RCC_OscConfig error\r\n");

	/**Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
						  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
		APP_DEBUG("--- Main: HAL_RCC_ClockConfig error\r\n");

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART3 | RCC_PERIPHCLK_UART5|RCC_PERIPHCLK_I2C1 | RCC_PERIPHCLK_ADC;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
	PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
	PeriphClkInit.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	PeriphClkInit.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
	PeriphClkInit.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
	PeriphClkInit.PLLSAI1.PLLSAI1M = 1;
	PeriphClkInit.PLLSAI1.PLLSAI1N = 16;
	PeriphClkInit.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
	PeriphClkInit.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
	PeriphClkInit.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
	PeriphClkInit.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_ADC1CLK;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
		APP_DEBUG("--- Main: HAL_RCCEx_PeriphCLKConfig error\r\n");

	/**Configure the main internal regulator output voltage
	*/
	if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
		APP_DEBUG("--- Main: HAL_PWREx_ControlVoltageScaling error\r\n");
}




/******************************************************************************
 * Function		: void Main_getUID( uint8_t *UID )
 * Description	: Get unique id
 * Param		: None
 * Return		: None
 * ***************************************************************************/
static void Main_getUID( uint8_t *UID )
{
	uint8_t Hex64[65] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz=@";
	uint8_t index = 0;
	uint32_t Unique_ID_Low = HAL_GetUIDw0();
	uint32_t Unique_ID_Mid = HAL_GetUIDw1();
	uint32_t Unique_ID_High = HAL_GetUIDw2();

	UID[index++] = Hex64[ ((Unique_ID_Low >> 0) & 0xFFF) / 64 ];
	UID[index++] = Hex64[ ((Unique_ID_Low >> 0) & 0xFFF) % 64 ];
	UID[index++] = Hex64[ ((Unique_ID_Low >> 12) & 0xFFF) / 64 ];
	UID[index++] = Hex64[ ((Unique_ID_Low >> 12) & 0xFFF) % 64 ];

	UID[index++] = Hex64[ (((Unique_ID_Low >> 24) & 0xFF) | ((Unique_ID_Mid << 8) & 0xF00)) / 64 ];
	UID[index++] = Hex64[ (((Unique_ID_Low >> 24) & 0xFF) | ((Unique_ID_Mid << 8) & 0xF00)) % 64 ];
	UID[index++] = Hex64[ ((Unique_ID_Mid >> 4) & 0xFFF) / 64 ];
	UID[index++] = Hex64[ ((Unique_ID_Mid >> 4) & 0xFFF) % 64 ];
	UID[index++] = Hex64[ ((Unique_ID_Mid >> 16) & 0xFFF) / 64 ];
	UID[index++] = Hex64[ ((Unique_ID_Mid >> 16) & 0xFFF) % 64 ];

	UID[index++] = Hex64[ (((Unique_ID_Mid >> 28) & 0xF) | ((Unique_ID_High << 4) & 0xFF0)) / 64 ];
	UID[index++] = Hex64[ (((Unique_ID_Mid >> 28) & 0xF) | ((Unique_ID_High << 4) & 0xFF0)) % 64 ];
	UID[index++] = Hex64[ ((Unique_ID_High >> 8) & 0xFFF) / 64 ];
	UID[index++] = Hex64[ ((Unique_ID_High >> 8) & 0xFFF) % 64 ];
	UID[index++] = Hex64[ ((Unique_ID_High >> 20) & 0xFFF) / 64 ];
	UID[index++] = Hex64[ ((Unique_ID_High >> 20) & 0xFFF) % 64 ];
}




#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
	//HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
	HAL_UART_Transmit(&_Uart1_Debug._UartHandle, (uint8_t *)&ch, 1, 0xFF); // send message via UART
	return ch;
}













