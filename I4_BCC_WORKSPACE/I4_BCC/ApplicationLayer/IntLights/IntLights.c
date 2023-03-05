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
#include "BTC.h"
#include "RTE.h"

#define LIGHTSON_CENLOCON BTC_RX_CENLOC_ON
#define LIGHTSOFF_CENLOCOFF BTC_RX_CENLOC_OFF
#define LIGHTSON_INTLIGHTSON BTC_RX_INTLIGHTS_INTERIORLIGHT_ON
#define LIGHTSOFF_INTLIGHTSOFF BTC_RX_INTLIGHTS_INTERIORLIGHT_OFF

uint8 IntLights_CurrentState;
uint8 IntLights_StateFlag;

StdReturnType IntLights_Init();
void IntLights_MainFunction();
void IntLights_ToggleIntLights(uint8 PinState);
void IntLights_RxBtcState();

void IntLights_RxBtcState()
{

	uint8 lightsStateFromBtcCommand;

	Rte_Read_Btc_BtcPort_Btc_ReceivedDataOnBluetooth(&lightsStateFromBtcCommand);

	switch(lightsStateFromBtcCommand)
	{
		case LIGHTSON_CENLOCON:

			IntLights_CurrentState = STD_HIGH;

			break;

		case LIGHTSOFF_CENLOCOFF:

			IntLights_CurrentState = STD_LOW;

			break;

		case LIGHTSON_INTLIGHTSON:

			IntLights_CurrentState = STD_HIGH;

			break;

		case LIGHTSOFF_INTLIGHTSOFF:

			IntLights_CurrentState = STD_LOW;

			break;

	}

}

void IntLights_MainFunction()
{

	IntLights_RxBtcState();
	IntLights_ToggleIntLights(IntLights_CurrentState);

}

StdReturnType IntLights_Init()
{

	IntLights_CurrentState 	= STD_LOW;
	IntLights_StateFlag 	= STD_LOW;

	return E_OK;

}

void IntLights_ToggleIntLights(uint8 PinState)
{

	Rte_Call_Gpio_R_GpioPort_HAL_GPIO_WritePin(INTERIOR_LIGHT_PORT, INTERIOR_LIGHT_PIN, PinState);

}
