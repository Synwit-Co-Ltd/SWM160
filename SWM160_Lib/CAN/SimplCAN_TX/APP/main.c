#include "SWM160.h"

void SerialInit(void);

int main(void)
{
	uint32_t i;
	uint8_t tx_data[8] = {1, 2, 3, 4, 5, 6, 7, 8};
	CAN_InitStructure CAN_initStruct;
	
	SystemInit();
	
	SerialInit();
	
   	PORT_Init(PORTB, PIN0, PORTB_PIN0_CAN_RX, 1);	//GPIOB.0配置为CAN输入引脚
	PORT_Init(PORTB, PIN1, PORTB_PIN1_CAN_TX, 0);	//GPIOB.1配置为CAN输出引脚
	
	CAN_initStruct.Mode = CAN_MODE_NORMAL;
	CAN_initStruct.CAN_BS1 = CAN_BS1_5tq;
	CAN_initStruct.CAN_BS2 = CAN_BS2_4tq;
	CAN_initStruct.CAN_SJW = CAN_SJW_2tq;
	CAN_initStruct.Baudrate = 100000;
	CAN_initStruct.FilterMode = CAN_FILTER_32b;
   	CAN_initStruct.FilterMask32b = 0xFFFFFFFF;
	CAN_initStruct.FilterCheck32b = 0xFFFFFFFF;
	CAN_initStruct.RXNotEmptyIEn = 0;
	CAN_initStruct.RXOverflowIEn = 0;
	CAN_initStruct.ArbitrLostIEn = 0;
	CAN_initStruct.ErrPassiveIEn = 0;
	CAN_Init(CAN, &CAN_initStruct);
	
	CAN_Open(CAN);
	
	while(1==1)
	{
		CAN_Transmit(CAN, CAN_FRAME_STD, 0x3FF, tx_data, 8, 0);
		
		for(i = 0; CAN_TXComplete(CAN) == 0; i++)
		{
			if(i == 1000) CAN_AbortTransmit(CAN);	//超时，终止发送
		}
		
		if(CAN_TXSuccess(CAN) == 1)
		{
			printf("Transmit Success!\r\n");
		}
		else
		{
			printf("Transmit Failure!\r\n");
		}
		
		for(i = 0; i < 1000000; i++);
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
