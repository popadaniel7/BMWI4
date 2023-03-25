#include "CrcH.h"
#include "Rte.h"

uint32 Crc_CenLoc_On;
uint32 Crc_CenLoc_Off;
uint32 Crc_ExtLights_HighBeam_On;
uint32 Crc_ExtLights_HighBeam_Off;
uint32 Crc_ExtLights_FlashHighBeam_On;
uint32 Crc_ExtLights_FlashHighBeam_Off;
uint32 Crc_ExtLights_TurnSignalLeft_On;
uint32 Crc_ExtLights_TurnSignalLeft_Off;
uint32 Crc_ExtLights_TurnSignalRight_On;
uint32 Crc_ExtLights_TurnSignalRight_Off;
uint32 Crc_ExtLights_HazardLight_On;
uint32 Crc_ExtLights_HazardLight_Off;
uint32 Crc_ExtLights_FogLightFront_On;
uint32 Crc_ExtLights_FogLightFront_Off;
uint32 Crc_ExtLights_FogLightRear_On;
uint32 Crc_ExtLights_FogLightRear_Off;
uint32 Crc_ExtLights_BrakeLight_On;
uint32 Crc_ExtLights_BrakeLight_Off;
uint32 Crc_ExtLights_ReverseLight_On;
uint32 Crc_ExtLights_ReverseLight_Off;
uint32 Crc_ExtLights_PositionZero;
uint32 Crc_ExtLights_AutomaticLights;
uint32 Crc_ExtLights_PositionLights;
uint32 Crc_ExtLights_NightTimeLights;
uint32 Crc_Ignition_Step_One;
uint32 Crc_Ignition_Step_Two;
uint32 Crc_Ignition_Turn_Off;
uint32 Crc_IntLights_InteriorLight_On;
uint32 Crc_IntLights_InteriorLights_Off;

StdReturnType Crc_VerifyUartData();
StdReturnType Crc_Init();
StdReturnType Crc_DeInit();
void Crc_MainFunction();
void Crc_InitCrcValuesForUart();
void HAL_CRC_ErrorCallback(CRC_HandleTypeDef *hcrc);

StdReturnType Crc_VerifyUartData()
{

	uint8 returnValue = E_OK;
	uint8 receivedValue = STD_LOW;
	uint32 calculatedCrc = STD_LOW;

	Rte_Read_Btc_BtcPort_Btc_ReceivedDataOnBluetooth(&receivedValue);

	calculatedCrc = HAL_CRC_Calculate(&hcrc, (uint32*)&receivedValue, 1);

	switch(receivedValue)
	{

		case RTE_P_BTC_RX_IGNITION_STEP_ONE:

			if(calculatedCrc == Crc_Ignition_Step_One)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_IGNITION_STEP_TWO:

			if(calculatedCrc == Crc_Ignition_Step_Two)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_IGNITION_TURN_OFF:

			if(calculatedCrc == Crc_Ignition_Turn_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_REVERSELIGHT_ON:

			if(calculatedCrc == Crc_ExtLights_ReverseLight_On)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_REVERSELIGHT_OFF:

			if(calculatedCrc == Crc_ExtLights_ReverseLight_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_POSITIONZERO:

			if(calculatedCrc == Crc_ExtLights_PositionZero)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_AUTOMATICLIGHTS:

			if(calculatedCrc == Crc_ExtLights_AutomaticLights)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_POSITIONLIGHTS:

			if(calculatedCrc == Crc_ExtLights_PositionLights)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_NIGHTTIMELIGHTS:

			if(calculatedCrc == Crc_ExtLights_NightTimeLights)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_CENLOC_ON:

			if(calculatedCrc == Crc_CenLoc_On)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_CENLOC_OFF:

			if(calculatedCrc == Crc_CenLoc_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_HIGHBEAM_ON:

			if(calculatedCrc == Crc_ExtLights_HighBeam_On)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_HIGHBEAM_OFF:

			if(calculatedCrc == Crc_ExtLights_HighBeam_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_FLASHHIGHBEAM_ON:

			if(calculatedCrc == Crc_ExtLights_FlashHighBeam_On)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_FLASHHIGHBEAM_OFF:

			if(calculatedCrc == Crc_ExtLights_FlashHighBeam_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_TURNSIGNALLEFT_ON:

			if(calculatedCrc == Crc_ExtLights_TurnSignalLeft_On)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_TURNSIGNALLEFT_OFF:

			if(calculatedCrc == Crc_ExtLights_TurnSignalLeft_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_TURNSIGNALRIGHT_ON:

			if(calculatedCrc == Crc_ExtLights_TurnSignalRight_On)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_TURNSIGNALRIGHT_OFF:

			if(calculatedCrc == Crc_ExtLights_TurnSignalRight_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_HAZARDLIGHT_ON:

			if(calculatedCrc == Crc_ExtLights_HazardLight_On)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_HAZARDLIGHT_OFF:

			if(calculatedCrc == Crc_ExtLights_HazardLight_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_FOGLIGHTFRONT_ON:

			if(calculatedCrc == Crc_ExtLights_FogLightFront_On)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_FOGLIGHTFRONT_OFF:

			if(calculatedCrc == Crc_ExtLights_FogLightFront_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_FOGLIGHTREAR_ON:

			if(calculatedCrc == Crc_ExtLights_FogLightRear_On)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_FOGLIGHTREAR_OFF:

			if(calculatedCrc == Crc_ExtLights_FogLightRear_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_BRAKELIGHTON:

			if(calculatedCrc == Crc_ExtLights_BrakeLight_On)
						{

							returnValue = E_OK;

						}
						else
						{

							returnValue = E_NOT_OK;

						}

			break;

		case RTE_P_BTC_RX_EXTLIGHTS_BRAKELIGHTOFF:

			if(calculatedCrc == Crc_ExtLights_BrakeLight_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_INTLIGHTS_INTERIORLIGHT_ON:

			if(calculatedCrc == Crc_IntLights_InteriorLight_On)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		case RTE_P_BTC_RX_INTLIGHTS_INTERIORLIGHT_OFF:

			if(calculatedCrc == Crc_IntLights_InteriorLights_Off)
			{

				returnValue = E_OK;

			}
			else
			{

				returnValue = E_NOT_OK;

			}

			break;

		default:

			break;

	}

	return returnValue;

}

void Crc_InitCrcValuesForUart()
{

	uint32 value = 0;

	value = RTE_P_BTC_RX_EXTLIGHTS_FOGLIGHTREAR_ON;
	Crc_ExtLights_FogLightRear_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_FOGLIGHTREAR_OFF;
	Crc_ExtLights_FogLightRear_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_CENLOC_ON;
	Crc_CenLoc_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_CENLOC_OFF;
	Crc_CenLoc_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_HIGHBEAM_ON;
	Crc_ExtLights_HighBeam_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_HIGHBEAM_OFF;
	Crc_ExtLights_HighBeam_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_FLASHHIGHBEAM_ON;
	Crc_ExtLights_FlashHighBeam_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_FLASHHIGHBEAM_OFF;
	Crc_ExtLights_FlashHighBeam_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_TURNSIGNALLEFT_ON;
	Crc_ExtLights_TurnSignalLeft_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_TURNSIGNALLEFT_OFF;
	Crc_ExtLights_TurnSignalLeft_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_TURNSIGNALRIGHT_ON;
	Crc_ExtLights_TurnSignalRight_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_TURNSIGNALRIGHT_OFF;
	Crc_ExtLights_TurnSignalRight_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_HAZARDLIGHT_ON;
	Crc_ExtLights_HazardLight_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_HAZARDLIGHT_OFF;
	Crc_ExtLights_HazardLight_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_FOGLIGHTFRONT_ON;
	Crc_ExtLights_FogLightFront_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_FOGLIGHTFRONT_OFF;
	Crc_ExtLights_FogLightFront_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_BRAKELIGHTON;
	Crc_ExtLights_BrakeLight_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_BRAKELIGHTOFF;
	Crc_ExtLights_BrakeLight_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_REVERSELIGHT_ON;
	Crc_ExtLights_ReverseLight_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_REVERSELIGHT_OFF;
	Crc_ExtLights_ReverseLight_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_POSITIONZERO;
	Crc_ExtLights_PositionZero = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_AUTOMATICLIGHTS;
	Crc_ExtLights_AutomaticLights = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_POSITIONLIGHTS;
	Crc_ExtLights_PositionLights = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_EXTLIGHTS_NIGHTTIMELIGHTS;
	Crc_ExtLights_NightTimeLights = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_IGNITION_STEP_ONE;
	Crc_Ignition_Step_One = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_IGNITION_STEP_TWO;
	Crc_Ignition_Step_Two = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_IGNITION_TURN_OFF;
	Crc_Ignition_Turn_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_INTLIGHTS_INTERIORLIGHT_ON;
	Crc_IntLights_InteriorLight_On = HAL_CRC_Calculate(&hcrc, &value, 1);

	value = RTE_P_BTC_RX_INTLIGHTS_INTERIORLIGHT_OFF;
	Crc_IntLights_InteriorLights_Off = HAL_CRC_Calculate(&hcrc, &value, 1);

}

void HAL_CRC_ErrorCallback(CRC_HandleTypeDef *hcrc)
{

	Crc_DeInit();
	Crc_Init();

}

StdReturnType Crc_Init()
{

	hcrc.Instance = CRC;

	if (HAL_CRC_Init(&hcrc) != HAL_OK)
	{

		HAL_CRC_ErrorCallback(&hcrc);

	}
	else
	{

		/* do nothing */

	}

	Crc_InitCrcValuesForUart();

	return E_OK;

}

StdReturnType Crc_DeInit()
{

	HAL_CRC_DeInit(&hcrc);

	return E_OK;

}

void Crc_MainFunction()
{

	uint32 returnValue = HAL_CRC_GetState(&hcrc);

	Crc_VerifyUartData();

	if(returnValue == HAL_CRC_STATE_ERROR)
	{

		HAL_CRC_ErrorCallback(&hcrc);

	}

}
