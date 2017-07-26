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
#include "steper.h"
#include "drivers_motor.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	fw_printfln("HAL_GPIO_EXTI_Callback %x", GPIO_Pin);
	switch(GPIO_Pin){
		case KEY0_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
				pwm_server_motor_set_angle(0, 0);
				pwm_server_motor_set_angle(1, 0);
				pwm_server_motor_set_angle(2, 0);
				
				RotateMotorA();
//				RotateMotorB();
				MSD_Z_Move(500);
				MSD_Move(-300,0,2);
			}
			break;
		case KEY1_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
				pwm_server_motor_set_angle(0, 90);
				pwm_server_motor_set_angle(1, 90);
				pwm_server_motor_set_angle(2, 90);
				
				RotateMotorA_R();
//				RotateMotorB_R();
      MSD_Move(0,-300,2);
				MSD_Z_Move(-500);
			}
			break;
		case KEY2_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
				pwm_server_motor_set_angle(0, 45);
				pwm_server_motor_set_angle(1, 45);
				pwm_server_motor_set_angle(2, 45);
				MSD_Move(300,0,2);
				StopMotorA();
				StopMotorB();
			}
			break;
		case KEY_UP_Pin:
			{
			  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
				MSD_Move(0,300,2);
			}
			break;
		case TRAVELSWITCH6_Pin://下电机，上限位
			{
				StopMotorA();
//				fw_printfln("TravelSitch6");
			}
			break;
		case TRAVELSWITCH7_Pin://上电机，逆时针限位
			{
				StopMotorB();
//				fw_printfln("TravelSitch7");
			}
			break;
		case TRAVELSWITCH8_Pin://下电机，下限位
			{
				StopMotorA();
//				fw_printfln("TravelSitch8");
			}
			break;
		case TRAVELSWITCH9_Pin://上电机，顺时针限位
			{
				StopMotorB();
//				fw_printfln("TravelSitch9");
			}
			break;
		default:
			fw_Warning();
	}
}
