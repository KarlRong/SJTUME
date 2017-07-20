#ifndef _STEPER_H
#define _STEPER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/6/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


#define T1_FREQ 10000     //��ʱ��Ƶ��
#define FSPR    400         //���������Ȧ����
#define SPR     (FSPR*25)  //25ϸ�ֵĲ��� 10000��һȦ
// ��ѧ������ ����MSD_Move�����ļ򻯼���
#define ALPHA (2*3.14159/SPR)                    // 2*pi/spr
#define A_T_x100 ((long)(ALPHA*T1_FREQ*100))     // (ALPHA / T1_FREQ)*100


#define T1_FREQ_148 ((int)((T1_FREQ*0.676)/25)) // divided by 100 and scaled by 0.676
#define A_SQ (long)(ALPHA*2*10000000000)         // 
#define A_x20000 (int)(ALPHA*20000)              // ALPHA*20000


//�ٶ�����״̬
#define STOP  0
#define ACCEL 1
#define DECEL 2
#define RUN   3

typedef struct {
  //�������״̬
  unsigned char run_state : 3;
  //������з���
  unsigned char dir : 1;
  //��һ��������ʱ���ڣ�����ʱΪ���ٶ�����
  unsigned int step_delay;
  //��ʼ���ٵ�λ��
  unsigned int decel_start;
  //���پ���
  signed int decel_val;
  //��С��ʱ��������ٶȣ�
  signed int min_delay;
  //���ٻ��߼��ټ�����
  signed int accel_count;
  //�ƶ�����
  long step_count_X;
	long step_count_Y;
	long step_count;
  //�ƶ�Ŀ����
  signed int target_count_X;
	signed int target_count_Y;
	signed int target_count;
} speedRampData;



#define DIR_A PAout(1)	// ����λ
#define EN_A PAout(3)		// �ѻ�λ
#define PULSE_A PAout(6)	// ����λ

#define DIR_B PAout(4)	// ����λ
#define EN_B PAout(2)		// �ѻ�λ
#define PULSE_B PAout(5)	// ����λ


void Steper_Init(void);
void MSD_Move_B(signed int step);
void MSD_Move_A(signed int step);
void MSD_Move(signed int step_X,signed int step_Y, char flag);

#endif
