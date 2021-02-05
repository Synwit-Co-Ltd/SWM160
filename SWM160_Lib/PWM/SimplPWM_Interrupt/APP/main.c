#include "SWM160.h"


int main(void)
{
	PWM_InitStructure  PWM_initStruct;
	
	SystemInit();
	
	GPIO_Init(GPIOA, PIN6, 1, 0, 0, 0);			//反转PA6，指示PWM新周期开始中断位置
	GPIO_Init(GPIOA, PIN7, 1, 0, 0, 0);			//反转PA7，指示PWM高电平结束中断位置
	
	PWM_initStruct.clk_div = PWM_CLKDIV_4;		//F_PWM = 24M/4 = 6M
	
	PWM_initStruct.mode = PWM_MODE_INDEP;		//A路和B路独立输出					
	PWM_initStruct.cycleA = 10000;				//6M/10000 = 600Hz			
	PWM_initStruct.hdutyA =  2500;				//2500/10000 = 25%
	PWM_initStruct.initLevelA = 1;
	PWM_initStruct.cycleB = 10000;
	PWM_initStruct.hdutyB =  5000;				//5000/10000 = 50%
	PWM_initStruct.initLevelB = 1;
	PWM_initStruct.HEndAIEn = 1;
	PWM_initStruct.NCycleAIEn = 1;
	PWM_initStruct.HEndBIEn = 0;
	PWM_initStruct.NCycleBIEn = 0;
	
	PWM_Init(PWM0, &PWM_initStruct);
	
	PWM_initStruct.HEndAIEn = 0;
	PWM_initStruct.NCycleAIEn = 0;
	
	PWM_Init(PWM1, &PWM_initStruct);
	PWM_Init(PWM2, &PWM_initStruct);
	
	PORT_Init(PORTA, PIN3,  PORTA_PIN3_PWM0A, 0);
	PORT_Init(PORTC, PIN14, PORTC_PIN14_PWM0A, 0);
	PORT_Init(PORTB, PIN2,  PORTB_PIN2_PWM0B, 0);
	PORT_Init(PORTC, PIN6,  PORTC_PIN6_PWM1A, 0);
	PORT_Init(PORTB, PIN13, PORTB_PIN13_PWM1B, 0);
	PORT_Init(PORTC, PIN11, PORTC_PIN11_PWM2A, 0);
	PORT_Init(PORTC, PIN15, PORTC_PIN15_PWM2B, 0);
	
	PWM_Start(PWM0, 1, 1);
	PWM_Start(PWM1, 1, 1);
	PWM_Start(PWM2, 1, 1);
	
	while(1==1)
	{
	
	}
}

void PWMNC_Handler(void)
{
	if(PWM_IntNCycleStat(PWM0, PWM_CH_A))
	{
		PWM_IntNCycleClr(PWM0, PWM_CH_A);
		
		GPIO_InvBit(GPIOA, PIN6);
	}
}

void PWMHE_Handler(void)
{
	if(PWM_IntHEndStat(PWM0, PWM_CH_A))
	{
		PWM_IntHEndClr(PWM0, PWM_CH_A);
		
		GPIO_InvBit(GPIOA, PIN7);
	}
}
