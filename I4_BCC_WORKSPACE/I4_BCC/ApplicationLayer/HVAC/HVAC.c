#include "HVAC.h"
#include "I2cLcd.h"
#include "adc.h"
#include "Project_Definitions.h"

uint8 HVAC_CurrentState;
uint8 HVAC_TemperatureValue;
uint8 HVAC_FanValue;
uint8 HVAC_LegVents_CurrentState;
uint8 HVAC_MidVents_CurrentState;
uint8 HVAC_WindshieldVents_CurrentState;
uint8 HVAC_WindshieldDefrost_CurrentState;
uint8 HVAC_AC_CurrentState;
uint8 HVAC_AutomaticMode_CurrentState;
uint8 HVAC_RecirculationMode_CurrentState;
uint8 HVAC_BackwindowDefrost_CurrentState;
uint8 Btc_TemperatureValue;
uint8 Btc_FanValue;
uint8 Btc_LegVents;
uint8 Btc_MidVents;
uint8 Btc_WindshieldVents;
uint8 Btc_WindshieldDefrost;
uint8 Btc_BackwindowDefrost;
uint8 Btc_AC;
uint8 Btc_AutomaticMode;
uint8 Btc_RecirculationMode;
uint8 Btc_NormalMode;

float HVAC_TemSenAdcRxValue;
float HVAC_TemSenRxTemperature;

uint32 ADC_BUFFER[ADC_BUFFER_LENGTH] = {0};

void HVACTemSenTemperatureStatus();
float HVACTemSenReturnTemperatureValue(float TemSenVal);
float HVACTemSenAdcReceivedValues();

StdReturnType HVACInit();
void HVACMainFunction();
void HVACState();
void HVACI2cTxToLcd();

void HVACTemSenTemperatureStatus()
{

	float tempStatus = 0;

	tempStatus = HVACTemSenAdcReceivedValues();

	if(tempStatus <= 3)
	{
		//buzz
		//SecAlmToggleAlarmBuzzer(STD_HIGH);

	}

}

float HVACTemSenReturnTemperatureValue(float TemSenVal)
{

	/* redo */

	return 1;

}

float HVACTemSenAdcReceivedValues()
{

	uint32 RxTem = 0;

	HAL_ADC_Start_DMA(&hadc1, ADC_BUFFER, 6);
	RxTem = HVACTemSenReturnTemperatureValue(ADC_BUFFER[0]);

	return RxTem;

}


void HVACI2cTxToLcd()
{

	if(HVAC_CurrentState == STD_LOW)
	{

		lcd_clear();

	}
	else if(HVAC_CurrentState == STD_HIGH)
	{

		lcd_put_cur(0, 0);
		lcd_send_string("F=");
		lcd_put_cur(0, 2);
		lcd_send_data(HVAC_FanValue);
		lcd_put_cur(0, 4);
		lcd_send_string("T=");
		lcd_put_cur(0, 6);
		lcd_send_data(HVAC_TemperatureValue);
		lcd_put_cur(0, 8);

		if(HVAC_LegVents_CurrentState == STD_HIGH)
		{

			lcd_send_string("L");

		}
		else if(HVAC_LegVents_CurrentState == STD_LOW)
		{

			lcd_send_string(" ");

		}
		else
		{

			/* do nothing */

		}

		lcd_put_cur(0, 9);

		if(HVAC_MidVents_CurrentState == STD_HIGH)
		{

			lcd_send_string("M");

		}
		else if(HVAC_MidVents_CurrentState == STD_LOW)
		{

			lcd_send_string(" ");

		}
		else
		{

			/* do nothing */

		}

		lcd_put_cur(0, 10);

		if(HVAC_WindshieldVents_CurrentState == STD_HIGH)
		{

			lcd_send_string("W");

		}
		else if(HVAC_WindshieldVents_CurrentState == STD_LOW)
		{

			lcd_send_string(" ");

		}
		else
		{

			/* do nothing */

		}

		lcd_put_cur(0, 10);

		if(HVAC_WindshieldVents_CurrentState == STD_HIGH)
		{

			lcd_send_string("W");

		}
		else if(HVAC_WindshieldVents_CurrentState == STD_LOW)
		{

			lcd_send_string(" ");

		}
		else
		{

			/* do nothing */

		}

		lcd_put_cur(0, 11);

		if(HVAC_WindshieldDefrost_CurrentState == STD_HIGH)
		{

			lcd_send_string("WD");

		}
		else if(HVAC_WindshieldDefrost_CurrentState == STD_LOW)
		{

			lcd_send_string("  ");

		}
		else
		{

			/* do nothing */

		}

		lcd_put_cur(0, 13);

		if(HVAC_BackwindowDefrost_CurrentState == STD_HIGH)
		{

			lcd_send_string("BD");

		}
		else if(HVAC_BackwindowDefrost_CurrentState == STD_LOW)
		{

			lcd_send_string("  ");

		}
		else
		{

			/* do nothing */

		}

		lcd_put_cur(1, 0);

		if(HVAC_RecirculationMode_CurrentState == STD_HIGH && HVAC_AutomaticMode_CurrentState == STD_LOW)
		{

			lcd_send_string("(C)");

		}
		else if(HVAC_RecirculationMode_CurrentState == STD_LOW && HVAC_AutomaticMode_CurrentState == STD_HIGH)
		{

			lcd_send_string("(A)");

		}
		else if(HVAC_RecirculationMode_CurrentState == STD_LOW && HVAC_AutomaticMode_CurrentState == STD_LOW)
		{

			lcd_send_string("(N)");

		}
		else
		{

			/* do nothing */

		}

		lcd_put_cur(1, 3);

		if(HVAC_AutomaticMode_CurrentState == STD_HIGH)
		{

			lcd_send_string("AUTO");

		}
		else if(HVAC_AutomaticMode_CurrentState == STD_LOW)
		{

			lcd_send_string("    ");

		}
		else
		{

			/* do nothing */

		}

		lcd_put_cur(1, 7);
		lcd_send_string("Tc: ");
		lcd_put_cur(1, 11);
		lcd_send_data(HVAC_TemSenRxTemperature);

	}
	else
	{

		/* do nothing */

	}



}

void HVACMainFunction()
{

	//HVACI2cTxToLcd();
	HVAC_TemSenRxTemperature = HVACTemSenAdcReceivedValues();
	HVACState();

}

void HVACState()
{

	HVAC_BackwindowDefrost_CurrentState 	= Btc_BackwindowDefrost;
	HVAC_AC_CurrentState 					= Btc_AC;
	HVAC_RecirculationMode_CurrentState 	= Btc_RecirculationMode;

	if(Btc_TemperatureValue != STD_LOW)
	{

		HVAC_TemperatureValue = Btc_TemperatureValue;

	}
	else if(Btc_TemperatureValue == STD_LOW)
	{

		Btc_TemperatureValue 	= 22;
		Btc_FanValue 		= 1;

	}
	else
	{

		/* do nothing */

	}

	if(Btc_FanValue == STD_LOW)
	{

		HVAC_CurrentState = STD_LOW;

	}
	else if(Btc_FanValue != STD_LOW)
	{

		HVAC_CurrentState 	= STD_HIGH;
		HVAC_FanValue 		= Btc_FanValue;

	}
	else
	{

		/* do nothing */

	}

	if(Btc_LegVents == STD_HIGH)
	{

		Btc_AutomaticMode 			= STD_LOW;
		HVAC_LegVents_CurrentState 	= Btc_LegVents;

	}
	else if(Btc_LegVents == STD_LOW)
	{

		Btc_AutomaticMode 			= STD_LOW;
		HVAC_LegVents_CurrentState 	= Btc_LegVents;

	}
	else
	{

		/* do nothing */

	}

	if(Btc_MidVents == STD_HIGH)
	{

		Btc_AutomaticMode 			= STD_LOW;
		HVAC_MidVents_CurrentState 	= Btc_MidVents;

	}
	else if(Btc_MidVents == STD_LOW)
	{

		Btc_AutomaticMode 			= STD_LOW;
		HVAC_MidVents_CurrentState 	= Btc_MidVents;

	}
	else
	{

		/* do nothing */

	}

	if(Btc_WindshieldVents == STD_HIGH)
	{

		Btc_AutomaticMode 					= STD_LOW;
		HVAC_WindshieldVents_CurrentState 	= Btc_WindshieldVents;

	}
	else if(Btc_WindshieldVents == STD_LOW)
	{

		Btc_AutomaticMode 					= STD_LOW;
		HVAC_WindshieldVents_CurrentState 	= Btc_WindshieldVents;

	}
	else
	{

		/* do nothing */

	}

	if(Btc_WindshieldDefrost == STD_HIGH)
	{

		Btc_AutomaticMode				 		= STD_LOW;
		HVAC_WindshieldDefrost_CurrentState 	= Btc_WindshieldDefrost;
		HVAC_LegVents_CurrentState 				= STD_LOW;
		HVAC_MidVents_CurrentState 				= STD_LOW;
		HVAC_WindshieldVents_CurrentState 		= STD_LOW;

	}
	else if(Btc_WindshieldDefrost == STD_LOW)
	{

		Btc_AutomaticMode				 		= STD_LOW;
		HVAC_WindshieldDefrost_CurrentState 	= Btc_WindshieldDefrost;
		HVAC_LegVents_CurrentState 				= Btc_LegVents;
		HVAC_MidVents_CurrentState 				= Btc_MidVents;
		HVAC_WindshieldVents_CurrentState 		= Btc_WindshieldVents;

	}
	else
	{

		/* do nothing */

	}

	if(Btc_AutomaticMode == STD_HIGH)
	{

		HVAC_AutomaticMode_CurrentState 		= STD_HIGH;
		HVAC_WindshieldDefrost_CurrentState 	= STD_LOW;
		HVAC_WindshieldVents_CurrentState 		= STD_LOW;
		HVAC_MidVents_CurrentState 				= STD_LOW;
		HVAC_LegVents_CurrentState 				= STD_LOW;

		if(HVAC_TemperatureValue < HVAC_TemSenRxTemperature)
		{

			if((HVAC_TemSenRxTemperature - HVAC_TemperatureValue) * 2 > 7)
			{

				HVAC_FanValue = 7;

			}
			else if((HVAC_TemSenRxTemperature - HVAC_TemperatureValue) * 2 <= 7)
			{

				HVAC_FanValue = (HVAC_TemSenRxTemperature - HVAC_TemperatureValue) * 2;

			}
			else
			{

				/* do nothing */

			}

		}
		else if(HVAC_TemperatureValue >= HVAC_TemSenRxTemperature)
		{

			if((HVAC_TemSenRxTemperature - HVAC_TemperatureValue) / 2 < 1)
			{

				HVAC_FanValue = 1;

			}
			else if((HVAC_TemSenRxTemperature - HVAC_TemperatureValue) / 2 > 1)
			{

				HVAC_FanValue = (HVAC_TemSenRxTemperature - HVAC_TemperatureValue) / 2;

			}
			else
			{

				/* do nothing */

			}

		}

	}
	else if(Btc_NormalMode == STD_HIGH)
	{

		HVAC_AutomaticMode_CurrentState 		= STD_LOW;
		HVAC_WindshieldDefrost_CurrentState 	= Btc_WindshieldDefrost;
		HVAC_WindshieldVents_CurrentState 		= Btc_WindshieldVents;
		HVAC_MidVents_CurrentState 				= Btc_MidVents;
		HVAC_LegVents_CurrentState 				= Btc_LegVents;

	}
	else
	{

		/* do nothing */

	}

}

StdReturnType HVACInit()
{

	lcd_init();

	HVAC_CurrentState					    = STD_HIGH;
	HVAC_TemperatureValue 					= STD_LOW;
	HVAC_FanValue 							= STD_LOW;
	HVAC_LegVents_CurrentState 				= STD_LOW;
	HVAC_MidVents_CurrentState 				= STD_LOW;
	HVAC_WindshieldVents_CurrentState 		= STD_LOW;
	HVAC_WindshieldDefrost_CurrentState 	= STD_LOW;
	HVAC_AC_CurrentState 					= STD_LOW;
	HVAC_AutomaticMode_CurrentState 		= STD_LOW;
	HVAC_RecirculationMode_CurrentState 	= STD_LOW;
	HVAC_BackwindowDefrost_CurrentState     = STD_LOW;
	HVAC_TemSenAdcRxValue 					= STD_LOW;
	HVAC_TemSenRxTemperature 				= STD_LOW;
	Btc_TemperatureValue 					= STD_LOW;
	Btc_FanValue 							= STD_LOW;
	Btc_LegVents 							= STD_LOW;
	Btc_MidVents 							= STD_LOW;
	Btc_WindshieldVents 					= STD_LOW;
	Btc_WindshieldDefrost 					= STD_LOW;
	Btc_BackwindowDefrost 					= STD_LOW;
	Btc_AC 									= STD_LOW;
	Btc_AutomaticMode 						= STD_LOW;
	Btc_RecirculationMode 					= STD_LOW;
	Btc_NormalMode							= STD_LOW;

	return E_OK;

}
