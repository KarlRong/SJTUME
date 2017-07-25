#include <usart.h>
#include "drivers_uart.h"
#include "peripheral_define.h"
#include "utilities_debug.h"
#include "drivers_debuguart.h"

/********************所有串口接收中断****************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
//	fw_printfln("uart received");
	if(UartHandle == &DEBUG_UART){
		//调试串口UART1
		DebugUartRxCpltCallback();
	}
}   
