/**
  ******************************************************************************
  * File Name          : external_interruption.c
  * Description        : GPIO外部中断处理
  ******************************************************************************
  *
  * Copyright (c) 2017 Team TPP-Shanghai Jiao Tong University
  * All rights reserved.
  *
  * 按键，行程开关
  ******************************************************************************
  */
#include <gpio.h>
#include "utilities_debug.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	fw_printfln("HAL_GPIO_EXTI_Callback %d", GPIO_Pin);
	switch(GPIO_Pin){
		case KEY0_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
			}
			break;
		case KEY1_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
			}
			break;
		case KEY2_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
			}
			break;
		case KEY_UP_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
			}
			break;
		default:
			fw_Warning();
	}
}
