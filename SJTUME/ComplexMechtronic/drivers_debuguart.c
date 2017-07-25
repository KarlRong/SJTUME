#include "usart.h"
#include <stdlib.h>
#include <math.h>
#include "utilities_debug.h"
#include "peripheral_define.h"
#include "drivers_debuguart.h"

uint8_t g_pDebugData[1] = {0};

void InitDebugUart()
{
//控制串口DMA接收开启(一次接收1个字节)
	if(HAL_UART_Receive_DMA(&DEBUG_UART, g_pDebugData, 1) != HAL_OK){
			Error_Handler();
	} 
}

void DebugUartRxCpltCallback()
{
	uint8_t *pData = g_pDebugData;
	HAL_UART_Transmit(&DEBUG_UART , pData, 1, 0xFFFF);
	if(HAL_UART_Receive_DMA(&DEBUG_UART, g_pDebugData, 1) != HAL_OK){
			Error_Handler();
	} 
}


