#include "SWM160.h"


int main(void)
{	
	SystemInit();
	
	GPIO_Init(GPIOA, PIN5, 1, 0, 0, 0);			//输出，接LED
	
	SysTick_Config(SystemCoreClock/4);			//每0.25秒钟触发一次中断；注意：周期寄存器是24位的，最大计数个数约16_000_000
		
	while(1==1)
	{
	}
}

void SysTick_Handler(void)
{	
	GPIO_InvBit(GPIOA, PIN5);	//反转LED亮灭状态
}
