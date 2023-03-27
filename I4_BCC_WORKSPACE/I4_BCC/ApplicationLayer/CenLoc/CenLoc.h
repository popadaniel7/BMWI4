#include "Std_Types.h"

#define CENLOC_DOOR_LED_PORT 	GPIOA
#define CENLOC_DOOR_LED_PIN 	GPIO_PIN_6
#define CENLOC_BUZZER_PORT 		GPIOB
#define CENLOC_BUZZER_PIN		GPIO_PIN_2

EXTERN uint8 CenLoc_CurrentState;
EXTERN uint8 CenLoc_PreviousState;
EXTERN uint8 CenLoc_FollowMeHomeState;
EXTERN uint8 CenLoc_BlinkState;
EXTERN uint8 CenLoc_Tim2IRQFlag;
EXTERN uint8 CenLoc_Tim3IRQFlag;
EXTERN uint8 CenLoc_Tim5IRQFlag;
EXTERN uint8 CenLoc_Tim11IRQFlag;
EXTERN uint8 CenLoc_PreviousStateFlag;

EXTERN void CenLoc_MainFunction();
EXTERN void CenLoc_ToggleDoorLED(uint8 PinState);
EXTERN void CenLoc_ToggleBuzzer(uint8 PinState);
EXTERN void CenLoc_FollowMeHome();
EXTERN void CenLoc_BlinkSignals();
EXTERN void CenLoc_SecAlmStateToOff();
EXTERN void CenLoc_UnlockSequence();
EXTERN void CenLoc_LockSequence();
EXTERN void CenLoc_ControlAlarmLed();
EXTERN StdReturnType CenLoc_Init();
EXTERN void CenLoc_State();
EXTERN void CenLoc_LockUnlockStates();
