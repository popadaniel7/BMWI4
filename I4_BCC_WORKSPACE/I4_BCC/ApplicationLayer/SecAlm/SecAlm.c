#include "tim.h"
#include "CenLoc.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ExtLights.h"
#include "IntLights.h"
#include "SecAlm.h"
#include "Std_Types.h"
#include "usart.h"
#include "gpio.h"

uint8 SecAlm_Trigger;
uint8 SecAlm_Counter;
uint8 SecAlm_PreviousState;
uint8 SecAlm_VibSenStatusFlag;
uint8 SecAlm_VibSenStateSetToOff;
uint8 SecAlm_PinStateChange;

StdReturnType SecAlmVibSenStatus();
StdReturnType SecAlmVibeSenReadPin();
StdReturnType SecAlmInit();
void SecAlmMainFunction();
void SecAlmToggleAlarmBuzzer(uint8 PinState);
void SecAlmToggleAlarmLed(uint8 PinState);
void SecAlmState();
void SecAlmLightsBuzzerControl();
void SecAlmTurnOnExtLights();

StdReturnType SecAlmVibeSenReadPin()
{

	uint8 PinState = 0;

	PinState = HAL_GPIO_ReadPin(SECALM_VIBSEN_PORT, SECALM_VIBSEN_PIN);

	return PinState;

}

StdReturnType SecAlmVibSenStatus()
{

	//SecAlm_VibSenStatusFlag = SecAlmVibeSenReadPin();

	if(CenLoc_CurrentState == STD_HIGH)
	{

		SecAlm_VibSenStateSetToOff = STD_HIGH;

	}
	else if(CenLoc_CurrentState == STD_LOW)
	{

		SecAlm_VibSenStateSetToOff = STD_LOW;

	}
	else
	{

		/* do nothing */

	}

	if(SecAlm_VibSenStateSetToOff == STD_LOW && SecAlm_VibSenStatusFlag == STD_LOW)
	{

		return STD_LOW;

	}
	else
	{

		/* do nothing */

	}

	return STD_HIGH;

}

void SecAlmState()
{

	if(SecAlm_PreviousState != SecAlm_Trigger)
	{

		HAL_TIM_Base_Init(&htim5);
		SecAlm_PreviousState = SecAlm_Trigger;

	}
	else
	{

		/* do nothing */

	}

	if(SecAlmVibSenStatus() == STD_HIGH)
	{

		SecAlm_Trigger = SecAlmVibSenStatus();

	}
	else if(SecAlmVibSenStatus() == STD_LOW)
	{

		SecAlm_Trigger = SecAlmVibSenStatus();

	}
	else
	{

		/* do nothing */

	}

}

void SecAlmTurnOnExtLights()
{

	ExtLightsLowBeam(SecAlm_PinStateChange);
	ExtLightsRearPositionLight(SecAlm_PinStateChange);
	ExtLightsFrontFogLight(SecAlm_PinStateChange);
	ExtLightsRearFogLight(SecAlm_PinStateChange);
	ExtLightsTurnSignalRight(SecAlm_PinStateChange);
	ExtLightsTurnSignalLeft(SecAlm_PinStateChange);

}

void SecAlmLightsBuzzerControl()
{

	SecAlmState();

	if(SecAlm_Trigger == STD_HIGH)
	{

		HAL_TIM_Base_Start(&htim5);

		if(__HAL_TIM_GET_COUNTER(&htim5) < 100000)
		{

			HAL_TIM_Base_Start(&htim4);

			if(__HAL_TIM_GET_COUNTER(&htim4) < 5000)
			{

				SecAlm_PinStateChange = STD_HIGH;
				SecAlmTurnOnExtLights();

			}
			else if(5000 < __HAL_TIM_GET_COUNTER(&htim4) && __HAL_TIM_GET_COUNTER(&htim4) < 10000)
			{
				SecAlm_PinStateChange = STD_LOW;
				SecAlmTurnOnExtLights();
			}
			else
			{

				/* do nothing */

			}

		}
		else if(__HAL_TIM_GET_COUNTER(&htim5) > 100000)
		{

			SecAlm_Trigger = STD_LOW;
			HAL_TIM_Base_Stop(&htim5);

		}
		else
		{

			/* do nothing */

		}

	}
	else if(SecAlm_Trigger == STD_LOW)
	{

		HAL_TIM_Base_Stop(&htim4);
		SecAlm_PinStateChange = STD_LOW;
		SecAlmTurnOnExtLights();

	}
	else
	{

		/* do nothing */

	}

}

void SecAlmMainFunction()
{

	SecAlmLightsBuzzerControl();

}

StdReturnType SecAlmInit()
{

	SecAlm_Trigger 				= STD_LOW;
	SecAlm_Counter 				= STD_LOW;
	SecAlm_PreviousState 		= STD_LOW;
	SecAlm_VibSenStatusFlag 	= STD_LOW;
	SecAlm_VibSenStateSetToOff 	= STD_LOW;
	SecAlm_PinStateChange 		= STD_LOW;

	return E_OK;

}

void SecAlmToggleAlarmBuzzer(uint8 PinState)
{

	HAL_GPIO_WritePin(SECALM_BUZZER_PORT, SECALM_BUZZER_PIN, PinState);

}

void SecAlmToggleAlarmLed(uint8 PinState)
{

	HAL_GPIO_WritePin(SECALM_LED_PORT, SECALM_LED_PIN, PinState);

}
