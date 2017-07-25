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



//��ʱ��4�жϷ�����
void tim4_CallBack(void)
{  
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
//	{
		if(step_flag == 1)   //��ʼ
		{
			if(run_flag_X == 0 && run_flag_Y == 1)   //Y�����ƶ�
			{
				if(srd.target_count_Y < 0)//��ʱ��
				{
					DIR_A_LOW;   //��ת
					DIR_B_LOW;
					srd.target_count_Y = -srd.target_count_Y;
				}
				else//˳ʱ��
				{
					DIR_A_HIGH;
					DIR_B_HIGH;
				}
				srd.target_count = srd.target_count_Y;
				srd.step_count = 0;
			}
			if(run_flag_X == 1 && run_flag_Y == 0)   //X�����ƶ�
			{
				if(srd.target_count_X < 0)//��ʱ��
				{
					DIR_A_HIGH;   //��ת
					DIR_B_LOW;
					srd.target_count_X = -srd.target_count_X;
				}
				else//˳ʱ��
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
			step_flag++;   //��������״̬
		}
		if(step_flag == 3)   //���з����л�
		{
			if(run_flag_X == 1 && run_flag_Y == 0)   //�л���Y�����˶�
			{
				if(srd.target_count_Y < 0)//��ʱ��
				{
					DIR_A_LOW;   //��ת
					DIR_B_LOW;
					srd.target_count_Y = -srd.target_count_Y;
				}
				else//˳ʱ��
				{
					DIR_A_HIGH;
					DIR_B_HIGH;
				}
				srd.target_count = srd.target_count_Y;
				srd.step_count = 0;
			}
			if(run_flag_X == 0 && run_flag_Y == 1)   //�л���X�����˶�
			{
				if(srd.target_count_X < 0)//��ʱ��
				{
					DIR_A_HIGH;  
					DIR_B_LOW;
					srd.target_count_X = -srd.target_count_X;
				}
				else//˳ʱ��
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
			step_flag++;   //��������״̬			
		}
		
		if(step_flag == 5)   
		{
			if(srd.target_count_Z < 0)//��ʱ��
				{
					DIR_C_LOW;   //��ת
					DIR_C_LOW;
					srd.target_count_Z = -srd.target_count_Z;
				}
				else//˳ʱ��
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

//��ʱ��3�жϷ�����
void tim3_CallBack(void)
{
	
  // ������ʱ����
  static unsigned int new_step_delay = 50;
  // ��¼new_step_delay�е������������һ������ľ���
  static signed int rest = 0;
  // ��¼�������һ�� ����
  static signed int last_delay = 0;
	if(__HAL_TIM_GET_IT_SOURCE(&htim3,TIM_IT_UPDATE) == SET) //����ж�
	{
		PULSE_A_TOGGLE;
		PULSE_B_TOGGLE;
		if(PULSE_A == 0); //����ǰ����ڣ����������˳��ж�
		else			 //һ�����ڽ��� 
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
			__HAL_TIM_SET_AUTORELOAD(&htim3,new_step_delay-1);//�޸���װֵ
			srd.step_count++;
		}
	}
	__HAL_TIM_CLEAR_IT(&htim3,TIM_IT_UPDATE);  //����жϱ�־λ
}
//��ʱ��3�жϷ�����10
void tim10_CallBack(void)
{
	
  // ������ʱ����
  static unsigned int new_step_delay = 50;
  // ��¼new_step_delay�е������������һ������ľ���
  static signed int rest = 0;
  // ��¼�������һ�� ����
  static signed int last_delay = 0;
	if(__HAL_TIM_GET_IT_SOURCE(&htim10,TIM_IT_UPDATE) == SET) //����ж�
	{
		PULSE_C_TOGGLE;
		
		if(PULSE_C == 0); //����ǰ����ڣ����������˳��ж�
		else			 //һ�����ڽ��� 
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
			__HAL_TIM_SET_AUTORELOAD(&htim10,new_step_delay-1);//�޸���װֵ
			srd.step_count++;
		}
	}
	__HAL_TIM_CLEAR_IT(&htim10,TIM_IT_UPDATE);  //����жϱ�־λ
}

