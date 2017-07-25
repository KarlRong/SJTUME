#include "timer.h"
#include "steper.h"
#include <math.h>
#include "tim.h"
#include "utilities_debug.h"
extern char step_flag ;
extern char run_flag_A ;
extern char run_flag_B ;
extern char run_flag_X ;
extern char run_flag_Y ;

extern char Step_Table[101];
extern speedRampData srd;



//定时器4中断服务函数
void tim4_CallBack(void)
{  
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
//	{
		if(step_flag == 1)   //开始
		{
			if(run_flag_X == 0 && run_flag_Y == 1)   //Y方向移动
			{
				if(srd.target_count_Y < 0)//逆时针
				{
					DIR_A_LOW;   //反转
					DIR_B_LOW;
					srd.target_count_Y = -srd.target_count_Y;
				}
				else//顺时针
				{
					DIR_A_HIGH;
					DIR_B_HIGH;
				}
				srd.target_count = srd.target_count_Y;
				srd.step_count = 0;
			}
			if(run_flag_X == 1 && run_flag_Y == 0)   //X方向移动
			{
				if(srd.target_count_X < 0)//逆时针
				{
					DIR_A_HIGH;   //反转
					DIR_B_LOW;
					srd.target_count_X = -srd.target_count_X;
				}
				else//顺时针
				{
					DIR_A_LOW;
					DIR_B_HIGH;
				}
				srd.target_count = srd.target_count_X;
				srd.step_count = 0;
			}
			PULSE_A_HIGH;
			PULSE_B_HIGH;
			HAL_TIM_Base_Start_IT(&htim3);	
			step_flag++;   //进入运行状态
		}
		if(step_flag == 3)   //运行方向切换
		{
			if(run_flag_X == 1 && run_flag_Y == 0)   //切换至Y方向运动
			{
				if(srd.target_count_Y < 0)//逆时针
				{
					DIR_A_LOW;   //反转
					DIR_B_LOW;
					srd.target_count_Y = -srd.target_count_Y;
				}
				else//顺时针
				{
					DIR_A_HIGH;
					DIR_B_HIGH;
				}
				srd.target_count = srd.target_count_Y;
				srd.step_count = 0;
			}
			if(run_flag_X == 0 && run_flag_Y == 1)   //切换至X方向运动
			{
				if(srd.target_count_X < 0)//逆时针
				{
					DIR_A_HIGH;  
					DIR_B_LOW;
					srd.target_count_X = -srd.target_count_X;
				}
				else//顺时针
				{
					DIR_A_LOW;
					DIR_B_HIGH;
				}
				srd.target_count = srd.target_count_X;
				srd.step_count = 0;
			}
			PULSE_A_HIGH;
			PULSE_B_HIGH;
			HAL_TIM_Base_Start_IT(&htim3);	
			step_flag++;   //进入运行状态			
		}
		
		if(step_flag == 5)   
		{
			if(srd.target_count_Z < 0)//逆时针
				{
					DIR_C_LOW;   //反转
					DIR_C_LOW;
					srd.target_count_Z = -srd.target_count_Z;
				}
				else//顺时针
				{
					DIR_C_HIGH;
					DIR_C_HIGH;
				}
				srd.target_count = srd.target_count_Z;
				srd.step_count = 0;
			  step_flag++; 
				HAL_TIM_Base_Start_IT(&htim3);	
		}
		if(step_flag == 7)  
		{
	    step_flag = 0;
			HAL_TIM_Base_Stop_IT(&htim10);
		  
		}			
		
}

//定时器3中断服务函数
void tim3_CallBack(void)
{
	
  // 保存延时周期
  static unsigned int new_step_delay = 50;
  // 记录new_step_delay中的余数，提高下一步计算的精度
  static signed int rest = 0;
  // 记录加速最后一次 参数
  static signed int last_delay = 0;
	if(__HAL_TIM_GET_IT_SOURCE(&htim3,TIM_IT_UPDATE) == SET) //溢出中断
	{
		PULSE_A_TOGGLE;
		PULSE_B_TOGGLE;
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
					step_flag++;
					HAL_TIM_Base_Stop_IT(&htim3);;
			}
			__HAL_TIM_SET_AUTORELOAD(&htim3,new_step_delay-1);//修改重装值
			srd.step_count++;
		}
	}
	__HAL_TIM_CLEAR_IT(&htim3,TIM_IT_UPDATE);  //清除中断标志位
}
//定时器3中断服务函数10
void tim10_CallBack(void)
{
	
  // 保存延时周期
  static unsigned int new_step_delay = 50;
  // 记录new_step_delay中的余数，提高下一步计算的精度
  static signed int rest = 0;
  // 记录加速最后一次 参数
  static signed int last_delay = 0;
	if(__HAL_TIM_GET_IT_SOURCE(&htim10,TIM_IT_UPDATE) == SET) //溢出中断
	{
		PULSE_C_TOGGLE;
		
		if(PULSE_C == 0); //如果是半周期，则不做处理，退出中断
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
					step_flag++;
					HAL_TIM_Base_Stop_IT(&htim10);;
			}
			__HAL_TIM_SET_AUTORELOAD(&htim10,new_step_delay-1);//修改重装值
			srd.step_count++;
		}
	}
	__HAL_TIM_CLEAR_IT(&htim10,TIM_IT_UPDATE);  //清除中断标志位
}

