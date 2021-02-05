#include "SWM160.h"


int main(void)
{	
	SystemInit();
	
	GPIO_Init(GPIOA, PIN5, 1, 0, 0, 0);			//输出，接LED
	
	TIMR_Init(TIMR0, TIMR_MODE_TIMER, SystemCoreClock/4, 1);	//每0.25秒钟触发一次中断；注意：周期寄存器是24位的，最大计数个数约16_000_000
	
	TIMR_Start(TIMR0);
	
	while(1==1)
	{
	}
}

void TIMR0_Handler(void)
{
	TIMR_INTClr(TIMR0);
	
	GPIO_InvBit(GPIOA, PIN5);	//反转LED亮灭状态
}
