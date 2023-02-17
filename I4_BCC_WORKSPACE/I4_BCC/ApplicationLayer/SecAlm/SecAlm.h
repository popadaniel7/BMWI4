#include "Std_Types.h"

#define SECALM_BUZZER_PORT 		GPIOB
#define SECALM_BUZZER_PIN 		GPIO_PIN_13
#define SECALM_LED_PORT 		GPIOA
#define SECALM_LED_PIN 			GPIO_PIN_15

EXTERN uint8 SecAlm_Trigger;
EXTERN uint8 SecAlm_PinStateChange;
EXTERN uint8 SecAlm_TriggerIRQCounterForTimer4;
EXTERN uint16 SecAlm_SensorStatusCounter;
EXTERN uint16 SecAlm_SensorStatus;

EXTERN uint16 SecAlmVibeSenReadPin();
EXTERN StdReturnType SecAlmVibSenStatus();
EXTERN StdReturnType SecAlmInit();
EXTERN void SecAlmMainFunction();
EXTERN void SecAlmToggleAlarmBuzzer(uint8 PinState);
EXTERN void SecAlmToggleAlarmLed(uint8 PinState);
EXTERN void SecAlmLightsBuzzerControl();
EXTERN void SecAlmLightsBuzzerControl();
