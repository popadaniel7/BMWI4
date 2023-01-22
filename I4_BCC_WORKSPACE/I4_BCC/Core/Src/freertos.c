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

#include "Mcp2515.h"
#include "CanSpi.h"
#include "CenLoc.h"
#include "ExtLights.h"
#include "IntLights.h"
#include "SecAlm.h"
#include "BTC.h"
#include "PDC.h"
#include "HVAC.h"
#include "Std_Types.h"
#include "Project_Definitions.h"

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
/* Definitions for QM_APPL_LP */
osThreadId_t QM_APPL_LPHandle;
const osThreadAttr_t QM_APPL_LP_attributes = {
  .name = "QM_APPL_LP",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for OS_StartHook */
osThreadId_t OS_StartHookHandle;
const osThreadAttr_t OS_StartHook_attributes = {
  .name = "OS_StartHook",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime7,
};
/* Definitions for PdcFrontDelayTimer */
osTimerId_t PdcFrontDelayTimerHandle;
const osTimerAttr_t PdcFrontDelayTimer_attributes = {
  .name = "PdcFrontDelayTimer"
};
/* Definitions for PdcRearDelayTimer */
osTimerId_t PdcRearDelayTimerHandle;
const osTimerAttr_t PdcRearDelayTimer_attributes = {
  .name = "PdcRearDelayTimer"
};
/* Definitions for PdcSecondFrontDelayTimer */
osTimerId_t PdcSecondFrontDelayTimerHandle;
const osTimerAttr_t PdcSecondFrontDelayTimer_attributes = {
  .name = "PdcSecondFrontDelayTimer"
};
/* Definitions for PdcSecondRearDelayTimer */
osTimerId_t PdcSecondRearDelayTimerHandle;
const osTimerAttr_t PdcSecondRearDelayTimer_attributes = {
  .name = "PdcSecondRearDelayTimer"
};
/* Definitions for PdcFrontGlobalTimer */
osTimerId_t PdcFrontGlobalTimerHandle;
const osTimerAttr_t PdcFrontGlobalTimer_attributes = {
  .name = "PdcFrontGlobalTimer"
};
/* Definitions for PdcRearGlobalTimer */
osTimerId_t PdcRearGlobalTimerHandle;
const osTimerAttr_t PdcRearGlobalTimer_attributes = {
  .name = "PdcRearGlobalTimer"
};
/* Definitions for eventPOR */
osEventFlagsId_t eventPORHandle;
const osEventFlagsAttr_t eventPOR_attributes = {
  .name = "eventPOR"
};
/* Definitions for eventHWR */
osEventFlagsId_t eventHWRHandle;
const osEventFlagsAttr_t eventHWR_attributes = {
  .name = "eventHWR"
};
/* Definitions for eventSWR */
osEventFlagsId_t eventSWRHandle;
const osEventFlagsAttr_t eventSWR_attributes = {
  .name = "eventSWR"
};
/* Definitions for eventCoreReset */
osEventFlagsId_t eventCoreResetHandle;
const osEventFlagsAttr_t eventCoreReset_attributes = {
  .name = "eventCoreReset"
};
/* Definitions for eventMemManage */
osEventFlagsId_t eventMemManageHandle;
const osEventFlagsAttr_t eventMemManage_attributes = {
  .name = "eventMemManage"
};
/* Definitions for eventNMI */
osEventFlagsId_t eventNMIHandle;
const osEventFlagsAttr_t eventNMI_attributes = {
  .name = "eventNMI"
};
/* Definitions for eventHardFault */
osEventFlagsId_t eventHardFaultHandle;
const osEventFlagsAttr_t eventHardFault_attributes = {
  .name = "eventHardFault"
};
/* Definitions for eventBusFault */
osEventFlagsId_t eventBusFaultHandle;
const osEventFlagsAttr_t eventBusFault_attributes = {
  .name = "eventBusFault"
};
/* Definitions for eventUsageFault */
osEventFlagsId_t eventUsageFaultHandle;
const osEventFlagsAttr_t eventUsageFault_attributes = {
  .name = "eventUsageFault"
};
/* Definitions for eventDebugMon */
osEventFlagsId_t eventDebugMonHandle;
const osEventFlagsAttr_t eventDebugMon_attributes = {
  .name = "eventDebugMon"
};
/* Definitions for eventPVD_IRQ */
osEventFlagsId_t eventPVD_IRQHandle;
const osEventFlagsAttr_t eventPVD_IRQ_attributes = {
  .name = "eventPVD_IRQ"
};
/* Definitions for eventFlash_IRQ */
osEventFlagsId_t eventFlash_IRQHandle;
const osEventFlagsAttr_t eventFlash_IRQ_attributes = {
  .name = "eventFlash_IRQ"
};
/* Definitions for eventRCC_IRQ */
osEventFlagsId_t eventRCC_IRQHandle;
const osEventFlagsAttr_t eventRCC_IRQ_attributes = {
  .name = "eventRCC_IRQ"
};
/* Definitions for eventTIM1_IRQ */
osEventFlagsId_t eventTIM1_IRQHandle;
const osEventFlagsAttr_t eventTIM1_IRQ_attributes = {
  .name = "eventTIM1_IRQ"
};
/* Definitions for eventTIM10_IRQ */
osEventFlagsId_t eventTIM10_IRQHandle;
const osEventFlagsAttr_t eventTIM10_IRQ_attributes = {
  .name = "eventTIM10_IRQ"
};
/* Definitions for eventTIM2_IRQ */
osEventFlagsId_t eventTIM2_IRQHandle;
const osEventFlagsAttr_t eventTIM2_IRQ_attributes = {
  .name = "eventTIM2_IRQ"
};
/* Definitions for eventTIM3_IRQ */
osEventFlagsId_t eventTIM3_IRQHandle;
const osEventFlagsAttr_t eventTIM3_IRQ_attributes = {
  .name = "eventTIM3_IRQ"
};
/* Definitions for eventTIM4_IRQ */
osEventFlagsId_t eventTIM4_IRQHandle;
const osEventFlagsAttr_t eventTIM4_IRQ_attributes = {
  .name = "eventTIM4_IRQ"
};
/* Definitions for eventSPI2_IRQ */
osEventFlagsId_t eventSPI2_IRQHandle;
const osEventFlagsAttr_t eventSPI2_IRQ_attributes = {
  .name = "eventSPI2_IRQ"
};
/* Definitions for eventSPI3_IRQ */
osEventFlagsId_t eventSPI3_IRQHandle;
const osEventFlagsAttr_t eventSPI3_IRQ_attributes = {
  .name = "eventSPI3_IRQ"
};
/* Definitions for eventUSART1_IRQ */
osEventFlagsId_t eventUSART1_IRQHandle;
const osEventFlagsAttr_t eventUSART1_IRQ_attributes = {
  .name = "eventUSART1_IRQ"
};
/* Definitions for eventWDGR */
osEventFlagsId_t eventWDGRHandle;
const osEventFlagsAttr_t eventWDGR_attributes = {
  .name = "eventWDGR"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TASK_QM_APPL_LP(void *argument);
void TASK_OS_StartHook(void *argument);
void PdcFrontDelayCallback(void *argument);
void PdcRearDelayCallback(void *argument);
void PdcSecondFrontDelayCallback(void *argument);
void PdcSecondRearDelayCallback(void *argument);
void PdcFrontGlobalTimerCallback(void *argument);
void PdcRearGlobalTimerCallback(void *argument);

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
  /* creation of PdcFrontDelayTimer */
  PdcFrontDelayTimerHandle = osTimerNew(PdcFrontDelayCallback, osTimerPeriodic, NULL, &PdcFrontDelayTimer_attributes);

  /* creation of PdcRearDelayTimer */
  PdcRearDelayTimerHandle = osTimerNew(PdcRearDelayCallback, osTimerPeriodic, NULL, &PdcRearDelayTimer_attributes);

  /* creation of PdcSecondFrontDelayTimer */
  PdcSecondFrontDelayTimerHandle = osTimerNew(PdcSecondFrontDelayCallback, osTimerPeriodic, NULL, &PdcSecondFrontDelayTimer_attributes);

  /* creation of PdcSecondRearDelayTimer */
  PdcSecondRearDelayTimerHandle = osTimerNew(PdcSecondRearDelayCallback, osTimerPeriodic, NULL, &PdcSecondRearDelayTimer_attributes);

  /* creation of PdcFrontGlobalTimer */
  PdcFrontGlobalTimerHandle = osTimerNew(PdcFrontGlobalTimerCallback, osTimerPeriodic, NULL, &PdcFrontGlobalTimer_attributes);

  /* creation of PdcRearGlobalTimer */
  PdcRearGlobalTimerHandle = osTimerNew(PdcRearGlobalTimerCallback, osTimerPeriodic, NULL, &PdcRearGlobalTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of QM_APPL_LP */
  QM_APPL_LPHandle = osThreadNew(TASK_QM_APPL_LP, NULL, &QM_APPL_LP_attributes);

  /* creation of OS_StartHook */
  OS_StartHookHandle = osThreadNew(TASK_OS_StartHook, NULL, &OS_StartHook_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the event(s) */
  /* creation of eventPOR */
  eventPORHandle = osEventFlagsNew(&eventPOR_attributes);

  /* creation of eventHWR */
  eventHWRHandle = osEventFlagsNew(&eventHWR_attributes);

  /* creation of eventSWR */
  eventSWRHandle = osEventFlagsNew(&eventSWR_attributes);

  /* creation of eventCoreReset */
  eventCoreResetHandle = osEventFlagsNew(&eventCoreReset_attributes);

  /* creation of eventMemManage */
  eventMemManageHandle = osEventFlagsNew(&eventMemManage_attributes);

  /* creation of eventNMI */
  eventNMIHandle = osEventFlagsNew(&eventNMI_attributes);

  /* creation of eventHardFault */
  eventHardFaultHandle = osEventFlagsNew(&eventHardFault_attributes);

  /* creation of eventBusFault */
  eventBusFaultHandle = osEventFlagsNew(&eventBusFault_attributes);

  /* creation of eventUsageFault */
  eventUsageFaultHandle = osEventFlagsNew(&eventUsageFault_attributes);

  /* creation of eventDebugMon */
  eventDebugMonHandle = osEventFlagsNew(&eventDebugMon_attributes);

  /* creation of eventPVD_IRQ */
  eventPVD_IRQHandle = osEventFlagsNew(&eventPVD_IRQ_attributes);

  /* creation of eventFlash_IRQ */
  eventFlash_IRQHandle = osEventFlagsNew(&eventFlash_IRQ_attributes);

  /* creation of eventRCC_IRQ */
  eventRCC_IRQHandle = osEventFlagsNew(&eventRCC_IRQ_attributes);

  /* creation of eventTIM1_IRQ */
  eventTIM1_IRQHandle = osEventFlagsNew(&eventTIM1_IRQ_attributes);

  /* creation of eventTIM10_IRQ */
  eventTIM10_IRQHandle = osEventFlagsNew(&eventTIM10_IRQ_attributes);

  /* creation of eventTIM2_IRQ */
  eventTIM2_IRQHandle = osEventFlagsNew(&eventTIM2_IRQ_attributes);

  /* creation of eventTIM3_IRQ */
  eventTIM3_IRQHandle = osEventFlagsNew(&eventTIM3_IRQ_attributes);

  /* creation of eventTIM4_IRQ */
  eventTIM4_IRQHandle = osEventFlagsNew(&eventTIM4_IRQ_attributes);

  /* creation of eventSPI2_IRQ */
  eventSPI2_IRQHandle = osEventFlagsNew(&eventSPI2_IRQ_attributes);

  /* creation of eventSPI3_IRQ */
  eventSPI3_IRQHandle = osEventFlagsNew(&eventSPI3_IRQ_attributes);

  /* creation of eventUSART1_IRQ */
  eventUSART1_IRQHandle = osEventFlagsNew(&eventUSART1_IRQ_attributes);

  /* creation of eventWDGR */
  eventWDGRHandle = osEventFlagsNew(&eventWDGR_attributes);

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_TASK_QM_APPL_LP */
/**
  * @brief  Function implementing the QM_APPL_LP_TASK thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TASK_QM_APPL_LP */
void TASK_QM_APPL_LP(void *argument)
{
  /* USER CODE BEGIN TASK_QM_APPL_LP */
	CenLocMainFunction();
	SecAlmMainFunction();
	//PdcMainFunction();
	BtcMainFunction();
	ExtLightsMainFunction();
	IntLightsMainFunction();
	//HVACMainFunction();
  /* USER CODE END TASK_QM_APPL_LP */
}

/* USER CODE BEGIN Header_TASK_OS_StartHook */
/**
* @brief Function implementing the OS_StartHook thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TASK_OS_StartHook */
void TASK_OS_StartHook(void *argument)
{
  /* USER CODE BEGIN TASK_OS_StartHook */

	OS_Counter++;

  /* USER CODE END TASK_OS_StartHook */
}

/* PdcFrontDelayCallback function */
void PdcFrontDelayCallback(void *argument)
{
  /* USER CODE BEGIN PdcFrontDelayCallback */
	Pdc_FrontGenerateDelayFlag = STD_HIGH;
  /* USER CODE END PdcFrontDelayCallback */
}

/* PdcRearDelayCallback function */
void PdcRearDelayCallback(void *argument)
{
  /* USER CODE BEGIN PdcRearDelayCallback */
	Pdc_RearGenerateDelayFlag = STD_HIGH;
  /* USER CODE END PdcRearDelayCallback */
}

/* PdcSecondFrontDelayCallback function */
void PdcSecondFrontDelayCallback(void *argument)
{
  /* USER CODE BEGIN PdcSecondFrontDelayCallback */
	Pdc_SecondFrontGenerateDelayFlag = STD_HIGH;
  /* USER CODE END PdcSecondFrontDelayCallback */
}

/* PdcSecondRearDelayCallback function */
void PdcSecondRearDelayCallback(void *argument)
{
  /* USER CODE BEGIN PdcSecondRearDelayCallback */
	Pdc_SecondRearGenerateDelayFlag = STD_HIGH;
  /* USER CODE END PdcSecondRearDelayCallback */
}

/* PdcFrontGlobalTimerCallback function */
void PdcFrontGlobalTimerCallback(void *argument)
{
  /* USER CODE BEGIN PdcFrontGlobalTimerCallback */

  /* USER CODE END PdcFrontGlobalTimerCallback */
}

/* PdcRearGlobalTimerCallback function */
void PdcRearGlobalTimerCallback(void *argument)
{
  /* USER CODE BEGIN PdcRearGlobalTimerCallback */

  /* USER CODE END PdcRearGlobalTimerCallback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

