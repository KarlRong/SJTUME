#include "steper.h"
#include "timer.h"
#include <math.h>

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


void MSD_Z_Move(signed int step_Z)   //  flag == 1:��Y��X    flag == 2:��X��Y
{
	step_flag = 1;  //START 1  RUN 2  TURN 3  RUN 4  OVER 5
	
	srd.target_count_Z = step_Z;
	srd.target_count=0;
	srd.step_count=0;
	
}

