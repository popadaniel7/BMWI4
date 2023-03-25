#include "AdcH.h"
#include "SystemManager_Types.h"

uint32 Adc_ChannelOne_Buffer[ADC_BUFFER_LENGTH];

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
void Adc_MainFunction();
StdReturnType Adc_Init();
StdReturnType Adc_DeInit();

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc)
{

	uint32 receivedStatus = HAL_ADC_GetError(&hadc1);

	switch(receivedStatus)
	{

		case HAL_ADC_ERROR_NONE:

			/* do nothing */

			break;

		case HAL_ADC_ERROR_INTERNAL:

			SystemManager_Fault.fault[ADC_ERROR_INTERNAL] = ADC_ERROR_INTERNAL;

			Adc_DeInit();
			Adc_Init();

			break;

		case HAL_ADC_ERROR_OVR:

			SystemManager_Fault.fault[ADC_ERROR_OVR] = ADC_ERROR_OVR;

			Adc_DeInit();
			Adc_Init();

			break;

		case HAL_ADC_ERROR_DMA:

			SystemManager_Fault.fault[ADC_ERROR_DMA] = ADC_ERROR_DMA;

			Adc_DeInit();
			Adc_Init();

			break;

		default:

			break;

	}

}

void Adc_MainFunction()
{

	uint32 statusValue = STD_LOW;

	statusValue = HAL_ADC_GetState(&hadc1);

	if(statusValue == HAL_ADC_STATE_ERROR)
	{

		HAL_ADC_ErrorCallback(&hadc1);

	}
	else
	{

		/* do nothing */

	}

}

StdReturnType Adc_DeInit()
{

	HAL_ADC_DeInit(&hadc1);

	return E_OK;

}

StdReturnType Adc_Init()
{

	ADC_ChannelConfTypeDef sConfig = {0};

	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ENABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 2;
	hadc1.Init.DMAContinuousRequests = DISABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{

		HAL_ADC_ErrorCallback(&hadc1);

	}
	else
	{

		/* do nothing */

	}


	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{

		HAL_ADC_ErrorCallback(&hadc1);

	}
	else
	{

		/* do nothing */

	}


	sConfig.Channel = ADC_CHANNEL_15;
	sConfig.Rank = 2;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{

		HAL_ADC_ErrorCallback(&hadc1);

	}
	else
	{

		/* do nothing */

	}

	return E_OK;

}
