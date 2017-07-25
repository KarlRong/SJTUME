/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define KEY2_Pin GPIO_PIN_2
#define KEY2_GPIO_Port GPIOE
#define KEY2_EXTI_IRQn EXTI2_IRQn
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY1_EXTI_IRQn EXTI3_IRQn
#define KEY0_Pin GPIO_PIN_4
#define KEY0_GPIO_Port GPIOE
#define KEY0_EXTI_IRQn EXTI4_IRQn
#define LED1_Pin GPIO_PIN_9
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_10
#define LED2_GPIO_Port GPIOF
#define KEY_UP_Pin GPIO_PIN_0
#define KEY_UP_GPIO_Port GPIOA
#define KEY_UP_EXTI_IRQn EXTI0_IRQn
#define TRAVELSWITCH2_Pin GPIO_PIN_5
#define TRAVELSWITCH2_GPIO_Port GPIOA
#define TRAVELSWITCH2_EXTI_IRQn EXTI9_5_IRQn
#define TRAVELSWITCH3_Pin GPIO_PIN_6
#define TRAVELSWITCH3_GPIO_Port GPIOA
#define TRAVELSWITCH3_EXTI_IRQn EXTI9_5_IRQn
#define TRAVELSWITCH4_Pin GPIO_PIN_7
#define TRAVELSWITCH4_GPIO_Port GPIOA
#define TRAVELSWITCH4_EXTI_IRQn EXTI9_5_IRQn
#define TRAVELSWITCH1_Pin GPIO_PIN_1
#define TRAVELSWITCH1_GPIO_Port GPIOB
#define TRAVELSWITCH1_EXTI_IRQn EXTI1_IRQn
#define TRAVELSWITCH5_Pin GPIO_PIN_8
#define TRAVELSWITCH5_GPIO_Port GPIOE
#define TRAVELSWITCH5_EXTI_IRQn EXTI9_5_IRQn
#define TRAVELSWITCH6_Pin GPIO_PIN_9
#define TRAVELSWITCH6_GPIO_Port GPIOE
#define TRAVELSWITCH6_EXTI_IRQn EXTI9_5_IRQn
#define TRAVELSWITCH7_Pin GPIO_PIN_10
#define TRAVELSWITCH7_GPIO_Port GPIOB
#define TRAVELSWITCH7_EXTI_IRQn EXTI15_10_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
