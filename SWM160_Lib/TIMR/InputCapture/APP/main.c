#include "SWM160.h"

void SerialInit(void);
void TestSignal(void);

int main(void)
{	
	SystemInit();
	
	SerialInit();
	
	TestSignal();	//产生测试信号供Input Capture功能测量
	
	PORT_Init(PORTA, PIN4, PORTA_PIN4_TIMR2_IN, 1);
	
	TIMR_Init(TIMR2, TIMR_MODE_TIMER, 0xFFFFFF, 0);
	
	TIMR_IC_Init(TIMR2, 0, 1, 1, 1);
	
	TIMR_IC_Start(TIMR2);
	
	while(1==1)
	{
	}
}

void TestSignal(void)
{
	PWM_InitStructure  PWM_initStruct;
	
	PORT_Init(PORTC, PIN6,  PORTC_PIN6_PWM1A,  0);
	PORT_Init(PORTB, PIN13, PORTB_PIN13_PWM1B, 0);
	
	PWM_initStruct.clk_div = PWM_CLKDIV_128;	//F_PWM = 24M/4 = 187.5KHz
	
	PWM_initStruct.mode = PWM_MODE_INDEP;		//A路和B路独立输出					
	PWM_initStruct.cycleA = 10000;				//187.5K/10000 = 18.75Hz			
	PWM_initStruct.hdutyA =  2500;				//2500/10000 = 25%
	PWM_initStruct.initLevelA = 0;
	PWM_initStruct.cycleB = 10000;
	PWM_initStruct.hdutyB =  5000;				//5000/10000 = 50%
	PWM_initStruct.initLevelB = 1;
	PWM_initStruct.HEndAIEn = 0;
	PWM_initStruct.NCycleAIEn = 0;
	PWM_initStruct.HEndBIEn = 0;
	PWM_initStruct.NCycleBIEn = 0;
	
	PWM_Init(PWM1, &PWM_initStruct);
	PWM_Start(PWM1, 1, 1);
}

void TIMR2_Handler(void)
{
	if(TIMR_IC_CaptureOV_INTStat(TIMR2))
	{
		TIMR_IC_CaptureOV_INTClr(TIMR2);
		
		printf("Overflow\r\n");
	}
	else if(TIMR_IC_CaptureH_INTStat(TIMR2))
	{
		TIMR_IC_CaptureH_INTClr(TIMR2);
		
		printf("H: %d\r\n", TIMR_IC_GetCaptureH(TIMR2));
	}
	else if(TIMR_IC_CaptureL_INTStat(TIMR2))
	{
		TIMR_IC_CaptureL_INTClr(TIMR2);
		
		printf("L: %d\r\n", TIMR_IC_GetCaptureL(TIMR2));
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
