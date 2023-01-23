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

#define LIGHTSON_CENLOCON BTC_RX_CENLOC_ON
#define LIGHTSOFF_CENLOCOFF BTC_RX_CENLOC_OFF
#define LIGHTSON_INTLIGHTSON BTC_RX_INTLIGHTS_INTERIORLIGHT_ON
#define LIGHTSOFF_INTLIGHTSOFF BTC_RX_INTLIGHTS_INTERIORLIGHT_OFF

uint8 IntLights_CurrentState;
uint8 IntLights_StateFlag;
uint8 Btc_IntLights;

StdReturnType IntLightsInit();
void IntLightsMainFunction();
void IntLightsToggleIntLights(uint8 PinState);
void IntLightsRxBtcState();

void IntLightsRxBtcState()
{

	uint8 lightsStateFromBtcCommand = BtcReceivedDataOnBluetooth;

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

void IntLightsMainFunction()
{

	IntLightsRxBtcState();
	IntLightsToggleIntLights(IntLights_CurrentState);

}

StdReturnType IntLightsInit()
{

	IntLights_CurrentState 	= STD_LOW;
	IntLights_StateFlag 	= STD_LOW;
	Btc_IntLights 			= STD_LOW;

	return E_OK;

}

void IntLightsToggleIntLights(uint8 PinState)
{

	HAL_GPIO_WritePin(INTERIOR_LIGHT_PORT, INTERIOR_LIGHT_PIN, PinState);

}
