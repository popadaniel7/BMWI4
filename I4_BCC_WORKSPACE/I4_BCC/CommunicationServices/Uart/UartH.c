#include "UartH.h"
#include "SystemManager_Types.h"

uint8 UartCounter_Btc_RxCount;

StdReturnType Uart_Init();
StdReturnType Uart_DeInit();
void Uart_MainFunction();
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

StdReturnType Uart_Init()
{

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 9600;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&huart1) != HAL_OK)
	{

		HAL_UART_ErrorCallback(&huart1);

	}
	else
	{

		/* do nothing */

	}

	return E_OK;

}

StdReturnType Uart_DeInit()
{

	HAL_UART_DeInit(&huart1);

	return E_OK;

}

void Uart_MainFunction()
{

	uint32 localState = HAL_UART_GetState(&huart1);

	if(localState == HAL_UART_STATE_ERROR)
	{

		HAL_UART_ErrorCallback(&huart1);

	}
	else
	{

		/* do nothing */

	}

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

	uint32 receivedValue = HAL_UART_GetError(huart);

	switch(receivedValue)
	{

		case HAL_UART_ERROR_NONE:

			/* do nothing */

			break;

		case HAL_UART_ERROR_PE:

			SystemManager_Fault.fault[UART_ERROR_PE] = UART_ERROR_PE;

			break;

		case HAL_UART_ERROR_NE:

			SystemManager_Fault.fault[UART_ERROR_NE] = UART_ERROR_NE;

			break;

		case HAL_UART_ERROR_FE:

			SystemManager_Fault.fault[UART_ERROR_FE] = UART_ERROR_FE;

			break;

		case HAL_UART_ERROR_ORE:

			SystemManager_Fault.fault[UART_ERROR_ORE] = UART_ERROR_ORE;

			break;

		case HAL_UART_ERROR_DMA:

			SystemManager_Fault.fault[UART_ERROR_ORE] = UART_ERROR_ORE;

			Uart_Init();
			Uart_DeInit();

			break;

		default:

			break;

	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if(huart->Instance == USART1)
	{

		if(Rte_P_Btc_BtcPort_Btc_RxData == '\n')
		{

			if(Rte_P_Btc_BtcPort_Btc_RxCount <= 3)
			{

				//char endChar = '\0';
				uint8 asciiToUint = 0;

				//Rte_Write_Btc_BtcPort_Btc_DataBuffer((uint8*)&endChar, Rte_P_Btc_BtcPort_Btc_RxCount);

				asciiToUint = atoi((char*)Rte_P_Btc_BtcPort_Btc_DataBuffer);

				Rte_Write_Btc_BtcPort_Btc_RxData(&asciiToUint);
				Rte_Write_Btc_BtcPort_Btc_ReceivedDataOnBluetooth(&Btc_RxData);

			}
			else
			{

				/* do nothing */

			}

			UartCounter_Btc_RxCount = 0;
			Rte_Write_Btc_BtcPort_Btc_RxCount(&UartCounter_Btc_RxCount);

		}
		else if(Rte_P_Btc_BtcPort_Btc_RxCount < 3)
		{

			Rte_Write_Btc_BtcPort_Btc_DataBuffer(&Rte_P_Btc_BtcPort_Btc_RxData, UartCounter_Btc_RxCount);
			UartCounter_Btc_RxCount++;

		}
		else
		{

			UartCounter_Btc_RxCount = 0;
			Rte_Write_Btc_BtcPort_Btc_RxCount(&UartCounter_Btc_RxCount);

		}

		Rte_Call_Uart_R_UartPort_HAL_UART_Receive_IT(&huart1, &Btc_RxData, 1);

	}
	else
	{

		/* do nothing */

	}

}
