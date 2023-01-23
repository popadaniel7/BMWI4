#include "Std_Types.h"

#define CENLOC_DOOR_LED_PORT 	GPIOB
#define CENLOC_DOOR_LED_PIN 	GPIO_PIN_6
#define CENLOC_BUZZER_PORT 		GPIOB
#define CENLOC_BUZZER_PIN		GPIO_PIN_6

EXTERN uint8 CenLoc_CurrentState;
EXTERN uint8 CenLoc_PreviousState;
EXTERN uint8 CenLoc_LockUnlockFlag;
EXTERN uint8 CenLoc_ExtLights_UnlockedState;
EXTERN uint8 CenLoc_ExtLights_LockedState;
EXTERN uint8 CenLoc_FollowMeHomeState;
EXTERN uint8 CenLoc_BlinkState;
EXTERN uint8 CenLoc_LockCounter;
EXTERN uint8 CenLoc_UnlockCounter;
EXTERN uint8 Btc_CenLoc;

EXTERN uint8 CenLoc_Timer5StartStopFlag;
EXTERN uint32 CenLoc_Timer2Value;
EXTERN uint32 CenLoc_Timer3Value;
EXTERN uint32 CenLoc_Timer5Value;

EXTERN void CenLocMainFunction();
EXTERN void CenLocToggleDoorLED(uint8 PinState);
EXTERN void CenLocToggleBuzzer(uint8 PinState);
EXTERN void CenLocFollowMeHome();
EXTERN void CenLocBlinkSignals();
EXTERN void CenLocRxBtcState();
EXTERN void CenLocSecAlmStateToOff();
EXTERN StdReturnType CenLocInit();
EXTERN StdReturnType CenLocState();
EXTERN StdReturnType CenLocLockUnlockStates();
