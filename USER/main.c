#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "steper.h"
#include "timer.h"


int main(void)
{ 
 
	u8 t;
	u8 len;	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(9600);	//串口初始化波特率为115200
	LED_Init();		  		//初始化与LED连接的硬件接口 
	Steper_Init();
	KEY_Init();
	TIM4_Int_Init(200-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，定时20ms
//	MSD_Move(-300,400,2);     //   +   -   x,正向
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{	
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			if(len >= 0 && USART_RX_BUF[0] == '1')   //位数长度不包含回车键
			{
				LED1 = !LED1;				
			}
/*			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         //向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结
			}
*/
			USART_RX_STA=0;
		}
		if(KEY_Scan(0)==1)
		{
			USART_SendData(USART1, 'A');
			LED0 = !LED0;			
		}
		
	}
}

