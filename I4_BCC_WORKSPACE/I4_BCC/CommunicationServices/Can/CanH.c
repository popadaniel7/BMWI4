#include "CanH.h"

CanMsg CanTx_Bus_Message;
CanMsg CanRx_Bus_Message;
CanMsg CanTx_Btc_Message;
CanMsg CanRx_Btc_Message;

CanStatus CanTPStatus;

StdReturnType Can_Init();
StdReturnType Can_DeInit();
void Can_MainFunction();
StdReturnType CanDrv_Transmit(uint32 TxCanMsgId, const uint32* CanMsgPtr);
StdReturnType CanDrv_Receive(uint32 RxCanMsgId, const uint32* CanMsgPtr);

StdReturnType Can_Init()
{

	if(CanOverSpi_Init() == E_NOT_OK)
	{

		CanTPStatus = CAN_INIT_ERROR;

		return E_NOT_OK;

	}
	else
	{

		/* do nothing */

	}

	CanTPStatus = CAN_INIT;

	return E_OK;

}
StdReturnType Can_DeInit()
{

	MCP2515_CanOverSpi_Reset();

	CanTPStatus = CAN_DEINIT;

	return E_OK;

}
void Can_MainFunction()
{

	CanStatus localProtocolStatus = CanTPStatus;

	switch(localProtocolStatus)
	{

		case CAN_DEINIT:

			break;

		case CAN_INIT:

			break;

		case CAN_BUSY:

			break;

		case CAN_RX:

			break;

		case CAN_TX:

			break;

		case CAN_ERROR:

			break;

		case CAN_INIT_ERROR:

			break;

		case CAN_BTC_REQUEST:

			break;

		case CAN_BUS_REQUEST:

			break;

		case CAN_BUS_OFF:

			break;

		default:

			break;

	}

}
StdReturnType CanDrv_Transmit(uint32 TxCanMsgId, const uint32* CanMsgPtr)
{

	CanMessage message;
	message.id = TxCanMsgId;
	message.dataLength = 8;

	memcpy(message.data, CanMsgPtr, message.dataLength);

	if (MCP2515_WriteMessage(&message, MCP2515_TXB0CTRL) != MCP2515_OK)
	{

		return E_NOT_OK;

	}
	else
	{

		/* do nothing */

	}

	if (MCP2515_RequestToSend(MCP2515_RTS_TX0) != MCP2515_OK)
	{

		return E_NOT_OK;

	}
	else
	{

		/* do nothing */

	}

	return E_OK;

}
StdReturnType CanDrv_Receive(uint32 RxCanMsgId, const uint32* CanMsgPtr)
{

	return E_OK;

}
