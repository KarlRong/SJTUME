/**
  ******************************************************************************
  * File Name          : pwm_server_motor.c
  * Description        : 舵机驱动
  ******************************************************************************
  *
  * Copyright (c) 2017 Team TPP-Shanghai Jiao Tong University
  * All rights reserved.
  *
  * PWM占空比对应舵机角度
  ******************************************************************************
  */
#include "pwm_server_motor.h"
#include "tim.h"

void InitServerMotors()
{
	pwm_server_motor_init(0);
	pwm_server_motor_init(1);
	pwm_server_motor_init(2);
}

void pwm_server_motor_init(uint8_t motorIndex)
{
	switch (motorIndex)
	{
		case 0:
		{
			HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
			__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,1500);
			break;
		}
		case 1:
		{
			HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_1);
			__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,1500);
			break;
		}
		case 2:
		{
			HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);
			__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,1500);
			break;
		}
	}
}

void pwm_server_motor_set_angle(uint8_t motorIndex,float angle)
{
	if(angle<0)
	{
		angle=0;
	}
	if(angle>180)
	{
		angle=180;
	}
	
	uint16_t x=angle/180*1900+500;
	
	switch(motorIndex)
	{
		case 0://靠外舵机
		{
			__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,x);
			break;
		}
		case 1:
		{
			__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_1,x);
			break;
		}
		case 2:
		{
			__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2,x);
			break;
		}
	}
}
