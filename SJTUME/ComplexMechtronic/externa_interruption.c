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
#include "pwm_server_motor.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	fw_printfln("HAL_GPIO_EXTI_Callback %x", GPIO_Pin);
	switch(GPIO_Pin){
		case KEY0_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
				pwm_server_motor_set_angle(0, 0);
			}
			break;
		case KEY1_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
				pwm_server_motor_set_angle(0, 90);
			}
			break;
		case KEY2_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
				pwm_server_motor_set_angle(0, 180);
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
