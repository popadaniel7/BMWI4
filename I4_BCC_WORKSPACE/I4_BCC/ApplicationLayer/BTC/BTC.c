/*****************************************
* Project: BCM I4						 *
* Developer: Daniel Popa				 *
* Module: Bluetooth Communication	     *
******************************************/
/*****************************************
*		INCLUDE PATHS					 *
******************************************/
#include "Btc.h"
#include "UartH.h"
#include "Rte.h"
#include "SystemManager.h"
/*****************************************
*		END OF INCLUDE PATHS		     *
******************************************/
/*****************************************
*		VARIABLES					 	 *
******************************************/
/* Data buffer for bluetooth communication through UART. */
uint8 Btc_DataBuffer[BTC_BUFFER_SIZE] = {STD_LOW};
/* UART data received from bluetooth module. */
uint8 Btc_RxData = STD_LOW;
/* Counter for data length. */
uint8 Btc_RxCount = STD_LOW;
/* Bluetooth command converted into uint8. */
uint8 Btc_ReceivedDataOnBluetooth = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_CenLoc = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_LightSwitch = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_HighBeam = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_FlashHighBeam = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_FrontFogLight = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_TurnSignalLeft = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_TurnSignalRight = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_HazardLight = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_BrakeLight = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_RearFogLight = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_ReverseLight = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_IntLights = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_FanValue = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_TemperatureValue = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_LegVent = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_MidVent = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_WindshieldVent = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_WindshieldDefrost = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_RearWindshieldDefrost = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_Ac = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_Recirculation = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_NoRecirculation = STD_LOW;
/* Auxiliary variable used for bluetooth command. */
uint8 Btc_AutomaticMode = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcMessage = "Present DTC in the system:\n";
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcMessageLength = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcLowBeamLeft = "Left low beam fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcLowBeamRight = "Right low beam fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcRearPositionLightLeft = "Left rear position fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcRearPositionLightRight = "Right rear position fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcRightTurnSignalFront = "Front right blinker fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcLeftTurnSignalFront = "Front left blinker fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcLeftTurnSignalRear = "Rear left blinker fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcLeftBrakeLight = "Left brake fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcRightBrakeLight = "Right brake fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcLightSensor = "Light sensor fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcVibrationSensor = "Vibration sensor fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcTemperatureSensor = "Temperature sensor fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcRearParkingSensor = "Rear parking sensor fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcFrontParkingSensor = "Front parking sensor fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcLcd = "LCD fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcHardware = "Hardware fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcBtc = "HC-05 fault.\n";
/* Diagnostic messages through HC-05. */
STATIC char* Btc_DtcMem = "EEPROM fault.\n";
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength1 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength2 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength3 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength4 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength5 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength6 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength7 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength8 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength9 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength10 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength11 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength12 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength13 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength14 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength15 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength16 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength17 = STD_LOW;
/* Diagnostic messages through HC-05. */
STATIC uint16 Btc_DtcDescriptionLength18 = STD_LOW;
/*****************************************
*		END OF VARIABLES				 *
******************************************/
/*****************************************
*		FUNCTIONS				 		 *
******************************************/
/* Bluetooth communication main function declaration. */
VOID Btc_MainFunction();
/* Request command processing function declaration. */
VOID Btc_RequestState();
/* Bluetooth command processing function declaration. */
VOID Btc_RxVal();
/*****************************************
*		END OF FUNCTIONS				 *
******************************************/
/***********************************************************************************
* Function: Btc_RequestState													   *
* Description: Process bluetooth command for request state 					       *
************************************************************************************/
VOID Btc_RequestState()
{
	if(Btc_ReceivedDataOnBluetooth == 99)
	{
		SystemManager_PerformReset();
	}
	else
	{
		/* do nothing */
	}
	if(Btc_ReceivedDataOnBluetooth == 90)
	{
		Btc_DtcMessageLength = strlen(Btc_DtcMessage);
		HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcMessage, Btc_DtcMessageLength);
		Btc_DtcDescriptionLength1 = strlen(Btc_DtcLowBeamLeft);
		Btc_DtcDescriptionLength2 = strlen(Btc_DtcLowBeamRight);
		Btc_DtcDescriptionLength3 = strlen(Btc_DtcRearPositionLightLeft);
		Btc_DtcDescriptionLength4 = strlen(Btc_DtcRearPositionLightRight);
		Btc_DtcDescriptionLength5 = strlen(Btc_DtcRightTurnSignalFront);
		Btc_DtcDescriptionLength6 = strlen(Btc_DtcLeftTurnSignalFront);
		Btc_DtcDescriptionLength7 = strlen(Btc_DtcLeftTurnSignalRear);
		Btc_DtcDescriptionLength8 = strlen(Btc_DtcRightBrakeLight);
		Btc_DtcDescriptionLength9 = strlen(Btc_DtcLeftBrakeLight);
		Btc_DtcDescriptionLength10 = strlen(Btc_DtcLightSensor);
		Btc_DtcDescriptionLength11 = strlen(Btc_DtcVibrationSensor);
		Btc_DtcDescriptionLength12 = strlen(Btc_DtcTemperatureSensor);
		Btc_DtcDescriptionLength13 = strlen(Btc_DtcRearParkingSensor);
		Btc_DtcDescriptionLength14 = strlen(Btc_DtcFrontParkingSensor);
		Btc_DtcDescriptionLength15 = strlen(Btc_DtcLcd);
		Btc_DtcDescriptionLength16 = strlen(Btc_DtcHardware);
		Btc_DtcDescriptionLength17 = strlen(Btc_DtcBtc);
		Btc_DtcDescriptionLength18 = strlen(Btc_DtcMem);
		if(Dem_DtcArray[16] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcBtc, Btc_DtcDescriptionLength17) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(Dem_DtcArray[17] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcMem, Btc_DtcDescriptionLength18) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(ExtLights_DtcArray[0] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcLowBeamLeft, Btc_DtcDescriptionLength1) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(ExtLights_DtcArray[1] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcLowBeamRight, Btc_DtcDescriptionLength2) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(ExtLights_DtcArray[2] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcRearPositionLightLeft, Btc_DtcDescriptionLength3) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(ExtLights_DtcArray[3] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcRearPositionLightRight, Btc_DtcDescriptionLength4) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(ExtLights_DtcArray[4] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcRightTurnSignalFront, Btc_DtcDescriptionLength5) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(ExtLights_DtcArray[6] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcLeftTurnSignalFront, Btc_DtcDescriptionLength6) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(ExtLights_DtcArray[7] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcLeftTurnSignalRear, Btc_DtcDescriptionLength7) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(ExtLights_DtcArray[8] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcRightBrakeLight, Btc_DtcDescriptionLength8) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(ExtLights_DtcArray[9] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcLeftBrakeLight, Btc_DtcDescriptionLength9) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(Dem_DtcArray[10] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcLightSensor, Btc_DtcDescriptionLength10) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(Dem_DtcArray[11] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcVibrationSensor, Btc_DtcDescriptionLength11) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(Dem_DtcArray[13] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcTemperatureSensor, Btc_DtcDescriptionLength12) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(Dem_DtcArray[14] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcRearParkingSensor, Btc_DtcDescriptionLength13) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(Dem_DtcArray[15] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcFrontParkingSensor, Btc_DtcDescriptionLength14) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(Dem_DtcArray[20] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcLcd, Btc_DtcDescriptionLength15) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		if(Dem_DtcArray[21] != 0 || Dem_DtcArray[22] != 0 || Dem_DtcArray[23] != 0)
		{
			while(HAL_UART_Transmit_IT(&huart1, (uint8*)Btc_DtcHardware, Btc_DtcDescriptionLength16) == HAL_BUSY);
			Rte_Runnable_Wdg_MainFunction();
		}
		else
		{
			/* do nothing */
		}
		Rte_Runnable_Wdg_MainFunction();
		Btc_ReceivedDataOnBluetooth = 0;
	}
	else
	{
		/* do nothing */
	}
}
/***********************************************************************************
* END OF Btc_RequestState											  			   *													       																	   *
************************************************************************************/
/***********************************************************************************
* Function: Btc_RxVal													   		   *
* Description: Process bluetooth commands.	 		   							   *
************************************************************************************/
VOID Btc_RxVal()
{
	if(Rte_Call_Crc_R_CrcPort_Crc_VerifyUartData() == E_OK)
	{
		if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
		{
			if(Btc_ReceivedDataOnBluetooth >= BTC_RX_HVAC_FANVALUE_MIN &&
				Btc_ReceivedDataOnBluetooth <= BTC_RX_HVAC_FANVALUE_MAX)
			{
				Btc_FanValue = Btc_ReceivedDataOnBluetooth;
				Rte_Write_Hvac_HvacPort_Hvac_FanValue(&Btc_FanValue);
			}
			else
			{
				/* do nothing */
			}

			if(Btc_ReceivedDataOnBluetooth >= BTC_RX_HVAC_TEMPERATUREVALUE_MIN &&
					Btc_ReceivedDataOnBluetooth <= BTC_RX_HVAC_TEMPERATUREVALUE_MAX)
			{
				Btc_TemperatureValue = Btc_ReceivedDataOnBluetooth;
				Rte_Write_Hvac_HvacPort_Hvac_TemperatureValue(&Btc_TemperatureValue);
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

		/* Process the command on each case and update the respective variable. */
		switch(Btc_ReceivedDataOnBluetooth)
		{
			case BTC_RX_HVAC_LEGVENT_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_LegVent = STD_HIGH;
					Rte_Write_Hvac_HvacPort_Hvac_LegVent(&Btc_LegVent);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_LEGVENT_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_LegVent = STD_LOW;
					Rte_Write_Hvac_HvacPort_Hvac_LegVent(&Btc_LegVent);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_MIDVENT_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_MidVent = STD_HIGH;
					Rte_Write_Hvac_HvacPort_Hvac_MidVent(&Btc_MidVent);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_MIDVENT_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_MidVent = STD_LOW;
					Rte_Write_Hvac_HvacPort_Hvac_MidVent(&Btc_MidVent);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_WINDSHIELDVENT_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_WindshieldVent = STD_HIGH;
					Rte_Write_Hvac_HvacPort_Hvac_WindshieldVent(&Btc_WindshieldVent);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_WINDSHIELDVENT_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_WindshieldVent = STD_LOW;
					Rte_Write_Hvac_HvacPort_Hvac_WindshieldVent(&Btc_WindshieldVent);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_WINDSHIELDDEFROST_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_WindshieldDefrost = STD_HIGH;
					Rte_Write_Hvac_HvacPort_Hvac_WindshieldDefrost(&Btc_WindshieldDefrost);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_WINDSHIELDDEFROST_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_WindshieldDefrost = STD_LOW;
					Rte_Write_Hvac_HvacPort_Hvac_WindshieldDefrost(&Btc_WindshieldDefrost);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_REARWINDSHIELDDEFROST_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_RearWindshieldDefrost = STD_HIGH;
					Rte_Write_Hvac_HvacPort_Hvac_RearWindshieldDefrost(&Btc_RearWindshieldDefrost);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_REARWINDSHIELDDEFROST_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_RearWindshieldDefrost = STD_LOW;
					Rte_Write_Hvac_HvacPort_Hvac_RearWindshieldDefrost(&Btc_RearWindshieldDefrost);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_AC_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_Ac = STD_HIGH;
					Rte_Write_Hvac_HvacPort_Hvac_Ac(&Btc_Ac);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_AC_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_Ac = STD_LOW;
					Rte_Write_Hvac_HvacPort_Hvac_Ac(&Btc_Ac);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_RECIRCULATION:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_Recirculation = STD_HIGH;
					Btc_NoRecirculation = STD_LOW;
					Rte_Write_Hvac_HvacPort_Hvac_Recirculation(&Btc_Recirculation);
					Rte_Write_Hvac_HvacPort_Hvac_NoRecirculation(&Btc_NoRecirculation);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_NORECIRCULATION:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_Recirculation = STD_LOW;
					Btc_NoRecirculation = STD_HIGH;
					Rte_Write_Hvac_HvacPort_Hvac_Recirculation(&Btc_Recirculation);
					Rte_Write_Hvac_HvacPort_Hvac_NoRecirculation(&Btc_NoRecirculation);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_AUTOMATICMODE_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_AutomaticMode = STD_HIGH;
					Rte_Write_Hvac_HvacPort_Hvac_AutomaticMode(&Btc_AutomaticMode);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_HVAC_AUTOMATICMODE_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_AutomaticMode = STD_LOW;
					Rte_Write_Hvac_HvacPort_Hvac_AutomaticMode(&Btc_AutomaticMode);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_REVERSELIGHT_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_ReverseLight = STD_HIGH;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_ReverseLight_CurrentState(&Btc_ReverseLight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_REVERSELIGHT_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_ReverseLight = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_ReverseLight_CurrentState(&Btc_ReverseLight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_POSITIONZERO:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_LightSwitch = BTC_RX_EXTLIGHTS_POSITIONZERO;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_LightsSwitch_CurrentState(&Btc_LightSwitch);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_AUTOMATICLIGHTS:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_LightSwitch = BTC_RX_EXTLIGHTS_AUTOMATICLIGHTS;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_LightsSwitch_CurrentState(&Btc_LightSwitch);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_POSITIONLIGHTS:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_LightSwitch = BTC_RX_EXTLIGHTS_POSITIONLIGHTS;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_LightsSwitch_CurrentState(&Btc_LightSwitch);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_NIGHTTIMELIGHTS:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_LightSwitch = BTC_RX_EXTLIGHTS_NIGHTTIMELIGHTS;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_LightsSwitch_CurrentState(&Btc_LightSwitch);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_CENLOC_ON:
				Btc_CenLoc = STD_HIGH;
				Rte_Write_CenLoc_CenLocPort_CenLoc_CurrentState(&Btc_CenLoc);
				break;
			case BTC_RX_CENLOC_OFF:
				Btc_CenLoc = STD_LOW;
				Rte_Write_CenLoc_CenLocPort_CenLoc_CurrentState(&Btc_CenLoc);
				break;
			case BTC_RX_EXTLIGHTS_HIGHBEAM_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_HighBeam = STD_HIGH;
					Btc_FlashHighBeam = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_HighBeam_CurrentState(&Btc_HighBeam);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_HIGHBEAM_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_HighBeam = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_HighBeam_CurrentState(&Btc_HighBeam);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_TURNSIGNALLEFT_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_TurnSignalLeft = STD_HIGH;
					Btc_TurnSignalRight = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_TurnSignalLeft_CurrentState(&Btc_TurnSignalLeft);
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_TurnSignalRight_CurrentState(&Btc_TurnSignalRight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_TURNSIGNALLEFT_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_TurnSignalLeft = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_TurnSignalLeft_CurrentState(&Btc_TurnSignalLeft);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_TURNSIGNALRIGHT_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_TurnSignalRight = STD_HIGH;
					Btc_TurnSignalLeft = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_TurnSignalLeft_CurrentState(&Btc_TurnSignalLeft);
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_TurnSignalRight_CurrentState(&Btc_TurnSignalRight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_TURNSIGNALRIGHT_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_TurnSignalRight = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_TurnSignalRight_CurrentState(&Btc_TurnSignalRight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_HAZARDLIGHT_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_HazardLight = STD_HIGH;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_HazardLight_CurrentState(&Btc_HazardLight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_HAZARDLIGHT_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_HazardLight = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_HazardLight_CurrentState(&Btc_HazardLight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_FOGLIGHTFRONT_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_FrontFogLight = STD_HIGH;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_FrontFogLight_CurrentState(&Btc_FrontFogLight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_FOGLIGHTFRONT_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_FrontFogLight = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_FrontFogLight_CurrentState(&Btc_FrontFogLight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_FOGLIGHTREAR_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_RearFogLight = STD_HIGH;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_RearFogLight_CurrentState(&Btc_RearFogLight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_FOGLIGHTREAR_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_RearFogLight = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_RearFogLight_CurrentState(&Btc_RearFogLight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_BRAKELIGHTON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_BrakeLight = STD_HIGH;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_BrakeLight_CurrentState(&Btc_BrakeLight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_EXTLIGHTS_BRAKELIGHTOFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_BrakeLight = STD_LOW;
					Rte_Write_ExtLights_ExtLightsPort_ExtLights_BrakeLight_CurrentState(&Btc_BrakeLight);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_INTLIGHTS_INTERIORLIGHT_ON:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_IntLights = STD_HIGH;
					Rte_Write_IntLights_IntLightsPort_IntLights_CurrentState(&Btc_IntLights);
				}
				else
				{
					/* do nothing */
				}
				break;
			case BTC_RX_INTLIGHTS_INTERIORLIGHT_OFF:
				if(Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH)
				{
					Btc_IntLights = STD_LOW;
					Rte_Write_IntLights_IntLightsPort_IntLights_CurrentState(&Btc_IntLights);
				}
				else
				{
					/* do nothing */
				}
				break;
			default:
				break;
		}
	}
	else
	{
		/* do nothing */
	}
}
/***********************************************************************************
* END OF Btc_RxVal											  					   * 		   																	       																	   *
************************************************************************************/
/***********************************************************************************
* Function: Btc_MainFunction											 		   *
* Description: Process bluetooth communication states.					           *
************************************************************************************/
VOID Btc_MainFunction()
{
	Btc_RxVal();
	Btc_RequestState();
}
/***********************************************************************************
* END OF Btc_MainFunction											  			   * 		   																	       																	   *
************************************************************************************/
