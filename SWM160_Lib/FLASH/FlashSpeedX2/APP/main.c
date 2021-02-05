#include "SWM160.h"


void SerialInit(void);

/* 注意：此程序只能在单片机速度小于25MHz时执行
*/
int main(void)
{
	uint32_t cnt1, cnt2;
	volatile uint32_t x = 123456789 ;
	volatile uint32_t y = 765;
	volatile uint32_t z;
	
	SystemInit();
	
	SerialInit();
	
	SysTick_Config(1000000);
	z = x / y;
	cnt1 = 1000000 - SysTick->VAL;
	SysTick->CTRL = 0;
	printf("Before Flash Speed X2: %d clock\r\n", cnt1);
	
	FlashSpeedX2();
	
	SysTick_Config(1000000);
	z = x / y;
	cnt2 = 1000000 - SysTick->VAL;
	SysTick->CTRL = 0;
	printf("After Flash Speed X2: %d clock\r\n", cnt2);
	
	printf("program execute speed promote %d%%\r\n", (cnt1 - cnt2) * 100 / cnt2);
	
	while(1==1)
	{
	}
}


void SerialInit(void)
{
	UART_InitStructure UART_initStruct;
	
	PORT_Init(PORTB, PIN11, PORTB_PIN11_UART0_RX, 1);	//GPIOB.11配置为UART0输入引脚
	PORT_Init(PORTB, PIN12, PORTB_PIN12_UART0_TX, 0);	//GPIOB.12配置为UART0输出引脚
 	
	UART_initStruct.Baudrate = 57600;
	UART_initStruct.DataBits = UART_DATABIT_8;
	UART_initStruct.Parity = UART_PARITY_NONE;
	UART_initStruct.StopBits = UART_STOPBIT_1;
	UART_initStruct.RXThresholdIEn = 0;
	UART_initStruct.TXThresholdIEn = 0;
	UART_initStruct.TimeoutIEn = 0;
 	UART_Init(UART0, &UART_initStruct);
	UART_Open(UART0);
}

/****************************************************************************************************************************************** 
* 函数名称: fputc()
* 功能说明: printf()使用此函数完成实际的串口打印动作
* 输    入: int ch		要打印的字符
*			FILE *f		文件句柄
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
int fputc(int ch, FILE *f)
{
	UART_WriteByte(UART0, ch);
	
	while(UART_IsTXBusy(UART0));
 	
	return ch;
}
