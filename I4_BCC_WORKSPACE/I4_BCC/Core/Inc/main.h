/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Std_Types.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "timers.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
EXTERN osTimerId_t PdcFrontDelayTimerHandle;
EXTERN osTimerId_t PdcRearDelayTimerHandle;
EXTERN osTimerId_t PdcSecondFrontDelayTimerHandle;
EXTERN osTimerId_t PdcSecondRearDelayTimerHandle;
EXTERN osTimerId_t PdcFrontGlobalTimerHandle;
EXTERN osTimerId_t PdcRearGlobalTimerHandle;
EXTERN osTimerId_t RLTSHLHandle;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
EXTERN void SystemClock_Config(void);
EXTERN void MX_FREERTOS_Init(void);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LTS_Pin GPIO_PIN_0
#define LTS_GPIO_Port GPIOC
#define RTS_Pin GPIO_PIN_1
#define RTS_GPIO_Port GPIOC
#define IL_Pin GPIO_PIN_2
#define IL_GPIO_Port GPIOC
#define FL_Pin GPIO_PIN_3
#define FL_GPIO_Port GPIOC
#define LPN_Pin GPIO_PIN_0
#define LPN_GPIO_Port GPIOA
#define DRL_Pin GPIO_PIN_1
#define DRL_GPIO_Port GPIOA
#define LB_Pin GPIO_PIN_4
#define LB_GPIO_Port GPIOA
#define BUZZ1_Pin GPIO_PIN_4
#define BUZZ1_GPIO_Port GPIOC
#define HB_Pin GPIO_PIN_0
#define HB_GPIO_Port GPIOB
#define BUZZ2_Pin GPIO_PIN_13
#define BUZZ2_GPIO_Port GPIOB
#define BUZZ3_Pin GPIO_PIN_14
#define BUZZ3_GPIO_Port GPIOB
#define BUZZ4_Pin GPIO_PIN_15
#define BUZZ4_GPIO_Port GPIOB
#define SAL_Pin GPIO_PIN_15
#define SAL_GPIO_Port GPIOA
#define RFL_Pin GPIO_PIN_10
#define RFL_GPIO_Port GPIOC
#define BL_Pin GPIO_PIN_11
#define BL_GPIO_Port GPIOC
#define PRL_Pin GPIO_PIN_12
#define PRL_GPIO_Port GPIOC
#define CLL_Pin GPIO_PIN_7
#define CLL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
