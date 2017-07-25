#include "stepmotor_timer.h"
#include "main.h"
#include "tim.h"
#include "timer.h"

extern int timer_count;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim4)
	{
		timer_count++;
		tim4_CallBack();
	}
	else if(htim == &htim3)
	{
		tim3_CallBack();
	}
	else if(htim == &htim10)
	{
		tim10_CallBack();
	}
}
