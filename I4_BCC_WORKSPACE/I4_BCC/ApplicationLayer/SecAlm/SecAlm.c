#include "tim.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"
#include "main.h"
#include "CenLoc.h"
#include "ExtLights.h"
#include "SecAlm.h"
#include "BTC.h"
#include "Project_Definitions.h"

#define SECALM_DEBOUNCETIME_SENSOR_VALUE 50

uint8 SecAlm_Trigger;
uint8 SecAlm_PinStateChange;
uint8 SecAlm_TriggerIRQCounterForTimer4;
uint16 SecAlm_SensorStatusCounter;
uint16 SecAlm_SensorStatus;

static uint32 lastTick 				= STD_LOW;
static uint32 currentTick 			= STD_LOW;
static uint16 debouncedSensorValue 	= STD_LOW;

uint16 SecAlmVibeSenReadPin();
StdReturnType SecAlmVibSenStatus();
StdReturnType SecAlmInit();
void SecAlmMainFunction();
void SecAlmToggleAlarmBuzzer(uint8 PinState);
void SecAlmToggleAlarmLed(uint8 PinState);
void SecAlmTurnOnExtLights();
void SecAlmLightsBuzzerControl();


uint8 SecAlm_TriggerPreviousState;
void SecAlmLightsBuzzerControl()
{

	uint16 sensorStatus = STD_LOW;

	sensorStatus = SecAlmVibSenStatus();

	if(SecAlm_TriggerPreviousState != SecAlm_Trigger && !SecAlm_Trigger)
	{

		SecAlm_TriggerIRQCounterForTimer4 = STD_LOW;

	}
	else
	{

		/* do nothing */

	}

	if(SecAlm_TriggerIRQCounterForTimer4 >= 20)
	{

		SecAlm_TriggerPreviousState 		= SecAlm_Trigger;
		CenLoc_Tim3IRQFlag 					= STD_HIGH;
		CenLoc_Tim11IRQFlag 				= STD_LOW;
		SecAlm_Trigger 						= STD_LOW;
		SecAlm_PinStateChange 				= STD_LOW;
		SecAlm_TriggerIRQCounterForTimer4 	= STD_LOW;
		SecAlm_SensorStatusCounter 			= STD_LOW;
		SecAlm_SensorStatus 				= STD_LOW;
		SecAlm_SensorStatusCounter 			= STD_LOW;

		HAL_TIM_Base_Stop_IT(&htim4);
		SecAlmTurnOnExtLights();

	}
	else
	{

		/* do nothing */

	}

	if(SecAlm_SensorStatusCounter == STD_LOW)
	{

		sensorStatus 	= STD_LOW;
		SecAlm_Trigger 	= STD_LOW;
		SecAlm_PinStateChange = STD_LOW;
	}
	else
	{

		/* do nothing */

	}

	if(sensorStatus == STD_HIGH)
	{

		SecAlm_Trigger = STD_HIGH;

	}
	else
	{

		/* do nothing */

	}

	if(SecAlm_Trigger == STD_HIGH)
	{

		HAL_TIM_Base_Start_IT(&htim4);

		if(SecAlm_TriggerIRQCounterForTimer4 % 2 == 1)
		{

			SecAlm_PinStateChange = STD_HIGH;
			SecAlmTurnOnExtLights();

		}
		else if(SecAlm_TriggerIRQCounterForTimer4 % 2 == 0)
		{

			SecAlm_PinStateChange = STD_LOW;
			SecAlmTurnOnExtLights();

		}
		else
		{

			/* do nothing */

		}

	}
	else if(SecAlm_Trigger == STD_LOW)
	{

		SecAlmToggleAlarmBuzzer(STD_LOW);

	}
	else
	{

		/* do nothing */

	}

}


uint16 SecAlmVibeSenReadPin()
{

	uint16 sensorValue = STD_LOW;

	HAL_ADC_Start_DMA(&hadc1, ADC_BUFFER, 2);

	sensorValue = ADC_BUFFER[0];

	return sensorValue;

}

StdReturnType SecAlmVibSenStatus()
{

	uint16 sensorValue 		= STD_LOW;
	uint16 sensorStatus 	= STD_LOW;

	sensorValue = SecAlmVibeSenReadPin();
	currentTick = HAL_GetTick();

	if(sensorValue != debouncedSensorValue)
	{

		if((currentTick - lastTick) >= SECALM_DEBOUNCETIME_SENSOR_VALUE)
		{

			debouncedSensorValue = sensorValue;

		}
		else
		{

			/* do nothing */

		}

		if(debouncedSensorValue == 4095)
		{

			SecAlm_SensorStatusCounter = SecAlm_SensorStatusCounter + 1;
			osTimerStart(AlarmResetHandle, 10000);

		}

	}
	else
	{

		lastTick = currentTick;

	}

	if(SecAlm_SensorStatusCounter >= 2000)
	{

		sensorStatus = STD_HIGH;

	}
	else if(SecAlm_SensorStatusCounter < 2000)
	{

		sensorStatus = STD_LOW;

	}
	else
	{

		/* do nothing */

	}

	return sensorStatus;

}


void SecAlmTurnOnExtLights()
{

	ExtLightsLowBeam(SecAlm_PinStateChange);
	ExtLightsRearPositionLight(SecAlm_PinStateChange);
	ExtLightsFrontFogLight(SecAlm_PinStateChange);
	ExtLightsRearFogLight(SecAlm_PinStateChange);
	ExtLightsTurnSignalRight(SecAlm_PinStateChange);
	ExtLightsTurnSignalLeft(SecAlm_PinStateChange);
	SecAlmToggleAlarmBuzzer(SecAlm_PinStateChange);

}

void SecAlmMainFunction()
{

	SecAlmLightsBuzzerControl();

}


StdReturnType SecAlmInit()
{

	SecAlm_Trigger 						= STD_LOW;
	SecAlm_PinStateChange 				= STD_LOW;
	SecAlm_TriggerIRQCounterForTimer4 	= STD_LOW;
	SecAlm_SensorStatusCounter 			= STD_LOW;
	SecAlm_SensorStatus 				= STD_LOW;

	HAL_TIM_Base_Init(&htim4);

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
