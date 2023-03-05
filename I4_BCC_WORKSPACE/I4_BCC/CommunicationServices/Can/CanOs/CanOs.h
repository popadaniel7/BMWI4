#include "main.h"
#include <stdbool.h>
#include "Std_Types.h"

#define CMD_STANDARD_CAN_MSG_ID 	0
#define CMD_EXTENDED_CAN_MSG_ID 	1
#define EXTENDED_CAN_MSG_ID_2_0B 	2

typedef union
{

	struct
	{

		uint8 idType;
		uint32 id;
		uint8 dlc;
		uint8 data0;
		uint8 data1;
		uint8 data2;
		uint8 data3;
		uint8 data4;
		uint8 data5;
		uint8 data6;
		uint8 data7;

	}frame;

	uint8_t array[14];

}uCAN_MSG;

EXTERN StdReturnType CanOverSpi_Initialize();
EXTERN StdReturnType CanOverSpi_Init_Mask(uint8 num, uint8 ext, uint32 id);
EXTERN StdReturnType CanOverSpi_Init_Filter(uint8 num, uint8 ext, uint32 id);
EXTERN StdReturnType CanOverSpi_Transmit(uCAN_MSG *tempCanMsg);
EXTERN StdReturnType CanOverSpi_Receive(uCAN_MSG *tempCanMsg);
EXTERN StdReturnType CanOverSpi_messagesInBuffer();
EXTERN StdReturnType CanOverSpi_isBussOff();
EXTERN StdReturnType CanOverSpi_isRxErrorPassive();
EXTERN StdReturnType CanOverSpi_isTxErrorPassive();
