#include "WatchdogManager.h"

StdReturnType Wdg_Init();
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg);
void Wdg_MainFunction();

void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{

	SystemManager_SetFault(WATCHDOG_RESET);

}

StdReturnType Wdg_Init()
{

	hwwdg.Instance = WWDG;
	hwwdg.Init.Window = 127;
	hwwdg.Init.Prescaler = WWDG_PRESCALER_8;
	hwwdg.Init.Counter = 127;
	hwwdg.Init.EWIMode = WWDG_EWI_ENABLE;

	if (HAL_WWDG_Init(&hwwdg) != HAL_OK)
	{

		SystemManager_SetFault(WATCHDOG_RESET);

		Error_Handler();

	}
	else
	{

		/* do nothing */

	}

	return E_OK;

}

void Wdg_MainFunction()
{

	HAL_WWDG_Refresh(&hwwdg);

}
