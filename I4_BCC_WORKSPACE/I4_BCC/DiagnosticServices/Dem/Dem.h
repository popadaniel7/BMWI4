/*****************************************
* Project: BCM I4						 *
* Developer: Daniel Popa				 *
* Module: Diagnostic Event Manager	     *
******************************************/
#ifndef Dem_H
#define Dem_H
/*****************************************
*		INCLUDE PATHS					 *
******************************************/
#include "Std_Types.h"
/*****************************************
*		END OF INCLUDE PATHS		     *
******************************************/
/*****************************************
*		DEFINES					 		 *
******************************************/
/* DTC code */
#define DTC_LOW_BEAM_LEFT_MALFUNCTION 							0x04
/* DTC code */
#define DTC_LOW_BEAM_RIGHT_MALFUNCTION 							0x05
/* DTC code */
#define DTC_REAR_POSITION_LIGHT_LEFT_MALFUNCTION	 			0x44
/* DTC code */
#define DTC_REAR_POSITION_LIGHT_RIGHT_MALFUNCTION	 			0x45
/* DTC code */
#define DTC_RIGHT_TURN_SIGNAL_FRONT_MALFUNCTION 				0x54
/* DTC code */
#define DTC_RIGHT_TURN_SIGNAL_REAR_MALFUNCTION 					0x55
/* DTC code */
#define DTC_LEFT_TURN_SIGNAL_FRONT_MALFUNCTION 					0x64
/* DTC code */
#define DTC_LEFT_TURN_SIGNAL_REAR_MALFUNCTION 					0x65
/* DTC code */
#define DTC_BRAKE_LIGHT_LEFT_MALFUNCTION 						0x74
/* DTC code */
#define DTC_BRAKE_LIGHT_RIGHT_MALFUNCTION 						0x75
/* DTC code */
#define DTC_LIGHT_SENSOR_MALFUNCTION 							0x03
/* DTC code */
#define DTC_VIBRATION_SENSOR_MALFUNCTION 						0x13
/* DTC code */
#define DTC_AIR_QUALITY_SENSOR_MALFUNCTION 						0x23
/* DTC code */
#define DTC_TEMPERATURE_SENSOR_MALFUNCTION 						0x33
/* DTC code */
#define DTC_REAR_PARKING_DISTANCE_SENSOR_MALFUNCTION 			0x02
/* DTC code */
#define DTC_FRONT_PARKING_DISTANCE_SENSOR_MALFUNCTION 			0x12
/* DTC code */
#define DTC_BLUETOOTH_MODULE_MALFUNCTION 						0x22
/* DTC code */
#define DTC_EXTERNAL_EEPROM_MODULE_MALFUNCTION 					0x32
/* DTC code */
#define DTC_CAN_TRANSCEIVER_MODULE_MALFUNCTION 					0x42
/* DTC code */
#define DTC_CAN_BUS_OFF 										0x52
/* DTC code */
#define DTC_LCD_MODULE_MALFUNCTION 								0x62
/* DTC code */
#define DTC_SOFTWARE_RESET 										0x35
/* DTC code */
#define DTC_HARDWARE_RESET 										0x56
/* DTC code */
#define DTC_PERIPHERAL_ERROR 									0x99
/* DTC code */
#define POSITION_DTC_LOW_BEAM_LEFT_MALFUNCTION 					0
/* DTC code */
#define POSITION_DTC_LOW_BEAM_RIGHT_MALFUNCTION 				1
/* DTC code */
#define POSITION_DTC_REAR_POSITION_LIGHT_LEFT_MALFUNCTION	 	2
/* DTC code */
#define POSITION_DTC_REAR_POSITION_LIGHT_RIGHT_MALFUNCTION	 	3
/* DTC code */
#define POSITION_DTC_RIGHT_TURN_SIGNAL_FRONT_MALFUNCTION 		4
/* DTC code */
#define POSITION_DTC_RIGHT_TURN_SIGNAL_REAR_MALFUNCTION 		5
/* DTC code */
#define POSITION_DTC_LEFT_TURN_SIGNAL_FRONT_MALFUNCTION 		6
/* DTC code */
#define POSITION_DTC_LEFT_TURN_SIGNAL_REAR_MALFUNCTION 			7
/* DTC code */
#define POSITION_DTC_BRAKE_LIGHT_LEFT_MALFUNCTION 				8
/* DTC code */
#define POSITION_DTC_BRAKE_LIGHT_RIGHT_MALFUNCTION 				9
/* DTC code */
#define POSITION_DTC_LIGHT_SENSOR_MALFUNCTION 					10
/* DTC code */
#define POSITION_DTC_VIBRATION_SENSOR_MALFUNCTION 				11
/* DTC code */
#define POSITION_DTC_AIR_QUALITY_SENSOR_MALFUNCTION 			12
/* DTC code */
#define POSITION_POSITION_DTC_TEMPERATURE_SENSOR_MALFUNCTION 	13
/* DTC code */
#define POSITION_DTC_REAR_PARKING_DISTANCE_SENSOR_MALFUNCTION 	14
/* DTC code */
#define POSITION_DTC_FRONT_PARKING_DISTANCE_SENSOR_MALFUNCTION 	15
/* DTC code */
#define POSITION_DTC_BLUETOOTH_MODULE_MALFUNCTION 				16
/* DTC code */
#define POSITION_DTC_EXTERNAL_EEPROM_MODULE_MALFUNCTION 		17
/* DTC code */
#define POSITION_DTC_CAN_TRANSCEIVER_MODULE_MALFUNCTION 		18
/* DTC code */
#define POSITION_DTC_CAN_BUS_OFF 								19
/* DTC code */
#define POSITION_DTC_LCD_MODULE_MALFUNCTION 					20
/* DTC code */
#define POSITION_DTC_SOFTWARE_RESET 							21
/* DTC code */
#define POSITION_DTC_HARDWARE_RESET 							22
/* DTC code */
#define POSITION_DTC_PERIPHERAL_ERROR 							23
/*****************************************
* 		END OF DEFINES					 *
******************************************/
/*****************************************
*		VARIABLES					 	 *
******************************************/
/* Module state variable. */
EXTERN uint8 Dem_BswState;
/* DTC array. */
EXTERN uint8 Dem_DtcArray[24];
/*****************************************
*		END OF VARIABLES				 *
******************************************/
/*****************************************
*		FUNCTIONS				 		 *
******************************************/
/* Module initialization. */
EXTERN StdReturnType Dem_Init();
/* Module de-initialization. */
EXTERN StdReturnType Dem_DeInit();
/* Module main function. */
EXTERN VOID Dem_MainFunction();
/* Receive fault from application. */
EXTERN VOID Dem_ReceiveFault(uint8 faultValue);
/* Process fault from application. */
EXTERN VOID Dem_ProcessFault();
/*****************************************
*		END OF FUNCTIONS				 *
******************************************/
#endif /* Dem_H */
