#ifndef _STEPER_H
#define _STEPER_H
#include "main.h"
#include "gpio.h"

#define T1_FREQ 10000     //定时器频率
#define FSPR    400         //步进电机单圈步数
#define SPR     (FSPR*25)  //25细分的步数 10000步一圈
// 数学常数。 用于MSD_Move函数的简化计算
#define ALPHA (2*3.14159/SPR)                    // 2*pi/spr
#define A_T_x100 ((long)(ALPHA*T1_FREQ*100))     // (ALPHA / T1_FREQ)*100


#define T1_FREQ_148 ((int)((T1_FREQ*0.676)/25)) // divided by 100 and scaled by 0.676
#define A_SQ (long)(ALPHA*2*10000000000)         // 
#define A_x20000 (int)(ALPHA*20000)              // ALPHA*20000


//速度曲线状态
#define STOP  0
#define ACCEL 1
#define DECEL 2
#define RUN   3

typedef struct {
  //电机运行状态
  unsigned char run_state : 3;
  //电机运行方向
  unsigned char dir : 1;
  //下一个脉冲延时周期，启动时为加速度速率
  unsigned int step_delay;
  //开始减速的位置
  unsigned int decel_start;
  //减速距离
  signed int decel_val;
  //最小延时（即最大速度）
  signed int min_delay;
  //加速或者减速计数器
  signed int accel_count;
  //移动计数
  long step_count_X;
	long step_count_Y;
	long step_count;
  //移动目标数
  signed int target_count_X;
	signed int target_count_Y;
	signed int target_count_Z;
	signed int target_count;
} speedRampData;



#define DIR_A PAout(1)	// 方向位
#define DIR_A_HIGH  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)
#define DIR_A_LOW HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)

#define PULSE_A HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)	// 脉冲位
#define PULSE_A_HIGH  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET)
#define PULSE_A_LOW HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET)
#define PULSE_A_TOGGLE HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6)


#define DIR_B PAout(4)	// 方向位
#define DIR_B_HIGH  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define DIR_B_LOW HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)

#define PULSE_B PAout(5)	// 脉冲位
#define PULSE_B_HIGH  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)
#define PULSE_B_LOW HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)
#define PULSE_B_TOGGLE HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5)


#define DIR_C PAout(2)	// 方向位
#define DIR_C_HIGH  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET)
#define DIR_C_LOW HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET)


#define PULSE_C HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)	// 脉冲位
#define PULSE_C_HIGH  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET)
#define PULSE_C_LOW HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET)
#define PULSE_C_TOGGLE HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7)

void MSD_Move(signed int step_X,signed int step_Y, char flag);
void MSD_Z_Move(signed int step_Z);

#endif
