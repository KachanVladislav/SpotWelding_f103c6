/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define IRQ_ZERO_DETECTER_Pin GPIO_PIN_7
#define IRQ_ZERO_DETECTER_GPIO_Port GPIOA
#define IRQ_ZERO_DETECTER_EXTI_IRQn EXTI9_5_IRQn
#define SIGNAL_FIRE_Pin GPIO_PIN_0
#define SIGNAL_FIRE_GPIO_Port GPIOB
#define EncoderB_Pin GPIO_PIN_1
#define EncoderB_GPIO_Port GPIOB
#define EncoderA_Pin GPIO_PIN_10
#define EncoderA_GPIO_Port GPIOB
#define EncoderA_EXTI_IRQn EXTI15_10_IRQn
#define BUTTON_IRQ_Pin GPIO_PIN_11
#define BUTTON_IRQ_GPIO_Port GPIOB
#define BUTTON_IRQ_EXTI_IRQn EXTI15_10_IRQn
#define LED_SELECT_4_Pin GPIO_PIN_15
#define LED_SELECT_4_GPIO_Port GPIOB
#define LED_SELECT_3_Pin GPIO_PIN_8
#define LED_SELECT_3_GPIO_Port GPIOA
#define LED_SEGMENT_8_Pin GPIO_PIN_9
#define LED_SEGMENT_8_GPIO_Port GPIOA
#define LED_SEGMENT_7_Pin GPIO_PIN_10
#define LED_SEGMENT_7_GPIO_Port GPIOA
#define LED_SELECT_2_Pin GPIO_PIN_15
#define LED_SELECT_2_GPIO_Port GPIOA
#define LED_SELECT_1_Pin GPIO_PIN_3
#define LED_SELECT_1_GPIO_Port GPIOB
#define LED_SEGMENT_6_Pin GPIO_PIN_4
#define LED_SEGMENT_6_GPIO_Port GPIOB
#define LED_SEGMENT_5_Pin GPIO_PIN_5
#define LED_SEGMENT_5_GPIO_Port GPIOB
#define LED_SEGMENT_4_Pin GPIO_PIN_6
#define LED_SEGMENT_4_GPIO_Port GPIOB
#define LED_SEGMENT_3_Pin GPIO_PIN_7
#define LED_SEGMENT_3_GPIO_Port GPIOB
#define LED_SEGMENT_2_Pin GPIO_PIN_8
#define LED_SEGMENT_2_GPIO_Port GPIOB
#define LED_SEGMENT_1_Pin GPIO_PIN_9
#define LED_SEGMENT_1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
