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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(9600);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ� 
	Steper_Init();
	KEY_Init();
	TIM4_Int_Init(200-1,8400-1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ���ʱ20ms
//	MSD_Move(-300,400,2);     //   +   -   x,����
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{	
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			if(len >= 0 && USART_RX_BUF[0] == '1')   //λ�����Ȳ������س���
			{
				LED1 = !LED1;				
			}
/*			for(t=0;t<len;t++)
			{
				USART_SendData(USART1, USART_RX_BUF[t]);         //�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ�
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

