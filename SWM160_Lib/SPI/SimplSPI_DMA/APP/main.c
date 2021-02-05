#include "SWM160.h"

uint32_t SPI_TXBuff[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
};

uint32_t SPI_RXBuff[sizeof(SPI_TXBuff)/sizeof(SPI_TXBuff[0])] = {0};
volatile uint32_t SPI_RXComplete = 0;

#define SPI_DATA_BITS	8
#define SPI_DATA_MASK	((1 << SPI_DATA_BITS) - 1)


void SerialInit(void);

int main(void)
{	
	uint32_t i;
	SPI_InitStructure SPI_initStruct;
	
	SystemInit();
	
	SerialInit();	
	
	PORT_Init(PORTB, PIN13, PORTB_PIN13_SPI0_SSEL, 0);
	PORT_Init(PORTC, PIN1,  PORTC_PIN1_SPI0_MISO,  1);	// MOSI 与 MISO 连一起
	PORT_Init(PORTC, PIN2,  PORTC_PIN2_SPI0_MOSI,  0);
	PORT_Init(PORTC, PIN0,  PORTC_PIN0_SPI0_SCLK,  0);
	
	SPI_initStruct.clkDiv = SPI_CLKDIV_16;
	SPI_initStruct.FrameFormat = SPI_FORMAT_SPI;
	SPI_initStruct.SampleEdge = SPI_SECOND_EDGE;
	SPI_initStruct.IdleLevel = SPI_HIGH_LEVEL;
	SPI_initStruct.FrameSize = SPI_DATA_BITS;
	SPI_initStruct.Master = 1;
	SPI_initStruct.RXFullIEn = 0;
	SPI_initStruct.RXHFullIEn = 0;
	SPI_initStruct.TXEmptyIEn = 0;
	SPI_initStruct.TXHFullIEn = 0;
	SPI_Init(SPI0, &SPI_initStruct);
	
	DMA_CH_Config(DMA_CHW_SPI, (uint32_t)SPI_TXBuff, sizeof(SPI_TXBuff)/sizeof(SPI_TXBuff[0]), 1);
	DMA_CH_Config(DMA_CHR_SPI, (uint32_t)SPI_RXBuff, sizeof(SPI_RXBuff)/sizeof(SPI_RXBuff[0]), 1);
	
	DMA_CH_Open(DMA_CHR_SPI);
	DMA_CH_Open(DMA_CHW_SPI);
	
	SPI_Open(SPI0);
	
	while(1==1)
	{
		if(SPI_RXComplete)
		{
			SPI_RXComplete = 0;
			
			for(i = 0; i < sizeof(SPI_RXBuff)/sizeof(SPI_RXBuff[0]); i++)
				printf("%04X, ", SPI_RXBuff[i] & SPI_DATA_MASK);
			printf("\r\n\r\n");
			
			for(i = 0; i < sizeof(SPI_RXBuff)/sizeof(SPI_RXBuff[0]); i++) SPI_RXBuff[i] = 0;
			for(i = 0; i < 6000000; i++) __NOP();
			
			DMA_CH_Open(DMA_CHR_SPI);
			DMA_CH_Open(DMA_CHW_SPI);		//在传输完成后通道开启会自动清零，通道开启再此发送
		}
	}
}

void DMA_Handler(void)
{	
	if(DMA_CH_INTStat(DMA_CHW_SPI))
	{		
		DMA_CH_INTClr(DMA_CHW_SPI);		//清除中断标志
		
		printf("SPI Send Complete\n");
	}
	
	if(DMA_CH_INTStat(DMA_CHR_SPI))
	{		
		DMA_CH_INTClr(DMA_CHR_SPI);		//清除中断标志
		
		printf("SPI Recv Complete\n");
		
		SPI_RXComplete = 1;
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
