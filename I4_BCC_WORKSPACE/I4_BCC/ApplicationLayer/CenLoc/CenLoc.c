#include "tim.h"
#include "CenLoc.h"
#include "ExtLights.h"
#include "IntLights.h"
#include "SecAlm.h"
#include "main.h"
#include "timers.h"

uint8 CenLoc_CurrentState;
uint8 CenLoc_PreviousState;
uint8 CenLoc_FollowMeHomeState;
uint8 CenLoc_BlinkState;
uint8 CenLoc_PreviousStateFlag;
uint8 Btc_CenLoc;

static uint8 localPreviousState = STD_LOW;

uint8 CenLoc_Tim2IRQFlag;
uint8 CenLoc_Tim3IRQFlag;
uint8 CenLoc_Tim5IRQFlag;
uint8 CenLoc_Tim11IRQFlag;

void CenLocMainFunction();
void CenLocToggleDoorLED(uint8 PinState);
void CenLocRxBtcState();
void CenLocSecAlmStateToOff();
void CenLocFollowMeHome();
void CenLocBlinkSignals();
void CenLocUnlockSequence();
void CenLocLockSequence();
void CenLocControlAlarmLed();
StdReturnType CenLocInit();
StdReturnType CenLocState();
StdReturnType CenLocLockUnlockStates();

StdReturnType CenLocInit()
{

	CenLoc_CurrentState 			= STD_LOW;
	CenLoc_PreviousState 			= STD_LOW;
	CenLoc_Tim2IRQFlag 				= STD_LOW;
	CenLoc_Tim5IRQFlag 				= STD_LOW;
	CenLoc_Tim3IRQFlag				= STD_LOW;
	CenLoc_Tim11IRQFlag				= STD_LOW;
	CenLoc_FollowMeHomeState 		= STD_LOW;
	CenLoc_BlinkState 				= STD_LOW;
	Btc_CenLoc 						= STD_LOW;
	CenLoc_PreviousStateFlag 		= STD_LOW;

	return E_OK;
}

StdReturnType CenLocState()
{

	uint8 status = E_OK;

	if(CenLoc_PreviousState != CenLoc_CurrentState)
	{
		CenLoc_PreviousStateFlag 		= CenLoc_PreviousState;
		CenLoc_PreviousState 			= CenLoc_CurrentState;
		CenLoc_Tim2IRQFlag 				= STD_LOW;
		CenLoc_Tim5IRQFlag 				= STD_LOW;
		CenLoc_Tim3IRQFlag				= STD_LOW;
		CenLoc_Tim11IRQFlag				= STD_LOW;

		HAL_TIM_Base_Init(&htim2);
		HAL_TIM_Base_Init(&htim3);
		HAL_TIM_Base_Init(&htim5);

	}
	else
	{

		/* do nothing */

	}

	return status;

}

void CenLocSecAlmStateToOff()
{

	if(CenLoc_CurrentState == STD_HIGH)
	{

		SecAlm_Trigger = STD_LOW;


	}
	else
	{

		/* do nothing */

	}

}

void CenLocRxBtcState()
{

	CenLoc_CurrentState = Btc_CenLoc;

}

void CenLocToggleDoorLED(uint8 PinState)
{

	HAL_GPIO_WritePin(CENLOC_DOOR_LED_PORT, CENLOC_DOOR_LED_PIN, PinState);

}

void CenLocFollowMeHome()
{

	if(CenLoc_Tim5IRQFlag == 1)
	{

		CenLoc_FollowMeHomeState = STD_HIGH;

	}
	else if(CenLoc_Tim5IRQFlag == 2)
	{

		CenLoc_FollowMeHomeState = STD_LOW;

	}
	else
	{

		/* do nothing */

	}

}

void CenLocBlinkSignals()
{

	ExtLightsTurnSignalLeft(CenLoc_BlinkState);
	ExtLightsTurnSignalRight(CenLoc_BlinkState);

}

void CenLocUnlockSequence()
{

	HAL_TIM_Base_Stop_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim5);
	__HAL_TIM_SET_COUNTER(&htim3, 0);

	CenLocToggleDoorLED(CenLoc_CurrentState);
	CenLocFollowMeHome();

	localPreviousState = STD_HIGH;

	if(CenLoc_Tim2IRQFlag <= 4)
	{

		HAL_TIM_Base_Start_IT(&htim2);

		switch(CenLoc_Tim2IRQFlag)
		{

			case 1:

				CenLoc_BlinkState = STD_HIGH;
				CenLocToggleBuzzer(CenLoc_BlinkState);

				break;

			case 2:

				CenLoc_BlinkState = STD_LOW;
				CenLocToggleBuzzer(CenLoc_BlinkState);

				break;

			case 3:

				CenLoc_BlinkState = STD_HIGH;
				CenLocToggleBuzzer(CenLoc_BlinkState);

				break;

			case 4:

				CenLoc_BlinkState = STD_LOW;
				CenLocToggleBuzzer(CenLoc_BlinkState);

				break;

			default:

				break;

		}

	}
	else if(CenLoc_Tim2IRQFlag == 5)
	{

		CenLoc_BlinkState = 2;
		HAL_TIM_Base_Stop_IT(&htim2);

	}
	else
	{

		/* do nothing */

	}

}

void CenLocLockSequence()
{

	CenLocToggleDoorLED(CenLoc_CurrentState);
	CenLocFollowMeHome();

	if(CenLoc_Tim2IRQFlag <= 2 && localPreviousState == STD_HIGH)
	{
		HAL_TIM_Base_Start_IT(&htim5);
		HAL_TIM_Base_Start_IT(&htim2);

		switch(CenLoc_Tim2IRQFlag)
		{

		case 1:

			CenLoc_BlinkState = STD_HIGH;
			CenLocToggleBuzzer(CenLoc_BlinkState);

			break;

		case 2:

			CenLoc_BlinkState = STD_LOW;
			CenLocToggleBuzzer(CenLoc_BlinkState);
			localPreviousState = STD_LOW;

			break;

		default:

			break;

		}

	}
	else if(CenLoc_Tim2IRQFlag == 3)
	{

		CenLoc_BlinkState = 2;
		HAL_TIM_Base_Stop_IT(&htim2);

	}
	else
	{
		/* do nothing */
	}

}

void CenLocControlAlarmLed()
{
	if(CenLoc_CurrentState == STD_HIGH)
	{

		SecAlmToggleAlarmLed(STD_LOW);

	}
	else if(CenLoc_CurrentState == STD_LOW)
	{

		HAL_TIM_Base_Start_IT(&htim3);

		if(CenLoc_Tim3IRQFlag == 2)
		{

			HAL_TIM_Base_Start_IT(&htim11);

			if(CenLoc_Tim11IRQFlag == 1)
			{

				SecAlmToggleAlarmLed(STD_HIGH);

			}
			else if(CenLoc_Tim11IRQFlag > 1)
			{

				SecAlmToggleAlarmLed(STD_LOW);
				CenLoc_Tim11IRQFlag = 0;
				CenLoc_Tim3IRQFlag = 1;
				HAL_TIM_Base_Stop_IT(&htim11);

			}
			else
			{

				/* do nothing */

			}

		}
		else
		{

			/* do nothing */

		}

	}
}

StdReturnType CenLocLockUnlockStates()
{

	if(CenLoc_CurrentState == STD_HIGH && SecAlm_Trigger == STD_LOW)
	{

		CenLocUnlockSequence();
		CenLocControlAlarmLed();

	}
	else if(CenLoc_CurrentState == STD_LOW && SecAlm_Trigger == STD_LOW)
	{

		CenLocLockSequence();
		CenLocControlAlarmLed();

	}

	return 1;

}

void CenLocToggleBuzzer(uint8 PinState)
{

	HAL_GPIO_WritePin(CENLOC_BUZZER_PORT, CENLOC_BUZZER_PIN, PinState);

}

void CenLocMainFunction()
{

	CenLocRxBtcState();
	CenLocState();
	CenLocSecAlmStateToOff();
	CenLocLockUnlockStates();

}
