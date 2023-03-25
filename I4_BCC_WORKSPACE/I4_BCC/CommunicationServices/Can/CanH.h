#include "Std_Types.h"
#include "CanOs.h"
#include "Mcp2515_CanOs.h"

typedef uCAN_MSG CanMsg;

typedef enum
{
	CAN_DEINIT,
	CAN_INIT,
	CAN_BUSY,
	CAN_RX,
	CAN_TX,
	CAN_ERROR,
	CAN_INIT_ERROR,
	CAN_BTC_REQUEST,
	CAN_BUS_REQUEST,
	CAN_BUS_OFF

}CanStatus;

EXTERN CanStatus CanTPStatus;

EXTERN CanMsg CanTx_Bus_Message;
EXTERN CanMsg CanRx_Bus_Message;
EXTERN CanMsg CanTx_Btc_Message;
EXTERN CanMsg CanRx_Btc_Message;

EXTERN StdReturnType Can_Init();
EXTERN StdReturnType Can_DeInit();
EXTERN void Can_MainFunction();
EXTERN StdReturnType CanDrv_Transmit(uint32 TxCanMsgId, const uint32* CanMsgPtr);
EXTERN StdReturnType CanDrv_Receive(uint32 RxCanMsgId, const uint32* CanMsgPtr);
