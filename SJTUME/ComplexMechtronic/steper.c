#include "steper.h"
#include "timer.h"
#include <math.h>

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


void MSD_Z_Move(signed int step_Z)   //  flag == 1:先Y后X    flag == 2:先X后Y
{
	step_flag = 1;  //START 1  RUN 2  TURN 3  RUN 4  OVER 5
	
	srd.target_count_Z = step_Z;
	srd.target_count=0;
	srd.step_count=0;
	
}

