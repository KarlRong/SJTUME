#include "steper.h"
#include "led.h"
#include "timer.h"
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



//ϵͳ�Ӽ��ٲ���
speedRampData srd;
//��¼���������λ��
int stepPosition = 0;
char step_flag = 0;
char run_flag_A = 0;
char run_flag_B = 0;
char run_flag_X = 0;
char run_flag_Y = 0;

//���������ʼ��
void Steper_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOFʱ��

	//A�ŵ����ʼ��  GPIOA6(pul),A1(dir)��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	//B�ŵ����ʼ��  GPIOA5(pul),A4(dir)��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_6);//
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_5 | GPIO_Pin_4);//
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);

}

/*! \brief �Ը����Ĳ����ƶ��������
 *  ͨ��������ٵ�����ٶȣ��Ը����Ĳ�����ʼ����
 *  ������ٶȺͼ��ٶȺ�С������������ƶ���������û�ﵽ����ٶȾ�Ҫ��ʼ����
 *  \param step   �ƶ��Ĳ��� (����Ϊ˳ʱ�룬����Ϊ��ʱ��).
 *  \param accel  ���ٶ�,���ȡֵΪ100��ʵ��ֵΪ100*0.01*rad/sec^2=1rad/sec^2
 *  \param decel  ���ٶ�,���ȡֵΪ100��ʵ��ֵΪ100*0.01*rad/sec^2=1rad/sec^2
 *  \param speed  ����ٶ�,���ȡֵΪ100��ʵ��ֵΪ100*0.01*rad/sec=1rad/sec
 */

void MSD_Move(signed int step_X,signed int step_Y, char flag)   //  flag == 1:��Y��X    flag == 2:��X��Y
{
	step_flag = 1;  //START 1  RUN 2  TURN 3  RUN 4  OVER 5
	srd.target_count_X = step_X;
	srd.target_count_Y = step_Y;
	srd.target_count=0;
	srd.step_count=0;
	switch (flag)
	{
		case 1:       //����Y���ƶ�������X���ƶ�
			run_flag_X = 0;
			run_flag_Y = 1;
			break;
		case 2:       //����X���ƶ�������Y���ƶ�
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
    // ���ݲ������������жϷ���
    if(step < 0)//��ʱ��
    {
        DIR_A = 0;   //��ת
        step = -step;
    }
    else//˳ʱ��
    {
        DIR_A = 1;
    }
    if(step != 0)
    {	 
		//�ƶ�Ŀ����
		srd.target_count_A = 	step;
		//�ƶ�����
		srd.step_count_A = 0;
		srd.decel_start = srd.target_count_A-287;

		srd.min_delay = 5;

		srd.step_delay = 32;
		
		PULSE_A = 1;
//		state = 0;  //��ʼ��״̬��־λ���������״̬
		TIM3_Int_Init(60-1,1750-1);	//��ʱ��ʱ��84M����Ƶϵ��3500������84M/3500=24Khz�ļ���Ƶ�ʣ�����Ƶ��12KHz
	}

}	


void MSD_Move_B(signed int step)
{

    // ���ݲ������������жϷ���
    if(step < 0)//��ʱ��
    {
        DIR_B = 0;   //��ת
        step = -step;
    }
    else//˳ʱ��
    {
        DIR_B = 1;
    }
    if(step != 0)
    {	 
		//�ƶ�Ŀ����
		srd.target_count_B = 	step;
	    //���ٻ��߼��ټ�����
		srd.accel_count = 0;
		//�ƶ�����
		srd.step_count_B = 0;
		srd.decel_start = srd.target_count_B-287;

		srd.min_delay = 5;

		srd.step_delay = 32;
		
		PULSE_B = 1;
//		state = 0;  //��ʼ��״̬��־λ���������״̬
		TIM2_Int_Init(60-1,1750-1);	//��ʱ��ʱ��84M����Ƶϵ��3500������84M/3500=24Khz�ļ���Ƶ�ʣ�����Ƶ��12KHz
	}
}	 
*/
