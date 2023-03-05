/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "CenLoc.h"
#include "ExtLights.h"
#include "IntLights.h"
#include "SecAlm.h"
#include "BTC.h"
#include "Std_Types.h"
#include "Project_Definitions.h"
#include "timers.h"
#include "RTE.h"
#include "wwdg.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

uint32 OS_Counter;

/* USER CODE END Variables */
/* Definitions for QM_APPL_HP */
osThreadId_t QM_APPL_HPHandle;
const osThreadAttr_t QM_APPL_HP_attributes = {
  .name = "QM_APPL_HP",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for QM_APPL_LP */
osThreadId_t QM_APPL_LPHandle;
const osThreadAttr_t QM_APPL_LP_attributes = {
  .name = "QM_APPL_LP",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ASIL_APPL_HP */
osThreadId_t ASIL_APPL_HPHandle;
const osThreadAttr_t ASIL_APPL_HP_attributes = {
  .name = "ASIL_APPL_HP",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for ASIL_APPL_LP */
osThreadId_t ASIL_APPL_LPHandle;
const osThreadAttr_t ASIL_APPL_LP_attributes = {
  .name = "ASIL_APPL_LP",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for OS_COUNTER */
osThreadId_t OS_COUNTERHandle;
const osThreadAttr_t OS_COUNTER_attributes = {
  .name = "OS_COUNTER",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for QM_BSW_HP */
osThreadId_t QM_BSW_HPHandle;
const osThreadAttr_t QM_BSW_HP_attributes = {
  .name = "QM_BSW_HP",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal1,
};
/* Definitions for QM_BSW_LP */
osThreadId_t QM_BSW_LPHandle;
const osThreadAttr_t QM_BSW_LP_attributes = {
  .name = "QM_BSW_LP",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for ASIL_BSW_HP */
osThreadId_t ASIL_BSW_HPHandle;
const osThreadAttr_t ASIL_BSW_HP_attributes = {
  .name = "ASIL_BSW_HP",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime1,
};
/* Definitions for ASIL_BSW_LP */
osThreadId_t ASIL_BSW_LPHandle;
const osThreadAttr_t ASIL_BSW_LP_attributes = {
  .name = "ASIL_BSW_LP",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh1,
};
/* Definitions for OsInit */
osThreadId_t OsInitHandle;
const osThreadAttr_t OsInit_attributes = {
  .name = "OsInit",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for Watchdog_MainFunction */
osThreadId_t Watchdog_MainFunctionHandle;
const osThreadAttr_t Watchdog_MainFunction_attributes = {
  .name = "Watchdog_MainFunction",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime7,
};
/* Definitions for Os_SecAlm_AlarmReset */
osTimerId_t Os_SecAlm_AlarmResetHandle;
const osTimerAttr_t Os_SecAlm_AlarmReset_attributes = {
  .name = "Os_SecAlm_AlarmReset"
};
/* Definitions for Os_CenLoc_LockUnlockSequence_Timer */
osTimerId_t Os_CenLoc_LockUnlockSequence_TimerHandle;
const osTimerAttr_t Os_CenLoc_LockUnlockSequence_Timer_attributes = {
  .name = "Os_CenLoc_LockUnlockSequence_Timer"
};
/* Definitions for SysEvent_WatchdogReset */
osEventFlagsId_t SysEvent_WatchdogResetHandle;
const osEventFlagsAttr_t SysEvent_WatchdogReset_attributes = {
  .name = "SysEvent_WatchdogReset"
};
/* Definitions for SysEvent_PowerOnReset */
osEventFlagsId_t SysEvent_PowerOnResetHandle;
const osEventFlagsAttr_t SysEvent_PowerOnReset_attributes = {
  .name = "SysEvent_PowerOnReset"
};
/* Definitions for SysEvent_CoreReset */
osEventFlagsId_t SysEvent_CoreResetHandle;
const osEventFlagsAttr_t SysEvent_CoreReset_attributes = {
  .name = "SysEvent_CoreReset"
};
/* Definitions for SysEvent_HardwareReset */
osEventFlagsId_t SysEvent_HardwareResetHandle;
const osEventFlagsAttr_t SysEvent_HardwareReset_attributes = {
  .name = "SysEvent_HardwareReset"
};
/* Definitions for SysEvent_HardFault */
osEventFlagsId_t SysEvent_HardFaultHandle;
const osEventFlagsAttr_t SysEvent_HardFault_attributes = {
  .name = "SysEvent_HardFault"
};
/* Definitions for SysEvent_MemHandlerFault */
osEventFlagsId_t SysEvent_MemHandlerFaultHandle;
const osEventFlagsAttr_t SysEvent_MemHandlerFault_attributes = {
  .name = "SysEvent_MemHandlerFault"
};
/* Definitions for SysEvent_BusFault */
osEventFlagsId_t SysEvent_BusFaultHandle;
const osEventFlagsAttr_t SysEvent_BusFault_attributes = {
  .name = "SysEvent_BusFault"
};
/* Definitions for SysEvent_NonMaskableInterrupt */
osEventFlagsId_t SysEvent_NonMaskableInterruptHandle;
const osEventFlagsAttr_t SysEvent_NonMaskableInterrupt_attributes = {
  .name = "SysEvent_NonMaskableInterrupt"
};
/* Definitions for SysEvent_UsageFault */
osEventFlagsId_t SysEvent_UsageFaultHandle;
const osEventFlagsAttr_t SysEvent_UsageFault_attributes = {
  .name = "SysEvent_UsageFault"
};
/* Definitions for SysEvent_DebugMonFault */
osEventFlagsId_t SysEvent_DebugMonFaultHandle;
const osEventFlagsAttr_t SysEvent_DebugMonFault_attributes = {
  .name = "SysEvent_DebugMonFault"
};
/* Definitions for SysEvent_WWDGInterrupt */
osEventFlagsId_t SysEvent_WWDGInterruptHandle;
const osEventFlagsAttr_t SysEvent_WWDGInterrupt_attributes = {
  .name = "SysEvent_WWDGInterrupt"
};
/* Definitions for SysEvent_PVDInterrupt */
osEventFlagsId_t SysEvent_PVDInterruptHandle;
const osEventFlagsAttr_t SysEvent_PVDInterrupt_attributes = {
  .name = "SysEvent_PVDInterrupt"
};
/* Definitions for SysEvent_RTCWakeupInterrupt */
osEventFlagsId_t SysEvent_RTCWakeupInterruptHandle;
const osEventFlagsAttr_t SysEvent_RTCWakeupInterrupt_attributes = {
  .name = "SysEvent_RTCWakeupInterrupt"
};
/* Definitions for SysEvent_FlashInterurpt */
osEventFlagsId_t SysEvent_FlashInterurptHandle;
const osEventFlagsAttr_t SysEvent_FlashInterurpt_attributes = {
  .name = "SysEvent_FlashInterurpt"
};
/* Definitions for SysEvent_RCCInterrupt */
osEventFlagsId_t SysEvent_RCCInterruptHandle;
const osEventFlagsAttr_t SysEvent_RCCInterrupt_attributes = {
  .name = "SysEvent_RCCInterrupt"
};
/* Definitions for SysEvent_ADCInterrupt */
osEventFlagsId_t SysEvent_ADCInterruptHandle;
const osEventFlagsAttr_t SysEvent_ADCInterrupt_attributes = {
  .name = "SysEvent_ADCInterrupt"
};
/* Definitions for SysEvent_TIM1Interrupt */
osEventFlagsId_t SysEvent_TIM1InterruptHandle;
const osEventFlagsAttr_t SysEvent_TIM1Interrupt_attributes = {
  .name = "SysEvent_TIM1Interrupt"
};
/* Definitions for SysEvent_TIM2Interrupt */
osEventFlagsId_t SysEvent_TIM2InterruptHandle;
const osEventFlagsAttr_t SysEvent_TIM2Interrupt_attributes = {
  .name = "SysEvent_TIM2Interrupt"
};
/* Definitions for SysEvent_TIM3Interrupt */
osEventFlagsId_t SysEvent_TIM3InterruptHandle;
const osEventFlagsAttr_t SysEvent_TIM3Interrupt_attributes = {
  .name = "SysEvent_TIM3Interrupt"
};
/* Definitions for SysEvent_TIM4Interrupt */
osEventFlagsId_t SysEvent_TIM4InterruptHandle;
const osEventFlagsAttr_t SysEvent_TIM4Interrupt_attributes = {
  .name = "SysEvent_TIM4Interrupt"
};
/* Definitions for SysEvent_TIM5Interrupt */
osEventFlagsId_t SysEvent_TIM5InterruptHandle;
const osEventFlagsAttr_t SysEvent_TIM5Interrupt_attributes = {
  .name = "SysEvent_TIM5Interrupt"
};
/* Definitions for SysEvent_TIM9Interrupt */
osEventFlagsId_t SysEvent_TIM9InterruptHandle;
const osEventFlagsAttr_t SysEvent_TIM9Interrupt_attributes = {
  .name = "SysEvent_TIM9Interrupt"
};
/* Definitions for SysEvent_TIM11Interrupt */
osEventFlagsId_t SysEvent_TIM11InterruptHandle;
const osEventFlagsAttr_t SysEvent_TIM11Interrupt_attributes = {
  .name = "SysEvent_TIM11Interrupt"
};
/* Definitions for SysEvent_TIMFault */
osEventFlagsId_t SysEvent_TIMFaultHandle;
const osEventFlagsAttr_t SysEvent_TIMFault_attributes = {
  .name = "SysEvent_TIMFault"
};
/* Definitions for SysEvent_I2CInterrupt */
osEventFlagsId_t SysEvent_I2CInterruptHandle;
const osEventFlagsAttr_t SysEvent_I2CInterrupt_attributes = {
  .name = "SysEvent_I2CInterrupt"
};
/* Definitions for SysEvent_I2CFault */
osEventFlagsId_t SysEvent_I2CFaultHandle;
const osEventFlagsAttr_t SysEvent_I2CFault_attributes = {
  .name = "SysEvent_I2CFault"
};
/* Definitions for SysEvent_SPIFault */
osEventFlagsId_t SysEvent_SPIFaultHandle;
const osEventFlagsAttr_t SysEvent_SPIFault_attributes = {
  .name = "SysEvent_SPIFault"
};
/* Definitions for SysEvent_SPIInterrupt */
osEventFlagsId_t SysEvent_SPIInterruptHandle;
const osEventFlagsAttr_t SysEvent_SPIInterrupt_attributes = {
  .name = "SysEvent_SPIInterrupt"
};
/* Definitions for SysEvent_USARTInterrupt */
osEventFlagsId_t SysEvent_USARTInterruptHandle;
const osEventFlagsAttr_t SysEvent_USARTInterrupt_attributes = {
  .name = "SysEvent_USARTInterrupt"
};
/* Definitions for SysEvent_USARTFault */
osEventFlagsId_t SysEvent_USARTFaultHandle;
const osEventFlagsAttr_t SysEvent_USARTFault_attributes = {
  .name = "SysEvent_USARTFault"
};
/* Definitions for SysEvent_DMAInterrupt */
osEventFlagsId_t SysEvent_DMAInterruptHandle;
const osEventFlagsAttr_t SysEvent_DMAInterrupt_attributes = {
  .name = "SysEvent_DMAInterrupt"
};
/* Definitions for SysEvent_SoftwareReset */
osEventFlagsId_t SysEvent_SoftwareResetHandle;
const osEventFlagsAttr_t SysEvent_SoftwareReset_attributes = {
  .name = "SysEvent_SoftwareReset"
};
/* Definitions for DemEvent_DTC_HardwareReset */
osEventFlagsId_t DemEvent_DTC_HardwareResetHandle;
const osEventFlagsAttr_t DemEvent_DTC_HardwareReset_attributes = {
  .name = "DemEvent_DTC_HardwareReset"
};
/* Definitions for DemEvent_DTC_SoftwareReset */
osEventFlagsId_t DemEvent_DTC_SoftwareResetHandle;
const osEventFlagsAttr_t DemEvent_DTC_SoftwareReset_attributes = {
  .name = "DemEvent_DTC_SoftwareReset"
};
/* Definitions for DemEvent_DTC_PowerOnReset */
osEventFlagsId_t DemEvent_DTC_PowerOnResetHandle;
const osEventFlagsAttr_t DemEvent_DTC_PowerOnReset_attributes = {
  .name = "DemEvent_DTC_PowerOnReset"
};
/* Definitions for DemEvent_DTC_WatchdogReset */
osEventFlagsId_t DemEvent_DTC_WatchdogResetHandle;
const osEventFlagsAttr_t DemEvent_DTC_WatchdogReset_attributes = {
  .name = "DemEvent_DTC_WatchdogReset"
};
/* Definitions for DemEvent_DTC_DMAFault */
osEventFlagsId_t DemEvent_DTC_DMAFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_DMAFault_attributes = {
  .name = "DemEvent_DTC_DMAFault"
};
/* Definitions for DemEvent_DTC_I2CFault */
osEventFlagsId_t DemEvent_DTC_I2CFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_I2CFault_attributes = {
  .name = "DemEvent_DTC_I2CFault"
};
/* Definitions for DemEvent_DTC_SPIFault */
osEventFlagsId_t DemEvent_DTC_SPIFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_SPIFault_attributes = {
  .name = "DemEvent_DTC_SPIFault"
};
/* Definitions for SysEvent_OSFault */
osEventFlagsId_t SysEvent_OSFaultHandle;
const osEventFlagsAttr_t SysEvent_OSFault_attributes = {
  .name = "SysEvent_OSFault"
};
/* Definitions for SysEvent_ComFault */
osEventFlagsId_t SysEvent_ComFaultHandle;
const osEventFlagsAttr_t SysEvent_ComFault_attributes = {
  .name = "SysEvent_ComFault"
};
/* Definitions for SysEvent_IOFault */
osEventFlagsId_t SysEvent_IOFaultHandle;
const osEventFlagsAttr_t SysEvent_IOFault_attributes = {
  .name = "SysEvent_IOFault"
};
/* Definitions for SysEvent_DiagFault */
osEventFlagsId_t SysEvent_DiagFaultHandle;
const osEventFlagsAttr_t SysEvent_DiagFault_attributes = {
  .name = "SysEvent_DiagFault"
};
/* Definitions for SysEvent_MemFault */
osEventFlagsId_t SysEvent_MemFaultHandle;
const osEventFlagsAttr_t SysEvent_MemFault_attributes = {
  .name = "SysEvent_MemFault"
};
/* Definitions for SysEvent_SysFault */
osEventFlagsId_t SysEvent_SysFaultHandle;
const osEventFlagsAttr_t SysEvent_SysFault_attributes = {
  .name = "SysEvent_SysFault"
};
/* Definitions for SysEvent_ApplFault */
osEventFlagsId_t SysEvent_ApplFaultHandle;
const osEventFlagsAttr_t SysEvent_ApplFault_attributes = {
  .name = "SysEvent_ApplFault"
};
/* Definitions for SysEvent_CenLocFault */
osEventFlagsId_t SysEvent_CenLocFaultHandle;
const osEventFlagsAttr_t SysEvent_CenLocFault_attributes = {
  .name = "SysEvent_CenLocFault"
};
/* Definitions for SysEvent_SecAlmFault */
osEventFlagsId_t SysEvent_SecAlmFaultHandle;
const osEventFlagsAttr_t SysEvent_SecAlmFault_attributes = {
  .name = "SysEvent_SecAlmFault"
};
/* Definitions for SysEvent_BtcFault */
osEventFlagsId_t SysEvent_BtcFaultHandle;
const osEventFlagsAttr_t SysEvent_BtcFault_attributes = {
  .name = "SysEvent_BtcFault"
};
/* Definitions for SysEvent_IntLightsFault */
osEventFlagsId_t SysEvent_IntLightsFaultHandle;
const osEventFlagsAttr_t SysEvent_IntLightsFault_attributes = {
  .name = "SysEvent_IntLightsFault"
};
/* Definitions for SysEvent_CanFault */
osEventFlagsId_t SysEvent_CanFaultHandle;
const osEventFlagsAttr_t SysEvent_CanFault_attributes = {
  .name = "SysEvent_CanFault"
};
/* Definitions for SysEvent_DcmFault */
osEventFlagsId_t SysEvent_DcmFaultHandle;
const osEventFlagsAttr_t SysEvent_DcmFault_attributes = {
  .name = "SysEvent_DcmFault"
};
/* Definitions for SysEvent_RteFault */
osEventFlagsId_t SysEvent_RteFaultHandle;
const osEventFlagsAttr_t SysEvent_RteFault_attributes = {
  .name = "SysEvent_RteFault"
};
/* Definitions for SysEvent_DemFault */
osEventFlagsId_t SysEvent_DemFaultHandle;
const osEventFlagsAttr_t SysEvent_DemFault_attributes = {
  .name = "SysEvent_DemFault"
};
/* Definitions for SysEvent_CrcFault */
osEventFlagsId_t SysEvent_CrcFaultHandle;
const osEventFlagsAttr_t SysEvent_CrcFault_attributes = {
  .name = "SysEvent_CrcFault"
};
/* Definitions for SysEvent_EcuFault */
osEventFlagsId_t SysEvent_EcuFaultHandle;
const osEventFlagsAttr_t SysEvent_EcuFault_attributes = {
  .name = "SysEvent_EcuFault"
};
/* Definitions for SysEvent_PortFault */
osEventFlagsId_t SysEvent_PortFaultHandle;
const osEventFlagsAttr_t SysEvent_PortFault_attributes = {
  .name = "SysEvent_PortFault"
};
/* Definitions for SysEvent_PWMFault */
osEventFlagsId_t SysEvent_PWMFaultHandle;
const osEventFlagsAttr_t SysEvent_PWMFault_attributes = {
  .name = "SysEvent_PWMFault"
};
/* Definitions for DemEvent_DTC_ADCFault */
osEventFlagsId_t DemEvent_DTC_ADCFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_ADCFault_attributes = {
  .name = "DemEvent_DTC_ADCFault"
};
/* Definitions for DemEvent_DTC_PWMFault */
osEventFlagsId_t DemEvent_DTC_PWMFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_PWMFault_attributes = {
  .name = "DemEvent_DTC_PWMFault"
};
/* Definitions for DemEvent_DTC_CanFault */
osEventFlagsId_t DemEvent_DTC_CanFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_CanFault_attributes = {
  .name = "DemEvent_DTC_CanFault"
};
/* Definitions for DemEvent_DTC_BtcFault */
osEventFlagsId_t DemEvent_DTC_BtcFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_BtcFault_attributes = {
  .name = "DemEvent_DTC_BtcFault"
};
/* Definitions for DemEvent_DTC_USARTFault */
osEventFlagsId_t DemEvent_DTC_USARTFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_USARTFault_attributes = {
  .name = "DemEvent_DTC_USARTFault"
};
/* Definitions for DemEvent_DTC_WatchdogFault */
osEventFlagsId_t DemEvent_DTC_WatchdogFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_WatchdogFault_attributes = {
  .name = "DemEvent_DTC_WatchdogFault"
};
/* Definitions for DemEvent_DTC_FlashFault */
osEventFlagsId_t DemEvent_DTC_FlashFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_FlashFault_attributes = {
  .name = "DemEvent_DTC_FlashFault"
};
/* Definitions for DemEvent_DTC_RamFault */
osEventFlagsId_t DemEvent_DTC_RamFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_RamFault_attributes = {
  .name = "DemEvent_DTC_RamFault"
};
/* Definitions for DemEvent_DTC_TimerFault */
osEventFlagsId_t DemEvent_DTC_TimerFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_TimerFault_attributes = {
  .name = "DemEvent_DTC_TimerFault"
};
/* Definitions for DemEvent_DTC_EcuUnderVoltage */
osEventFlagsId_t DemEvent_DTC_EcuUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_EcuUnderVoltage_attributes = {
  .name = "DemEvent_DTC_EcuUnderVoltage"
};
/* Definitions for DemEvent_DTC_LowBeamShorted */
osEventFlagsId_t DemEvent_DTC_LowBeamShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_LowBeamShorted_attributes = {
  .name = "DemEvent_DTC_LowBeamShorted"
};
/* Definitions for DemEvent_DTC_LowBeamUnderVoltage */
osEventFlagsId_t DemEvent_DTC_LowBeamUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_LowBeamUnderVoltage_attributes = {
  .name = "DemEvent_DTC_LowBeamUnderVoltage"
};
/* Definitions for DemEvent_DTC_RTCFault */
osEventFlagsId_t DemEvent_DTC_RTCFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_RTCFault_attributes = {
  .name = "DemEvent_DTC_RTCFault"
};
/* Definitions for DemEvent_DTC_HighBeamUnderVoltage */
osEventFlagsId_t DemEvent_DTC_HighBeamUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_HighBeamUnderVoltage_attributes = {
  .name = "DemEvent_DTC_HighBeamUnderVoltage"
};
/* Definitions for DemEvent_DTC_HighBeamShorted */
osEventFlagsId_t DemEvent_DTC_HighBeamShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_HighBeamShorted_attributes = {
  .name = "DemEvent_DTC_HighBeamShorted"
};
/* Definitions for DemEvent_DTC_DayTimeRunningLightUnderVoltage */
osEventFlagsId_t DemEvent_DTC_DayTimeRunningLightUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_DayTimeRunningLightUnderVoltage_attributes = {
  .name = "DemEvent_DTC_DayTimeRunningLightUnderVoltage"
};
/* Definitions for DemEvent_DTC_DayTimeRunningLightShorted */
osEventFlagsId_t DemEvent_DTC_DayTimeRunningLightShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_DayTimeRunningLightShorted_attributes = {
  .name = "DemEvent_DTC_DayTimeRunningLightShorted"
};
/* Definitions for DemEvent_DTC_FrontFogLightsUnderVoltage */
osEventFlagsId_t DemEvent_DTC_FrontFogLightsUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_FrontFogLightsUnderVoltage_attributes = {
  .name = "DemEvent_DTC_FrontFogLightsUnderVoltage"
};
/* Definitions for DemEvent_DTC_FrontFogLightShorted */
osEventFlagsId_t DemEvent_DTC_FrontFogLightShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_FrontFogLightShorted_attributes = {
  .name = "DemEvent_DTC_FrontFogLightShorted"
};
/* Definitions for DemEvent_DTC_RearFogLightUnderVoltage */
osEventFlagsId_t DemEvent_DTC_RearFogLightUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_RearFogLightUnderVoltage_attributes = {
  .name = "DemEvent_DTC_RearFogLightUnderVoltage"
};
/* Definitions for DemEvent_DTC_RearFogLightShorted */
osEventFlagsId_t DemEvent_DTC_RearFogLightShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_RearFogLightShorted_attributes = {
  .name = "DemEvent_DTC_RearFogLightShorted"
};
/* Definitions for DemEvent_DTC_RearPositionLightUnderVoltage */
osEventFlagsId_t DemEvent_DTC_RearPositionLightUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_RearPositionLightUnderVoltage_attributes = {
  .name = "DemEvent_DTC_RearPositionLightUnderVoltage"
};
/* Definitions for DemEvent_DTC_RearPositionLightShorted */
osEventFlagsId_t DemEvent_DTC_RearPositionLightShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_RearPositionLightShorted_attributes = {
  .name = "DemEvent_DTC_RearPositionLightShorted"
};
/* Definitions for DemEvent_DTC_RightTurnSignalUnderVoltage */
osEventFlagsId_t DemEvent_DTC_RightTurnSignalUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_RightTurnSignalUnderVoltage_attributes = {
  .name = "DemEvent_DTC_RightTurnSignalUnderVoltage"
};
/* Definitions for DemEvent_DTC_LeftTurnSignalUnderVoltage */
osEventFlagsId_t DemEvent_DTC_LeftTurnSignalUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_LeftTurnSignalUnderVoltage_attributes = {
  .name = "DemEvent_DTC_LeftTurnSignalUnderVoltage"
};
/* Definitions for DemEvent_DTC_RightTurnSignalShorted */
osEventFlagsId_t DemEvent_DTC_RightTurnSignalShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_RightTurnSignalShorted_attributes = {
  .name = "DemEvent_DTC_RightTurnSignalShorted"
};
/* Definitions for DemEvent_DTC_LeftTurnSignalShorted */
osEventFlagsId_t DemEvent_DTC_LeftTurnSignalShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_LeftTurnSignalShorted_attributes = {
  .name = "DemEvent_DTC_LeftTurnSignalShorted"
};
/* Definitions for DemEvent_DTC_ReverseLightUnderVoltage */
osEventFlagsId_t DemEvent_DTC_ReverseLightUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_ReverseLightUnderVoltage_attributes = {
  .name = "DemEvent_DTC_ReverseLightUnderVoltage"
};
/* Definitions for DemEvent_DTC_ReverseLightShorted */
osEventFlagsId_t DemEvent_DTC_ReverseLightShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_ReverseLightShorted_attributes = {
  .name = "DemEvent_DTC_ReverseLightShorted"
};
/* Definitions for DemEvent_DTC_InteriorLightsUnderVoltage */
osEventFlagsId_t DemEvent_DTC_InteriorLightsUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_InteriorLightsUnderVoltage_attributes = {
  .name = "DemEvent_DTC_InteriorLightsUnderVoltage"
};
/* Definitions for DemEvent_DTC_InteriorLightsShorted */
osEventFlagsId_t DemEvent_DTC_InteriorLightsShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_InteriorLightsShorted_attributes = {
  .name = "DemEvent_DTC_InteriorLightsShorted"
};
/* Definitions for DemEvent_DTC_DoorLedUnderVoltage */
osEventFlagsId_t DemEvent_DTC_DoorLedUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_DoorLedUnderVoltage_attributes = {
  .name = "DemEvent_DTC_DoorLedUnderVoltage"
};
/* Definitions for DemEvent_DTC_DoorLedShorted */
osEventFlagsId_t DemEvent_DTC_DoorLedShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_DoorLedShorted_attributes = {
  .name = "DemEvent_DTC_DoorLedShorted"
};
/* Definitions for DemEvent_DTC_LicensePlateLigthUnderVoltage */
osEventFlagsId_t DemEvent_DTC_LicensePlateLigthUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_LicensePlateLigthUnderVoltage_attributes = {
  .name = "DemEvent_DTC_LicensePlateLigthUnderVoltage"
};
/* Definitions for DemEvent_DTC_LicensePlateLigthShorted */
osEventFlagsId_t DemEvent_DTC_LicensePlateLigthShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_LicensePlateLigthShorted_attributes = {
  .name = "DemEvent_DTC_LicensePlateLigthShorted"
};
/* Definitions for DemEvent_DTC_Mcp2515Fault */
osEventFlagsId_t DemEvent_DTC_Mcp2515FaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_Mcp2515Fault_attributes = {
  .name = "DemEvent_DTC_Mcp2515Fault"
};
/* Definitions for DemEvent_DTC_ExtEEPROMFault */
osEventFlagsId_t DemEvent_DTC_ExtEEPROMFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_ExtEEPROMFault_attributes = {
  .name = "DemEvent_DTC_ExtEEPROMFault"
};
/* Definitions for DemEvent_DTC_VibrationSensorFault */
osEventFlagsId_t DemEvent_DTC_VibrationSensorFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_VibrationSensorFault_attributes = {
  .name = "DemEvent_DTC_VibrationSensorFault"
};
/* Definitions for DemEvent_DTC_LightSensorFault */
osEventFlagsId_t DemEvent_DTC_LightSensorFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_LightSensorFault_attributes = {
  .name = "DemEvent_DTC_LightSensorFault"
};
/* Definitions for DemEvent_DTC_HC05Fault */
osEventFlagsId_t DemEvent_DTC_HC05FaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_HC05Fault_attributes = {
  .name = "DemEvent_DTC_HC05Fault"
};
/* Definitions for DemEvent_DTC_AlarmLedUnderVoltage */
osEventFlagsId_t DemEvent_DTC_AlarmLedUnderVoltageHandle;
const osEventFlagsAttr_t DemEvent_DTC_AlarmLedUnderVoltage_attributes = {
  .name = "DemEvent_DTC_AlarmLedUnderVoltage"
};
/* Definitions for DemEvent_DTC_AlarmLedShorted */
osEventFlagsId_t DemEvent_DTC_AlarmLedShortedHandle;
const osEventFlagsAttr_t DemEvent_DTC_AlarmLedShorted_attributes = {
  .name = "DemEvent_DTC_AlarmLedShorted"
};
/* Definitions for DemEvent_DTC_CentralLockBuzzerFault */
osEventFlagsId_t DemEvent_DTC_CentralLockBuzzerFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_CentralLockBuzzerFault_attributes = {
  .name = "DemEvent_DTC_CentralLockBuzzerFault"
};
/* Definitions for DemEvent_DTC_AlarmBuzzerFault */
osEventFlagsId_t DemEvent_DTC_AlarmBuzzerFaultHandle;
const osEventFlagsAttr_t DemEvent_DTC_AlarmBuzzerFault_attributes = {
  .name = "DemEvent_DTC_AlarmBuzzerFault"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/* USER CODE END FunctionPrototypes */

void OS_TASK_QM_APPL_HP(void *argument);
void OS_TASK_QM_APPL_LP(void *argument);
void OS_TASK_ASIL_APPL_HP(void *argument);
void OS_TASK_ASIL_APPL_LP(void *argument);
void OS_TASK_OS_COUNTER(void *argument);
void OS_TASK_QM_BSW_HP(void *argument);
void OS_TASK_QM_BSW_LP(void *argument);
void OS_TASK_ASIL_BSW_HP(void *argument);
void OS_TASK_ASIL_BSW_LP(void *argument);
void TASK_OS_OsInit(void *argument);
void TASK_OS_Watchdog_MainFunction(void *argument);
void Os_SecAlm_AlarmReset_Callback(void *argument);
void Os_CenLoc_LockUnlockSequence_Timer_Callback(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
void vApplicationIdleHook(void);
void vApplicationTickHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);
void vApplicationDaemonTaskStartupHook(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{

}

__weak unsigned long getRunTimeCounterValue(void)
{
return 0;
}
/* USER CODE END 1 */

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
}
/* USER CODE END 3 */

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* USER CODE BEGIN DAEMON_TASK_STARTUP_HOOK */
void vApplicationDaemonTaskStartupHook(void)
{
}
/* USER CODE END DAEMON_TASK_STARTUP_HOOK */

/* USER CODE BEGIN PREPOSTSLEEP */
__weak void PreSleepProcessing(uint32_t ulExpectedIdleTime)
{
/* place for user code */
}

__weak void PostSleepProcessing(uint32_t ulExpectedIdleTime)
{
/* place for user code */
}
/* USER CODE END PREPOSTSLEEP */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of Os_SecAlm_AlarmReset */
  Os_SecAlm_AlarmResetHandle = osTimerNew(Os_SecAlm_AlarmReset_Callback, osTimerPeriodic, NULL, &Os_SecAlm_AlarmReset_attributes);

  /* creation of Os_CenLoc_LockUnlockSequence_Timer */
  Os_CenLoc_LockUnlockSequence_TimerHandle = osTimerNew(Os_CenLoc_LockUnlockSequence_Timer_Callback, osTimerPeriodic, NULL, &Os_CenLoc_LockUnlockSequence_Timer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */

  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of QM_APPL_HP */
  QM_APPL_HPHandle = osThreadNew(OS_TASK_QM_APPL_HP, NULL, &QM_APPL_HP_attributes);

  /* creation of QM_APPL_LP */
  QM_APPL_LPHandle = osThreadNew(OS_TASK_QM_APPL_LP, NULL, &QM_APPL_LP_attributes);

  /* creation of ASIL_APPL_HP */
  ASIL_APPL_HPHandle = osThreadNew(OS_TASK_ASIL_APPL_HP, NULL, &ASIL_APPL_HP_attributes);

  /* creation of ASIL_APPL_LP */
  ASIL_APPL_LPHandle = osThreadNew(OS_TASK_ASIL_APPL_LP, NULL, &ASIL_APPL_LP_attributes);

  /* creation of OS_COUNTER */
  OS_COUNTERHandle = osThreadNew(OS_TASK_OS_COUNTER, NULL, &OS_COUNTER_attributes);

  /* creation of QM_BSW_HP */
  QM_BSW_HPHandle = osThreadNew(OS_TASK_QM_BSW_HP, NULL, &QM_BSW_HP_attributes);

  /* creation of QM_BSW_LP */
  QM_BSW_LPHandle = osThreadNew(OS_TASK_QM_BSW_LP, NULL, &QM_BSW_LP_attributes);

  /* creation of ASIL_BSW_HP */
  ASIL_BSW_HPHandle = osThreadNew(OS_TASK_ASIL_BSW_HP, NULL, &ASIL_BSW_HP_attributes);

  /* creation of ASIL_BSW_LP */
  ASIL_BSW_LPHandle = osThreadNew(OS_TASK_ASIL_BSW_LP, NULL, &ASIL_BSW_LP_attributes);

  /* creation of OsInit */
  OsInitHandle = osThreadNew(TASK_OS_OsInit, NULL, &OsInit_attributes);

  /* creation of Watchdog_MainFunction */
  Watchdog_MainFunctionHandle = osThreadNew(TASK_OS_Watchdog_MainFunction, NULL, &Watchdog_MainFunction_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of SysEvent_WatchdogReset */
  SysEvent_WatchdogResetHandle = osEventFlagsNew(&SysEvent_WatchdogReset_attributes);

  /* creation of SysEvent_PowerOnReset */
  SysEvent_PowerOnResetHandle = osEventFlagsNew(&SysEvent_PowerOnReset_attributes);

  /* creation of SysEvent_CoreReset */
  SysEvent_CoreResetHandle = osEventFlagsNew(&SysEvent_CoreReset_attributes);

  /* creation of SysEvent_HardwareReset */
  SysEvent_HardwareResetHandle = osEventFlagsNew(&SysEvent_HardwareReset_attributes);

  /* creation of SysEvent_HardFault */
  SysEvent_HardFaultHandle = osEventFlagsNew(&SysEvent_HardFault_attributes);

  /* creation of SysEvent_MemHandlerFault */
  SysEvent_MemHandlerFaultHandle = osEventFlagsNew(&SysEvent_MemHandlerFault_attributes);

  /* creation of SysEvent_BusFault */
  SysEvent_BusFaultHandle = osEventFlagsNew(&SysEvent_BusFault_attributes);

  /* creation of SysEvent_NonMaskableInterrupt */
  SysEvent_NonMaskableInterruptHandle = osEventFlagsNew(&SysEvent_NonMaskableInterrupt_attributes);

  /* creation of SysEvent_UsageFault */
  SysEvent_UsageFaultHandle = osEventFlagsNew(&SysEvent_UsageFault_attributes);

  /* creation of SysEvent_DebugMonFault */
  SysEvent_DebugMonFaultHandle = osEventFlagsNew(&SysEvent_DebugMonFault_attributes);

  /* creation of SysEvent_WWDGInterrupt */
  SysEvent_WWDGInterruptHandle = osEventFlagsNew(&SysEvent_WWDGInterrupt_attributes);

  /* creation of SysEvent_PVDInterrupt */
  SysEvent_PVDInterruptHandle = osEventFlagsNew(&SysEvent_PVDInterrupt_attributes);

  /* creation of SysEvent_RTCWakeupInterrupt */
  SysEvent_RTCWakeupInterruptHandle = osEventFlagsNew(&SysEvent_RTCWakeupInterrupt_attributes);

  /* creation of SysEvent_FlashInterurpt */
  SysEvent_FlashInterurptHandle = osEventFlagsNew(&SysEvent_FlashInterurpt_attributes);

  /* creation of SysEvent_RCCInterrupt */
  SysEvent_RCCInterruptHandle = osEventFlagsNew(&SysEvent_RCCInterrupt_attributes);

  /* creation of SysEvent_ADCInterrupt */
  SysEvent_ADCInterruptHandle = osEventFlagsNew(&SysEvent_ADCInterrupt_attributes);

  /* creation of SysEvent_TIM1Interrupt */
  SysEvent_TIM1InterruptHandle = osEventFlagsNew(&SysEvent_TIM1Interrupt_attributes);

  /* creation of SysEvent_TIM2Interrupt */
  SysEvent_TIM2InterruptHandle = osEventFlagsNew(&SysEvent_TIM2Interrupt_attributes);

  /* creation of SysEvent_TIM3Interrupt */
  SysEvent_TIM3InterruptHandle = osEventFlagsNew(&SysEvent_TIM3Interrupt_attributes);

  /* creation of SysEvent_TIM4Interrupt */
  SysEvent_TIM4InterruptHandle = osEventFlagsNew(&SysEvent_TIM4Interrupt_attributes);

  /* creation of SysEvent_TIM5Interrupt */
  SysEvent_TIM5InterruptHandle = osEventFlagsNew(&SysEvent_TIM5Interrupt_attributes);

  /* creation of SysEvent_TIM9Interrupt */
  SysEvent_TIM9InterruptHandle = osEventFlagsNew(&SysEvent_TIM9Interrupt_attributes);

  /* creation of SysEvent_TIM11Interrupt */
  SysEvent_TIM11InterruptHandle = osEventFlagsNew(&SysEvent_TIM11Interrupt_attributes);

  /* creation of SysEvent_TIMFault */
  SysEvent_TIMFaultHandle = osEventFlagsNew(&SysEvent_TIMFault_attributes);

  /* creation of SysEvent_I2CInterrupt */
  SysEvent_I2CInterruptHandle = osEventFlagsNew(&SysEvent_I2CInterrupt_attributes);

  /* creation of SysEvent_I2CFault */
  SysEvent_I2CFaultHandle = osEventFlagsNew(&SysEvent_I2CFault_attributes);

  /* creation of SysEvent_SPIFault */
  SysEvent_SPIFaultHandle = osEventFlagsNew(&SysEvent_SPIFault_attributes);

  /* creation of SysEvent_SPIInterrupt */
  SysEvent_SPIInterruptHandle = osEventFlagsNew(&SysEvent_SPIInterrupt_attributes);

  /* creation of SysEvent_USARTInterrupt */
  SysEvent_USARTInterruptHandle = osEventFlagsNew(&SysEvent_USARTInterrupt_attributes);

  /* creation of SysEvent_USARTFault */
  SysEvent_USARTFaultHandle = osEventFlagsNew(&SysEvent_USARTFault_attributes);

  /* creation of SysEvent_DMAInterrupt */
  SysEvent_DMAInterruptHandle = osEventFlagsNew(&SysEvent_DMAInterrupt_attributes);

  /* creation of SysEvent_SoftwareReset */
  SysEvent_SoftwareResetHandle = osEventFlagsNew(&SysEvent_SoftwareReset_attributes);

  /* creation of DemEvent_DTC_HardwareReset */
  DemEvent_DTC_HardwareResetHandle = osEventFlagsNew(&DemEvent_DTC_HardwareReset_attributes);

  /* creation of DemEvent_DTC_SoftwareReset */
  DemEvent_DTC_SoftwareResetHandle = osEventFlagsNew(&DemEvent_DTC_SoftwareReset_attributes);

  /* creation of DemEvent_DTC_PowerOnReset */
  DemEvent_DTC_PowerOnResetHandle = osEventFlagsNew(&DemEvent_DTC_PowerOnReset_attributes);

  /* creation of DemEvent_DTC_WatchdogReset */
  DemEvent_DTC_WatchdogResetHandle = osEventFlagsNew(&DemEvent_DTC_WatchdogReset_attributes);

  /* creation of DemEvent_DTC_DMAFault */
  DemEvent_DTC_DMAFaultHandle = osEventFlagsNew(&DemEvent_DTC_DMAFault_attributes);

  /* creation of DemEvent_DTC_I2CFault */
  DemEvent_DTC_I2CFaultHandle = osEventFlagsNew(&DemEvent_DTC_I2CFault_attributes);

  /* creation of DemEvent_DTC_SPIFault */
  DemEvent_DTC_SPIFaultHandle = osEventFlagsNew(&DemEvent_DTC_SPIFault_attributes);

  /* creation of SysEvent_OSFault */
  SysEvent_OSFaultHandle = osEventFlagsNew(&SysEvent_OSFault_attributes);

  /* creation of SysEvent_ComFault */
  SysEvent_ComFaultHandle = osEventFlagsNew(&SysEvent_ComFault_attributes);

  /* creation of SysEvent_IOFault */
  SysEvent_IOFaultHandle = osEventFlagsNew(&SysEvent_IOFault_attributes);

  /* creation of SysEvent_DiagFault */
  SysEvent_DiagFaultHandle = osEventFlagsNew(&SysEvent_DiagFault_attributes);

  /* creation of SysEvent_MemFault */
  SysEvent_MemFaultHandle = osEventFlagsNew(&SysEvent_MemFault_attributes);

  /* creation of SysEvent_SysFault */
  SysEvent_SysFaultHandle = osEventFlagsNew(&SysEvent_SysFault_attributes);

  /* creation of SysEvent_ApplFault */
  SysEvent_ApplFaultHandle = osEventFlagsNew(&SysEvent_ApplFault_attributes);

  /* creation of SysEvent_CenLocFault */
  SysEvent_CenLocFaultHandle = osEventFlagsNew(&SysEvent_CenLocFault_attributes);

  /* creation of SysEvent_SecAlmFault */
  SysEvent_SecAlmFaultHandle = osEventFlagsNew(&SysEvent_SecAlmFault_attributes);

  /* creation of SysEvent_BtcFault */
  SysEvent_BtcFaultHandle = osEventFlagsNew(&SysEvent_BtcFault_attributes);

  /* creation of SysEvent_IntLightsFault */
  SysEvent_IntLightsFaultHandle = osEventFlagsNew(&SysEvent_IntLightsFault_attributes);

  /* creation of SysEvent_CanFault */
  SysEvent_CanFaultHandle = osEventFlagsNew(&SysEvent_CanFault_attributes);

  /* creation of SysEvent_DcmFault */
  SysEvent_DcmFaultHandle = osEventFlagsNew(&SysEvent_DcmFault_attributes);

  /* creation of SysEvent_RteFault */
  SysEvent_RteFaultHandle = osEventFlagsNew(&SysEvent_RteFault_attributes);

  /* creation of SysEvent_DemFault */
  SysEvent_DemFaultHandle = osEventFlagsNew(&SysEvent_DemFault_attributes);

  /* creation of SysEvent_CrcFault */
  SysEvent_CrcFaultHandle = osEventFlagsNew(&SysEvent_CrcFault_attributes);

  /* creation of SysEvent_EcuFault */
  SysEvent_EcuFaultHandle = osEventFlagsNew(&SysEvent_EcuFault_attributes);

  /* creation of SysEvent_PortFault */
  SysEvent_PortFaultHandle = osEventFlagsNew(&SysEvent_PortFault_attributes);

  /* creation of SysEvent_PWMFault */
  SysEvent_PWMFaultHandle = osEventFlagsNew(&SysEvent_PWMFault_attributes);

  /* creation of DemEvent_DTC_ADCFault */
  DemEvent_DTC_ADCFaultHandle = osEventFlagsNew(&DemEvent_DTC_ADCFault_attributes);

  /* creation of DemEvent_DTC_PWMFault */
  DemEvent_DTC_PWMFaultHandle = osEventFlagsNew(&DemEvent_DTC_PWMFault_attributes);

  /* creation of DemEvent_DTC_CanFault */
  DemEvent_DTC_CanFaultHandle = osEventFlagsNew(&DemEvent_DTC_CanFault_attributes);

  /* creation of DemEvent_DTC_BtcFault */
  DemEvent_DTC_BtcFaultHandle = osEventFlagsNew(&DemEvent_DTC_BtcFault_attributes);

  /* creation of DemEvent_DTC_USARTFault */
  DemEvent_DTC_USARTFaultHandle = osEventFlagsNew(&DemEvent_DTC_USARTFault_attributes);

  /* creation of DemEvent_DTC_WatchdogFault */
  DemEvent_DTC_WatchdogFaultHandle = osEventFlagsNew(&DemEvent_DTC_WatchdogFault_attributes);

  /* creation of DemEvent_DTC_FlashFault */
  DemEvent_DTC_FlashFaultHandle = osEventFlagsNew(&DemEvent_DTC_FlashFault_attributes);

  /* creation of DemEvent_DTC_RamFault */
  DemEvent_DTC_RamFaultHandle = osEventFlagsNew(&DemEvent_DTC_RamFault_attributes);

  /* creation of DemEvent_DTC_TimerFault */
  DemEvent_DTC_TimerFaultHandle = osEventFlagsNew(&DemEvent_DTC_TimerFault_attributes);

  /* creation of DemEvent_DTC_EcuUnderVoltage */
  DemEvent_DTC_EcuUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_EcuUnderVoltage_attributes);

  /* creation of DemEvent_DTC_LowBeamShorted */
  DemEvent_DTC_LowBeamShortedHandle = osEventFlagsNew(&DemEvent_DTC_LowBeamShorted_attributes);

  /* creation of DemEvent_DTC_LowBeamUnderVoltage */
  DemEvent_DTC_LowBeamUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_LowBeamUnderVoltage_attributes);

  /* creation of DemEvent_DTC_RTCFault */
  DemEvent_DTC_RTCFaultHandle = osEventFlagsNew(&DemEvent_DTC_RTCFault_attributes);

  /* creation of DemEvent_DTC_HighBeamUnderVoltage */
  DemEvent_DTC_HighBeamUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_HighBeamUnderVoltage_attributes);

  /* creation of DemEvent_DTC_HighBeamShorted */
  DemEvent_DTC_HighBeamShortedHandle = osEventFlagsNew(&DemEvent_DTC_HighBeamShorted_attributes);

  /* creation of DemEvent_DTC_DayTimeRunningLightUnderVoltage */
  DemEvent_DTC_DayTimeRunningLightUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_DayTimeRunningLightUnderVoltage_attributes);

  /* creation of DemEvent_DTC_DayTimeRunningLightShorted */
  DemEvent_DTC_DayTimeRunningLightShortedHandle = osEventFlagsNew(&DemEvent_DTC_DayTimeRunningLightShorted_attributes);

  /* creation of DemEvent_DTC_FrontFogLightsUnderVoltage */
  DemEvent_DTC_FrontFogLightsUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_FrontFogLightsUnderVoltage_attributes);

  /* creation of DemEvent_DTC_FrontFogLightShorted */
  DemEvent_DTC_FrontFogLightShortedHandle = osEventFlagsNew(&DemEvent_DTC_FrontFogLightShorted_attributes);

  /* creation of DemEvent_DTC_RearFogLightUnderVoltage */
  DemEvent_DTC_RearFogLightUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_RearFogLightUnderVoltage_attributes);

  /* creation of DemEvent_DTC_RearFogLightShorted */
  DemEvent_DTC_RearFogLightShortedHandle = osEventFlagsNew(&DemEvent_DTC_RearFogLightShorted_attributes);

  /* creation of DemEvent_DTC_RearPositionLightUnderVoltage */
  DemEvent_DTC_RearPositionLightUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_RearPositionLightUnderVoltage_attributes);

  /* creation of DemEvent_DTC_RearPositionLightShorted */
  DemEvent_DTC_RearPositionLightShortedHandle = osEventFlagsNew(&DemEvent_DTC_RearPositionLightShorted_attributes);

  /* creation of DemEvent_DTC_RightTurnSignalUnderVoltage */
  DemEvent_DTC_RightTurnSignalUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_RightTurnSignalUnderVoltage_attributes);

  /* creation of DemEvent_DTC_LeftTurnSignalUnderVoltage */
  DemEvent_DTC_LeftTurnSignalUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_LeftTurnSignalUnderVoltage_attributes);

  /* creation of DemEvent_DTC_RightTurnSignalShorted */
  DemEvent_DTC_RightTurnSignalShortedHandle = osEventFlagsNew(&DemEvent_DTC_RightTurnSignalShorted_attributes);

  /* creation of DemEvent_DTC_LeftTurnSignalShorted */
  DemEvent_DTC_LeftTurnSignalShortedHandle = osEventFlagsNew(&DemEvent_DTC_LeftTurnSignalShorted_attributes);

  /* creation of DemEvent_DTC_ReverseLightUnderVoltage */
  DemEvent_DTC_ReverseLightUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_ReverseLightUnderVoltage_attributes);

  /* creation of DemEvent_DTC_ReverseLightShorted */
  DemEvent_DTC_ReverseLightShortedHandle = osEventFlagsNew(&DemEvent_DTC_ReverseLightShorted_attributes);

  /* creation of DemEvent_DTC_InteriorLightsUnderVoltage */
  DemEvent_DTC_InteriorLightsUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_InteriorLightsUnderVoltage_attributes);

  /* creation of DemEvent_DTC_InteriorLightsShorted */
  DemEvent_DTC_InteriorLightsShortedHandle = osEventFlagsNew(&DemEvent_DTC_InteriorLightsShorted_attributes);

  /* creation of DemEvent_DTC_DoorLedUnderVoltage */
  DemEvent_DTC_DoorLedUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_DoorLedUnderVoltage_attributes);

  /* creation of DemEvent_DTC_DoorLedShorted */
  DemEvent_DTC_DoorLedShortedHandle = osEventFlagsNew(&DemEvent_DTC_DoorLedShorted_attributes);

  /* creation of DemEvent_DTC_LicensePlateLigthUnderVoltage */
  DemEvent_DTC_LicensePlateLigthUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_LicensePlateLigthUnderVoltage_attributes);

  /* creation of DemEvent_DTC_LicensePlateLigthShorted */
  DemEvent_DTC_LicensePlateLigthShortedHandle = osEventFlagsNew(&DemEvent_DTC_LicensePlateLigthShorted_attributes);

  /* creation of DemEvent_DTC_Mcp2515Fault */
  DemEvent_DTC_Mcp2515FaultHandle = osEventFlagsNew(&DemEvent_DTC_Mcp2515Fault_attributes);

  /* creation of DemEvent_DTC_ExtEEPROMFault */
  DemEvent_DTC_ExtEEPROMFaultHandle = osEventFlagsNew(&DemEvent_DTC_ExtEEPROMFault_attributes);

  /* creation of DemEvent_DTC_VibrationSensorFault */
  DemEvent_DTC_VibrationSensorFaultHandle = osEventFlagsNew(&DemEvent_DTC_VibrationSensorFault_attributes);

  /* creation of DemEvent_DTC_LightSensorFault */
  DemEvent_DTC_LightSensorFaultHandle = osEventFlagsNew(&DemEvent_DTC_LightSensorFault_attributes);

  /* creation of DemEvent_DTC_HC05Fault */
  DemEvent_DTC_HC05FaultHandle = osEventFlagsNew(&DemEvent_DTC_HC05Fault_attributes);

  /* creation of DemEvent_DTC_AlarmLedUnderVoltage */
  DemEvent_DTC_AlarmLedUnderVoltageHandle = osEventFlagsNew(&DemEvent_DTC_AlarmLedUnderVoltage_attributes);

  /* creation of DemEvent_DTC_AlarmLedShorted */
  DemEvent_DTC_AlarmLedShortedHandle = osEventFlagsNew(&DemEvent_DTC_AlarmLedShorted_attributes);

  /* creation of DemEvent_DTC_CentralLockBuzzerFault */
  DemEvent_DTC_CentralLockBuzzerFaultHandle = osEventFlagsNew(&DemEvent_DTC_CentralLockBuzzerFault_attributes);

  /* creation of DemEvent_DTC_AlarmBuzzerFault */
  DemEvent_DTC_AlarmBuzzerFaultHandle = osEventFlagsNew(&DemEvent_DTC_AlarmBuzzerFault_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_OS_TASK_QM_APPL_HP */
/**
  * @brief  Function implementing the QM_APPL_HP thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_OS_TASK_QM_APPL_HP */
void OS_TASK_QM_APPL_HP(void *argument)
{
  /* USER CODE BEGIN OS_TASK_QM_APPL_HP */

//	TickType_t osAlarmLastCount;
//	const TickType_t osAlarmPeriod = pdMS_TO_TICKS(100);
//	osAlarmLastCount = xTaskGetTickCount();

	for(;;)
	{

		//vTaskDelayUntil(&osAlarmLastCount, osAlarmPeriod);

		Rte_Runnable_CenLoc_MainFunction();

		osDelay(1);

	}

  /* USER CODE END OS_TASK_QM_APPL_HP */
}

/* USER CODE BEGIN Header_OS_TASK_QM_APPL_LP */
/**
* @brief Function implementing the QM_APPL_LP thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OS_TASK_QM_APPL_LP */
void OS_TASK_QM_APPL_LP(void *argument)
{
  /* USER CODE BEGIN OS_TASK_QM_APPL_LP */

//	TickType_t osAlarmLastCount;
//	const TickType_t osAlarmPeriod = pdMS_TO_TICKS(100);
//	osAlarmLastCount = xTaskGetTickCount();

	for(;;)
	{

		//vTaskDelayUntil(&osAlarmLastCount, osAlarmPeriod);

		Rte_Runnable_IntLights_MainFunction();

		osDelay(1);

	}

  /* USER CODE END OS_TASK_QM_APPL_LP */
}

/* USER CODE BEGIN Header_OS_TASK_ASIL_APPL_HP */
/**
* @brief Function implementing the ASIL_APPL_HP thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OS_TASK_ASIL_APPL_HP */
void OS_TASK_ASIL_APPL_HP(void *argument)
{
  /* USER CODE BEGIN OS_TASK_ASIL_APPL_HP */

//	TickType_t osAlarmLastCount;
//	const TickType_t osAlarmPeriod = pdMS_TO_TICKS(10);
//	osAlarmLastCount = xTaskGetTickCount();

	for(;;)
	{

		//vTaskDelayUntil(&osAlarmLastCount, osAlarmPeriod);

		Rte_Runnable_Btc_MainFunction();

		osDelay(1);

	}

  /* USER CODE END OS_TASK_ASIL_APPL_HP */
}

/* USER CODE BEGIN Header_OS_TASK_ASIL_APPL_LP */
/**
* @brief Function implementing the ASIL_APPL_LP thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OS_TASK_ASIL_APPL_LP */
void OS_TASK_ASIL_APPL_LP(void *argument)
{
  /* USER CODE BEGIN OS_TASK_ASIL_APPL_LP */

//	TickType_t osAlarmLastCount;
//	const TickType_t osAlarmPeriod = pdMS_TO_TICKS(15);
//	osAlarmLastCount = xTaskGetTickCount();

	for(;;)
	{

		//vTaskDelayUntil(&osAlarmLastCount, osAlarmPeriod);

		Rte_Runnable_ExtLights_MainFunction();
		Rte_Runnable_SecAlm_MainFunction();

		osDelay(1);

	}

  /* USER CODE END OS_TASK_ASIL_APPL_LP */
}

/* USER CODE BEGIN Header_OS_TASK_OS_COUNTER */
/**
* @brief Function implementing the OS_COUNTER thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OS_TASK_OS_COUNTER */
void OS_TASK_OS_COUNTER(void *argument)
{
  /* USER CODE BEGIN OS_TASK_OS_COUNTER */

	for(;;)
	{

	  OS_Counter++;

	  osDelay(1);

	}

  /* USER CODE END OS_TASK_OS_COUNTER */
}

/* USER CODE BEGIN Header_OS_TASK_QM_BSW_HP */
/**
* @brief Function implementing the QM_BSW_HP thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OS_TASK_QM_BSW_HP */
void OS_TASK_QM_BSW_HP(void *argument)
{
  /* USER CODE BEGIN OS_TASK_QM_BSW_HP */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END OS_TASK_QM_BSW_HP */
}

/* USER CODE BEGIN Header_OS_TASK_QM_BSW_LP */
/**
* @brief Function implementing the QM_BSW_LP thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OS_TASK_QM_BSW_LP */
void OS_TASK_QM_BSW_LP(void *argument)
{
  /* USER CODE BEGIN OS_TASK_QM_BSW_LP */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END OS_TASK_QM_BSW_LP */
}

/* USER CODE BEGIN Header_OS_TASK_ASIL_BSW_HP */
/**
* @brief Function implementing the ASIL_BSW_HP thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OS_TASK_ASIL_BSW_HP */
void OS_TASK_ASIL_BSW_HP(void *argument)
{
  /* USER CODE BEGIN OS_TASK_ASIL_BSW_HP */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END OS_TASK_ASIL_BSW_HP */
}

/* USER CODE BEGIN Header_OS_TASK_ASIL_BSW_LP */
/**
* @brief Function implementing the ASIL_BSW_LP thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OS_TASK_ASIL_BSW_LP */
void OS_TASK_ASIL_BSW_LP(void *argument)
{
  /* USER CODE BEGIN OS_TASK_ASIL_BSW_LP */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END OS_TASK_ASIL_BSW_LP */
}

/* USER CODE BEGIN Header_TASK_OS_OsInit */
/**
* @brief Function implementing the OsInit thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_OS_OsInit */
void TASK_OS_OsInit(void *argument)
{
  /* USER CODE BEGIN TASK_OS_OsInit */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END TASK_OS_OsInit */
}

/* USER CODE BEGIN Header_TASK_OS_Watchdog_MainFunction */
/**
* @brief Function implementing the Watchdog_MainFunction thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_OS_Watchdog_MainFunction */
void TASK_OS_Watchdog_MainFunction(void *argument)
{
  /* USER CODE BEGIN TASK_OS_Watchdog_MainFunction */
  /* Infinite loop */
  for(;;)
  {

	  HAL_WWDG_Refresh(&hwwdg);
    osDelay(1);
  }
  /* USER CODE END TASK_OS_Watchdog_MainFunction */
}

/* Os_SecAlm_AlarmReset_Callback function */
void Os_SecAlm_AlarmReset_Callback(void *argument)
{
  /* USER CODE BEGIN Os_SecAlm_AlarmReset_Callback */

  /* USER CODE END Os_SecAlm_AlarmReset_Callback */
}

/* Os_CenLoc_LockUnlockSequence_Timer_Callback function */
void Os_CenLoc_LockUnlockSequence_Timer_Callback(void *argument)
{
  /* USER CODE BEGIN Os_CenLoc_LockUnlockSequence_Timer_Callback */

	if(Timer2Counter_CenLoc_Tim2IRQFlag <= 6
		&& ((Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_LOW && Rte_P_CenLoc_CenLocPort_CenLoc_PreviousStateFlag == STD_HIGH)
		|| (Rte_P_CenLoc_CenLocPort_CenLoc_CurrentState == STD_HIGH && Rte_P_CenLoc_CenLocPort_CenLoc_PreviousStateFlag == STD_LOW)))
	{

		Timer2Counter_CenLoc_Tim2IRQFlag++;
		Rte_Write_CenLoc_CenLocPort_CenLoc_Tim2IRQFlag(&Timer2Counter_CenLoc_Tim2IRQFlag);

	}
	else
	{

		Timer2Counter_CenLoc_Tim2IRQFlag = 7;
		Rte_Write_CenLoc_CenLocPort_CenLoc_Tim2IRQFlag(&Timer2Counter_CenLoc_Tim2IRQFlag);

	}

  /* USER CODE END Os_CenLoc_LockUnlockSequence_Timer_Callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
/* USER CODE END Application */

