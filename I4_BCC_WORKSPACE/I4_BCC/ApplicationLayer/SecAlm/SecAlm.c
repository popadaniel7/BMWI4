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
uint32 SecAlm_VibSenStatusFlag;
uint8 SecAlm_PinStateChange;
uint32 SecAlm_Timer5Value;
uint32 SecAlm_Timer4Value;

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

	uint8 status = STD_LOW;

	SecAlm_VibSenStatusFlag = SecAlmVibeSenReadPin();

	if(SecAlm_VibSenStatusFlag >= 1000)
	{

		status = STD_HIGH;

	}
	else
	{
		/* do nothing */
	}

	return status;

}

void SecAlmState()
{

	if(SecAlmVibSenStatus() == STD_HIGH && CenLoc_CurrentState == STD_LOW)
	{

		SecAlm_Trigger = STD_HIGH;

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

	if(SecAlm_Trigger == STD_HIGH)
	{

		if(SecAlm_Timer5Value > 100000)
		{

			HAL_TIM_Base_Stop(&htim5);

		}
		else
		{

			/* do nothing */

		}

		HAL_TIM_Base_Start(&htim5);
		SecAlm_Timer5Value = __HAL_TIM_GET_COUNTER(&htim5);

		if(__HAL_TIM_GET_COUNTER(&htim5) < 100000)
		{

			HAL_TIM_Base_Start(&htim4);
			SecAlm_Timer4Value = __HAL_TIM_GET_COUNTER(&htim4);

			if(__HAL_TIM_GET_COUNTER(&htim4) < 5000)
			{

				SecAlm_PinStateChange = STD_HIGH;
				SecAlmToggleAlarmBuzzer(SecAlm_PinStateChange);
				SecAlmTurnOnExtLights();

			}
			else if(5000 < __HAL_TIM_GET_COUNTER(&htim4) && __HAL_TIM_GET_COUNTER(&htim4) < 10000)
			{

				SecAlm_PinStateChange = STD_LOW;
				SecAlmToggleAlarmBuzzer(SecAlm_PinStateChange);
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
		SecAlm_VibSenStatusFlag = STD_LOW;
		SecAlmTurnOnExtLights();

	}
	else
	{

		/* do nothing */

	}

}

void SecAlmMainFunction()
{

	SecAlmState();
	SecAlmLightsBuzzerControl();

}

StdReturnType SecAlmInit()
{

	SecAlm_Trigger 				= STD_LOW;
	SecAlm_VibSenStatusFlag 	= STD_LOW;
	SecAlm_PinStateChange 		= STD_LOW;
	SecAlm_Timer5Value			= STD_LOW;
	SecAlm_Timer4Value			= STD_LOW;

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
