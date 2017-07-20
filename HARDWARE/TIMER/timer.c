#include "timer.h"
#include "led.h"
#include "steper.h"
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
extern char step_flag ;
extern char run_flag_A ;
extern char run_flag_B ;
extern char run_flag_X ;
extern char run_flag_Y ;

extern char Step_Table[101];
extern speedRampData srd;

//通用定时器4中断初始化--电机管理
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器4!
void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化TIM3
		
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x04; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM4,ENABLE); //使能定时器3
	
}

//通用定时器3中断初始化--电机A
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3
		
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
}

//通用定时器2中断初始化--电机B
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器2!
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///使能TIM2时钟
	
  	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM2
	

	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

 //  	TIM_ARRPreloadConfig(TIM2, DISABLE); //禁止ARR预装载缓冲器

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许定时器2更新中断
	TIM_Cmd(TIM2,ENABLE); //使能定时器2
	
}


//定时器4中断服务函数
void TIM4_IRQHandler(void)
{  
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
	{
		if(step_flag == 1)   //开始
		{
			if(run_flag_X == 0 && run_flag_Y == 1)   //Y方向移动
			{
				if(srd.target_count_Y < 0)//逆时针
				{
					DIR_A = 0;   //反转
					DIR_B = 0;
					srd.target_count_Y = -srd.target_count_Y;
				}
				else//顺时针
				{
					DIR_A = 1;
					DIR_B = 1;
				}
				srd.target_count = srd.target_count_Y;
				srd.step_count = 0;
			}
			if(run_flag_X == 1 && run_flag_Y == 0)   //X方向移动
			{
				if(srd.target_count_X < 0)//逆时针
				{
					DIR_A = 1;   //反转
					DIR_B = 0;
					srd.target_count_X = -srd.target_count_X;
				}
				else//顺时针
				{
					DIR_A = 0;
					DIR_B = 1;
				}
				srd.target_count = srd.target_count_X;
				srd.step_count = 0;
			}
			PULSE_A = 1;
			PULSE_B = 1;
			TIM3_Int_Init(60-1,1750-1);	//定时器时钟84M，分频系数3500，所以84M/3500=24Khz的计数频率，脉冲频率12KHz		
			step_flag++;   //进入运行状态
		}
		if(step_flag == 3)   //运行方向切换
		{
			if(run_flag_X == 1 && run_flag_Y == 0)   //切换至Y方向运动
			{
				if(srd.target_count_Y < 0)//逆时针
				{
					DIR_A = 0;   //反转
					DIR_B = 0;
					srd.target_count_Y = -srd.target_count_Y;
				}
				else//顺时针
				{
					DIR_A = 1;
					DIR_B = 1;
				}
				srd.target_count = srd.target_count_Y;
				srd.step_count = 0;
			}
			if(run_flag_X == 0 && run_flag_Y == 1)   //切换至X方向运动
			{
				if(srd.target_count_X < 0)//逆时针
				{
					DIR_A = 1;  
					DIR_B = 0;
					srd.target_count_X = -srd.target_count_X;
				}
				else//顺时针
				{
					DIR_A = 0;
					DIR_B = 1;
				}
				srd.target_count = srd.target_count_X;
				srd.step_count = 0;
			}
			PULSE_A = 1;
			PULSE_B = 1;
			TIM3_Int_Init(60-1,1750-1);	//定时器时钟84M，分频系数3500，所以84M/3500=24Khz的计数频率，脉冲频率12KHz
			step_flag++;   //进入运行状态			
		}
		if(step_flag == 5)   //结束运行
		{
			step_flag = 0;
			TIM_Cmd(TIM3,DISABLE);
		}
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	
  // 保存延时周期
  static unsigned int new_step_delay = 50;
  // 记录new_step_delay中的余数，提高下一步计算的精度
  static signed int rest = 0;
  // 记录加速最后一次 参数
  static signed int last_delay = 0;
  
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		PULSE_A = !PULSE_A;
		PULSE_B = !PULSE_B;
		if(PULSE_A == 0); //如果是半周期，则不做处理，退出中断
		else			 //一个周期结束 
		{
			if(srd.step_count<51)
			{
				new_step_delay = Step_Table[srd.step_count];
			}
			else if(srd.step_count>=51&&srd.step_count<srd.target_count-51 )
			{
					new_step_delay = 10;
			}
			else if(srd.step_count>=srd.target_count-51 && srd.step_count<=srd.target_count-1)
			{
					new_step_delay =  Step_Table[srd.target_count-1-srd.step_count];
			}
			else
			{
					LED1 = !LED1;
					step_flag++;
					TIM_Cmd(TIM3,DISABLE);
			}
			TIM_SetAutoreload(TIM3,new_step_delay-1);//修改重装值
			srd.step_count++;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}


/*
//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	
  // 保存延时周期
  static unsigned int new_step_delay_A = 50;
  // 记录new_step_delay中的余数，提高下一步计算的精度
  static signed int rest = 0;
  // 记录加速最后一次 参数
  static signed int last_delay = 0;
  
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		PULSE_A = !PULSE_A;
		if(PULSE_A == 0); //如果是半周期，则不做处理，退出中断
		else			 //一个周期结束 
		{
			if(srd.step_count_A<51)
			{
				new_step_delay_A = Step_Table[srd.step_count_A];
			}
			else if(srd.step_count_A>=51&&srd.step_count_A<srd.target_count_A-51 )
			{
					new_step_delay_A = 10;
			}
			else if(srd.step_count_A>=srd.target_count_A-51 && srd.step_count_A<=1599)
			{
					new_step_delay_A =  Step_Table[srd.target_count_A-1-srd.step_count_A];
			}
			else
			{
						LED1 = !LED1;
						TIM_Cmd(TIM3,DISABLE);
			}
			TIM_SetAutoreload(TIM3,new_step_delay_A-1);//修改重装值
			srd.step_count_A++;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}

//定时器2中断服务函数
void TIM2_IRQHandler(void)
{
	
  // 保存延时周期
  static unsigned int new_step_delay_B = 50;
  // 记录new_step_delay中的余数，提高下一步计算的精度
  static signed int rest = 0;
  // 记录加速最后一次 参数
  static signed int last_delay = 0;
  
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //溢出中断
	{
		PULSE_B = !PULSE_B;
		if(PULSE_B == 0); //如果是半周期，则不做处理，退出中断
		else			 //一个周期结束 
		{
			if(srd.step_count_B<51)
			{
				new_step_delay_B = Step_Table[srd.step_count_B];
			}
			else if(srd.step_count_B>=51&&srd.step_count_B<srd.target_count_B-51 )
			{
					new_step_delay_B = 10;
			}
			else if(srd.step_count_B>=srd.target_count_B-51 && srd.step_count_B<=1599)
			{
					new_step_delay_B =  Step_Table[srd.target_count_B-1-srd.step_count_B];
			}
			else
			{
						LED0 = !LED0;
						run_flag_B = 0;
						TIM_Cmd(TIM2,DISABLE);
			}
			TIM_SetAutoreload(TIM2,new_step_delay_B-1);//修改重装值
			srd.step_count_B++;
		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //清除中断标志位
}
*/