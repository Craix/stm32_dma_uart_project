#include "uartLog.h"

void UART_tx(char * msg )
{
	HAL_UART_Transmit(&hlpuart1, (uint8_t *)msg, strlen(msg), 200);
}
