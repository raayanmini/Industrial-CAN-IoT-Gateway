/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include <stdio.h>
#include <string.h>
#include "CANSPI.h"
#include "MCP2515.h"
#include "16x2_LCD.h"
#include "USART6.h"
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
#define SPI_CS_Pin GPIO_PIN_4
#define SPI_CS_GPIO_Port GPIOC
#define DATA4_Pin GPIO_PIN_0
#define DATA4_GPIO_Port GPIOB
#define DATA5_Pin GPIO_PIN_1
#define DATA5_GPIO_Port GPIOB
#define DATA6_Pin GPIO_PIN_2
#define DATA6_GPIO_Port GPIOB
#define GREEN_LED_Pin GPIO_PIN_14
#define GREEN_LED_GPIO_Port GPIOB
#define SWITCH_UP_Pin GPIO_PIN_8
#define SWITCH_UP_GPIO_Port GPIOC
#define SWITCH_DOWN_Pin GPIO_PIN_9
#define SWITCH_DOWN_GPIO_Port GPIOC
#define DATA7_Pin GPIO_PIN_3
#define DATA7_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_4
#define RS_GPIO_Port GPIOB
#define RW_Pin GPIO_PIN_5
#define RW_GPIO_Port GPIOB
#define EN_Pin GPIO_PIN_8
#define EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define CAN_CS_Pin GPIO_PIN_4
#define CAN_CS_GPIO_Port GPIOC
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
