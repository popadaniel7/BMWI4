#include "tim.h"
#include "CenLoc.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ExtLights.h"
#include "IntLights.h"
#include "SecAlm.h"
#include "gpio.h"
#include "Project_Definitions.h"
#include "BTC.h"

uint8 ExtLights_ReverseLight_CurrentState;
uint8 ExtLights_BrakeLight_CurrentState;
uint8 ExtLights_FlashHighBeam_CurrentState;
uint8 ExtLights_LightsSwitch_CurrentState;
uint8 ExtLights_HighBeam_CurrentState;
uint8 ExtLights_FrontFogLight_CurrentState;
uint8 ExtLights_TurnSignalLeft_CurrentState;
uint8 ExtLights_TurnSignalRight_CurrentState;
uint8 ExtLights_HazardLight_CurrentState;
uint8 ExtLights_RearFogLight_CurrentState;
uint8 Btc_LightSwitch;
uint8 Btc_HighBeam;
uint8 Btc_FlashHighBeam;
uint8 Btc_FrontFogLight;
uint8 Btc_TurnSignalLeft;
uint8 Btc_TurnSignalRight;
uint8 Btc_HazardLight;
uint8 Btc_BrakeLight;
uint8 Btc_RearFogLight;
uint8 Btc_ReverseLight;
uint8 ExtLights_RTS_PrevState;
uint8 ExtLights_LTS_PrevState;
uint8 ExtLights_HL_PrevState;
uint32 ExtLights_RTSFlag;
uint32 ExtLights_LTSFlag;
uint32 ExtLights_HLFlag;


static uint8 lightSensorState;

void ExtLightsMainFunction();
void ExtLightsLowBeam(uint8 PinState);
void ExtLightsHighBeam(uint8 PinState);
void ExtLightsDayTimeRunningLight(uint8 PinState);
void ExtLightsTurnSignalLeft(uint8 PinState);
void ExtLightsTurnSignalRight(uint8 PinState);
void ExtLightsFrontFogLight(uint8 PinState);
void ExtLightsRearPositionLight(uint8 PinState);
void ExtLightsBrakeLight(uint8 PinState);
void ExtLightsLicensePlateLight(uint8 PinState);
void ExtLightsRearFogLight(uint8 PinState);
void ExtLightsReverseLight(uint8 PinState);
void ExtLightsRxBtcState();
void ExtLightsLightState();
void ExtLightsTurnSignalHazardLight();
void ExtLightsLightSwitchMode();
void ExtLightsPrevStateTSHL();
StdReturnType ExtLightsInit();
uint32 ExtLightsLightReadSensorValue();

void ExtLightsTurnSignalHazardLight()
{

	if(ExtLights_TurnSignalLeft_CurrentState == STD_HIGH)
	{

		HAL_TIM_Base_Start_IT(&htim2);

		if(ExtLights_LTSFlag % 2 == 0)
		{

			ExtLightsTurnSignalLeft(STD_HIGH);

		}
		else if(ExtLights_LTSFlag % 2 == STD_HIGH)
		{

			ExtLightsTurnSignalLeft(STD_LOW);

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

	if(ExtLights_TurnSignalRight_CurrentState == STD_HIGH)
	{

		HAL_TIM_Base_Start_IT(&htim2);

		if(ExtLights_RTSFlag % 2 == STD_LOW)
		{

			ExtLightsTurnSignalRight(STD_HIGH);

		}
		else if(ExtLights_RTSFlag % 2 == STD_HIGH)
		{

			ExtLightsTurnSignalRight(STD_LOW);

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

	if(ExtLights_HazardLight_CurrentState == STD_HIGH)
	{

		HAL_TIM_Base_Start_IT(&htim2);

		if(ExtLights_HLFlag % 2 == STD_LOW)
		{

			ExtLightsTurnSignalLeft(STD_HIGH);
			ExtLightsTurnSignalRight(STD_HIGH);

		}
		else if(ExtLights_HLFlag % 2 == STD_HIGH)
		{

			ExtLightsTurnSignalLeft(STD_LOW);
			ExtLightsTurnSignalRight(STD_LOW);

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

	if(ExtLights_TurnSignalRight_CurrentState == STD_LOW && ExtLights_HazardLight_CurrentState == STD_LOW)
	{

		ExtLightsTurnSignalRight(STD_LOW);

	}
	else
	{

		/* do nothing */

	}

	if(ExtLights_TurnSignalLeft_CurrentState == STD_LOW && ExtLights_HazardLight_CurrentState == STD_LOW)
	{

		ExtLightsTurnSignalLeft(STD_LOW);

	}
	else
	{

		/* do nothing */

	}

}

void ExtLightsPrevStateTSHL()
{

	if(ExtLights_TurnSignalLeft_CurrentState != ExtLights_LTS_PrevState)
	{

		ExtLights_LTS_PrevState = ExtLights_TurnSignalLeft_CurrentState;
		ExtLights_LTSFlag = 0;

	}
	else
	{

		/* do nothing */

	}

	if(ExtLights_TurnSignalRight_CurrentState != ExtLights_RTS_PrevState)
	{

		ExtLights_RTS_PrevState = ExtLights_TurnSignalRight_CurrentState;
		ExtLights_RTSFlag = 0;

	}
	else
	{

		/* do nothing */

	}

	if(ExtLights_HazardLight_CurrentState != ExtLights_HL_PrevState)
	{

		ExtLights_HL_PrevState = ExtLights_HazardLight_CurrentState;
		ExtLights_HLFlag = 0;

	}
	else
	{

		/* do nothing */

	}

}

void ExtLightsLightState()
{

	if(CenLoc_FollowMeHomeState == STD_HIGH)
	{

		ExtLightsLowBeam(CenLoc_FollowMeHomeState);
		ExtLightsDayTimeRunningLight(CenLoc_FollowMeHomeState);
		ExtLightsRearPositionLight(CenLoc_FollowMeHomeState);
		ExtLightsLicensePlateLight(CenLoc_FollowMeHomeState);

	}
	else if(CenLoc_FollowMeHomeState == STD_LOW && ExtLights_LightsSwitch_CurrentState == 0)
	{

		ExtLights_LightsSwitch_CurrentState = EXTLIGHTS_LIGHTSWITCH_STATEZERO;
		HAL_TIM_Base_Stop_IT(&htim5);

	}

	if(ExtLights_ReverseLight_CurrentState == STD_HIGH ||
				ExtLights_BrakeLight_CurrentState == STD_HIGH ||
				ExtLights_FlashHighBeam_CurrentState == STD_HIGH ||
				ExtLights_LightsSwitch_CurrentState != STD_LOW ||
				ExtLights_HighBeam_CurrentState == STD_HIGH ||
				ExtLights_FrontFogLight_CurrentState == STD_HIGH ||
				ExtLights_TurnSignalLeft_CurrentState == STD_HIGH ||
				ExtLights_TurnSignalRight_CurrentState == STD_HIGH ||
				ExtLights_HazardLight_CurrentState == STD_HIGH ||
				ExtLights_RearFogLight_CurrentState == STD_HIGH)
	{

		CenLoc_FollowMeHomeState = STD_LOW;
		CenLoc_Tim5IRQFlag = 2;

	}
	else
	{

		/* do nothing */

	}

	if(CenLoc_BlinkState == STD_HIGH)
	{

		ExtLightsTurnSignalLeft(CenLoc_BlinkState);
		ExtLightsTurnSignalRight(CenLoc_BlinkState);

	}
	else if(CenLoc_BlinkState == STD_LOW)
	{

		ExtLightsTurnSignalLeft(CenLoc_BlinkState);
		ExtLightsTurnSignalRight(CenLoc_BlinkState);

	}
	else if(CenLoc_BlinkState == 2)
	{

		ExtLightsTurnSignalHazardLight();

	}
	else
	{

		/* do nothing */

	}

	ExtLightsLightSwitchMode();
	ExtLightsReverseLight(ExtLights_ReverseLight_CurrentState);
	ExtLightsBrakeLight(ExtLights_BrakeLight_CurrentState);
	ExtLightsHighBeam(ExtLights_HighBeam_CurrentState);
	ExtLightsRearFogLight(ExtLights_RearFogLight_CurrentState);
	ExtLightsFrontFogLight(ExtLights_FrontFogLight_CurrentState);

}

void ExtLightsMainFunction()
{

	ExtLightsRxBtcState();
	ExtLightsLightState();
	ExtLightsPrevStateTSHL();

}

void ExtLightsLightSwitchMode()
{

	switch(ExtLights_LightsSwitch_CurrentState)
	{
		case EXTLIGHTS_LIGHTSWITCH_STATEZERO:

			ExtLightsLowBeam(STD_LOW);
			ExtLightsDayTimeRunningLight(STD_LOW);
			ExtLightsRearPositionLight(STD_LOW);
			ExtLightsLicensePlateLight(STD_LOW);

			break;

		case EXTLIGHTS_LIGHTSWITCH_STATEONE:

			lightSensorState = ExtLightsLightReadSensorValue();

			if(lightSensorState < EXTLIGHTS_LIGHTSENSOR_DAYNIGHTVALUE)
			{

				ExtLightsLowBeam(STD_HIGH);
				ExtLightsDayTimeRunningLight(STD_HIGH);
				ExtLightsRearPositionLight(STD_HIGH);
				ExtLightsLicensePlateLight(STD_HIGH);

			}
			else if(lightSensorState > EXTLIGHTS_LIGHTSENSOR_DAYNIGHTVALUE)
			{

				ExtLightsLowBeam(STD_LOW);
				ExtLightsDayTimeRunningLight(STD_HIGH);
				ExtLightsRearPositionLight(STD_LOW);
				ExtLightsLicensePlateLight(STD_LOW);

			}

			break;

		case EXTLIGHTS_LIGHTSWITCH_STATETWO:

			ExtLightsLowBeam(STD_LOW);
			ExtLightsDayTimeRunningLight(STD_HIGH);
			ExtLightsRearPositionLight(STD_HIGH);
			ExtLightsLicensePlateLight(STD_HIGH);

			break;

		case EXTLIGHTS_LIGHTSWITCH_STATETHREE:

			ExtLightsLowBeam(STD_HIGH);
			ExtLightsDayTimeRunningLight(STD_HIGH);
			ExtLightsRearPositionLight(STD_HIGH);
			ExtLightsLicensePlateLight(STD_HIGH);

			break;

		default:

			break;

	}

}

StdReturnType ExtLightsInit()
{

	ExtLights_ReverseLight_CurrentState 		= STD_LOW;
	ExtLights_BrakeLight_CurrentState 			= STD_LOW;
	ExtLights_FlashHighBeam_CurrentState 		= STD_LOW;
	ExtLights_LightsSwitch_CurrentState 		= STD_LOW;
	ExtLights_HighBeam_CurrentState 			= STD_LOW;
	ExtLights_FrontFogLight_CurrentState 		= STD_LOW;
	ExtLights_TurnSignalLeft_CurrentState 		= STD_LOW;
	ExtLights_TurnSignalRight_CurrentState 		= STD_LOW;
	ExtLights_HazardLight_CurrentState 			= STD_LOW;
	ExtLights_RearFogLight_CurrentState 		= STD_LOW;
	Btc_LightSwitch 							= STD_LOW;
	Btc_HighBeam 								= STD_LOW;
	Btc_FlashHighBeam 							= STD_LOW;
	Btc_FrontFogLight 							= STD_LOW;
	Btc_TurnSignalLeft 							= STD_LOW;
	Btc_TurnSignalRight 						= STD_LOW;
	Btc_HazardLight 							= STD_LOW;
	Btc_BrakeLight								= STD_LOW;
	Btc_RearFogLight 							= STD_LOW;
	Btc_ReverseLight							= STD_LOW;
	ExtLights_RTSFlag 							= STD_LOW;
	ExtLights_LTSFlag 							= STD_LOW;
	ExtLights_HLFlag 							= STD_LOW;

	return E_OK;

}

void ExtLightsRxBtcState()
{

	ExtLights_ReverseLight_CurrentState 	= Btc_ReverseLight;
	ExtLights_LightsSwitch_CurrentState 	= Btc_LightSwitch;
	ExtLights_HighBeam_CurrentState 		= Btc_HighBeam;
	ExtLights_FrontFogLight_CurrentState 	= Btc_FrontFogLight;
	ExtLights_RearFogLight_CurrentState 	= Btc_RearFogLight;
	ExtLights_BrakeLight_CurrentState 		= Btc_BrakeLight;
	ExtLights_TurnSignalLeft_CurrentState 	= Btc_TurnSignalLeft;
	ExtLights_TurnSignalRight_CurrentState 	= Btc_TurnSignalRight;
	ExtLights_HazardLight_CurrentState		= Btc_HazardLight;

}

uint32 ExtLightsLightReadSensorValue()
{

	uint8 sensorValue = 0;

	sensorValue = ADC_BUFFER[2];

	return sensorValue;

}

void ExtLightsLowBeam(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_LOWBEAM_PORT, EXTLIGHTS_LOWBEAM_PIN, PinState);

}

void ExtLightsHighBeam(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_HIGHBEAM_PORT, EXTLIGHTS_HIGHBEAM_PIN, PinState);

}

void ExtLightsDayTimeRunningLight(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_DAYTIMERUNNINGLIGHT_PORT, EXTLIGHTS_DAYTIMERUNNINGLIGHT_PIN, PinState);

}

void ExtLightsFrontFogLight(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_FRONTFOGLIGHT_PORT, EXTLIGHTS_FRONTFOGLIGHT_PIN, PinState);

}

void ExtLightsTurnSignalLeft(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_TURNSIGNALLEFT_PORT, EXTLIGHTS_TURNSIGNALLEFT_PIN, PinState);

}

void ExtLightsTurnSignalRight(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_TURNSIGNALRIGHT_PORT, EXTLIGHTS_TURNSIGNALRIGHT_PIN, PinState);

}

void ExtLightsRearPositionLight(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_REARPOSITIONLIGHT_PORT, EXTLIGHTS_REARPOSITIONLIGHT_PIN, PinState);

}

void ExtLightsRearFogLight(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_REARFOGLIGHT_PORT, EXTLIGHTS_REARFOGLIGHT_PIN, PinState);

}

void ExtLightsBrakeLight(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_BRAKELIGHT_PORT, EXTLIGHTS_BRAKELIGHT_PIN, PinState);

}

void ExtLightsReverseLight(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_REVERSELIGHT_PORT, EXTLIGHTS_REVERSELIGHT_PIN, PinState);

}

void ExtLightsLicensePlateLight(uint8 PinState)
{

	HAL_GPIO_WritePin(EXTLIGHTS_LICENSEPLATELIGHT_PORT, EXTLIGHTS_LICENSEPLATELIGHT_PIN, PinState);

}



