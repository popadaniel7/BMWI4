#include "Std_Types.h"

#define INTERIOR_LIGHT_PORT 	GPIOB
#define INTERIOR_LIGHT_PIN 		GPIO_PIN_3

EXTERN uint8 IntLights_CurrentState;
EXTERN uint8 IntLights_StateFlag;

EXTERN StdReturnType IntLights_Init();
EXTERN void IntLights_MainFunction();
EXTERN void IntLights_ToggleIntLights(uint8 PinState);
EXTERN void IntLights_RxBtcState();
