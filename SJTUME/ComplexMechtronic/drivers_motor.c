#include "drivers_motor.h"
#include "main.h"
#include "gpio.h"

//MotorA 下方电机
void RotateMotorA(void)//向上
{
	HAL_GPIO_WritePin(MOTORA_1_GPIO_Port, MOTORA_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTORA_2_GPIO_Port, MOTORA_2_Pin, GPIO_PIN_RESET);
}

void RotateMotorA_R(void)//向下
{
	HAL_GPIO_WritePin(MOTORA_1_GPIO_Port, MOTORA_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTORA_2_GPIO_Port, MOTORA_2_Pin, GPIO_PIN_SET);
}

void StopMotorA(void)
{
	HAL_GPIO_WritePin(MOTORA_1_GPIO_Port, MOTORA_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTORA_2_GPIO_Port, MOTORA_2_Pin, GPIO_PIN_RESET);
}

void RotateMotorB(void)//俯视逆时针
{
	HAL_GPIO_WritePin(MOTORB_1_GPIO_Port, MOTORB_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTORB_2_GPIO_Port, MOTORB_2_Pin, GPIO_PIN_SET);
}

void RotateMotorB_R(void)//俯视顺时针
{
	HAL_GPIO_WritePin(MOTORB_1_GPIO_Port, MOTORB_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(MOTORB_2_GPIO_Port, MOTORB_2_Pin, GPIO_PIN_RESET);
}

void StopMotorB(void)
{
	HAL_GPIO_WritePin(MOTORB_1_GPIO_Port, MOTORB_1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MOTORB_2_GPIO_Port, MOTORB_2_Pin, GPIO_PIN_RESET);
}
