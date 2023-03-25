#include "usart.h"
#include "Std_Types.h"
#include "main.h"
#include "Rte.h"

EXTERN uint8 UartCounter_Btc_RxCount;

EXTERN StdReturnType Uart_Init();
EXTERN StdReturnType Uart_DeInit();
EXTERN void Uart_MainFunction();
EXTERN void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
EXTERN void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
