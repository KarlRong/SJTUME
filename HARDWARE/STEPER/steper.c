#include "steper.h"
#include "led.h"
#include "timer.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
/*
99,99,99,99,99,99,99,99,99,99,
												98,98,98,98,98,97,97,97,96,96,
												96,95,95,94,94,93,93,92,91,90,
												89,88,87,86,85,84,82,81,79,78,
												76,74,72,70,68,66,64,62,59,57,
												55,53,51,48,46,44,42,40,38,36,
												34,32,31,29,28,26,25,24,23,22,
												21,20,19,18,17,17,16,16,15,15,
												14,14,14,13,13,13,12,12,12,12,
												12,11,11,11,11,11,11,11,11,11,11
												
												30,30,30,30,30,30,30,30,30,30,
															30,30,30,30,29,29,29,29,29,29,
															29,29,29,29,29,28,28,28,28,28,
															28,27,27,27,27,26,26,26,25,25,
															25,24,24,23,23,22,22,21,21,20,
															20,
															20,19,19,18,18,17,17,16,16,15,
															15,15,14,14,14,13,13,13,13,12,
															12,12,12,12,12,11,11,11,11,11,
															11,11,11,11,11,11,10,10,10,10,
															10,10,10,10,10,10,10,10,10,10
												60,60,60,60,60,59,59,59,59,59,
															59,59,59,59,59,59,58,58,58,58,
															58,57,57,57,57,56,56,55,55,55,
															54,53,53,52,52,51,50,49,48,48,
															47,46,44,43,42,41,40,39,37,36,
															35,
															34,33,31,30,29,28,27,26,24,23,
															22,22,21,20,19,18,18,17,17,16,
															15,15,15,14,14,13,13,13,13,12,
															12,12,12,12,11,11,11,11,11,11,
															11,11,11,11,11,10,10,10,10,10
												*/
const char Step_Table[51] = {60,60,60,59,59,59,59,59,58,58,
															58,57,57,56,55,54,53,52,50,48,
															47,44,42,40,37,35,33,30,28,26,
															23,22,20,18,17,16,15,14,13,13,
															12,12,12,11,11,11,11,11,10,10,
															10};



//系统加减速参数
speedRampData srd;
//记录步进电机的位置
int stepPosition = 0;
char step_flag = 0;
char run_flag_A = 0;
char run_flag_B = 0;
char run_flag_X = 0;
char run_flag_Y = 0;

//步进电机初始化
void Steper_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOF时钟

	//A号电机初始化  GPIOA6(pul),A1(dir)初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	//B号电机初始化  GPIOA5(pul),A4(dir)初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_6);//
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_5 | GPIO_Pin_4);//
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);

}

/*! \brief 以给定的步数移动步进电机
 *  通过计算加速到最大速度，以给定的步数开始减速
 *  如果加速度和减速度很小，步进电机会移动很慢，还没达到最大速度就要开始减速
 *  \param step   移动的步数 (正数为顺时针，负数为逆时针).
 *  \param accel  加速度,如果取值为100，实际值为100*0.01*rad/sec^2=1rad/sec^2
 *  \param decel  减速度,如果取值为100，实际值为100*0.01*rad/sec^2=1rad/sec^2
 *  \param speed  最大速度,如果取值为100，实际值为100*0.01*rad/sec=1rad/sec
 */

void MSD_Move(signed int step_X,signed int step_Y, char flag)   //  flag == 1:先Y后X    flag == 2:先X后Y
{
	step_flag = 1;  //START 1  RUN 2  TURN 3  RUN 4  OVER 5
	srd.target_count_X = step_X;
	srd.target_count_Y = step_Y;
	srd.target_count=0;
	srd.step_count=0;
	switch (flag)
	{
		case 1:       //先沿Y轴移动，再沿X轴移动
			run_flag_X = 0;
			run_flag_Y = 1;
			break;
		case 2:       //先沿X轴移动，再沿Y轴移动
			run_flag_X = 1;
			run_flag_Y = 0;
			break;
		default:
			break;		
	}
}
/*
void MSD_Move_A(signed int step)
{
    // 根据步数的正负来判断方向
    if(step < 0)//逆时针
    {
        DIR_A = 0;   //反转
        step = -step;
    }
    else//顺时针
    {
        DIR_A = 1;
    }
    if(step != 0)
    {	 
		//移动目标数
		srd.target_count_A = 	step;
		//移动计数
		srd.step_count_A = 0;
		srd.decel_start = srd.target_count_A-287;

		srd.min_delay = 5;

		srd.step_delay = 32;
		
		PULSE_A = 1;
//		state = 0;  //初始化状态标志位，进入加速状态
		TIM3_Int_Init(60-1,1750-1);	//定时器时钟84M，分频系数3500，所以84M/3500=24Khz的计数频率，脉冲频率12KHz
	}

}	


void MSD_Move_B(signed int step)
{

    // 根据步数的正负来判断方向
    if(step < 0)//逆时针
    {
        DIR_B = 0;   //反转
        step = -step;
    }
    else//顺时针
    {
        DIR_B = 1;
    }
    if(step != 0)
    {	 
		//移动目标数
		srd.target_count_B = 	step;
	    //加速或者减速计数器
		srd.accel_count = 0;
		//移动计数
		srd.step_count_B = 0;
		srd.decel_start = srd.target_count_B-287;

		srd.min_delay = 5;

		srd.step_delay = 32;
		
		PULSE_B = 1;
//		state = 0;  //初始化状态标志位，进入加速状态
		TIM2_Int_Init(60-1,1750-1);	//定时器时钟84M，分频系数3500，所以84M/3500=24Khz的计数频率，脉冲频率12KHz
	}
}	 
*/
