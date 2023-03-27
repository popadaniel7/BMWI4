#include "tim.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "usart.h"
#include "gpio.h"
#include "AdcH.h"
#include "main.h"
#include "CenLoc.h"
#include "ExtLights.h"
#include "SecAlm.h"
#include "BTC.h"
#include "Project_Definitions.h"
#include "RTE.h"

#define SECALM_DEBOUNCETIME_SENSOR_VALUE 50

uint8 SecAlm_Trigger;
uint8 SecAlm_PinStateChange;
uint8 SecAlm_TriggerIRQCounterForTimer4;
uint16 SecAlm_SensorStatusCounter;
uint16 SecAlm_SensorStatus;

uint32 SecAlm_VibeSenReadPin();
StdReturnType SecAlm_VibSenStatus();
StdReturnType SecAlm_Init();
void SecAlm_MainFunction();
void SecAlm_ToggleAlarmBuzzer(uint8 PinState);
void SecAlm_ToggleAlarmLed(uint8 PinState);
void SecAlm_TurnOnExtLights();
void SecAlm_LightsBuzzerControl();

uint8 SecAlm_TriggerPreviousState;

void SecAlm_LightsBuzzerControl()
{

	uint32 sensorStatus = STD_LOW;

	sensorStatus = SecAlm_VibSenStatus();

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

		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStop(Os_SecAlmAlarm_TimerHandle);
		SecAlm_TurnOnExtLights();

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

		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStart(Os_SecAlmAlarm_TimerHandle, 10000);

		if(SecAlm_TriggerIRQCounterForTimer4 % 2 == 1)
		{

			SecAlm_PinStateChange = STD_HIGH;
			SecAlm_TurnOnExtLights();

		}
		else if(SecAlm_TriggerIRQCounterForTimer4 % 2 == 0)
		{

			SecAlm_PinStateChange = STD_LOW;
			SecAlm_TurnOnExtLights();

		}
		else
		{

			/* do nothing */

		}

	}
	else if(SecAlm_Trigger == STD_LOW)
	{

		SecAlm_ToggleAlarmBuzzer(STD_LOW);

	}
	else
	{

		/* do nothing */

	}

}


uint32 SecAlm_VibSenReadSensorValue()
{

	uint32 sensorValue = STD_LOW;

	Rte_Call_ADC_R_ADCPort_HAL_ADC_Start_DMA(&hadc1, Adc_ChannelOne_Buffer, ADC_BUFFER_LENGTH);
	Rte_Read_Adc_AdcPort_Adc_ChannelOne_Buffer(&sensorValue, RTE_P_ADC_BUFFER_VIBSEN);

	return sensorValue;

}

StdReturnType SecAlm_VibSenStatus()
{

	uint16 sensorValue 		= STD_LOW;
	uint16 sensorStatus 	= STD_LOW;

	sensorValue = SecAlm_VibSenReadSensorValue();

	if(sensorValue == 4095)
	{

		SecAlm_SensorStatusCounter = SecAlm_SensorStatusCounter + 1;
		Rte_Call_OsTimer_R_OsTimerPort_OsTimerStart(Os_SecAlm_AlarmResetHandle, 10000);

	}
	else
	{

		/* do nothing */

	}

	if(SecAlm_SensorStatusCounter >= 500)
	{

		sensorStatus = STD_HIGH;

	}
	else if(SecAlm_SensorStatusCounter < 500)
	{

		sensorStatus = STD_LOW;

	}
	else
	{

		/* do nothing */

	}

	return sensorStatus;

}


void SecAlm_TurnOnExtLights()
{

	Rte_Call_ExtLights_R_ExtLightsPort_ExtLights_LowBeam(SecAlm_PinStateChange);
	Rte_Call_ExtLights_R_ExtLightsPort_ExtLights_RearPositionLight(SecAlm_PinStateChange);
	Rte_Call_ExtLights_R_ExtLightsPort_ExtLights_FrontFogLight(SecAlm_PinStateChange);
	Rte_Call_ExtLights_R_ExtLightsPort_ExtLights_RearFogLight(SecAlm_PinStateChange);
	Rte_Call_ExtLights_R_ExtLightsPort_ExtLights_TurnSignalRight(SecAlm_PinStateChange);
	Rte_Call_ExtLights_R_ExtLightsPort_ExtLights_TurnSignalLeft(SecAlm_PinStateChange);
	SecAlm_ToggleAlarmBuzzer(SecAlm_PinStateChange);

}

void SecAlm_MainFunction()
{

	SecAlm_LightsBuzzerControl();

}


StdReturnType SecAlm_Init()
{

	SecAlm_Trigger 						= STD_LOW;
	SecAlm_PinStateChange 				= STD_LOW;
	SecAlm_TriggerIRQCounterForTimer4 	= STD_LOW;
	SecAlm_SensorStatusCounter 			= STD_LOW;
	SecAlm_SensorStatus 				= STD_LOW;

	return E_OK;

}


void SecAlm_ToggleAlarmBuzzer(uint8 PinState)
{

	Rte_Call_Gpio_R_GpioPort_HAL_GPIO_WritePin(SECALM_BUZZER_PORT, SECALM_BUZZER_PIN, PinState);

}


void SecAlm_ToggleAlarmLed(uint8 PinState)
{

	Rte_Call_Gpio_R_GpioPort_HAL_GPIO_WritePin(SECALM_LED_PORT, SECALM_LED_PIN, PinState);

}
