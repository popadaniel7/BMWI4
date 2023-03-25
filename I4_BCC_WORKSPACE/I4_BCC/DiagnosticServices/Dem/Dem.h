#include "Std_Types.h"

#define DTC_LBUV 35
#define DTC_HBUV 36
#define DTC_DRLUV 37
#define DTC_FFLUV 38
#define DTC_RFLUV 39
#define DTC_RPLUV 40
#define DTC_RTSUV 41
#define DTC_LTSUV 42
#define DTC_RLUV 43
#define DTC_ILUV 44
#define DTC_DLUV 45
#define DTC_LPLUV 46
#define DTC_HC05 47
#define DTC_MCP2515 48
#define DTC_VS 49
#define DTC_LS 50
#define DTC_ALUV 51
#define DTC_CLBUV 52
#define DTC_ALBUV 53
#define DTC_LBS 54
#define DTC_HBS 55
#define DTC_DRLS 56
#define DTC_FFLS 57
#define DTC_RFLS 58
#define DTC_RPLS 59
#define DTC_RTSS 60
#define DTC_LTSS 61
#define DTC_RLS 62
#define DTC_ILS 63
#define DTC_DLS 64
#define DTC_LPLS 65
#define DTC_ALS 70
#define DTC_CLBS 71
#define DTC_ALBS 72

EXTERN uint8 Dem_StoreInFlashFlag;

EXTERN StdReturnType Dem_Init();
EXTERN StdReturnType Dem_DeInit();
EXTERN void Dem_MainFunction();
EXTERN void Dem_ProcessSystemFault();
EXTERN void Dem_ProcessCircuitFault();
EXTERN void Dem_SetDtc();
