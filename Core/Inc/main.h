/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define LED1_Pin GPIO_PIN_5
#define LED1_GPIO_Port GPIOE
#define SCAN_R_Pin GPIO_PIN_1
#define SCAN_R_GPIO_Port GPIOF
#define XU_0_Pin GPIO_PIN_2
#define XU_0_GPIO_Port GPIOF
#define XU_1_Pin GPIO_PIN_3
#define XU_1_GPIO_Port GPIOF
#define XU_2_Pin GPIO_PIN_4
#define XU_2_GPIO_Port GPIOF
#define XU_3_Pin GPIO_PIN_5
#define XU_3_GPIO_Port GPIOF
#define SCAN_L_Pin GPIO_PIN_6
#define SCAN_L_GPIO_Port GPIOF
#define arrive_Pin GPIO_PIN_7
#define arrive_GPIO_Port GPIOF
#define pos_Pin GPIO_PIN_8
#define pos_GPIO_Port GPIOF
#define Buzzer_Pin GPIO_PIN_10
#define Buzzer_GPIO_Port GPIOE
#define Red_Pin GPIO_PIN_11
#define Red_GPIO_Port GPIOE
#define Green_Pin GPIO_PIN_12
#define Green_GPIO_Port GPIOE
#define Yellow_Pin GPIO_PIN_13
#define Yellow_GPIO_Port GPIOE
#define AIN1_Pin GPIO_PIN_4
#define AIN1_GPIO_Port GPIOG
#define AIN2_Pin GPIO_PIN_5
#define AIN2_GPIO_Port GPIOG
#define BIN1_Pin GPIO_PIN_6
#define BIN1_GPIO_Port GPIOG
#define BIN2_Pin GPIO_PIN_7
#define BIN2_GPIO_Port GPIOG
#define LED0_Pin GPIO_PIN_5
#define LED0_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
