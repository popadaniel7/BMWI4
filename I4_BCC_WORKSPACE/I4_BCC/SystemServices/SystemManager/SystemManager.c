#include "SystemManager.h"
#include "SystemManager_Types.h"
#include "Dem.h"

SystemManager_SystemFaultType SystemManager_Fault;

StdReturnType SystemManager_StoreInFlash();
StdReturnType SystemManager_ReadFromFlash();
StdReturnType SystemManager_SetFault(uint8 faultType);
void SystemManager_Init();
void SystemManager_MainFunction();
void SystemManager_PerformReset();
void SystemClock_Config(void);
void Error_Handler(void);
void MX_NVIC_Init(void);

void SystemManager_Init()
{

	HAL_Init();
	SystemClock_Config();
	MX_NVIC_Init();

}

StdReturnType SystemManager_SetFault(uint8 faultType)
{

	for(uint8 index = 0; index <= 13; index++)
	{

		if(faultType == index)
		{

			SystemManager_Fault.fault[index] = index + 1;

		}
		else
		{

			/* do nothing */

		}

	}

	return E_OK;

}

void SystemManager_MainFunction()
{

}

void SystemManager_PerformReset()
{

	HAL_NVIC_SystemReset();

}

void MX_NVIC_Init(void)
{

	HAL_NVIC_SetPriority(WWDG_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(WWDG_IRQn);
	HAL_NVIC_SetPriority(PVD_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(PVD_IRQn);
	HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
	HAL_NVIC_SetPriority(FLASH_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(FLASH_IRQn);
	HAL_NVIC_SetPriority(RCC_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(RCC_IRQn);
	HAL_NVIC_SetPriority(ADC_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(ADC_IRQn);
	HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_NVIC_SetPriority(TIM3_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	HAL_NVIC_SetPriority(TIM4_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	HAL_NVIC_SetPriority(I2C1_EV_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
	HAL_NVIC_SetPriority(I2C1_ER_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
	HAL_NVIC_SetPriority(SPI1_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(SPI1_IRQn);
	HAL_NVIC_SetPriority(SPI2_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(SPI2_IRQn);
	HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	HAL_NVIC_SetPriority(TIM5_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(TIM5_IRQn);
	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

void SystemClock_Config(void)
{

	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 100;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{

		Error_Handler();

	}
	else
	{

		/* do nothing */

	}


	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
	{

		Error_Handler();

	}
	else
	{

		/* do nothing */

	}

}

void Error_Handler(void)
{

	__disable_irq();

	SystemManager_PerformReset();

	while (1)
	{
	}

}
