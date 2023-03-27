#include "TimH.h"
#include "Rte.h"
#include "SystemManager_Types.h"

uint32 Timer2Counter_ExtLights_LTSFlag;
uint32 Timer2Counter_ExtLights_RTSFlag;
uint32 Timer2Counter_ExtLights_HLFlag;
uint8  Timer2Counter_CenLoc_Tim2IRQFlag;
uint8  Timer5Counter_CenLoc_Tim5IRQFlag;
uint8  Timer11Counter_CenLoc_Tim11IRQFlag;
uint8  Timer3Counter_CenLoc_Tim3IRQFlag;

static TIM_ClockConfigTypeDef sClockSourceConfig2 = {0};
static TIM_MasterConfigTypeDef sMasterConfig2 = {0};
static TIM_ClockConfigTypeDef sClockSourceConfig3 = {0};
static TIM_MasterConfigTypeDef sMasterConfig3 = {0};
static TIM_ClockConfigTypeDef sClockSourceConfig4 = {0};
static TIM_MasterConfigTypeDef sMasterConfig4 = {0};
static TIM_ClockConfigTypeDef sClockSourceConfig5 = {0};
static TIM_MasterConfigTypeDef sMasterConfig5 = {0};
static TIM_ClockConfigTypeDef sClockSourceConfig9 = {0};

StdReturnType Tim_Init(uint8 TimerChannel);
StdReturnType Tim_DeInit(uint8 TimerChannel);
void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void Tim_MainFunction();

StdReturnType Tim_Init(uint8 TimerChannel)
{

	switch(TimerChannel)
	{

		case TIMER_TWO:

			htim2.Instance = TIM2;
			htim2.Init.Prescaler = 10000-1;
			htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
			htim2.Init.Period = 5000-1;
			htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
			htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim2);

			}
			else
			{

				/* do nothing */

			}

			sClockSourceConfig2.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

			if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig2) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim2);

			}
			else
			{

				/* do nothing */

			}

			sMasterConfig2.MasterOutputTrigger = TIM_TRGO_RESET;
			sMasterConfig2.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

			if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig2) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim2);

			}
			else
			{

				/* do nothing */

			}

			break;

		case TIMER_THREE:

			htim3.Instance = TIM3;
			htim3.Init.Prescaler = 10000-1;
			htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
			htim3.Init.Period = 40000-1;
			htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
			htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim3);

			}
			else
			{

				/* do nothing */

			}

			sClockSourceConfig3.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

			if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig3) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim3);

			}
			else
			{

				/* do nothing */

			}

			sMasterConfig3.MasterOutputTrigger = TIM_TRGO_RESET;
			sMasterConfig3.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

			if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig3) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim3);

			}
			else
			{

				/* do nothing */

			}

			break;

		case TIMER_FOUR:

			htim4.Instance = TIM4;
			htim4.Init.Prescaler = 10000-1;
			htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
			htim4.Init.Period = 5000-1;
			htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
			htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim4);

			}
			else
			{

				/* do nothing */

			}

			sClockSourceConfig4.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

			if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig4) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim4);

			}
			else
			{

				/* do nothing */

			}

			sMasterConfig4.MasterOutputTrigger = TIM_TRGO_RESET;
			sMasterConfig4.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

			if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig4) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim4);

			}
			else
			{

				/* do nothing */

			}

			break;

		case TIMER_FIVE:

			htim5.Instance = TIM5;
			htim5.Init.Prescaler = 10000-1;
			htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
			htim5.Init.Period = 100000-1;
			htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
			htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim5);

			}
			else
			{

				/* do nothing */

			}

			sClockSourceConfig5.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

			if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig5) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim5);

			}
			else
			{

				/* do nothing */

			}

			sMasterConfig5.MasterOutputTrigger = TIM_TRGO_RESET;
			sMasterConfig5.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

			if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig5) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim5);

			}
			else
			{

				/* do nothing */

			}

			break;

		case TIMER_NINE:


			htim9.Instance = TIM9;
			htim9.Init.Prescaler = 10000-1;
			htim9.Init.CounterMode = TIM_COUNTERMODE_UP;
			htim9.Init.Period = 10000-1;
			htim9.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
			htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			if (HAL_TIM_Base_Init(&htim9) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim9);

			}
			else
			{

				/* do nothing */

			}

			sClockSourceConfig9.ClockSource = TIM_CLOCKSOURCE_INTERNAL;

			if (HAL_TIM_ConfigClockSource(&htim9, &sClockSourceConfig9) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim9);

			}
			else
			{

				/* do nothing */

			}

			break;

//		case TIMER_TEN:
//
//			htim10.Instance = TIM10;
//			htim10.Init.Prescaler = 0;
//			htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
//			htim10.Init.Period = (SystemCoreClock / 1000UL) - 1;
//			htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//			htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//
//			if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
//			{
//
//				HAL_TIM_ErrorCallback(&htim10);
//
//			}
//			else
//			{
//
//				/* do nothing */
//
//			}

		case TIMER_ELEVEN:

			htim11.Instance = TIM11;
			htim11.Init.Prescaler = 10000-1;
			htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
			htim11.Init.Period = 5000-1;
			htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
			htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

			if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
			{

				HAL_TIM_ErrorCallback(&htim11);

			}
			else
			{

				/* do nothing */

			}

			break;

		default:

			break;

	}

	return E_OK;

}

StdReturnType Tim_DeInit(uint8 TimerChannel)
{

	return E_OK;

}

void HAL_TIM_ErrorCallback(TIM_HandleTypeDef *htim)
{

	if(htim->Instance == TIM2)
	{

		SystemManager_Fault.fault[TIMER2_ERROR] = TIMER2_ERROR;

		Tim_DeInit(TIMER_TWO);
		Tim_Init(TIMER_TWO);

	}
	else if(htim->Instance == TIM3)
	{

		SystemManager_Fault.fault[TIMER3_ERROR] = TIMER3_ERROR;

		Tim_DeInit(TIMER_THREE);
		Tim_Init(TIMER_THREE);

	}
	else if(htim->Instance == TIM4)
	{

		SystemManager_Fault.fault[TIMER4_ERROR] = TIMER4_ERROR;

		Tim_DeInit(TIMER_FOUR);
		Tim_Init(TIMER_FOUR);

	}
	else if(htim->Instance == TIM5)
	{

		SystemManager_Fault.fault[TIMER5_ERROR] = TIMER5_ERROR;

		Tim_DeInit(TIMER_FIVE);
		Tim_Init(TIMER_FIVE);

	}
	else if(htim->Instance == TIM9)
	{

		SystemManager_Fault.fault[TIMER9_ERROR] = TIMER9_ERROR;

		Tim_DeInit(TIMER_NINE);
		Tim_Init(TIMER_NINE);

	}
	else if(htim->Instance == TIM11)
	{

		SystemManager_Fault.fault[TIMER11_ERROR] = TIMER11_ERROR;

		Tim_DeInit(TIMER_ELEVEN);
		Tim_Init(TIMER_ELEVEN);

	}
	else
	{

		/* do nothing */

	}

}

void Tim_MainFunction()
{

	uint32 localStateTimerTwo = HAL_TIM_Base_GetState(&htim2);
	uint32 localStateTimerThree = HAL_TIM_Base_GetState(&htim3);
	uint32 localStateTimerFour = HAL_TIM_Base_GetState(&htim4);
	uint32 localStateTimerFive = HAL_TIM_Base_GetState(&htim5);
	uint32 localStateTimerNine = HAL_TIM_Base_GetState(&htim9);
	uint32 localStateTimerEleven = HAL_TIM_Base_GetState(&htim11);

	if(localStateTimerTwo == HAL_TIM_STATE_ERROR)
	{

		HAL_TIM_ErrorCallback(&htim2);

	}
	else if(localStateTimerThree == HAL_TIM_STATE_ERROR)
	{

		HAL_TIM_ErrorCallback(&htim3);

	}
	else if(localStateTimerFour == HAL_TIM_STATE_ERROR)
	{

		HAL_TIM_ErrorCallback(&htim4);

	}
	else if(localStateTimerFive == HAL_TIM_STATE_ERROR)
	{

		HAL_TIM_ErrorCallback(&htim5);

	}
	else if(localStateTimerNine == HAL_TIM_STATE_ERROR)
	{

		HAL_TIM_ErrorCallback(&htim9);

	}
	else if(localStateTimerEleven == HAL_TIM_STATE_ERROR)
	{

		HAL_TIM_ErrorCallback(&htim11);

	}
	else
	{

		/* do nothing */

	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if(htim->Instance == TIM3)
	{

		Timer3Counter_CenLoc_Tim3IRQFlag++;
		Rte_Write_CenLoc_CenLocPort_CenLoc_Tim3IRQFlag(&Timer3Counter_CenLoc_Tim3IRQFlag);

	}
	else if(htim->Instance == TIM4)
	{

		SecAlm_TriggerIRQCounterForTimer4++;
		Rte_Write_SecAlm_SecAlmPort_SecAlm_TriggerIRQCounterForTimer4(&SecAlm_TriggerIRQCounterForTimer4);

	}
	else if(htim->Instance == TIM5)
	{

		Timer5Counter_CenLoc_Tim5IRQFlag++;
		Rte_Write_CenLoc_CenLocPort_CenLoc_Tim5IRQFlag(&Timer5Counter_CenLoc_Tim5IRQFlag);


	}
	else if(htim->Instance == TIM11)
	{

		Timer11Counter_CenLoc_Tim11IRQFlag++;
		Rte_Write_CenLoc_CenLocPort_CenLoc_Tim11IRQFlag(&Timer11Counter_CenLoc_Tim11IRQFlag);

	}
	else if(htim->Instance == TIM2)
	{

		if(Rte_P_ExtLights_ExtLightsPort_ExtLights_TurnSignalLeft_CurrentState == STD_HIGH)
		{

			Timer2Counter_ExtLights_LTSFlag++;
			Rte_Write_ExtLights_ExtLightsPort_ExtLights_LTSFlag(&Timer2Counter_ExtLights_LTSFlag);

		}
		else
		{

			/* do nothing */

		}

		if(Rte_P_ExtLights_ExtLightsPort_ExtLights_TurnSignalRight_CurrentState == STD_HIGH)
		{

			Timer2Counter_ExtLights_RTSFlag++;
			Rte_Write_ExtLights_ExtLightsPort_ExtLights_RTSFlag(&Timer2Counter_ExtLights_RTSFlag);

		}
		else
		{

			/* do nothing */

		}

		if(Rte_P_ExtLights_ExtLightsPort_ExtLights_HazardLight_CurrentState == STD_HIGH)
		{

			Timer2Counter_ExtLights_HLFlag++;
			Rte_Write_ExtLights_ExtLightsPort_ExtLights_HLFlag(&Timer2Counter_ExtLights_HLFlag);

		}
		else
		{

			/* do nothing */

		}

	}
	else if (htim->Instance == TIM1)
	{

		HAL_IncTick();

	}
	else
	{

		/* do nothing */

	}

}