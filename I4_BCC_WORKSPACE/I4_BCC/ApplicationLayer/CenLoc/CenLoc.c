#include "tim.h"
#include "CenLoc.h"
#include "ExtLights.h"
#include "IntLights.h"
#include "SecAlm.h"
#include "main.h"
#include "timers.h"
#include "RTE.h"

uint8 CenLoc_CurrentState;
uint8 CenLoc_PreviousState;
uint8 CenLoc_FollowMeHomeState;
uint8 CenLoc_BlinkState = STD_OFF;
uint8 CenLoc_PreviousStateFlag;
uint8 CenLoc_Tim2IRQFlag;
uint8 CenLoc_Tim3IRQFlag;
uint8 CenLoc_Tim5IRQFlag;
uint8 CenLoc_Tim11IRQFlag;

static uint8 localPreviousState = STD_LOW;

void CenLoc_MainFunction();
void CenLoc_ToggleDoorLED(uint8 PinState);
void CenLoc_SecAlmStateToOff();
void CenLoc_FollowMeHome();
void CenLoc_BlinkSignals();
void CenLoc_UnlockSequence();
void CenLoc_LockSequence();
void CenLoc_ControlAlarmLed();
StdReturnType CenLoc_Init();
void CenLoc_State();

StdReturnType CenLoc_Init()
{

	CenLoc_CurrentState 			= STD_LOW;
	CenLoc_PreviousState 			= STD_LOW;
	CenLoc_Tim2IRQFlag 				= STD_LOW;
	CenLoc_Tim5IRQFlag 				= STD_LOW;
	CenLoc_Tim3IRQFlag				= STD_LOW;
	CenLoc_Tim11IRQFlag				= STD_LOW;
	CenLoc_FollowMeHomeState 		= STD_LOW;
	CenLoc_BlinkState 				= STD_OFF;
	CenLoc_PreviousStateFlag 		= STD_LOW;

	return E_OK;

}

void CenLoc_State()
{

	CenLoc_SecAlmStateToOff();

	if(CenLoc_PreviousState != CenLoc_CurrentState)
	{

		CenLoc_PreviousStateFlag 			= CenLoc_PreviousState;
		CenLoc_PreviousState 				= CenLoc_CurrentState;
		CenLoc_Tim2IRQFlag 					= STD_LOW;
		CenLoc_Tim5IRQFlag 					= STD_LOW;
		CenLoc_Tim3IRQFlag					= STD_LOW;
		CenLoc_Tim11IRQFlag					= STD_LOW;

		Rte_Call_SecAlm_R_SecAlmPort_SecAlm_Init();
		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStart(Os_CenLoc_LockUnlockSequence_TimerHandle, 250);
		Rte_Write_TimH_TimHPort_Timer2Counter_CenLoc_Tim2IRQFlag(&CenLoc_Tim2IRQFlag);
		Rte_Write_TimH_TimHPort_Timer5Counter_CenLoc_Tim5IRQFlag(&CenLoc_Tim5IRQFlag);
		Rte_Write_TimH_TimHPort_Timer3Counter_CenLoc_Tim3IRQFlag(&CenLoc_Tim3IRQFlag);
		Rte_Write_TimH_TimHPort_Timer11Counter_CenLoc_Tim11IRQFlag(&CenLoc_Tim11IRQFlag);

	}
	else
	{

		/* do nothing */

	}

}

void CenLoc_SecAlmStateToOff()
{

	if(CenLoc_CurrentState == STD_HIGH)
	{

		Rte_Call_SecAlm_R_SecAlmPort_SecAlm_Init();

	}
	else
	{

		/* do nothing */

	}

}

void CenLoc_ToggleDoorLED(uint8 PinState)
{

	Rte_Call_Gpio_R_GpioPort_HAL_GPIO_WritePin(CENLOC_DOOR_LED_PORT, CENLOC_DOOR_LED_PIN, PinState);

}

void CenLoc_FollowMeHome()
{

	if(CenLoc_Tim5IRQFlag == 1)
	{

		CenLoc_FollowMeHomeState = STD_HIGH;


	}
	else if(CenLoc_Tim5IRQFlag == 2)
	{

		CenLoc_FollowMeHomeState = STD_LOW;
		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStop(Os_FollowMeHome_TimerHandle);
		CenLoc_Tim5IRQFlag = 2;
		Rte_Write_TimH_TimHPort_Timer5Counter_CenLoc_Tim5IRQFlag(&CenLoc_Tim5IRQFlag);

	}
	else
	{

		/* do nothing */

	}

}

void CenLoc_BlinkSignals()
{

	Rte_Call_ExtLights_R_ExtLightsPort_ExtLights_TurnSignalLeft(CenLoc_BlinkState);
	Rte_Call_ExtLights_R_ExtLightsPort_ExtLights_TurnSignalRight(CenLoc_BlinkState);

}

void CenLoc_UnlockSequence()
{

	Rte_Call_OsTimer_R_OsTimerPort_OsTimerStop(Os_SecAlmLed_TurnOnCyclic_TimerHandle);

	CenLoc_ToggleDoorLED(CenLoc_CurrentState);
	CenLoc_FollowMeHome();

	localPreviousState = STD_HIGH;

	if(CenLoc_Tim2IRQFlag <= 3)
	{

		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStart(Os_TurnSignals_TimerHandle, 500);
		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStart(Os_FollowMeHome_TimerHandle, 10000);
		CenLoc_Tim5IRQFlag = 1;
		Rte_Write_TimH_TimHPort_Timer5Counter_CenLoc_Tim5IRQFlag(&CenLoc_Tim5IRQFlag);

		switch(CenLoc_Tim2IRQFlag)
		{

			case 0:

				CenLoc_BlinkState = STD_HIGH;
				CenLoc_ToggleBuzzer(CenLoc_BlinkState);

				break;

			case 1:

				CenLoc_BlinkState = STD_LOW;
				CenLoc_ToggleBuzzer(CenLoc_BlinkState);

				break;

			case 2:

				CenLoc_BlinkState = STD_HIGH;
				CenLoc_ToggleBuzzer(CenLoc_BlinkState);

				break;

			case 3:

				CenLoc_BlinkState = STD_LOW;
				CenLoc_ToggleBuzzer(CenLoc_BlinkState);

				break;

			default:

				break;

		}

	}
	else if(CenLoc_Tim2IRQFlag >= 3)
	{

		CenLoc_BlinkState = 2;
		CenLoc_Tim2IRQFlag = 6;
		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStop(Os_TurnSignals_TimerHandle);

	}
	else
	{

		/* do nothing */

	}

}

void CenLoc_LockSequence()
{

	CenLoc_ToggleDoorLED(CenLoc_CurrentState);
	CenLoc_FollowMeHome();

	if(CenLoc_Tim2IRQFlag <= 1 && localPreviousState == STD_HIGH)
	{

		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStart(Os_TurnSignals_TimerHandle, 500);
		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStart(Os_FollowMeHome_TimerHandle, 10000);
		CenLoc_Tim5IRQFlag = 1;
		Rte_Write_TimH_TimHPort_Timer5Counter_CenLoc_Tim5IRQFlag(&CenLoc_Tim5IRQFlag);

		switch(CenLoc_Tim2IRQFlag)
		{

			case 0:

				CenLoc_BlinkState = STD_HIGH;
				CenLoc_ToggleBuzzer(CenLoc_BlinkState);

				break;

			case 1:

				CenLoc_BlinkState = STD_LOW;
				CenLoc_ToggleBuzzer(CenLoc_BlinkState);
				localPreviousState = STD_LOW;

				break;

			default:

				break;

		}

	}
	else if(CenLoc_Tim2IRQFlag == 2)
	{

		CenLoc_BlinkState = 2;
		CenLoc_Tim2IRQFlag = 4;
		Rte_Write_TimH_TimHPort_Timer2Counter_CenLoc_Tim2IRQFlag(&CenLoc_Tim2IRQFlag);
		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStop(Os_CenLoc_LockUnlockSequence_TimerHandle);
		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStop(Os_TurnSignals_TimerHandle);

	}
	else
	{
		/* do nothing */
	}

}

void CenLoc_ControlAlarmLed()
{

	if(CenLoc_CurrentState == STD_HIGH)
	{

		Rte_Call_SecAlm_R_SecAlmPort_SecAlm_ToggleAlarmLed(STD_LOW);
		CenLoc_Tim11IRQFlag = STD_LOW;
		Rte_Write_TimH_TimHPort_Timer11Counter_CenLoc_Tim11IRQFlag(&CenLoc_Tim11IRQFlag);
		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStop(Os_SecAlmLedTurnOn_TimerHandle);

	}
	else if(CenLoc_CurrentState == STD_LOW)
	{

		if(osTimerIsRunning(Os_SecAlmLed_TurnOnCyclic_TimerHandle) == 0 && osTimerIsRunning(Os_SecAlmLedTurnOn_TimerHandle) == 0)
		{

			Rte_Call_OsTimer_R_OsTimerPort_OsTimerStart(Os_SecAlmLed_TurnOnCyclic_TimerHandle, 3750);

		}
		else
		{

			/* do nothing */

		}

		if(CenLoc_Tim3IRQFlag == 1)
		{

			if(osTimerIsRunning(Os_SecAlmLedTurnOn_TimerHandle) == 0)
			{

				Rte_Call_OsTimer_R_OsTimerPort_OsTimerStart(Os_SecAlmLedTurnOn_TimerHandle, 250);

			}
			else
			{

				/* do nothing */

			}

			if(CenLoc_Tim11IRQFlag < 1)
			{

				Rte_Call_SecAlm_R_SecAlmPort_SecAlm_ToggleAlarmLed(STD_HIGH);

			}
			else if(CenLoc_Tim11IRQFlag > 1)
			{

				Rte_Call_SecAlm_R_SecAlmPort_SecAlm_ToggleAlarmLed(STD_LOW);
				CenLoc_Tim11IRQFlag = 0;
				CenLoc_Tim3IRQFlag = 0;
				Rte_Write_TimH_TimHPort_Timer11Counter_CenLoc_Tim11IRQFlag(&CenLoc_Tim11IRQFlag);
				Rte_Write_TimH_TimHPort_Timer3Counter_CenLoc_Tim3IRQFlag(&CenLoc_Tim3IRQFlag);
				Rte_Call_OsTimer_R_OsTimerPort_OsTimerStop(Os_SecAlmLedTurnOn_TimerHandle);

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

void CenLoc_LockUnlockStates()
{

	if(CenLoc_CurrentState == STD_HIGH && SecAlm_Trigger == STD_LOW)
	{

		CenLoc_UnlockSequence();
		CenLoc_ControlAlarmLed();

	}
	else if(CenLoc_CurrentState == STD_LOW && SecAlm_Trigger == STD_LOW)
	{

		CenLoc_LockSequence();
		CenLoc_ControlAlarmLed();

	}

}

void CenLoc_ToggleBuzzer(uint8 PinState)
{

	Rte_Call_Gpio_R_GpioPort_HAL_GPIO_WritePin(CENLOC_BUZZER_PORT, CENLOC_BUZZER_PIN, PinState);

}

void CenLoc_MainFunction()
{

	CenLoc_State();
	CenLoc_LockUnlockStates();

}
