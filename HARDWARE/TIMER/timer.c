#include "timer.h"
#include "led.h"
#include "steper.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/4
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
extern char step_flag ;
extern char run_flag_A ;
extern char run_flag_B ;
extern char run_flag_X ;
extern char run_flag_Y ;

extern char Step_Table[101];
extern speedRampData srd;

//ͨ�ö�ʱ��4�жϳ�ʼ��--�������
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��4!
void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
		
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x04; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��3
	
}

//ͨ�ö�ʱ��3�жϳ�ʼ��--���A
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
		
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
}

//ͨ�ö�ʱ��2�жϳ�ʼ��--���B
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��2!
void TIM2_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///ʹ��TIM2ʱ��
	
  	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//��ʼ��TIM2
	

	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

 //  	TIM_ARRPreloadConfig(TIM2, DISABLE); //��ֹARRԤװ�ػ�����

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //����ʱ��2�����ж�
	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ��2
	
}


//��ʱ��4�жϷ�����
void TIM4_IRQHandler(void)
{  
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
	{
		if(step_flag == 1)   //��ʼ
		{
			if(run_flag_X == 0 && run_flag_Y == 1)   //Y�����ƶ�
			{
				if(srd.target_count_Y < 0)//��ʱ��
				{
					DIR_A = 0;   //��ת
					DIR_B = 0;
					srd.target_count_Y = -srd.target_count_Y;
				}
				else//˳ʱ��
				{
					DIR_A = 1;
					DIR_B = 1;
				}
				srd.target_count = srd.target_count_Y;
				srd.step_count = 0;
			}
			if(run_flag_X == 1 && run_flag_Y == 0)   //X�����ƶ�
			{
				if(srd.target_count_X < 0)//��ʱ��
				{
					DIR_A = 1;   //��ת
					DIR_B = 0;
					srd.target_count_X = -srd.target_count_X;
				}
				else//˳ʱ��
				{
					DIR_A = 0;
					DIR_B = 1;
				}
				srd.target_count = srd.target_count_X;
				srd.step_count = 0;
			}
			PULSE_A = 1;
			PULSE_B = 1;
			TIM3_Int_Init(60-1,1750-1);	//��ʱ��ʱ��84M����Ƶϵ��3500������84M/3500=24Khz�ļ���Ƶ�ʣ�����Ƶ��12KHz		
			step_flag++;   //��������״̬
		}
		if(step_flag == 3)   //���з����л�
		{
			if(run_flag_X == 1 && run_flag_Y == 0)   //�л���Y�����˶�
			{
				if(srd.target_count_Y < 0)//��ʱ��
				{
					DIR_A = 0;   //��ת
					DIR_B = 0;
					srd.target_count_Y = -srd.target_count_Y;
				}
				else//˳ʱ��
				{
					DIR_A = 1;
					DIR_B = 1;
				}
				srd.target_count = srd.target_count_Y;
				srd.step_count = 0;
			}
			if(run_flag_X == 0 && run_flag_Y == 1)   //�л���X�����˶�
			{
				if(srd.target_count_X < 0)//��ʱ��
				{
					DIR_A = 1;  
					DIR_B = 0;
					srd.target_count_X = -srd.target_count_X;
				}
				else//˳ʱ��
				{
					DIR_A = 0;
					DIR_B = 1;
				}
				srd.target_count = srd.target_count_X;
				srd.step_count = 0;
			}
			PULSE_A = 1;
			PULSE_B = 1;
			TIM3_Int_Init(60-1,1750-1);	//��ʱ��ʱ��84M����Ƶϵ��3500������84M/3500=24Khz�ļ���Ƶ�ʣ�����Ƶ��12KHz
			step_flag++;   //��������״̬			
		}
		if(step_flag == 5)   //��������
		{
			step_flag = 0;
			TIM_Cmd(TIM3,DISABLE);
		}
	}
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	
  // ������ʱ����
  static unsigned int new_step_delay = 50;
  // ��¼new_step_delay�е������������һ������ľ���
  static signed int rest = 0;
  // ��¼�������һ�� ����
  static signed int last_delay = 0;
  
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		PULSE_A = !PULSE_A;
		PULSE_B = !PULSE_B;
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
					LED1 = !LED1;
					step_flag++;
					TIM_Cmd(TIM3,DISABLE);
			}
			TIM_SetAutoreload(TIM3,new_step_delay-1);//�޸���װֵ
			srd.step_count++;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}


/*
//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	
  // ������ʱ����
  static unsigned int new_step_delay_A = 50;
  // ��¼new_step_delay�е������������һ������ľ���
  static signed int rest = 0;
  // ��¼�������һ�� ����
  static signed int last_delay = 0;
  
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		PULSE_A = !PULSE_A;
		if(PULSE_A == 0); //����ǰ����ڣ����������˳��ж�
		else			 //һ�����ڽ��� 
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
			TIM_SetAutoreload(TIM3,new_step_delay_A-1);//�޸���װֵ
			srd.step_count_A++;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}

//��ʱ��2�жϷ�����
void TIM2_IRQHandler(void)
{
	
  // ������ʱ����
  static unsigned int new_step_delay_B = 50;
  // ��¼new_step_delay�е������������һ������ľ���
  static signed int rest = 0;
  // ��¼�������һ�� ����
  static signed int last_delay = 0;
  
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET) //����ж�
	{
		PULSE_B = !PULSE_B;
		if(PULSE_B == 0); //����ǰ����ڣ����������˳��ж�
		else			 //һ�����ڽ��� 
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
			TIM_SetAutoreload(TIM2,new_step_delay_B-1);//�޸���װֵ
			srd.step_count_B++;
		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //����жϱ�־λ
}
*/