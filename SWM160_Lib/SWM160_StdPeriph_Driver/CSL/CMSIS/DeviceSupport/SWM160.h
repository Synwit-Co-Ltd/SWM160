#ifndef __SWM160_H__
#define __SWM160_H__

/*
 * ==========================================================================
 * ---------- Interrupt Number Definition -----------------------------------
 * ==========================================================================
 */
typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers **********************************************/
  NonINTMableInt_IRQn = -14,	/*!< 2 Non INTMable Interrupt								 */
  HardFault_IRQn	  = -13,	/*!< 3 Cortex-M0 Hard Fault Interrupt						 */
  SVCall_IRQn		  = -5,	 /*!< 11 Cortex-M0 SV Call Interrupt						     */
  PendSV_IRQn		  = -2,	 /*!< 14 Cortex-M0 Pend SV Interrupt						     */
  SysTick_IRQn		  = -1,	 /*!< 15 Cortex-M0 System Tick Interrupt					     */

/******  Cortex-M0 specific Interrupt Numbers ************************************************/
  GPIOA0_IRQn		  = 0,	  /*!< 														     */
  WDT_IRQn			  = 1,	  /*!< maximum of 32 Interrupts are possible	 			     */
  TIMR3_IRQn		  = 2,
  PWMNC_IRQn 		  = 3,
  ADC_IRQn			  = 4,
  TIMR2_IRQn		  = 5,
  RTC_IRQn			  = 6,
  GPIOA1_IRQn		  = 7,
  SPI1_IRQn		      = 8,
  GPIOD1_IRQn		  = 9,
  CAN_IRQn			  = 10,
  UART0_IRQn		  = 11,
  I2C0_IRQn			  = 12,
  SPI0_IRQn			  = 13,
  GPIOA_IRQn		  = 14,
  TIMR1_IRQn		  = 15,
  GPIOB0_IRQn		  = 16,
  UART1_IRQn		  = 17,
  GPIOB_IRQn		  = 18,
  TIMR0_IRQn		  = 19,
  GPIOB1_IRQn		  = 20,
  PWMHE_IRQn		  = 21,
  UART2_IRQn   		  = 22,
  BOD_IRQn	  		  = 23,
  I2C1_IRQn	   		  = 24,
  GPIOC0_IRQn	   	  = 25,
  GPIOC1_IRQn	   	  = 26,
  UART3_IRQn   		  = 27,
  PWMHALT_IRQn	  	  = 28,
  GPIOC_IRQn   		  = 29,
  GPIOD_IRQn		  = 30,
  DMA_IRQn			  = 31
} IRQn_Type;

/*
 * ==========================================================================
 * ----------- Processor and Core Peripheral Section ------------------------
 * ==========================================================================
 */

/* Configuration of the Cortex-M0 Processor and Core Peripherals */
#define __MPU_PRESENT		    0	   /*!< UART does not provide a MPU present or not	     */
#define __NVIC_PRIO_BITS		2	   /*!< UART Supports 2 Bits for the Priority Levels	 */
#define __Vendor_SysTickConfig  0	   /*!< Set to 1 if different SysTick Config is used	 */

#if   defined ( __CC_ARM )
  #pragma anon_unions
#endif

#include <stdio.h>
#include "core_cm0.h"				   /* Cortex-M0 processor and core peripherals		     */
#include "system_SWM160.h"


/******************************************************************************/
/*				Device Specific Peripheral registers structures			 */
/******************************************************************************/
typedef struct {
	__IO uint32_t CLKSEL;				    //Clock Select
	
		 uint32_t RESERVED;
	
	__IO uint32_t CLKEN;					//Clock Enable
	
		 uint32_t RESERVED2;
	
	__IO uint32_t SLEEP;
	
		 uint32_t RESERVED3[7];
	
	__IO uint32_t RTCWK;					//RTC Wakeup

		 uint32_t RESERVED4[51];
	
	__IO uint32_t CHIP_ID[4];
	
		 uint32_t RESERVED5[60];

	__IO uint32_t PAWKEN;				    //Port A Wakeup Enable
	__IO uint32_t PBWKEN;
	__IO uint32_t PCWKEN;
	__IO uint32_t PDWKEN;
	
		 uint32_t RESERVED6[2];
	
	__IO uint32_t PAWKSR;				    //Port A Wakeup Status Register，写1清零
	__IO uint32_t PBWKSR;
	__IO uint32_t PCWKSR;
	__IO uint32_t PDWKSR;
	
		 uint32_t RESERVED7[(0x308-0x224)/4-1];
		 
	__IO uint32_t RSTST;
	
         uint32_t RESERVED8[(0x5000C000-0x40000308)/4-1];
    
    __IO uint32_t HRCCR;					//High speed RC Control Register
	
		 uint32_t RESERVED9[3];
	
	__IO uint32_t BODCR;
	
		 uint32_t RESERVED10[2];
	
	__IO uint32_t XTALCR;
	
	__IO uint32_t LRCCR;					//Low speed RC Control Register
	
	     uint32_t RESERVED11[47];
	
	__IO uint32_t TESTANA;
} SYS_TypeDef;


#define SYS_CLKSEL_LFCK_Pos			0		//Low Frequency Clock Source	0 LRC	1 XTAL
#define SYS_CLKSEL_LFCK_Msk			(0x01 << SYS_CLKSEL_LFCK_Pos)
#define SYS_CLKSEL_HFCK_Pos			1		//High Frequency Clock Source	0 HRC	1 HRC/4
#define SYS_CLKSEL_HFCK_Msk			(0x01 << SYS_CLKSEL_HFCK_Pos)
#define SYS_CLKSEL_SYS_Pos			2		//系统时钟选择	0 LFCK	1 HFCK
#define SYS_CLKSEL_SYS_Msk			(0x01 << SYS_CLKSEL_SYS_Pos)
#define SYS_CLKSEL_RTC_Pos			4		//RTC校准参考时钟   0 XTAL	1 XTAL/2  2 XTAL/4  3 XTAL/8
#define SYS_CLKSEL_RTC_Msk			(0x03 << SYS_CLKSEL_RTC_Pos)

#define SYS_CLKEN_GPIOA_Pos			0
#define SYS_CLKEN_GPIOA_Msk			(0x01 << SYS_CLKEN_GPIOA_Pos)
#define SYS_CLKEN_GPIOB_Pos			1
#define SYS_CLKEN_GPIOB_Msk			(0x01 << SYS_CLKEN_GPIOB_Pos)
#define SYS_CLKEN_GPIOC_Pos			2
#define SYS_CLKEN_GPIOC_Msk			(0x01 << SYS_CLKEN_GPIOC_Pos)
#define SYS_CLKEN_GPIOD_Pos			3
#define SYS_CLKEN_GPIOD_Msk			(0x01 << SYS_CLKEN_GPIOD_Pos)
#define SYS_CLKEN_TIMR_Pos			6
#define SYS_CLKEN_TIMR_Msk			(0x01 << SYS_CLKEN_TIMR_Pos)
#define SYS_CLKEN_WDT_Pos			7
#define SYS_CLKEN_WDT_Msk			(0x01 << SYS_CLKEN_WDT_Pos)
#define SYS_CLKEN_ADC_Pos			8
#define SYS_CLKEN_ADC_Msk			(0x01 << SYS_CLKEN_ADC_Pos)
#define SYS_CLKEN_PWM_Pos			9
#define SYS_CLKEN_PWM_Msk			(0x01 << SYS_CLKEN_PWM_Pos)
#define SYS_CLKEN_RTC_Pos			10
#define SYS_CLKEN_RTC_Msk			(0x01 << SYS_CLKEN_RTC_Pos)
#define SYS_CLKEN_UART0_Pos			11
#define SYS_CLKEN_UART0_Msk			(0x01 << SYS_CLKEN_UART0_Pos)
#define SYS_CLKEN_UART1_Pos			12
#define SYS_CLKEN_UART1_Msk			(0x01 << SYS_CLKEN_UART1_Pos)
#define SYS_CLKEN_UART2_Pos			13
#define SYS_CLKEN_UART2_Msk			(0x01 << SYS_CLKEN_UART2_Pos)
#define SYS_CLKEN_UART3_Pos			14
#define SYS_CLKEN_UART3_Msk			(0x01 << SYS_CLKEN_UART3_Pos)
#define SYS_CLKEN_SPI1_Pos			15
#define SYS_CLKEN_SPI1_Msk			(0x01 << SYS_CLKEN_SPI1_Pos)
#define SYS_CLKEN_SPI0_Pos			16
#define SYS_CLKEN_SPI0_Msk			(0x01 << SYS_CLKEN_SPI0_Pos)
#define SYS_CLKEN_I2C0_Pos			17
#define SYS_CLKEN_I2C0_Msk			(0x01 << SYS_CLKEN_I2C0_Pos)
#define SYS_CLKEN_I2C1_Pos			18
#define SYS_CLKEN_I2C1_Msk			(0x01 << SYS_CLKEN_I2C1_Pos)
#define SYS_CLKEN_OSC_Pos			22
#define SYS_CLKEN_OSC_Msk			(0x01 << SYS_CLKEN_OSC_Pos)
#define SYS_CLKEN_CAN_Pos			25
#define SYS_CLKEN_CAN_Msk			(0x01 << SYS_CLKEN_CAN_Pos)
#define SYS_CLKEN_DIV_Pos			29
#define SYS_CLKEN_DIV_Msk			(0x01 << SYS_CLKEN_DIV_Pos)

#define SYS_SLEEP_SLEEP_Pos			0		//将该位置1后，系统将进入SLEEP模式
#define SYS_SLEEP_SLEEP_Msk			(0x01 << SYS_SLEEP_SLEEP_Pos)
#define SYS_SLEEP_STOP_Pos			1		//将该位置1后，系统将进入STOP 模式
#define SYS_SLEEP_STOP_Msk			(0x01 << SYS_SLEEP_STOP_Pos)

#define SYS_RTCWK_EN_Pos			0
#define SYS_RTCWK_EN_Msk			(0x01 << SYS_RTCWK_EN_Pos)
#define SYS_RTCWK_ST_Pos			1		//RTC唤醒状态标志位，写1清
#define SYS_RTCWK_ST_Msk			(0x01 << SYS_RTCWK_ST_Pos)

#define SYS_RSTST_POR_Pos			0		//1 表示出现过POR复位，写1清零
#define SYS_RSTST_POR_Msk			(0x01 << SYS_RSTST_POR_Pos)
#define SYS_RSTST_WDT_Pos			3		//1 表示出现过WDT复位，写1清零
#define SYS_RSTST_WDT_Msk			(0x01 << SYS_RSTST_WDT_Pos)

#define SYS_HRCCR_EN_Pos			0		//High speed RC Enable
#define SYS_HRCCR_EN_Msk			(0x01 << SYS_HRCCR_EN_Pos)
#define SYS_HRCCR_DBL_Pos		    1		//Double Frequency	0 24MHz	1 48MHz
#define SYS_HRCCR_DBL_Msk		    (0x01 << SYS_HRCCR_DBL_Pos)

#define SYS_BODCR_INTEN_Pos			1		//BOD中断使能
#define SYS_BODCR_INTEN_Msk			(0x01 << SYS_BODCR_INTEN_Pos)
#define SYS_BODCR_INTST_Pos			2		//BOD中断状态，只读
#define SYS_BODCR_INTST_Msk			(0x01 << SYS_BODCR_INTST_Pos)
#define SYS_BODCR_RSTLVL_Pos		4		//BOD复位电平，0 2.0V产生复位   1 1.7V产生复位
#define SYS_BODCR_RSTLVL_Msk		(0x01 << SYS_BODCR_RSTLVL_Pos)
#define SYS_BODCR_INTLVL_Pos		5		//BOD中断电平，0 2.7V产生中断   1 2.3V产生中断   2 2.0V产生中断
#define SYS_BODCR_INTLVL_Msk		(0x03 << SYS_BODCR_INTLVL_Pos)

#define SYS_XTALCR_EN_Pos		    1
#define SYS_XTALCR_EN_Msk		    (0x01 << SYS_XTALCR_EN_Pos)

#define SYS_LRCCR_EN_Pos			0		//Low Speed RC Enable
#define SYS_LRCCR_EN_Msk			(0x01 << SYS_LRCCR_EN_Pos)




typedef struct {
	__IO uint32_t FUNSEL;
	
		 uint32_t RESERVED[127];
	
	__IO uint32_t PULLU;                    //PULLU[n]为 PINn引脚 上拉使能位： 1 上拉使能	0 上拉禁止
	
		 uint32_t RESERVED2[63];
	
	__IO uint32_t PULLD;                    //PULLD[n]为 PINn引脚 下拉使能位： 1 下拉使能	0 下拉禁止
	
		 uint32_t RESERVED3[63];
	
	__IO uint32_t OPEND;                    //OPEND[n]为 PINn引脚 开漏使能位： 1 开漏使能	0 开漏禁止
	
		 uint32_t RESERVED4[127];
	
	__IO uint32_t INEN;                     //INEN[n] 为 PINn引脚 输入使能位： 1 输入使能	0 输入禁止
} PORT_TypeDef;


#define PORT_FUNSEL_PIN0_Pos		0
#define PORT_FUNSEL_PIN0_Msk		(0x01 << PORT_FUNSEL_PIN0_Pos)
#define PORT_FUNSEL_PIN1_Pos		1
#define PORT_FUNSEL_PIN1_Msk		(0x01 << PORT_FUNSEL_PIN1_Pos)
#define PORT_FUNSEL_PIN2_Pos		2
#define PORT_FUNSEL_PIN2_Msk		(0x01 << PORT_FUNSEL_PIN2_Pos)
#define PORT_FUNSEL_PIN3_Pos		3
#define PORT_FUNSEL_PIN3_Msk		(0x01 << PORT_FUNSEL_PIN3_Pos)
#define PORT_FUNSEL_PIN4_Pos		4
#define PORT_FUNSEL_PIN4_Msk		(0x01 << PORT_FUNSEL_PIN4_Pos)
#define PORT_FUNSEL_PIN5_Pos		5
#define PORT_FUNSEL_PIN5_Msk		(0x01 << PORT_FUNSEL_PIN5_Pos)
#define PORT_FUNSEL_PIN6_Pos		6
#define PORT_FUNSEL_PIN6_Msk		(0x01 << PORT_FUNSEL_PIN6_Pos)
#define PORT_FUNSEL_PIN7_Pos		7
#define PORT_FUNSEL_PIN7_Msk		(0x01 << PORT_FUNSEL_PIN7_Pos)
#define PORT_FUNSEL_PIN8_Pos		8
#define PORT_FUNSEL_PIN8_Msk		(0x01 << PORT_FUNSEL_PIN8_Pos)
#define PORT_FUNSEL_PIN9_Pos		9
#define PORT_FUNSEL_PIN9_Msk		(0x01 << PORT_FUNSEL_PIN9_Pos)
#define PORT_FUNSEL_PIN10_Pos		10
#define PORT_FUNSEL_PIN10_Msk		(0x01 << PORT_FUNSEL_PIN10_Pos)
#define PORT_FUNSEL_PIN11_Pos		11
#define PORT_FUNSEL_PIN11_Msk		(0x01 << PORT_FUNSEL_PIN11_Pos)
#define PORT_FUNSEL_PIN12_Pos		12
#define PORT_FUNSEL_PIN12_Msk		(0x01 << PORT_FUNSEL_PIN12_Pos)
#define PORT_FUNSEL_PIN13_Pos		13
#define PORT_FUNSEL_PIN13_Msk		(0x01 << PORT_FUNSEL_PIN13_Pos)
#define PORT_FUNSEL_PIN14_Pos		14
#define PORT_FUNSEL_PIN14_Msk		(0x01 << PORT_FUNSEL_PIN14_Pos)
#define PORT_FUNSEL_PIN15_Pos		15
#define PORT_FUNSEL_PIN15_Msk		(0x01 << PORT_FUNSEL_PIN15_Pos)

#define PORT_PULLU_PIN0_Pos			0
#define PORT_PULLU_PIN0_Msk			(0x01 << PORT_PULLU_PIN0_Pos)
#define PORT_PULLU_PIN1_Pos			1
#define PORT_PULLU_PIN1_Msk			(0x01 << PORT_PULLU_PIN1_Pos)
#define PORT_PULLU_PIN2_Pos			2
#define PORT_PULLU_PIN2_Msk			(0x01 << PORT_PULLU_PIN2_Pos)
#define PORT_PULLU_PIN3_Pos			3
#define PORT_PULLU_PIN3_Msk			(0x01 << PORT_PULLU_PIN3_Pos)
#define PORT_PULLU_PIN4_Pos			4
#define PORT_PULLU_PIN4_Msk			(0x01 << PORT_PULLU_PIN4_Pos)
#define PORT_PULLU_PIN5_Pos			5
#define PORT_PULLU_PIN5_Msk			(0x01 << PORT_PULLU_PIN5_Pos)
#define PORT_PULLU_PIN6_Pos			6
#define PORT_PULLU_PIN6_Msk			(0x01 << PORT_PULLU_PIN6_Pos)
#define PORT_PULLU_PIN7_Pos			7
#define PORT_PULLU_PIN7_Msk			(0x01 << PORT_PULLU_PIN7_Pos)
#define PORT_PULLU_PIN8_Pos			8
#define PORT_PULLU_PIN8_Msk			(0x01 << PORT_PULLU_PIN8_Pos)
#define PORT_PULLU_PIN9_Pos			9
#define PORT_PULLU_PIN9_Msk			(0x01 << PORT_PULLU_PIN9_Pos)
#define PORT_PULLU_PIN10_Pos		10
#define PORT_PULLU_PIN10_Msk		(0x01 << PORT_PULLU_PIN10_Pos)
#define PORT_PULLU_PIN11_Pos		11
#define PORT_PULLU_PIN11_Msk		(0x01 << PORT_PULLU_PIN11_Pos)
#define PORT_PULLU_PIN12_Pos		12
#define PORT_PULLU_PIN12_Msk		(0x01 << PORT_PULLU_PIN12_Pos)
#define PORT_PULLU_PIN13_Pos		13
#define PORT_PULLU_PIN13_Msk		(0x01 << PORT_PULLU_PIN13_Pos)
#define PORT_PULLU_PIN14_Pos		14
#define PORT_PULLU_PIN14_Msk		(0x01 << PORT_PULLU_PIN14_Pos)
#define PORT_PULLU_PIN15_Pos		15
#define PORT_PULLU_PIN15_Msk		(0x01 << PORT_PULLU_PIN15_Pos)

#define PORT_PULLD_PIN0_Pos			0
#define PORT_PULLD_PIN0_Msk			(0x01 << PORT_PULLD_PIN0_Pos)
#define PORT_PULLD_PIN1_Pos			1
#define PORT_PULLD_PIN1_Msk			(0x01 << PORT_PULLD_PIN1_Pos)
#define PORT_PULLD_PIN2_Pos			2
#define PORT_PULLD_PIN2_Msk			(0x01 << PORT_PULLD_PIN2_Pos)
#define PORT_PULLD_PIN3_Pos			3
#define PORT_PULLD_PIN3_Msk			(0x01 << PORT_PULLD_PIN3_Pos)
#define PORT_PULLD_PIN4_Pos			4
#define PORT_PULLD_PIN4_Msk			(0x01 << PORT_PULLD_PIN4_Pos)
#define PORT_PULLD_PIN5_Pos			5
#define PORT_PULLD_PIN5_Msk			(0x01 << PORT_PULLD_PIN5_Pos)
#define PORT_PULLD_PIN6_Pos			6
#define PORT_PULLD_PIN6_Msk			(0x01 << PORT_PULLD_PIN6_Pos)
#define PORT_PULLD_PIN7_Pos			7
#define PORT_PULLD_PIN7_Msk			(0x01 << PORT_PULLD_PIN7_Pos)
#define PORT_PULLD_PIN8_Pos			8
#define PORT_PULLD_PIN8_Msk			(0x01 << PORT_PULLD_PIN8_Pos)
#define PORT_PULLD_PIN9_Pos			9
#define PORT_PULLD_PIN9_Msk			(0x01 << PORT_PULLD_PIN9_Pos)
#define PORT_PULLD_PIN10_Pos		10
#define PORT_PULLD_PIN10_Msk		(0x01 << PORT_PULLD_PIN10_Pos)
#define PORT_PULLD_PIN11_Pos		11
#define PORT_PULLD_PIN11_Msk		(0x01 << PORT_PULLD_PIN11_Pos)
#define PORT_PULLD_PIN12_Pos		12
#define PORT_PULLD_PIN12_Msk		(0x01 << PORT_PULLD_PIN12_Pos)
#define PORT_PULLD_PIN13_Pos		13
#define PORT_PULLD_PIN13_Msk		(0x01 << PORT_PULLD_PIN13_Pos)
#define PORT_PULLD_PIN14_Pos		14
#define PORT_PULLD_PIN14_Msk		(0x01 << PORT_PULLD_PIN14_Pos)
#define PORT_PULLD_PIN15_Pos		15
#define PORT_PULLD_PIN15_Msk		(0x01 << PORT_PULLD_PIN15_Pos)

#define PORT_OPEND_PIN0_Pos			0
#define PORT_OPEND_PIN0_Msk			(0x01 << PORT_OPEND_PIN0_Pos)
#define PORT_OPEND_PIN1_Pos			1
#define PORT_OPEND_PIN1_Msk			(0x01 << PORT_OPEND_PIN1_Pos)
#define PORT_OPEND_PIN2_Pos			2
#define PORT_OPEND_PIN2_Msk			(0x01 << PORT_OPEND_PIN2_Pos)
#define PORT_OPEND_PIN3_Pos			3
#define PORT_OPEND_PIN3_Msk			(0x01 << PORT_OPEND_PIN3_Pos)
#define PORT_OPEND_PIN4_Pos			4
#define PORT_OPEND_PIN4_Msk			(0x01 << PORT_OPEND_PIN4_Pos)
#define PORT_OPEND_PIN5_Pos			5
#define PORT_OPEND_PIN5_Msk			(0x01 << PORT_OPEND_PIN5_Pos)
#define PORT_OPEND_PIN6_Pos			6
#define PORT_OPEND_PIN6_Msk			(0x01 << PORT_OPEND_PIN6_Pos)
#define PORT_OPEND_PIN7_Pos			7
#define PORT_OPEND_PIN7_Msk			(0x01 << PORT_OPEND_PIN7_Pos)
#define PORT_OPEND_PIN8_Pos			8
#define PORT_OPEND_PIN8_Msk			(0x01 << PORT_OPEND_PIN8_Pos)
#define PORT_OPEND_PIN9_Pos			9
#define PORT_OPEND_PIN9_Msk			(0x01 << PORT_OPEND_PIN9_Pos)
#define PORT_OPEND_PIN10_Pos		10
#define PORT_OPEND_PIN10_Msk		(0x01 << PORT_OPEND_PIN10_Pos)
#define PORT_OPEND_PIN11_Pos		11
#define PORT_OPEND_PIN11_Msk		(0x01 << PORT_OPEND_PIN11_Pos)
#define PORT_OPEND_PIN12_Pos		12
#define PORT_OPEND_PIN12_Msk		(0x01 << PORT_OPEND_PIN12_Pos)
#define PORT_OPEND_PIN13_Pos		13
#define PORT_OPEND_PIN13_Msk		(0x01 << PORT_OPEND_PIN13_Pos)
#define PORT_OPEND_PIN14_Pos		14
#define PORT_OPEND_PIN14_Msk		(0x01 << PORT_OPEND_PIN14_Pos)
#define PORT_OPEND_PIN15_Pos		15
#define PORT_OPEND_PIN15_Msk		(0x01 << PORT_OPEND_PIN15_Pos)

#define PORT_INEN_PIN0_Pos			0
#define PORT_INEN_PIN0_Msk			(0x01 << PORT_INEN_PIN0_Pos)
#define PORT_INEN_PIN1_Pos			1
#define PORT_INEN_PIN1_Msk			(0x01 << PORT_INEN_PIN1_Pos)
#define PORT_INEN_PIN2_Pos			2
#define PORT_INEN_PIN2_Msk			(0x01 << PORT_INEN_PIN2_Pos)
#define PORT_INEN_PIN3_Pos			3
#define PORT_INEN_PIN3_Msk			(0x01 << PORT_INEN_PIN3_Pos)
#define PORT_INEN_PIN4_Pos			4
#define PORT_INEN_PIN4_Msk			(0x01 << PORT_INEN_PIN4_Pos)
#define PORT_INEN_PIN5_Pos			5
#define PORT_INEN_PIN5_Msk			(0x01 << PORT_INEN_PIN5_Pos)
#define PORT_INEN_PIN6_Pos			6
#define PORT_INEN_PIN6_Msk			(0x01 << PORT_INEN_PIN6_Pos)
#define PORT_INEN_PIN7_Pos			7
#define PORT_INEN_PIN7_Msk			(0x01 << PORT_INEN_PIN7_Pos)
#define PORT_INEN_PIN8_Pos			8
#define PORT_INEN_PIN8_Msk			(0x01 << PORT_INEN_PIN8_Pos)
#define PORT_INEN_PIN9_Pos			9
#define PORT_INEN_PIN9_Msk			(0x01 << PORT_INEN_PIN9_Pos)
#define PORT_INEN_PIN10_Pos			10
#define PORT_INEN_PIN10_Msk			(0x01 << PORT_INEN_PIN10_Pos)
#define PORT_INEN_PIN11_Pos			11
#define PORT_INEN_PIN11_Msk			(0x01 << PORT_INEN_PIN11_Pos)
#define PORT_INEN_PIN12_Pos			12
#define PORT_INEN_PIN12_Msk			(0x01 << PORT_INEN_PIN12_Pos)
#define PORT_INEN_PIN13_Pos			13
#define PORT_INEN_PIN13_Msk			(0x01 << PORT_INEN_PIN13_Pos)
#define PORT_INEN_PIN14_Pos			14
#define PORT_INEN_PIN14_Msk			(0x01 << PORT_INEN_PIN14_Pos)
#define PORT_INEN_PIN15_Pos			15
#define PORT_INEN_PIN15_Msk			(0x01 << PORT_INEN_PIN15_Pos)




typedef struct {
	__IO uint32_t DATA;
#define PIN0    0
#define PIN1    1
#define PIN2    2
#define PIN3    3
#define PIN4    4
#define PIN5    5
#define PIN6    6
#define PIN7    7
#define PIN8    8
#define PIN9    9
#define PIN10   10
#define PIN11   11
#define PIN12   12
#define PIN13   13
#define PIN14   14
#define PIN15   15

	__IO uint32_t DIR;					    //0 输入	1 输出

	__IO uint32_t INTLVLTRG;				//Interrupt Level Trigger  1 电平触发中断	0 边沿触发中断

	__IO uint32_t INTBE;					//Both Edge，当INTLVLTRG设为边沿触发中断时，此位置1表示上升沿和下降沿都触发中断，置0时触发边沿由INTRISEEN选择

	__IO uint32_t INTRISEEN;				//Interrupt Rise Edge Enable   1 上升沿/高电平触发中断	0 下降沿/低电平触发中断

	__IO uint32_t INTEN;					//1 中断使能	0 中断禁止

	__IO uint32_t INTRAWSTAT;			    //中断检测单元是否检测到了触发中断的条件 1 检测到了中断触发条件	0 没有检测到中断触发条件

	__IO uint32_t INTSTAT;				    //INTSTAT.PIN0 = INTRAWSTAT.PIN0 & INTEN.PIN0

	__IO uint32_t INTCLR;				    //写1清除中断标志，只对边沿触发中断有用
	
	     uint32_t RESERVED[7];
	
	__IO uint32_t DATAPIN0;					//PIN0引脚的DATA寄存器，单个引脚对应整个32位寄存器，方便实现原子写操作
	__IO uint32_t DATAPIN1;
	__IO uint32_t DATAPIN2;
	__IO uint32_t DATAPIN3;
	__IO uint32_t DATAPIN4;
	__IO uint32_t DATAPIN5;
	__IO uint32_t DATAPIN6;
	__IO uint32_t DATAPIN7;
	__IO uint32_t DATAPIN8;
	__IO uint32_t DATAPIN9;
	__IO uint32_t DATAPIN10;
	__IO uint32_t DATAPIN11;
	__IO uint32_t DATAPIN12;
	__IO uint32_t DATAPIN13;
	__IO uint32_t DATAPIN14;
	__IO uint32_t DATAPIN15;
} GPIO_TypeDef;


#define GPIO_DATA_PIN0_Pos			0
#define GPIO_DATA_PIN0_Msk			(0x01 << GPIO_DATA_PIN0_Pos)
#define GPIO_DATA_PIN1_Pos			1
#define GPIO_DATA_PIN1_Msk			(0x01 << GPIO_DATA_PIN1_Pos)
#define GPIO_DATA_PIN2_Pos			2
#define GPIO_DATA_PIN2_Msk			(0x01 << GPIO_DATA_PIN2_Pos)
#define GPIO_DATA_PIN3_Pos			3
#define GPIO_DATA_PIN3_Msk			(0x01 << GPIO_DATA_PIN3_Pos)
#define GPIO_DATA_PIN4_Pos			4
#define GPIO_DATA_PIN4_Msk			(0x01 << GPIO_DATA_PIN4_Pos)
#define GPIO_DATA_PIN5_Pos			5
#define GPIO_DATA_PIN5_Msk			(0x01 << GPIO_DATA_PIN5_Pos)
#define GPIO_DATA_PIN6_Pos			6
#define GPIO_DATA_PIN6_Msk			(0x01 << GPIO_DATA_PIN6_Pos)
#define GPIO_DATA_PIN7_Pos			7
#define GPIO_DATA_PIN7_Msk			(0x01 << GPIO_DATA_PIN7_Pos)
#define GPIO_DATA_PIN8_Pos			8
#define GPIO_DATA_PIN8_Msk			(0x01 << GPIO_DATA_PIN8_Pos)
#define GPIO_DATA_PIN9_Pos			9
#define GPIO_DATA_PIN9_Msk			(0x01 << GPIO_DATA_PIN9_Pos)
#define GPIO_DATA_PIN10_Pos			10
#define GPIO_DATA_PIN10_Msk			(0x01 << GPIO_DATA_PIN10_Pos)
#define GPIO_DATA_PIN11_Pos			11
#define GPIO_DATA_PIN11_Msk			(0x01 << GPIO_DATA_PIN11_Pos)
#define GPIO_DATA_PIN12_Pos			12
#define GPIO_DATA_PIN12_Msk			(0x01 << GPIO_DATA_PIN12_Pos)
#define GPIO_DATA_PIN13_Pos			13
#define GPIO_DATA_PIN13_Msk			(0x01 << GPIO_DATA_PIN13_Pos)
#define GPIO_DATA_PIN14_Pos			14
#define GPIO_DATA_PIN14_Msk			(0x01 << GPIO_DATA_PIN14_Pos)
#define GPIO_DATA_PIN15_Pos			15
#define GPIO_DATA_PIN15_Msk			(0x01 << GPIO_DATA_PIN15_Pos)

#define GPIO_DIR_PIN0_Pos			0
#define GPIO_DIR_PIN0_Msk			(0x01 << GPIO_DIR_PIN0_Pos)
#define GPIO_DIR_PIN1_Pos			1
#define GPIO_DIR_PIN1_Msk			(0x01 << GPIO_DIR_PIN1_Pos)
#define GPIO_DIR_PIN2_Pos			2
#define GPIO_DIR_PIN2_Msk			(0x01 << GPIO_DIR_PIN2_Pos)
#define GPIO_DIR_PIN3_Pos			3
#define GPIO_DIR_PIN3_Msk			(0x01 << GPIO_DIR_PIN3_Pos)
#define GPIO_DIR_PIN4_Pos			4
#define GPIO_DIR_PIN4_Msk			(0x01 << GPIO_DIR_PIN4_Pos)
#define GPIO_DIR_PIN5_Pos			5
#define GPIO_DIR_PIN5_Msk			(0x01 << GPIO_DIR_PIN5_Pos)
#define GPIO_DIR_PIN6_Pos			6
#define GPIO_DIR_PIN6_Msk			(0x01 << GPIO_DIR_PIN6_Pos)
#define GPIO_DIR_PIN7_Pos			7
#define GPIO_DIR_PIN7_Msk			(0x01 << GPIO_DIR_PIN7_Pos)
#define GPIO_DIR_PIN8_Pos			8
#define GPIO_DIR_PIN8_Msk			(0x01 << GPIO_DIR_PIN8_Pos)
#define GPIO_DIR_PIN9_Pos			9
#define GPIO_DIR_PIN9_Msk			(0x01 << GPIO_DIR_PIN9_Pos)
#define GPIO_DIR_PIN10_Pos			10
#define GPIO_DIR_PIN10_Msk			(0x01 << GPIO_DIR_PIN10_Pos)
#define GPIO_DIR_PIN11_Pos			11
#define GPIO_DIR_PIN11_Msk			(0x01 << GPIO_DIR_PIN11_Pos)
#define GPIO_DIR_PIN12_Pos			12
#define GPIO_DIR_PIN12_Msk			(0x01 << GPIO_DIR_PIN12_Pos)
#define GPIO_DIR_PIN13_Pos			13
#define GPIO_DIR_PIN13_Msk			(0x01 << GPIO_DIR_PIN13_Pos)
#define GPIO_DIR_PIN14_Pos			14
#define GPIO_DIR_PIN14_Msk			(0x01 << GPIO_DIR_PIN14_Pos)
#define GPIO_DIR_PIN15_Pos			15
#define GPIO_DIR_PIN15_Msk			(0x01 << GPIO_DIR_PIN15_Pos)

#define GPIO_INTLVLTRG_PIN0_Pos		0
#define GPIO_INTLVLTRG_PIN0_Msk		(0x01 << GPIO_INTLVLTRG_PIN0_Pos)
#define GPIO_INTLVLTRG_PIN1_Pos		1
#define GPIO_INTLVLTRG_PIN1_Msk		(0x01 << GPIO_INTLVLTRG_PIN1_Pos)
#define GPIO_INTLVLTRG_PIN2_Pos		2
#define GPIO_INTLVLTRG_PIN2_Msk		(0x01 << GPIO_INTLVLTRG_PIN2_Pos)
#define GPIO_INTLVLTRG_PIN3_Pos		3
#define GPIO_INTLVLTRG_PIN3_Msk		(0x01 << GPIO_INTLVLTRG_PIN3_Pos)
#define GPIO_INTLVLTRG_PIN4_Pos		4
#define GPIO_INTLVLTRG_PIN4_Msk		(0x01 << GPIO_INTLVLTRG_PIN4_Pos)
#define GPIO_INTLVLTRG_PIN5_Pos		5
#define GPIO_INTLVLTRG_PIN5_Msk		(0x01 << GPIO_INTLVLTRG_PIN5_Pos)
#define GPIO_INTLVLTRG_PIN6_Pos		6
#define GPIO_INTLVLTRG_PIN6_Msk		(0x01 << GPIO_INTLVLTRG_PIN6_Pos)
#define GPIO_INTLVLTRG_PIN7_Pos		7
#define GPIO_INTLVLTRG_PIN7_Msk		(0x01 << GPIO_INTLVLTRG_PIN7_Pos)
#define GPIO_INTLVLTRG_PIN8_Pos		8
#define GPIO_INTLVLTRG_PIN8_Msk		(0x01 << GPIO_INTLVLTRG_PIN8_Pos)
#define GPIO_INTLVLTRG_PIN9_Pos		9
#define GPIO_INTLVLTRG_PIN9_Msk		(0x01 << GPIO_INTLVLTRG_PIN9_Pos)
#define GPIO_INTLVLTRG_PIN10_Pos	10
#define GPIO_INTLVLTRG_PIN10_Msk	(0x01 << GPIO_INTLVLTRG_PIN10_Pos)
#define GPIO_INTLVLTRG_PIN11_Pos	11
#define GPIO_INTLVLTRG_PIN11_Msk	(0x01 << GPIO_INTLVLTRG_PIN11_Pos)
#define GPIO_INTLVLTRG_PIN12_Pos	12
#define GPIO_INTLVLTRG_PIN12_Msk	(0x01 << GPIO_INTLVLTRG_PIN12_Pos)
#define GPIO_INTLVLTRG_PIN13_Pos	13
#define GPIO_INTLVLTRG_PIN13_Msk	(0x01 << GPIO_INTLVLTRG_PIN13_Pos)
#define GPIO_INTLVLTRG_PIN14_Pos	14
#define GPIO_INTLVLTRG_PIN14_Msk	(0x01 << GPIO_INTLVLTRG_PIN14_Pos)
#define GPIO_INTLVLTRG_PIN15_Pos	15
#define GPIO_INTLVLTRG_PIN15_Msk	(0x01 << GPIO_INTLVLTRG_PIN15_Pos)

#define GPIO_INTBE_PIN0_Pos			0
#define GPIO_INTBE_PIN0_Msk			(0x01 << GPIO_INTBE_PIN0_Pos)
#define GPIO_INTBE_PIN1_Pos			1
#define GPIO_INTBE_PIN1_Msk			(0x01 << GPIO_INTBE_PIN1_Pos)
#define GPIO_INTBE_PIN2_Pos			2
#define GPIO_INTBE_PIN2_Msk			(0x01 << GPIO_INTBE_PIN2_Pos)
#define GPIO_INTBE_PIN3_Pos			3
#define GPIO_INTBE_PIN3_Msk			(0x01 << GPIO_INTBE_PIN3_Pos)
#define GPIO_INTBE_PIN4_Pos			4
#define GPIO_INTBE_PIN4_Msk			(0x01 << GPIO_INTBE_PIN4_Pos)
#define GPIO_INTBE_PIN5_Pos			5
#define GPIO_INTBE_PIN5_Msk			(0x01 << GPIO_INTBE_PIN5_Pos)
#define GPIO_INTBE_PIN6_Pos			6
#define GPIO_INTBE_PIN6_Msk			(0x01 << GPIO_INTBE_PIN6_Pos)
#define GPIO_INTBE_PIN7_Pos			7
#define GPIO_INTBE_PIN7_Msk			(0x01 << GPIO_INTBE_PIN7_Pos)
#define GPIO_INTBE_PIN8_Pos			8
#define GPIO_INTBE_PIN8_Msk			(0x01 << GPIO_INTBE_PIN8_Pos)
#define GPIO_INTBE_PIN9_Pos			9
#define GPIO_INTBE_PIN9_Msk			(0x01 << GPIO_INTBE_PIN9_Pos)
#define GPIO_INTBE_PIN10_Pos		10
#define GPIO_INTBE_PIN10_Msk		(0x01 << GPIO_INTBE_PIN10_Pos)
#define GPIO_INTBE_PIN11_Pos		11
#define GPIO_INTBE_PIN11_Msk		(0x01 << GPIO_INTBE_PIN11_Pos)
#define GPIO_INTBE_PIN12_Pos		12
#define GPIO_INTBE_PIN12_Msk		(0x01 << GPIO_INTBE_PIN12_Pos)
#define GPIO_INTBE_PIN13_Pos		13
#define GPIO_INTBE_PIN13_Msk		(0x01 << GPIO_INTBE_PIN13_Pos)
#define GPIO_INTBE_PIN14_Pos		14
#define GPIO_INTBE_PIN14_Msk		(0x01 << GPIO_INTBE_PIN14_Pos)
#define GPIO_INTBE_PIN15_Pos		15
#define GPIO_INTBE_PIN15_Msk		(0x01 << GPIO_INTBE_PIN15_Pos)

#define GPIO_INTRISEEN_PIN0_Pos		0
#define GPIO_INTRISEEN_PIN0_Msk		(0x01 << GPIO_INTRISEEN_PIN0_Pos)
#define GPIO_INTRISEEN_PIN1_Pos		1
#define GPIO_INTRISEEN_PIN1_Msk		(0x01 << GPIO_INTRISEEN_PIN1_Pos)
#define GPIO_INTRISEEN_PIN2_Pos		2
#define GPIO_INTRISEEN_PIN2_Msk		(0x01 << GPIO_INTRISEEN_PIN2_Pos)
#define GPIO_INTRISEEN_PIN3_Pos		3
#define GPIO_INTRISEEN_PIN3_Msk		(0x01 << GPIO_INTRISEEN_PIN3_Pos)
#define GPIO_INTRISEEN_PIN4_Pos		4
#define GPIO_INTRISEEN_PIN4_Msk		(0x01 << GPIO_INTRISEEN_PIN4_Pos)
#define GPIO_INTRISEEN_PIN5_Pos		5
#define GPIO_INTRISEEN_PIN5_Msk		(0x01 << GPIO_INTRISEEN_PIN5_Pos)
#define GPIO_INTRISEEN_PIN6_Pos		6
#define GPIO_INTRISEEN_PIN6_Msk		(0x01 << GPIO_INTRISEEN_PIN6_Pos)
#define GPIO_INTRISEEN_PIN7_Pos		7
#define GPIO_INTRISEEN_PIN7_Msk		(0x01 << GPIO_INTRISEEN_PIN7_Pos)
#define GPIO_INTRISEEN_PIN8_Pos		8
#define GPIO_INTRISEEN_PIN8_Msk		(0x01 << GPIO_INTRISEEN_PIN8_Pos)
#define GPIO_INTRISEEN_PIN9_Pos		9
#define GPIO_INTRISEEN_PIN9_Msk		(0x01 << GPIO_INTRISEEN_PIN9_Pos)
#define GPIO_INTRISEEN_PIN10_Pos	10
#define GPIO_INTRISEEN_PIN10_Msk	(0x01 << GPIO_INTRISEEN_PIN10_Pos)
#define GPIO_INTRISEEN_PIN11_Pos	11
#define GPIO_INTRISEEN_PIN11_Msk	(0x01 << GPIO_INTRISEEN_PIN11_Pos)
#define GPIO_INTRISEEN_PIN12_Pos	12
#define GPIO_INTRISEEN_PIN12_Msk	(0x01 << GPIO_INTRISEEN_PIN12_Pos)
#define GPIO_INTRISEEN_PIN13_Pos	13
#define GPIO_INTRISEEN_PIN13_Msk	(0x01 << GPIO_INTRISEEN_PIN13_Pos)
#define GPIO_INTRISEEN_PIN14_Pos	14
#define GPIO_INTRISEEN_PIN14_Msk	(0x01 << GPIO_INTRISEEN_PIN14_Pos)
#define GPIO_INTRISEEN_PIN15_Pos	15
#define GPIO_INTRISEEN_PIN15_Msk	(0x01 << GPIO_INTRISEEN_PIN15_Pos)

#define GPIO_INTEN_PIN0_Pos			0
#define GPIO_INTEN_PIN0_Msk			(0x01 << GPIO_INTEN_PIN0_Pos)
#define GPIO_INTEN_PIN1_Pos			1
#define GPIO_INTEN_PIN1_Msk			(0x01 << GPIO_INTEN_PIN1_Pos)
#define GPIO_INTEN_PIN2_Pos			2
#define GPIO_INTEN_PIN2_Msk			(0x01 << GPIO_INTEN_PIN2_Pos)
#define GPIO_INTEN_PIN3_Pos			3
#define GPIO_INTEN_PIN3_Msk			(0x01 << GPIO_INTEN_PIN3_Pos)
#define GPIO_INTEN_PIN4_Pos			4
#define GPIO_INTEN_PIN4_Msk			(0x01 << GPIO_INTEN_PIN4_Pos)
#define GPIO_INTEN_PIN5_Pos			5
#define GPIO_INTEN_PIN5_Msk			(0x01 << GPIO_INTEN_PIN5_Pos)
#define GPIO_INTEN_PIN6_Pos			6
#define GPIO_INTEN_PIN6_Msk			(0x01 << GPIO_INTEN_PIN6_Pos)
#define GPIO_INTEN_PIN7_Pos			7
#define GPIO_INTEN_PIN7_Msk			(0x01 << GPIO_INTEN_PIN7_Pos)
#define GPIO_INTEN_PIN8_Pos			8
#define GPIO_INTEN_PIN8_Msk			(0x01 << GPIO_INTEN_PIN8_Pos)
#define GPIO_INTEN_PIN9_Pos			9
#define GPIO_INTEN_PIN9_Msk			(0x01 << GPIO_INTEN_PIN9_Pos)
#define GPIO_INTEN_PIN10_Pos		10
#define GPIO_INTEN_PIN10_Msk		(0x01 << GPIO_INTEN_PIN10_Pos)
#define GPIO_INTEN_PIN11_Pos		11
#define GPIO_INTEN_PIN11_Msk		(0x01 << GPIO_INTEN_PIN11_Pos)
#define GPIO_INTEN_PIN12_Pos		12
#define GPIO_INTEN_PIN12_Msk		(0x01 << GPIO_INTEN_PIN12_Pos)
#define GPIO_INTEN_PIN13_Pos		13
#define GPIO_INTEN_PIN13_Msk		(0x01 << GPIO_INTEN_PIN13_Pos)
#define GPIO_INTEN_PIN14_Pos		14
#define GPIO_INTEN_PIN14_Msk		(0x01 << GPIO_INTEN_PIN14_Pos)
#define GPIO_INTEN_PIN15_Pos		15
#define GPIO_INTEN_PIN15_Msk		(0x01 << GPIO_INTEN_PIN15_Pos)

#define GPIO_INTRAWSTAT_PIN0_Pos	0
#define GPIO_INTRAWSTAT_PIN0_Msk	(0x01 << GPIO_INTRAWSTAT_PIN0_Pos)
#define GPIO_INTRAWSTAT_PIN1_Pos	1
#define GPIO_INTRAWSTAT_PIN1_Msk	(0x01 << GPIO_INTRAWSTAT_PIN1_Pos)
#define GPIO_INTRAWSTAT_PIN2_Pos	2
#define GPIO_INTRAWSTAT_PIN2_Msk	(0x01 << GPIO_INTRAWSTAT_PIN2_Pos)
#define GPIO_INTRAWSTAT_PIN3_Pos	3
#define GPIO_INTRAWSTAT_PIN3_Msk	(0x01 << GPIO_INTRAWSTAT_PIN3_Pos)
#define GPIO_INTRAWSTAT_PIN4_Pos	4
#define GPIO_INTRAWSTAT_PIN4_Msk	(0x01 << GPIO_INTRAWSTAT_PIN4_Pos)
#define GPIO_INTRAWSTAT_PIN5_Pos	5
#define GPIO_INTRAWSTAT_PIN5_Msk	(0x01 << GPIO_INTRAWSTAT_PIN5_Pos)
#define GPIO_INTRAWSTAT_PIN6_Pos	6
#define GPIO_INTRAWSTAT_PIN6_Msk	(0x01 << GPIO_INTRAWSTAT_PIN6_Pos)
#define GPIO_INTRAWSTAT_PIN7_Pos	7
#define GPIO_INTRAWSTAT_PIN7_Msk	(0x01 << GPIO_INTRAWSTAT_PIN7_Pos)
#define GPIO_INTRAWSTAT_PIN8_Pos	8
#define GPIO_INTRAWSTAT_PIN8_Msk	(0x01 << GPIO_INTRAWSTAT_PIN8_Pos)
#define GPIO_INTRAWSTAT_PIN9_Pos	9
#define GPIO_INTRAWSTAT_PIN9_Msk	(0x01 << GPIO_INTRAWSTAT_PIN9_Pos)
#define GPIO_INTRAWSTAT_PIN10_Pos	10
#define GPIO_INTRAWSTAT_PIN10_Msk	(0x01 << GPIO_INTRAWSTAT_PIN10_Pos)
#define GPIO_INTRAWSTAT_PIN11_Pos	11
#define GPIO_INTRAWSTAT_PIN11_Msk	(0x01 << GPIO_INTRAWSTAT_PIN11_Pos)
#define GPIO_INTRAWSTAT_PIN12_Pos	12
#define GPIO_INTRAWSTAT_PIN12_Msk	(0x01 << GPIO_INTRAWSTAT_PIN12_Pos)
#define GPIO_INTRAWSTAT_PIN13_Pos	13
#define GPIO_INTRAWSTAT_PIN13_Msk	(0x01 << GPIO_INTRAWSTAT_PIN13_Pos)
#define GPIO_INTRAWSTAT_PIN14_Pos	14
#define GPIO_INTRAWSTAT_PIN14_Msk	(0x01 << GPIO_INTRAWSTAT_PIN14_Pos)
#define GPIO_INTRAWSTAT_PIN15_Pos	15
#define GPIO_INTRAWSTAT_PIN15_Msk	(0x01 << GPIO_INTRAWSTAT_PIN15_Pos)

#define GPIO_INTSTAT_PIN0_Pos		0
#define GPIO_INTSTAT_PIN0_Msk		(0x01 << GPIO_INTSTAT_PIN0_Pos)
#define GPIO_INTSTAT_PIN1_Pos		1
#define GPIO_INTSTAT_PIN1_Msk		(0x01 << GPIO_INTSTAT_PIN1_Pos)
#define GPIO_INTSTAT_PIN2_Pos		2
#define GPIO_INTSTAT_PIN2_Msk		(0x01 << GPIO_INTSTAT_PIN2_Pos)
#define GPIO_INTSTAT_PIN3_Pos		3
#define GPIO_INTSTAT_PIN3_Msk		(0x01 << GPIO_INTSTAT_PIN3_Pos)
#define GPIO_INTSTAT_PIN4_Pos		4
#define GPIO_INTSTAT_PIN4_Msk		(0x01 << GPIO_INTSTAT_PIN4_Pos)
#define GPIO_INTSTAT_PIN5_Pos		5
#define GPIO_INTSTAT_PIN5_Msk		(0x01 << GPIO_INTSTAT_PIN5_Pos)
#define GPIO_INTSTAT_PIN6_Pos		6
#define GPIO_INTSTAT_PIN6_Msk		(0x01 << GPIO_INTSTAT_PIN6_Pos)
#define GPIO_INTSTAT_PIN7_Pos		7
#define GPIO_INTSTAT_PIN7_Msk		(0x01 << GPIO_INTSTAT_PIN7_Pos)
#define GPIO_INTSTAT_PIN8_Pos		8
#define GPIO_INTSTAT_PIN8_Msk		(0x01 << GPIO_INTSTAT_PIN8_Pos)
#define GPIO_INTSTAT_PIN9_Pos		9
#define GPIO_INTSTAT_PIN9_Msk		(0x01 << GPIO_INTSTAT_PIN9_Pos)
#define GPIO_INTSTAT_PIN10_Pos		10
#define GPIO_INTSTAT_PIN10_Msk		(0x01 << GPIO_INTSTAT_PIN10_Pos)
#define GPIO_INTSTAT_PIN11_Pos		11
#define GPIO_INTSTAT_PIN11_Msk		(0x01 << GPIO_INTSTAT_PIN11_Pos)
#define GPIO_INTSTAT_PIN12_Pos		12
#define GPIO_INTSTAT_PIN12_Msk		(0x01 << GPIO_INTSTAT_PIN12_Pos)
#define GPIO_INTSTAT_PIN13_Pos		13
#define GPIO_INTSTAT_PIN13_Msk		(0x01 << GPIO_INTSTAT_PIN13_Pos)
#define GPIO_INTSTAT_PIN14_Pos		14
#define GPIO_INTSTAT_PIN14_Msk		(0x01 << GPIO_INTSTAT_PIN14_Pos)
#define GPIO_INTSTAT_PIN15_Pos		15
#define GPIO_INTSTAT_PIN15_Msk		(0x01 << GPIO_INTSTAT_PIN15_Pos)

#define GPIO_INTCLR_PIN0_Pos		0
#define GPIO_INTCLR_PIN0_Msk		(0x01 << GPIO_INTCLR_PIN0_Pos)
#define GPIO_INTCLR_PIN1_Pos		1
#define GPIO_INTCLR_PIN1_Msk		(0x01 << GPIO_INTCLR_PIN1_Pos)
#define GPIO_INTCLR_PIN2_Pos		2
#define GPIO_INTCLR_PIN2_Msk		(0x01 << GPIO_INTCLR_PIN2_Pos)
#define GPIO_INTCLR_PIN3_Pos		3
#define GPIO_INTCLR_PIN3_Msk		(0x01 << GPIO_INTCLR_PIN3_Pos)
#define GPIO_INTCLR_PIN4_Pos		4
#define GPIO_INTCLR_PIN4_Msk		(0x01 << GPIO_INTCLR_PIN4_Pos)
#define GPIO_INTCLR_PIN5_Pos		5
#define GPIO_INTCLR_PIN5_Msk		(0x01 << GPIO_INTCLR_PIN5_Pos)
#define GPIO_INTCLR_PIN6_Pos		6
#define GPIO_INTCLR_PIN6_Msk		(0x01 << GPIO_INTCLR_PIN6_Pos)
#define GPIO_INTCLR_PIN7_Pos		7
#define GPIO_INTCLR_PIN7_Msk		(0x01 << GPIO_INTCLR_PIN7_Pos)
#define GPIO_INTCLR_PIN8_Pos		8
#define GPIO_INTCLR_PIN8_Msk		(0x01 << GPIO_INTCLR_PIN8_Pos)
#define GPIO_INTCLR_PIN9_Pos		9
#define GPIO_INTCLR_PIN9_Msk		(0x01 << GPIO_INTCLR_PIN9_Pos)
#define GPIO_INTCLR_PIN10_Pos		10
#define GPIO_INTCLR_PIN10_Msk		(0x01 << GPIO_INTCLR_PIN10_Pos)
#define GPIO_INTCLR_PIN11_Pos		11
#define GPIO_INTCLR_PIN11_Msk		(0x01 << GPIO_INTCLR_PIN11_Pos)
#define GPIO_INTCLR_PIN12_Pos		12
#define GPIO_INTCLR_PIN12_Msk		(0x01 << GPIO_INTCLR_PIN12_Pos)
#define GPIO_INTCLR_PIN13_Pos		13
#define GPIO_INTCLR_PIN13_Msk		(0x01 << GPIO_INTCLR_PIN13_Pos)
#define GPIO_INTCLR_PIN14_Pos		14
#define GPIO_INTCLR_PIN14_Msk		(0x01 << GPIO_INTCLR_PIN14_Pos)
#define GPIO_INTCLR_PIN15_Pos		15
#define GPIO_INTCLR_PIN15_Msk		(0x01 << GPIO_INTCLR_PIN15_Pos)




typedef struct {
	__IO uint32_t LDVAL;					//定时器加载值，24位，使能后定时器从此数值开始向下递减计数

	__I  uint32_t CVAL;					 	//定时器当前值，24位，LDVAL-CVAL 可计算出计时时长

	__IO uint32_t CTRL;
} TIMR_TypeDef;


#define TIMR_CTRL_EN_Pos			0		//此位赋1导致TIMR从LDVAL开始向下递减计数
#define TIMR_CTRL_EN_Msk			(0x01 << TIMR_CTRL_EN_Pos)
#define TIMR_CTRL_CLKSRC_Pos		1		//时钟源：0 内部系统时钟	1 TIMRx-1的溢出信号驱动TIMRx计数	2 外部引脚脉冲计数
#define TIMR_CTRL_CLKSRC_Msk		(0x03 << TIMR_CTRL_CLKSRC_Pos)
#define TIMR_CTRL_OC_INILVL_Pos		3		//Output Compare Inital Level
#define TIMR_CTRL_OC_INILVL_Msk		(0x01 << TIMR_CTRL_OC_INILVL_Pos)
#define TIMR_CTRL_OC_MSKLVL_Pos		4		//输出比较功能被屏蔽时设置的引脚电平
#define TIMR_CTRL_OC_MSKLVL_Msk		(0x01 << TIMR_CTRL_OC_MSKLVL_Pos)
#define TIMR_CTRL_OC_MODE_Pos		5		//0 一个翻转点，___|--- 或 ---|___    1 两个翻转点，___|---|___ 或 ---|___|---
#define TIMR_CTRL_OC_MODE_Msk		(0x01 << TIMR_CTRL_OC_MODE_Pos)




typedef struct {
	__IO uint32_t ICCR;						//Input Capture Control Register
	
		 uint32_t RESERVED[5];
	
	__IO uint32_t HALT;
	
	     uint32_t RESERVED2;
	
	__IO uint32_t HALLCR;
	
	__IO uint32_t HALLSR;
	
		 uint32_t RESERVED3[2];
	
	__IO uint32_t HALL_A;					//霍尔信号A触发时刻TIMER0值，24位
	
	__IO uint32_t HALL_B;
	
	__IO uint32_t HALL_C;
	
		 uint32_t RESERVED4[25];
		 
	__IO uint32_t IF0;						//Interrupt Flag for Timer0
	
	__IO uint32_t IF1;
	
	__IO uint32_t IF2;
	
	__IO uint32_t IF3;
	
		 uint32_t RESERVED5[4];
		 
	__IO uint32_t IE0;						//中断使能=0，不产生IF信号
	
	__IO uint32_t IE1;
	
	__IO uint32_t IE2;
	
	__IO uint32_t IE3;
	
		 uint32_t RESERVED6[4];
		 
	__IO uint32_t IM0;						//中断屏蔽=1，就算有IF信号，也不输出到内核触发中断
	
	__IO uint32_t IM1;
	
	__IO uint32_t IM2;
	
	__IO uint32_t IM3;
	
		 uint32_t RESERVED7[4];
		 
	__IO uint32_t OCMAT0;					//Output Compare Match Register for Timer0，输出比较模式下TIMR只有16位，[15:0] 为第一个翻转点匹配值   [31:16] 为第二个翻转点匹配值
	
	__IO uint32_t OCMAT1;
	
	__IO uint32_t OCMAT2;
	
	__IO uint32_t OCMAT3;
	
		 uint32_t RESERVED8[4];
		 
	__IO uint32_t OCEN;						//Output Compare Enabel
	
	__IO uint32_t OCMSK;					//Output Compare Maks，屏蔽后引脚输出电平由TIMRx->CTRL.OC_MSKLVL决定
	
		 uint32_t RESERVED9[14];
		 
	__IO uint32_t ICVAL0H;					//Input Capture High Level Value for Timer0，24位
	
	__IO uint32_t ICVAL0L;					//Input Capture Low Level Value for Timer0，24位
	
	__IO uint32_t ICVAL1H;
	
	__IO uint32_t ICVAL1L;
	
	__IO uint32_t ICVAL2H;
	
	__IO uint32_t ICVAL2L;
	
	__IO uint32_t ICVAL3H;
	
	__IO uint32_t ICVAL3L;
} TIMRG_TypeDef;


#define TIMRG_ICCR_GO0_Pos			0		//Timer0测量启动 1：开始测量    0：停止测量
#define TIMRG_ICCR_GO0_Msk			(0x01 << TIMRG_ICCR_GO0_Pos)
#define TIMRG_ICCR_POL0_Pos			1		//Timer0测量起始极性 1 测量高电平起始    0 测量低电平起始
#define TIMRG_ICCR_POL0_Msk			(0x01 << TIMRG_ICCR_POL0_Pos)
#define TIMRG_ICCR_EN0_Pos			2		//Timer0测量功能使能
#define TIMRG_ICCR_EN0_Msk			(0x01 << TIMRG_ICCR_EN0_Pos)
#define TIMRG_ICCR_GO1_Pos			4		//Timer1测量启动
#define TIMRG_ICCR_GO1_Msk			(0x01 << TIMRG_ICCR_GO1_Pos)
#define TIMRG_ICCR_POL1_Pos			5		//Timer1测量起始极性
#define TIMRG_ICCR_POL1_Msk			(0x01 << TIMRG_ICCR_POL1_Pos)
#define TIMRG_ICCR_EN1_Pos			6		//Timer1测量功能使能
#define TIMRG_ICCR_EN1_Msk			(0x01 << TIMRG_ICCR_EN1_Pos)
#define TIMRG_ICCR_GO2_Pos			8
#define TIMRG_ICCR_GO2_Msk			(0x01 << TIMRG_ICCR_GO2_Pos)
#define TIMRG_ICCR_POL2_Pos			9
#define TIMRG_ICCR_POL2_Msk			(0x01 << TIMRG_ICCR_POL2_Pos)
#define TIMRG_ICCR_EN2_Pos			10
#define TIMRG_ICCR_EN2_Msk			(0x01 << TIMRG_ICCR_EN2_Pos)
#define TIMRG_ICCR_GO3_Pos			12
#define TIMRG_ICCR_GO3_Msk			(0x01 << TIMRG_ICCR_GO3_Pos)
#define TIMRG_ICCR_POL3_Pos			13
#define TIMRG_ICCR_POL3_Msk			(0x01 << TIMRG_ICCR_POL3_Pos)
#define TIMRG_ICCR_EN3_Pos			14
#define TIMRG_ICCR_EN3_Msk			(0x01 << TIMRG_ICCR_EN3_Pos)

#define TIMRG_HALT_TIMR0_Pos		0		//1 暂停计数
#define TIMRG_HALT_TIMR0_Msk		(0x01 << TIMRG_HALT_TIMR0_Pos)
#define TIMRG_HALT_TIMR1_Pos		1
#define TIMRG_HALT_TIMR1_Msk		(0x01 << TIMRG_HALT_TIMR1_Pos)
#define TIMRG_HALT_TIMR2_Pos		2
#define TIMRG_HALT_TIMR2_Msk		(0x01 << TIMRG_HALT_TIMR2_Pos)
#define TIMRG_HALT_TIMR3_Pos		3
#define TIMRG_HALT_TIMR3_Msk		(0x01 << TIMRG_HALT_TIMR3_Pos)

#define TIMRG_HALLCR_IEA_Pos		0		//0 霍尔信号A禁止中断    1 上升沿产生中断    2 下降沿产生中断    3 双边沿产生中断		
#define TIMRG_HALLCR_IEA_Msk		(0x03 << TIMRG_HALLCR_IEA_Pos)
#define TIMRG_HALLCR_IEB_Pos		2
#define TIMRG_HALLCR_IEB_Msk		(0x03 << TIMRG_HALLCR_IEB_Pos)
#define TIMRG_HALLCR_IEC_Pos		4
#define TIMRG_HALLCR_IEC_Msk		(0x03 << TIMRG_HALLCR_IEC_Pos)

#define TIMRG_HALLSR_IFA_Pos		0		//霍尔信号A中断标志，写1清零	
#define TIMRG_HALLSR_IFA_Msk		(0x01 << TIMRG_HALLSR_IFA_Pos)
#define TIMRG_HALLSR_IFB_Pos		1
#define TIMRG_HALLSR_IFB_Msk		(0x01 << TIMRG_HALLSR_IFB_Pos)
#define TIMRG_HALLSR_IFC_Pos		2
#define TIMRG_HALLSR_IFC_Msk		(0x01 << TIMRG_HALLSR_IFC_Pos)
#define TIMRG_HALLSR_STA_Pos		3		//霍尔信号A状态标志位
#define TIMRG_HALLSR_STA_Msk		(0x01 << TIMRG_HALLSR_STA_Pos)
#define TIMRG_HALLSR_STB_Pos		4
#define TIMRG_HALLSR_STB_Msk		(0x01 << TIMRG_HALLSR_STB_Pos)
#define TIMRG_HALLSR_STC_Pos		5
#define TIMRG_HALLSR_STC_Msk		(0x01 << TIMRG_HALLSR_STC_Pos)

#define TIMRG_IF_IF_Pos				0		//定时器递减至0中断，即一个定时周期，写1清零
#define TIMRG_IF_IF_Msk				(0x01 << TIMRG_IF_IF_Pos)
#define TIMRG_IF_OCMAT1_Pos			1		//Output Compare Match 1
#define TIMRG_IF_OCMAT1_Msk			(0x01 << TIMRG_IF_OCMAT1_Pos)
#define TIMRG_IF_OCMAT2_Pos			2		//Output Compare Match 2
#define TIMRG_IF_OCMAT2_Msk			(0x01 << TIMRG_IF_OCMAT2_Pos)
#define TIMRG_IF_ICH_Pos			8		//Input Capture High Level
#define TIMRG_IF_ICH_Msk			(0x01 << TIMRG_IF_ICH_Pos)
#define TIMRG_IF_ICL_Pos			9		//Input Capture Low Level
#define TIMRG_IF_ICL_Msk			(0x01 << TIMRG_IF_ICL_Pos)
#define TIMRG_IF_ICOV_Pos			10		//Input Capture Overflow
#define TIMRG_IF_ICOV_Msk			(0x01 << TIMRG_IF_ICOV_Pos)
#define TIMRG_IF_HALL_Pos			16
#define TIMRG_IF_HALL_Msk			(0x01 << TIMRG_IF_HALL_Pos)

#define TIMRG_IE_IF_Pos				0		//定时器递减至0中断，即一个定时周期
#define TIMRG_IE_IF_Msk				(0x01 << TIMRG_IE_IF_Pos)
#define TIMRG_IE_OCMAT1_Pos			1		//Output Compare Match 1
#define TIMRG_IE_OCMAT1_Msk			(0x01 << TIMRG_IE_OCMAT1_Pos)
#define TIMRG_IE_OCMAT2_Pos			2		//Output Compare Match 2
#define TIMRG_IE_OCMAT2_Msk			(0x01 << TIMRG_IE_OCMAT2_Pos)
#define TIMRG_IE_ICH_Pos			8		//Input Capture High Level
#define TIMRG_IE_ICH_Msk			(0x01 << TIMRG_IE_ICH_Pos)
#define TIMRG_IE_ICL_Pos			9		//Input Capture Low Level
#define TIMRG_IE_ICL_Msk			(0x01 << TIMRG_IE_ICL_Pos)
#define TIMRG_IE_ICOV_Pos			10		//Input Capture Overflow
#define TIMRG_IE_ICOV_Msk			(0x01 << TIMRG_IE_ICOV_Pos)
#define TIMRG_IE_HALL_Pos			16
#define TIMRG_IE_HALL_Msk			(0x01 << TIMRG_IE_HALL_Pos)

#define TIMRG_IM_IF_Pos				0		//定时器递减至0中断，即一个定时周期
#define TIMRG_IM_IF_Msk				(0x01 << TIMRG_IM_IF_Pos)
#define TIMRG_IM_OCMAT1_Pos			1		//Output Compare Match 1
#define TIMRG_IM_OCMAT1_Msk			(0x01 << TIMRG_IM_OCMAT1_Pos)
#define TIMRG_IM_OCMAT2_Pos			2		//Output Compare Match 2
#define TIMRG_IM_OCMAT2_Msk			(0x01 << TIMRG_IM_OCMAT2_Pos)
#define TIMRG_IM_ICH_Pos			8		//Input Capture High Level
#define TIMRG_IM_ICH_Msk			(0x01 << TIMRG_IM_ICH_Pos)
#define TIMRG_IM_ICL_Pos			9		//Input Capture Low Level
#define TIMRG_IM_ICL_Msk			(0x01 << TIMRG_IM_ICL_Pos)
#define TIMRG_IM_ICOV_Pos			10		//Input Capture Overflow
#define TIMRG_IM_ICOV_Msk			(0x01 << TIMRG_IM_ICOV_Pos)
#define TIMRG_IM_HALL_Pos			16
#define TIMRG_IM_HALL_Msk			(0x01 << TIMRG_IM_HALL_Pos)

#define TIMRG_OCEN_TIMR0_Pos		0
#define TIMRG_OCEN_TIMR0_Msk		(0x01 << TIMRG_OCEN_TIMR0_Pos)
#define TIMRG_OCEN_TIMR1_Pos		1
#define TIMRG_OCEN_TIMR1_Msk		(0x01 << TIMRG_OCEN_TIMR1_Pos)
#define TIMRG_OCEN_TIMR2_Pos		2
#define TIMRG_OCEN_TIMR2_Msk		(0x01 << TIMRG_OCEN_TIMR2_Pos)
#define TIMRG_OCEN_TIMR3_Pos		3
#define TIMRG_OCEN_TIMR3_Msk		(0x01 << TIMRG_OCEN_TIMR3_Pos)

#define TIMRG_OCMSK_TIMR0_Pos		0
#define TIMRG_OCMSK_TIMR0_Msk		(0x01 << TIMRG_OCMSK_TIMR0_Pos)
#define TIMRG_OCMSK_TIMR1_Pos		1
#define TIMRG_OCMSK_TIMR1_Msk		(0x01 << TIMRG_OCMSK_TIMR1_Pos)
#define TIMRG_OCMSK_TIMR2_Pos		2
#define TIMRG_OCMSK_TIMR2_Msk		(0x01 << TIMRG_OCMSK_TIMR2_Pos)
#define TIMRG_OCMSK_TIMR3_Pos		3
#define TIMRG_OCMSK_TIMR3_Msk		(0x01 << TIMRG_OCMSK_TIMR3_Pos)




typedef struct {
	__IO uint32_t DATA;
	
	__IO uint32_t CTRL;
	
	__IO uint32_t BAUD;
	
	__IO uint32_t FIFO;
} UART_TypeDef;


#define UART_DATA_DATA_Pos			0
#define UART_DATA_DATA_Msk			(0x1FF << UART_DATA_DATA_Pos)
#define UART_DATA_VALID_Pos			9		//当DATA字段有有效的接收数据时，该位硬件置1，读取数据后自动清零
#define UART_DATA_VALID_Msk			(0x01 << UART_DATA_VALID_Pos)
#define UART_DATA_PAERR_Pos			10		//Parity Error
#define UART_DATA_PAERR_Msk			(0x01 << UART_DATA_PAERR_Pos)

#define UART_CTRL_TXIDLE_Pos		0		//TX IDLE: 0 正在发送数据	1 空闲状态，没有数据发送
#define UART_CTRL_TXIDLE_Msk		(0x01 << UART_CTRL_TXIDLE_Pos)
#define UART_CTRL_TXF_Pos		    1		//TX FIFO Full
#define UART_CTRL_TXF_Msk		    (0x01 << UART_CTRL_TXF_Pos)
#define UART_CTRL_TXIE_Pos			2		//TX 中断使能: 1 TX FF 中数据少于设定个数时产生中断
#define UART_CTRL_TXIE_Msk			(0x01 << UART_CTRL_TXIE_Pos)
#define UART_CTRL_RXNE_Pos			3		//RX FIFO Not Empty
#define UART_CTRL_RXNE_Msk			(0x01 << UART_CTRL_RXNE_Pos)
#define UART_CTRL_RXIE_Pos			4		//RX 中断使能: 1 RX FF 中数据达到设定个数时产生中断
#define UART_CTRL_RXIE_Msk			(0x01 << UART_CTRL_RXIE_Pos)
#define UART_CTRL_RXOV_Pos			5		//RX FIFO Overflow，写1清零
#define UART_CTRL_RXOV_Msk			(0x01 << UART_CTRL_RXOV_Pos)
#define UART_CTRL_EN_Pos			9
#define UART_CTRL_EN_Msk			(0x01 << UART_CTRL_EN_Pos)
#define UART_CTRL_LOOP_Pos			10
#define UART_CTRL_LOOP_Msk			(0x01 << UART_CTRL_LOOP_Pos)
#define UART_CTRL_BAUDEN_Pos		13		//必须写1
#define UART_CTRL_BAUDEN_Msk		(0x01 << UART_CTRL_BAUDEN_Pos)
#define UART_CTRL_TOIE_Pos			14		//TimeOut 中断使能，接收到上个字符后，超过 TOTIME/BAUDRAUD 秒没有接收到新的数据
#define UART_CTRL_TOIE_Msk			(0x01 << UART_CTRL_TOIE_Pos)
#define UART_CTRL_BRKDET_Pos		15		//LIN Break Detect，检测到LIN Break，即RX线上检测到连续11位低电平
#define UART_CTRL_BRKDET_Msk		(0x01 << UART_CTRL_BRKDET_Pos)
#define UART_CTRL_BRKIE_Pos			16		//LIN Break Detect 中断使能
#define UART_CTRL_BRKIE_Msk			(0x01 << UART_CTRL_BRKIE_Pos)
#define UART_CTRL_GENBRK_Pos		17		//Generate LIN Break，发送LIN Break
#define UART_CTRL_GENBRK_Msk		(0x01 << UART_CTRL_GENBRK_Pos)
#define UART_CTRL_DATA9b_Pos		18		//1 9位数据位    0 8位数据位
#define UART_CTRL_DATA9b_Msk		(0x01 << UART_CTRL_DATA9b_Pos)
#define UART_CTRL_PARITY_Pos		19		//0 无奇偶校验    1 奇校验    3 偶校验    5 固定为1    7 固定为0
#define UART_CTRL_PARITY_Msk		(0x07 << UART_CTRL_PARITY_Pos)
#define UART_CTRL_STOP2b_Pos		22		//1 2位停止位    0 1位停止位
#define UART_CTRL_STOP2b_Msk		(0x03 << UART_CTRL_STOP2b_Pos)
#define UART_CTRL_TOTIME_Pos		24		//TimeOut 时长 = TOTIME/(BAUDRAUD/10) 秒
//#define UART_CTRL_TOTIME_Msk		(0xFF << UART_CTRL_TOTIME_Pos)	编译器警告： integer operation result is out of range
#define UART_CTRL_TOTIME_Msk		((uint32_t)0xFF << UART_CTRL_TOTIME_Pos)

#define UART_BAUD_BAUD_Pos			0		//串口波特率 = SYS_Freq/16/BAUD - 1
#define UART_BAUD_BAUD_Msk			(0x3FFF << UART_BAUD_BAUD_Pos)
#define UART_BAUD_TXD_Pos			14		//通过此位可直接读取串口TXD引脚上的电平
#define UART_BAUD_TXD_Msk			(0x01 << UART_BAUD_TXD_Pos)
#define UART_BAUD_RXD_Pos			15		//通过此位可直接读取串口RXD引脚上的电平
#define UART_BAUD_RXD_Msk			(0x01 << UART_BAUD_RXD_Pos)
#define UART_BAUD_RXTOIF_Pos		16		//接收&超时的中断标志 = RXIF | TOIF
#define UART_BAUD_RXTOIF_Msk		(0x01 << UART_BAUD_RXTOIF_Pos)
#define UART_BAUD_TXIF_Pos			17		//发送中断标志 = TXTHRF & TXIE
#define UART_BAUD_TXIF_Msk			(0x01 << UART_BAUD_TXIF_Pos)
#define UART_BAUD_BRKIF_Pos			18		//LIN Break Detect 中断标志，检测到LIN Break时若BRKIE=1，此位由硬件置位
#define UART_BAUD_BRKIF_Msk			(0x01 << UART_BAUD_BRKIF_Pos)
#define UART_BAUD_RXTHRF_Pos		19		//RX FIFO Threshold Flag，RX FIFO中数据达到设定个数（RXLVL >  RXTHR）时硬件置1
#define UART_BAUD_RXTHRF_Msk		(0x01 << UART_BAUD_RXTHRF_Pos)
#define UART_BAUD_TXTHRF_Pos		20		//TX FIFO Threshold Flag，TX FIFO中数据少于设定个数（TXLVL <= TXTHR）时硬件置1
#define UART_BAUD_TXTHRF_Msk		(0x01 << UART_BAUD_TXTHRF_Pos)
#define UART_BAUD_TOIF_Pos			21		//TimeOut 中断标志，超过 TOTIME/BAUDRAUD 秒没有接收到新的数据时若TOIE=1，此位由硬件置位
#define UART_BAUD_TOIF_Msk			(0x01 << UART_BAUD_TOIF_Pos)
#define UART_BAUD_RXIF_Pos			22		//接收中断标志 = RXTHRF & RXIE
#define UART_BAUD_RXIF_Msk			(0x01 << UART_BAUD_RXIF_Pos)

#define UART_FIFO_RXLVL_Pos			0		//RX FIFO Level，RX FIFO 中字符个数
#define UART_FIFO_RXLVL_Msk			(0xFF << UART_FIFO_RXLVL_Pos)
#define UART_FIFO_TXLVL_Pos			8		//TX FIFO Level，TX FIFO 中字符个数
#define UART_FIFO_TXLVL_Msk			(0xFF << UART_FIFO_TXLVL_Pos)
#define UART_FIFO_RXTHR_Pos			16		//RX FIFO Threshold，RX中断触发门限，中断使能时 RXLVL >  RXTHR 触发RX中断
#define UART_FIFO_RXTHR_Msk			(0xFF << UART_FIFO_RXTHR_Pos)
#define UART_FIFO_TXTHR_Pos			24		//TX FIFO Threshold，TX中断触发门限，中断使能时 TXLVL <= TXTHR 触发TX中断
//#define UART_FIFO_TXTHR_Msk			(0xFF << UART_FIFO_TXTHR_Pos)	编译器警告： integer operation result is out of range
#define UART_FIFO_TXTHR_Msk			((uint32_t)0xFF << UART_FIFO_TXTHR_Pos)




typedef struct {
	__IO uint32_t CTRL;

	__IO uint32_t DATA;

	__IO uint32_t STAT;

	__IO uint32_t IE;

	__IO uint32_t IF;
} SPI_TypeDef;


#define SPI_CTRL_CLKDIV_Pos			0		//Clock Divider, SPI工作时钟 = SYS_Freq/pow(2, CLKDIV+2)
#define SPI_CTRL_CLKDIV_Msk			(0x07 << SPI_CTRL_CLKDIV_Pos)
#define SPI_CTRL_EN_Pos				3
#define SPI_CTRL_EN_Msk				(0x01 << SPI_CTRL_EN_Pos)
#define SPI_CTRL_DSS_Pos			4		//Data Size Select, 取值3--15，表示4--16位
#define SPI_CTRL_DSS_Msk			(0x0F << SPI_CTRL_DSS_Pos)
#define SPI_CTRL_CPHA_Pos			8		//0 在SCLK的第一个跳变沿采样数据	1 在SCLK的第二个跳变沿采样数据
#define SPI_CTRL_CPHA_Msk			(0x01 << SPI_CTRL_CPHA_Pos)
#define SPI_CTRL_CPOL_Pos			9		//0 空闲状态下SCLK为低电平		  1 空闲状态下SCLK为高电平
#define SPI_CTRL_CPOL_Msk			(0x01 << SPI_CTRL_CPOL_Pos)
#define SPI_CTRL_FFS_Pos			10		//Frame Format Select, 0 SPI	1 TI SSI	2 SPI	3 SPI
#define SPI_CTRL_FFS_Msk			(0x03 << SPI_CTRL_FFS_Pos)
#define SPI_CTRL_MSTR_Pos			12		//Master, 1 主模式	0 从模式
#define SPI_CTRL_MSTR_Msk			(0x01 << SPI_CTRL_MSTR_Pos)
#define SPI_CTRL_FAST_Pos			13		//1 SPI工作时钟 = SYS_Freq/2    0 SPI工作时钟由SPI->CTRL.CLKDIV设置
#define SPI_CTRL_FAST_Msk			(0x01 << SPI_CTRL_FAST_Pos)
#define SPI_CTRL_DMAEN_Pos			14		//1 通过DMA CH0读写FIFO    0 通过MCU读写FIFO
#define SPI_CTRL_DMAEN_Msk			(0x01 << SPI_CTRL_DMAEN_Pos)
#define SPI_CTRL_FILTE_Pos			16		//1 对SPI输入信号进行去抖操作    0 对SPI输入信号不进行去抖操作
#define SPI_CTRL_FILTE_Msk			(0x01 << SPI_CTRL_FILTE_Pos)
#define SPI_CTRL_SSN_H_Pos			17		//0 传输过程中SSN始终为0    	 1 传输过程中每字符之间会将SSN拉高半个SCLK周期
#define SPI_CTRL_SSN_H_Msk			(0x01 << SPI_CTRL_SSN_H_Pos)

#define SPI_STAT_TC_Pos				0		//Transmit Complete，每传输完成一个数据帧由硬件置1，软件写1清零
#define SPI_STAT_TC_Msk				(0x01 << SPI_STAT_TC_Pos)
#define SPI_STAT_TFE_Pos			1		//发送FIFO Empty
#define SPI_STAT_TFE_Msk			(0x01 << SPI_STAT_TFE_Pos)
#define SPI_STAT_TFNF_Pos			2		//发送FIFO Not Full
#define SPI_STAT_TFNF_Msk			(0x01 << SPI_STAT_TFNF_Pos)
#define SPI_STAT_RFNE_Pos			3		//接收FIFO Not Empty
#define SPI_STAT_RFNE_Msk			(0x01 << SPI_STAT_RFNE_Pos)
#define SPI_STAT_RFF_Pos			4		//接收FIFO Full
#define SPI_STAT_RFF_Msk			(0x01 << SPI_STAT_RFF_Pos)
#define SPI_STAT_RFOVF_Pos			5		//接收FIFO Overflow
#define SPI_STAT_RFOVF_Msk			(0x01 << SPI_STAT_RFOVF_Pos)
#define SPI_STAT_TFLVL_Pos			6		//发送FIFO中数据个数， 0 TFNF=0时表示FIFO内有8个数据，TFNF=1时表示FIFO内有0个数据	1--7 FIFO内有1--7个数据
#define SPI_STAT_TFLVL_Msk			(0x07 << SPI_STAT_TFLVL_Pos)
#define SPI_STAT_RFLVL_Pos			9		//接收FIFO中数据个数， 0 RFF=1时表示FIFO内有8个数据， RFF=0时表示FIFO内有0个数据	1--7 FIFO内有1--7个数据
#define SPI_STAT_RFLVL_Msk			(0x07 << SPI_STAT_RFLVL_Pos)

#define SPI_IE_RFOVF_Pos			0
#define SPI_IE_RFOVF_Msk			(0x01 << SPI_IE_RFOVF_Pos)
#define SPI_IE_RFF_Pos				1
#define SPI_IE_RFF_Msk				(0x01 << SPI_IE_RFF_Pos)
#define SPI_IE_RFHF_Pos				2
#define SPI_IE_RFHF_Msk				(0x01 << SPI_IE_RFHF_Pos)
#define SPI_IE_TFE_Pos				3
#define SPI_IE_TFE_Msk				(0x01 << SPI_IE_TFE_Pos)
#define SPI_IE_TFHF_Pos				4
#define SPI_IE_TFHF_Msk				(0x01 << SPI_IE_TFHF_Pos)

#define SPI_IF_RFOVF_Pos			0		//写1清零
#define SPI_IF_RFOVF_Msk			(0x01 << SPI_IF_RFOVF_Pos)
#define SPI_IF_RFF_Pos				1
#define SPI_IF_RFF_Msk				(0x01 << SPI_IF_RFF_Pos)
#define SPI_IF_RFHF_Pos				2
#define SPI_IF_RFHF_Msk				(0x01 << SPI_IF_RFHF_Pos)
#define SPI_IF_TFE_Pos				3
#define SPI_IF_TFE_Msk				(0x01 << SPI_IF_TFE_Pos)
#define SPI_IF_TFHF_Pos				4
#define SPI_IF_TFHF_Msk				(0x01 << SPI_IF_TFHF_Pos)




typedef struct {
	__IO uint32_t CLKDIV;				   	//[15:0] 须将内部工作频率分到SCL频率的5倍，即CLKDIV = SYS_Freq/5/SCL_Freq - 1

	__IO uint32_t CTRL;

	__IO uint32_t MSTDAT;

	__IO uint32_t MSTCMD;
	
	__IO uint32_t SLVCR;
	
	__IO uint32_t SLVIF;
	
	__IO uint32_t SLVTX;
	
	__IO uint32_t SLVRX;
} I2C_TypeDef;


#define I2C_CTRL_MSTIE_Pos			6
#define I2C_CTRL_MSTIE_Msk			(0x01 << I2C_CTRL_MSTIE_Pos)
#define I2C_CTRL_EN_Pos				7
#define I2C_CTRL_EN_Msk				(0x01 << I2C_CTRL_EN_Pos)

#define I2C_MSTCMD_IF_Pos			0		//1 有等待处理的中断，写1清零	有两种情况下此位硬件置位：1、一个字节传输完成  2、总线访问权丢失
#define I2C_MSTCMD_IF_Msk			(0x01 << I2C_MSTCMD_IF_Pos)
#define I2C_MSTCMD_TIP_Pos			1		//Transmission In Process
#define I2C_MSTCMD_TIP_Msk			(0x01 << I2C_MSTCMD_TIP_Pos)
#define I2C_MSTCMD_ACK_Pos			3		//接收模式下，0 向发送端反馈ACK	1 向发送端反馈NACK
#define I2C_MSTCMD_ACK_Msk			(0x01 << I2C_MSTCMD_ACK_Pos)
#define I2C_MSTCMD_WR_Pos			4		//	  向Slave写数据时，把这一位写1，自动清零
#define I2C_MSTCMD_WR_Msk			(0x01 << I2C_MSTCMD_WR_Pos)
#define I2C_MSTCMD_RD_Pos			5		//写：从Slave读数据时，把这一位写1，自动清零	读：当I2C模块失去总线的访问权时硬件置1
#define I2C_MSTCMD_RD_Msk			(0x01 << I2C_MSTCMD_RD_Pos)
#define I2C_MSTCMD_BUSY_Pos			6		//读：当检测到START之后，这一位变1；当检测到STOP之后，这一位变0
#define I2C_MSTCMD_BUSY_Msk			(0x01 << I2C_MSTCMD_BUSY_Pos)
#define I2C_MSTCMD_STO_Pos			6		//写：产生STOP，自动清零
#define I2C_MSTCMD_STO_Msk			(0x01 << I2C_MSTCMD_STO_Pos)
#define I2C_MSTCMD_RXACK_Pos		7		//读：接收到的Slave的ACK位，0 收到ACK	1 收到NACK
#define I2C_MSTCMD_RXACK_Msk		(0x01 << I2C_MSTCMD_RXACK_Pos)
#define I2C_MSTCMD_STA_Pos			7		//写：产生START，自动清零
#define I2C_MSTCMD_STA_Msk			(0x01 << I2C_MSTCMD_STA_Pos)

#define I2C_SLVCR_IM_RXEND_Pos		0		//接收完成中断禁止
#define I2C_SLVCR_IM_RXEND_Msk		(0x01 << I2C_SLVCR_IM_RXEND_Pos)
#define I2C_SLVCR_IM_TXEND_Pos		1		//发送完成中断禁止
#define I2C_SLVCR_IM_TXEND_Msk		(0x01 << I2C_SLVCR_IM_TXEND_Pos)
#define I2C_SLVCR_IM_STADET_Pos		2		//检测到起始中断禁止
#define I2C_SLVCR_IM_STADET_Msk		(0x01 << I2C_SLVCR_IM_STADET_Pos)
#define I2C_SLVCR_IM_STODET_Pos		3		//检测到停止中断禁止
#define I2C_SLVCR_IM_STODET_Msk		(0x01 << I2C_SLVCR_IM_STODET_Pos)
#define I2C_SLVCR_IM_RDREQ_Pos		4		//接收到读请求中断禁止
#define I2C_SLVCR_IM_RDREQ_Msk		(0x01 << I2C_SLVCR_IM_RDREQ_Pos)
#define I2C_SLVCR_IM_WRREQ_Pos		5		//接收到写请求中断禁止
#define I2C_SLVCR_IM_WRREQ_Msk		(0x01 << I2C_SLVCR_IM_WRREQ_Pos)
#define I2C_SLVCR_ADDR7b_Pos		16		//1 7位地址模式    0 10位地址模式
#define I2C_SLVCR_ADDR7b_Msk		(0x01 << I2C_SLVCR_ADDR7b_Pos)
#define I2C_SLVCR_ACK_Pos			17		//1 应答ACK    0 应答NACK
#define I2C_SLVCR_ACK_Msk			(0x01 << I2C_SLVCR_ACK_Pos)
#define I2C_SLVCR_SLAVE_Pos			18		//1 从机模式   0 主机模式
#define I2C_SLVCR_SLAVE_Msk			(0x01 << I2C_SLVCR_SLAVE_Pos)
#define I2C_SLVCR_DEBOUNCE_Pos		19		//去抖动使能
#define I2C_SLVCR_DEBOUNCE_Msk		(0x01 << I2C_SLVCR_DEBOUNCE_Pos)
#define I2C_SLVCR_ADDR_Pos			20		//从机地址
#define I2C_SLVCR_ADDR_Msk			(0x3FF << I2C_SLVCR_ADDR_Pos)

#define I2C_SLVIF_RXEND_Pos			0		//接收完成中断标志，写1清零
#define I2C_SLVIF_RXEND_Msk			(0x01 << I2C_SLVIF_RXEND_Pos)
#define I2C_SLVIF_TXEND_Pos			1		//发送完成中断标志，写1清零
#define I2C_SLVIF_TXEND_Msk			(0x01 << I2C_SLVIF_TXEND_Pos)
#define I2C_SLVIF_STADET_Pos		2		//检测到起始中断标志，写1清零
#define I2C_SLVIF_STADET_Msk		(0x01 << I2C_SLVIF_STADET_Pos)
#define I2C_SLVIF_STODET_Pos		3		//检测到停止中断标志，写1清零
#define I2C_SLVIF_STODET_Msk		(0x01 << I2C_SLVIF_STODET_Pos)
#define I2C_SLVIF_RDREQ_Pos			4		//接收到读请求中断标志
#define I2C_SLVIF_RDREQ_Msk			(0x01 << I2C_SLVIF_RDREQ_Pos)
#define I2C_SLVIF_WRREQ_Pos			5		//接收到写请求中断标志
#define I2C_SLVIF_WRREQ_Msk			(0x01 << I2C_SLVIF_WRREQ_Pos)
#define I2C_SLVIF_ACTIVE_Pos		6		//slave 有效
#define I2C_SLVIF_ACTIVE_Msk		(0x01 << I2C_SLVIF_ACTIVE_Pos)




typedef struct {
	__IO uint32_t CTRL;
	
	__IO uint32_t START;
	
	__IO uint32_t IE;
	
	__IO uint32_t IF;
	
	struct {
		__IO uint32_t STAT;
		
		__IO uint32_t DATA;
		
			 uint32_t RESERVED[2];
	} CH[8];
	
	__IO uint32_t FFSTAT;				   //FIFO STAT
    
	__IO uint32_t FFDATA;				   //FIFO DATA
	
	     uint32_t RESERVED[2];
	
	__IO uint32_t CTRL1;
	
	__IO uint32_t CTRL2;
	
		 uint32_t RESERVED2[18];
	
	__IO uint32_t DEBUG;
	
	__IO uint32_t CALIBSET;
	
	__IO uint32_t CALIBEN;
} ADC_TypeDef;


#define ADC_CTRL_CH0_Pos			0		//通道选中
#define ADC_CTRL_CH0_Msk			(0x01 << ADC_CTRL_CH0_Pos)
#define ADC_CTRL_CH1_Pos			1
#define ADC_CTRL_CH1_Msk			(0x01 << ADC_CTRL_CH1_Pos)
#define ADC_CTRL_CH2_Pos			2
#define ADC_CTRL_CH2_Msk			(0x01 << ADC_CTRL_CH2_Pos)
#define ADC_CTRL_CH3_Pos			3
#define ADC_CTRL_CH3_Msk			(0x01 << ADC_CTRL_CH3_Pos)
#define ADC_CTRL_CH4_Pos			4
#define ADC_CTRL_CH4_Msk			(0x01 << ADC_CTRL_CH4_Pos)
#define ADC_CTRL_CH5_Pos			5
#define ADC_CTRL_CH5_Msk			(0x01 << ADC_CTRL_CH5_Pos)
#define ADC_CTRL_CH6_Pos			6
#define ADC_CTRL_CH6_Msk			(0x01 << ADC_CTRL_CH6_Pos)
#define ADC_CTRL_CH7_Pos			7
#define ADC_CTRL_CH7_Msk			(0x01 << ADC_CTRL_CH7_Pos)
#define ADC_CTRL_AVG_Pos			8		//0 1次采样	  1 2次采样取平均值	  3 4次采样取平均值	  7 8次采样取平均值	  15 16次采样取平均值
#define ADC_CTRL_AVG_Msk			(0x0F << ADC_CTRL_AVG_Pos)
#define ADC_CTRL_EN_Pos				12
#define ADC_CTRL_EN_Msk				(0x01 << ADC_CTRL_EN_Pos)
#define ADC_CTRL_CONT_Pos			13		//Continuous conversion，只在软件启动模式下有效，0 单次转换，转换完成后START位自动清除停止转换
#define ADC_CTRL_CONT_Msk			(0x01 << ADC_CTRL_CONT_Pos)							//   1 连续转换，启动后一直采样、转换，直到软件清除START位
#define ADC_CTRL_TRIG_Pos			14		//转换触发方式：0 软件启动转换	  1 PWM触发	  2 TIMR2触发	 3 TIMR3触发
#define ADC_CTRL_TRIG_Msk			(0x03 << ADC_CTRL_TRIG_Pos)
#define ADC_CTRL_RST_Pos			16
#define ADC_CTRL_RST_Msk			(0x01 << ADC_CTRL_RST_Pos)
#define ADC_CTRL_DMAEN_Pos			17		//只能在只选中一个通道的时候使用DMA功能，且RES2FF必须置1，DMA CH1 通过读取FFDATA寄存器读取转换结果
#define ADC_CTRL_DMAEN_Msk			(0x01 << ADC_CTRL_DMAEN_Pos)
#define ADC_CTRL_RES2FF_Pos			18		//Result to FIFO	1 转换结果进入FIFO	 0 转换结果进入相应CH的DATA寄存器
#define ADC_CTRL_RES2FF_Msk			(0x01 << ADC_CTRL_RES2FF_Pos)

#define ADC_START_GO_Pos			0		//软件触发模式下，写1启动ADC采样和转换，在单次模式下转换完成后硬件自动清零，在扫描模式下必须软件写0停止ADC转换
#define ADC_START_GO_Msk			(0x01 << ADC_START_GO_Pos)
#define ADC_START_BUSY_Pos			4
#define ADC_START_BUSY_Msk			(0x01 << ADC_START_BUSY_Pos)

#define ADC_IE_CH0EOC_Pos			0		//End Of Convertion
#define ADC_IE_CH0EOC_Msk			(0x01 << ADC_IE_CH0EOC_Pos)
#define ADC_IE_CH0OVF_Pos			1		//Overflow
#define ADC_IE_CH0OVF_Msk			(0x01 << ADC_IE_CH0OVF_Pos)
#define ADC_IE_CH1EOC_Pos			2
#define ADC_IE_CH1EOC_Msk			(0x01 << ADC_IE_CH1EOC_Pos)
#define ADC_IE_CH1OVF_Pos			3
#define ADC_IE_CH1OVF_Msk			(0x01 << ADC_IE_CH1OVF_Pos)
#define ADC_IE_CH2EOC_Pos			4
#define ADC_IE_CH2EOC_Msk			(0x01 << ADC_IE_CH2EOC_Pos)
#define ADC_IE_CH2OVF_Pos			5
#define ADC_IE_CH2OVF_Msk			(0x01 << ADC_IE_CH2OVF_Pos)
#define ADC_IE_CH3EOC_Pos			6
#define ADC_IE_CH3EOC_Msk			(0x01 << ADC_IE_CH3EOC_Pos)
#define ADC_IE_CH3OVF_Pos			7
#define ADC_IE_CH3OVF_Msk			(0x01 << ADC_IE_CH3OVF_Pos)
#define ADC_IE_CH4EOC_Pos			8
#define ADC_IE_CH4EOC_Msk			(0x01 << ADC_IE_CH4EOC_Pos)
#define ADC_IE_CH4OVF_Pos			9
#define ADC_IE_CH4OVF_Msk			(0x01 << ADC_IE_CH4OVF_Pos)
#define ADC_IE_CH5EOC_Pos			10
#define ADC_IE_CH5EOC_Msk			(0x01 << ADC_IE_CH5EOC_Pos)
#define ADC_IE_CH5OVF_Pos			11
#define ADC_IE_CH5OVF_Msk			(0x01 << ADC_IE_CH5OVF_Pos)
#define ADC_IE_CH6EOC_Pos			12
#define ADC_IE_CH6EOC_Msk			(0x01 << ADC_IE_CH6EOC_Pos)
#define ADC_IE_CH6OVF_Pos			13
#define ADC_IE_CH6OVF_Msk			(0x01 << ADC_IE_CH6OVF_Pos)
#define ADC_IE_CH7EOC_Pos			14
#define ADC_IE_CH7EOC_Msk			(0x01 << ADC_IE_CH7EOC_Pos)
#define ADC_IE_CH7OVF_Pos			15
#define ADC_IE_CH7OVF_Msk			(0x01 << ADC_IE_CH7OVF_Pos)
#define ADC_IE_FIFOOV_Pos			16
#define ADC_IE_FIFOOV_Msk			(0x01 << ADC_IE_FIFOOV_Pos)
#define ADC_IE_FIFOHF_Pos			17
#define ADC_IE_FIFOHF_Msk			(0x01 << ADC_IE_FIFOHF_Pos)
#define ADC_IE_FIFOF_Pos			18
#define ADC_IE_FIFOF_Msk			(0x01 << ADC_IE_FIFOF_Pos)

#define ADC_IF_CH0EOC_Pos			0		//写1清零
#define ADC_IF_CH0EOC_Msk			(0x01 << ADC_IF_CH0EOC_Pos)
#define ADC_IF_CH0OVF_Pos			1
#define ADC_IF_CH0OVF_Msk			(0x01 << ADC_IF_CH0OVF_Pos)
#define ADC_IF_CH1EOC_Pos			2
#define ADC_IF_CH1EOC_Msk			(0x01 << ADC_IF_CH1EOC_Pos)
#define ADC_IF_CH1OVF_Pos			3
#define ADC_IF_CH1OVF_Msk			(0x01 << ADC_IF_CH1OVF_Pos)
#define ADC_IF_CH2EOC_Pos			4
#define ADC_IF_CH2EOC_Msk			(0x01 << ADC_IF_CH2EOC_Pos)
#define ADC_IF_CH2OVF_Pos			5
#define ADC_IF_CH2OVF_Msk			(0x01 << ADC_IF_CH2OVF_Pos)
#define ADC_IF_CH3EOC_Pos			6
#define ADC_IF_CH3EOC_Msk			(0x01 << ADC_IF_CH3EOC_Pos)
#define ADC_IF_CH3OVF_Pos			7
#define ADC_IF_CH3OVF_Msk			(0x01 << ADC_IF_CH3OVF_Pos)
#define ADC_IF_CH4EOC_Pos			8
#define ADC_IF_CH4EOC_Msk			(0x01 << ADC_IF_CH4EOC_Pos)
#define ADC_IF_CH4OVF_Pos			9
#define ADC_IF_CH4OVF_Msk			(0x01 << ADC_IF_CH4OVF_Pos)
#define ADC_IF_CH5EOC_Pos			10
#define ADC_IF_CH5EOC_Msk			(0x01 << ADC_IF_CH5EOC_Pos)
#define ADC_IF_CH5OVF_Pos			11
#define ADC_IF_CH5OVF_Msk			(0x01 << ADC_IF_CH5OVF_Pos)
#define ADC_IF_CH6EOC_Pos			12
#define ADC_IF_CH6EOC_Msk			(0x01 << ADC_IF_CH6EOC_Pos)
#define ADC_IF_CH6OVF_Pos			13
#define ADC_IF_CH6OVF_Msk			(0x01 << ADC_IF_CH6OVF_Pos)
#define ADC_IF_CH7EOC_Pos			14
#define ADC_IF_CH7EOC_Msk			(0x01 << ADC_IF_CH7EOC_Pos)
#define ADC_IF_CH7OVF_Pos			15
#define ADC_IF_CH7OVF_Msk			(0x01 << ADC_IF_CH7OVF_Pos)
#define ADC_IF_FIFOOV_Pos			16
#define ADC_IF_FIFOOV_Msk			(0x01 << ADC_IF_FIFOOV_Pos)
#define ADC_IF_FIFOHF_Pos			17
#define ADC_IF_FIFOHF_Msk			(0x01 << ADC_IF_FIFOHF_Pos)
#define ADC_IF_FIFOF_Pos			18
#define ADC_IF_FIFOF_Msk			(0x01 << ADC_IF_FIFOF_Pos)

#define ADC_STAT_EOC_Pos			0		//写1清零
#define ADC_STAT_EOC_Msk			(0x01 << ADC_STAT_EOC_Pos)
#define ADC_STAT_OVF_Pos			1		//读数据寄存器清除
#define ADC_STAT_OVF_Msk			(0x01 << ADC_STAT_OVF_Pos)

#define ADC_DATA_VALUE_Pos			0		//溢出后，再次转换的数据会覆盖旧数据
#define ADC_DATA_VALUE_Msk			(0xFFF << ADC_DATA_VALUE_Pos)
#define ADC_DATA_CHNUM_Pos			12
#define ADC_DATA_CHNUM_Msk			(0x07 << ADC_DATA_CHNUM_Pos)

#define ADC_FFSTAT_OVF_Pos			0
#define ADC_FFSTAT_OVF_Msk			(0x01 << ADC_FFSTAT_OVF_Pos)
#define ADC_FFSTAT_HFULL_Pos		1
#define ADC_FFSTAT_HFULL_Msk		(0x01 << ADC_FFSTAT_HFULL_Pos)
#define ADC_FFSTAT_FULL_Pos			2
#define ADC_FFSTAT_FULL_Msk			(0x01 << ADC_FFSTAT_FULL_Pos)
#define ADC_FFSTAT_EMPTY_Pos		3
#define ADC_FFSTAT_EMPTY_Msk		(0x01 << ADC_FFSTAT_EMPTY_Pos)

#define ADC_FFDATA_VALUE_Pos		0		//溢出后，再次转换的数据会被丢掉
#define ADC_FFDATA_VALUE_Msk		(0xFFF << ADC_FFDATA_VALUE_Pos)
#define ADC_FFDATA_CHNUM_Pos		12
#define ADC_FFDATA_CHNUM_Msk		(0x07 << ADC_FFDATA_CHNUM_Pos)

#define ADC_CTRL1_CLKSRC_Pos		0
#define ADC_CTRL1_CLKSRC_Msk		(0x01 << ADC_CTRL1_CLKSRC_Pos)

#define ADC_CTRL2_ADCEVCM_Pos		1		//ADC External VCM，ADC与PGA输出共模电平选择
#define ADC_CTRL2_ADCEVCM_Msk		(0x01 << ADC_CTRL2_ADCEVCM_Pos)
#define ADC_CTRL2_PGAEVCM_Pos		2		//PGA External VCM，PGA输入共模电平选择
#define ADC_CTRL2_PGAEVCM_Msk		(0x01 << ADC_CTRL2_PGAEVCM_Pos)
#define ADC_CTRL2_PGAGAIN_Pos		3
#define ADC_CTRL2_PGAGAIN_Msk		(0x07 << ADC_CTRL2_PGAGAIN_Pos)
#define ADC_CTRL2_VCMSEL_Pos		8
#define ADC_CTRL2_VCMSEL_Msk		(0x07 << ADC_CTRL2_VCMSEL_Pos)
#define ADC_CTRL2_CLKDIV2_Pos		24
#define ADC_CTRL2_CLKDIV2_Msk		(0x1F << ADC_CTRL2_CLKDIV2_Pos)
#define ADC_CTRL2_CLKDIV1_Pos		29
#define ADC_CTRL2_CLKDIV1_Msk		(0x03 << ADC_CTRL2_CLKDIV1_Pos)

#define ADC_CALIBSET_OFFSET_Pos		0
#define ADC_CALIBSET_OFFSET_Msk		(0x1FF<< ADC_CALIBSET_OFFSET_Pos)
#define ADC_CALIBSET_K_Pos			16
#define ADC_CALIBSET_K_Msk			(0x1FF<< ADC_CALIBSET_K_Pos)

#define ADC_CALIBEN_OFFSET_Pos		0
#define ADC_CALIBEN_OFFSET_Msk		(0x01 << ADC_CALIBEN_OFFSET_Pos)
#define ADC_CALIBEN_K_Pos			1
#define ADC_CALIBEN_K_Msk			(0x01 << ADC_CALIBEN_K_Pos)




typedef struct {
	__IO uint32_t MODE;                     //0 普通模式，A、B两路输出互相独立
                                            //1 互补模式，A、B两路输出都由PERA、HIGHA控制，B路输出与A路输出极性相反，且DZA、DZB控制A、B路输出上升沿推迟时间
                                            //2 单次模式，同普通模式，但一个周期后自动停止
                                            //3 对称模式，A、B两路输出互相独立，以两个计数周期产生一个波形输出周期，分辨率提升一倍、频率降低一倍
                                            //4 对称互补模式，对称模式和互补模式的综合
	
	__IO uint32_t PERA;                     //[15:0] 周期
	
	__IO uint32_t HIGHA;                    //[15:0] 高电平持续时长
	
	__IO uint32_t DZA;                      //[5:0] 死区，即上升沿推迟时长，必须小于HIGHA
	
	__IO uint32_t PERB;
	
	__IO uint32_t HIGHB;
	
	__IO uint32_t DZB;
	
	__IO uint32_t INIOUT;                   //Init Output level，初始输出电平
} PWM_TypeDef;


#define PWM_INIOUT_PWMA_Pos		0		
#define PWM_INIOUT_PWMA_Msk		(0x01 << PWM_INIOUT_PWMA_Pos)
#define PWM_INIOUT_PWMB_Pos		1		
#define PWM_INIOUT_PWMB_Msk		(0x01 << PWM_INIOUT_PWMB_Pos)


typedef struct {
	__IO uint32_t CLKDIV;
    
	     uint32_t RESERVED[3];
    
	__IO uint32_t FORCEH;
    
    __IO uint32_t ADTRG0A;
    __IO uint32_t ADTRG0B;
    
    __IO uint32_t ADTRG1A;
    __IO uint32_t ADTRG1B;
    
    __IO uint32_t ADTRG2A;
    __IO uint32_t ADTRG2B;
    
	     uint32_t RESERVED2[9];
    
	__IO uint32_t HALT;						//刹车控制
    
	__IO uint32_t CHEN;
    
	__IO uint32_t IE;
    
	__IO uint32_t IF;
    
	__IO uint32_t IMSK;
    
	__IO uint32_t IRAWST;
} PWMG_TypeDef;


#define PWMG_FORCEH_PWM0_Pos		0		
#define PWMG_FORCEH_PWM0_Msk		(0x01 << PWMG_FORCEH_PWM0_Pos)
#define PWMG_FORCEH_PWM1_Pos		1		
#define PWMG_FORCEH_PWM1_Msk		(0x01 << PWMG_FORCEH_PWM1_Pos)
#define PWMG_FORCEH_PWM2_Pos		2		
#define PWMG_FORCEH_PWM2_Msk		(0x01 << PWMG_FORCEH_PWM2_Pos)

#define PWMG_ADTRG0A_VALUE_Pos		0		
#define PWMG_ADTRG0A_VALUE_Msk		(0xFFFF << PWMG_ADTRG0A_VALUE_Pos)
#define PWMG_ADTRG0A_EVEN_Pos		16		
#define PWMG_ADTRG0A_EVEN_Msk		(0x01 << PWMG_ADTRG0A_EVEN_Pos)
#define PWMG_ADTRG0A_EN_Pos		    17		
#define PWMG_ADTRG0A_EN_Msk		    (0x01 << PWMG_ADTRG0A_EN_Pos)
#define PWMG_ADTRG0B_VALUE_Pos		0		
#define PWMG_ADTRG0B_VALUE_Msk		(0xFFFF << PWMG_ADTRG0B_VALUE_Pos)
#define PWMG_ADTRG0B_EVEN_Pos		16		
#define PWMG_ADTRG0B_EVEN_Msk		(0x01 << PWMG_ADTRG0B_EVEN_Pos)
#define PWMG_ADTRG0B_EN_Pos		    17		
#define PWMG_ADTRG0B_EN_Msk		    (0x01 << PWMG_ADTRG0B_EN_Pos)

#define PWMG_ADTRG1A_VALUE_Pos		0		
#define PWMG_ADTRG1A_VALUE_Msk		(0xFFFF << PWMG_ADTRG1A_VALUE_Pos)
#define PWMG_ADTRG1A_EVEN_Pos		16		
#define PWMG_ADTRG1A_EVEN_Msk		(0x01 << PWMG_ADTRG1A_EVEN_Pos)
#define PWMG_ADTRG1A_EN_Pos		    17		
#define PWMG_ADTRG1A_EN_Msk		    (0x01 << PWMG_ADTRG1A_EN_Pos)
#define PWMG_ADTRG1B_VALUE_Pos		0		
#define PWMG_ADTRG1B_VALUE_Msk		(0xFFFF << PWMG_ADTRG1B_VALUE_Pos)
#define PWMG_ADTRG1B_EVEN_Pos		16		
#define PWMG_ADTRG1B_EVEN_Msk		(0x01 << PWMG_ADTRG1B_EVEN_Pos)
#define PWMG_ADTRG1B_EN_Pos		    17		
#define PWMG_ADTRG1B_EN_Msk		    (0x01 << PWMG_ADTRG1B_EN_Pos)

#define PWMG_ADTRG2A_VALUE_Pos		0		
#define PWMG_ADTRG2A_VALUE_Msk		(0xFFFF << PWMG_ADTRG2A_VALUE_Pos)
#define PWMG_ADTRG2A_EVEN_Pos		16		
#define PWMG_ADTRG2A_EVEN_Msk		(0x01 << PWMG_ADTRG2A_EVEN_Pos)
#define PWMG_ADTRG2A_EN_Pos		    17		
#define PWMG_ADTRG2A_EN_Msk		    (0x01 << PWMG_ADTRG2A_EN_Pos)
#define PWMG_ADTRG2B_VALUE_Pos		0		
#define PWMG_ADTRG2B_VALUE_Msk		(0xFFFF << PWMG_ADTRG2B_VALUE_Pos)
#define PWMG_ADTRG2B_EVEN_Pos		16		
#define PWMG_ADTRG2B_EVEN_Msk		(0x01 << PWMG_ADTRG2B_EVEN_Pos)
#define PWMG_ADTRG2B_EN_Pos		    17		
#define PWMG_ADTRG2B_EN_Msk		    (0x01 << PWMG_ADTRG2B_EN_Pos)

#define PWMG_HALT_EN_Pos		    0		
#define PWMG_HALT_EN_Msk		    (0x01 << PWMG_HALT_EN_Pos)
#define PWMG_HALT_PWM0_Pos		    1		
#define PWMG_HALT_PWM0_Msk		    (0x01 << PWMG_HALT_PWM0_Pos)
#define PWMG_HALT_PWM1_Pos		    2		
#define PWMG_HALT_PWM1_Msk		    (0x01 << PWMG_HALT_PWM1_Pos)
#define PWMG_HALT_PWM2_Pos		    3		
#define PWMG_HALT_PWM2_Msk		    (0x01 << PWMG_HALT_PWM2_Pos)
#define PWMG_HALT_STOPCNT_Pos		7		
#define PWMG_HALT_STOPCNT_Msk		(0x01 << PWMG_HALT_STOPCNT_Pos)
#define PWMG_HALT_VALIDI_Pos		8		
#define PWMG_HALT_VALIDI_Msk		(0x01 << PWMG_HALT_VALIDI_Pos)
#define PWMG_HALT_VALIDO_Pos		9		
#define PWMG_HALT_VALIDO_Msk		(0x01 << PWMG_HALT_VALIDO_Pos)
#define PWMG_HALT_STAT_Pos		    10		
#define PWMG_HALT_STAT_Msk		    (0x01 << PWMG_HALT_STAT_Pos)

#define PWMG_CHEN_PWM0A_Pos		    0		
#define PWMG_CHEN_PWM0A_Msk		    (0x01 << PWMG_CHEN_PWM0A_Pos)
#define PWMG_CHEN_PWM0B_Pos		    1		
#define PWMG_CHEN_PWM0B_Msk		    (0x01 << PWMG_CHEN_PWM0B_Pos)
#define PWMG_CHEN_PWM1A_Pos		    2		
#define PWMG_CHEN_PWM1A_Msk		    (0x01 << PWMG_CHEN_PWM1A_Pos)
#define PWMG_CHEN_PWM1B_Pos		    3		
#define PWMG_CHEN_PWM1B_Msk		    (0x01 << PWMG_CHEN_PWM1B_Pos)
#define PWMG_CHEN_PWM2A_Pos		    4		
#define PWMG_CHEN_PWM2A_Msk		    (0x01 << PWMG_CHEN_PWM2A_Pos)
#define PWMG_CHEN_PWM2B_Pos		    5		
#define PWMG_CHEN_PWM2B_Msk		    (0x01 << PWMG_CHEN_PWM2B_Pos)

#define PWMG_IE_NEWP0A_Pos			0		
#define PWMG_IE_NEWP0A_Msk			(0x01 << PWMG_IE_NEWP0A_Pos)
#define PWMG_IE_NEWP0B_Pos			1		
#define PWMG_IE_NEWP0B_Msk			(0x01 << PWMG_IE_NEWP0B_Pos)
#define PWMG_IE_NEWP1A_Pos			2		
#define PWMG_IE_NEWP1A_Msk			(0x01 << PWMG_IE_NEWP1A_Pos)
#define PWMG_IE_NEWP1B_Pos			3		
#define PWMG_IE_NEWP1B_Msk			(0x01 << PWMG_IE_NEWP1B_Pos)
#define PWMG_IE_NEWP2A_Pos			4		
#define PWMG_IE_NEWP2A_Msk			(0x01 << PWMG_IE_NEWP2A_Pos)
#define PWMG_IE_NEWP2B_Pos			5		
#define PWMG_IE_NEWP2B_Msk			(0x01 << PWMG_IE_NEWP2B_Pos)
#define PWMG_IE_HEND0A_Pos			12		
#define PWMG_IE_HEND0A_Msk			(0x01 << PWMG_IE_HEND0A_Pos)
#define PWMG_IE_HEND0B_Pos			13		
#define PWMG_IE_HEND0B_Msk			(0x01 << PWMG_IE_HEND0B_Pos)
#define PWMG_IE_HEND1A_Pos			14		
#define PWMG_IE_HEND1A_Msk			(0x01 << PWMG_IE_HEND1A_Pos)
#define PWMG_IE_HEND1B_Pos			15		
#define PWMG_IE_HEND1B_Msk			(0x01 << PWMG_IE_HEND1B_Pos)
#define PWMG_IE_HEND2A_Pos			16		
#define PWMG_IE_HEND2A_Msk			(0x01 << PWMG_IE_HEND2A_Pos)
#define PWMG_IE_HEND2B_Pos			17		
#define PWMG_IE_HEND2B_Msk			(0x01 << PWMG_IE_HEND2B_Pos)
#define PWMG_IE_HALT_Pos			24		
#define PWMG_IE_HALT_Msk			(0x01 << PWMG_IE_HALT_Pos)

#define PWMG_IF_NEWP0A_Pos			0		
#define PWMG_IF_NEWP0A_Msk			(0x01 << PWMG_IF_NEWP0A_Pos)
#define PWMG_IF_NEWP0B_Pos			1		
#define PWMG_IF_NEWP0B_Msk			(0x01 << PWMG_IF_NEWP0B_Pos)
#define PWMG_IF_NEWP1A_Pos			2		
#define PWMG_IF_NEWP1A_Msk			(0x01 << PWMG_IF_NEWP1A_Pos)
#define PWMG_IF_NEWP1B_Pos			3		
#define PWMG_IF_NEWP1B_Msk			(0x01 << PWMG_IF_NEWP1B_Pos)
#define PWMG_IF_NEWP2A_Pos			4		
#define PWMG_IF_NEWP2A_Msk			(0x01 << PWMG_IF_NEWP2A_Pos)
#define PWMG_IF_NEWP2B_Pos			5		
#define PWMG_IF_NEWP2B_Msk			(0x01 << PWMG_IF_NEWP2B_Pos)
#define PWMG_IF_HEND0A_Pos			12		
#define PWMG_IF_HEND0A_Msk			(0x01 << PWMG_IF_HEND0A_Pos)
#define PWMG_IF_HEND0B_Pos			13		
#define PWMG_IF_HEND0B_Msk			(0x01 << PWMG_IF_HEND0B_Pos)
#define PWMG_IF_HEND1A_Pos			14		
#define PWMG_IF_HEND1A_Msk			(0x01 << PWMG_IF_HEND1A_Pos)
#define PWMG_IF_HEND1B_Pos			15		
#define PWMG_IF_HEND1B_Msk			(0x01 << PWMG_IF_HEND1B_Pos)
#define PWMG_IF_HEND2A_Pos			16		
#define PWMG_IF_HEND2A_Msk			(0x01 << PWMG_IF_HEND2A_Pos)
#define PWMG_IF_HEND2B_Pos			17		
#define PWMG_IF_HEND2B_Msk			(0x01 << PWMG_IF_HEND2B_Pos)
#define PWMG_IF_HALT_Pos			24		
#define PWMG_IF_HALT_Msk			(0x01 << PWMG_IF_HALT_Pos)

#define PWMG_IMSK_NEWP0A_Pos		0		
#define PWMG_IMSK_NEWP0A_Msk		(0x01 << PWMG_IMSK_NEWP0A_Pos)
#define PWMG_IMSK_NEWP0B_Pos		1		
#define PWMG_IMSK_NEWP0B_Msk		(0x01 << PWMG_IMSK_NEWP0B_Pos)
#define PWMG_IMSK_NEWP1A_Pos		2		
#define PWMG_IMSK_NEWP1A_Msk		(0x01 << PWMG_IMSK_NEWP1A_Pos)
#define PWMG_IMSK_NEWP1B_Pos		3		
#define PWMG_IMSK_NEWP1B_Msk		(0x01 << PWMG_IMSK_NEWP1B_Pos)
#define PWMG_IMSK_NEWP2A_Pos		4		
#define PWMG_IMSK_NEWP2A_Msk		(0x01 << PWMG_IMSK_NEWP2A_Pos)
#define PWMG_IMSK_NEWP2B_Pos		5		
#define PWMG_IMSK_NEWP2B_Msk		(0x01 << PWMG_IMSK_NEWP2B_Pos)
#define PWMG_IMSK_HEND0A_Pos		12		
#define PWMG_IMSK_HEND0A_Msk		(0x01 << PWMG_IMSK_HEND0A_Pos)
#define PWMG_IMSK_HEND0B_Pos		13		
#define PWMG_IMSK_HEND0B_Msk		(0x01 << PWMG_IMSK_HEND0B_Pos)
#define PWMG_IMSK_HEND1A_Pos		14		
#define PWMG_IMSK_HEND1A_Msk		(0x01 << PWMG_IMSK_HEND1A_Pos)
#define PWMG_IMSK_HEND1B_Pos		15		
#define PWMG_IMSK_HEND1B_Msk		(0x01 << PWMG_IMSK_HEND1B_Pos)
#define PWMG_IMSK_HEND2A_Pos		16		
#define PWMG_IMSK_HEND2A_Msk		(0x01 << PWMG_IMSK_HEND2A_Pos)
#define PWMG_IMSK_HEND2B_Pos		17		
#define PWMG_IMSK_HEND2B_Msk		(0x01 << PWMG_IMSK_HEND2B_Pos)
#define PWMG_IMSK_HALT_Pos		    24		
#define PWMG_IMSK_HALT_Msk		    (0x01 << PWMG_IMSK_HALT_Pos)

#define PWMG_IRAWST_NEWP0A_Pos		0		//写1清零
#define PWMG_IRAWST_NEWP0A_Msk		(0x01 << PWMG_IRAWST_NEWP0A_Pos)
#define PWMG_IRAWST_NEWP0B_Pos		1		//写1清零
#define PWMG_IRAWST_NEWP0B_Msk		(0x01 << PWMG_IRAWST_NEWP0B_Pos)
#define PWMG_IRAWST_NEWP1A_Pos		2		//写1清零
#define PWMG_IRAWST_NEWP1A_Msk		(0x01 << PWMG_IRAWST_NEWP1A_Pos)
#define PWMG_IRAWST_NEWP1B_Pos		3		//写1清零
#define PWMG_IRAWST_NEWP1B_Msk		(0x01 << PWMG_IRAWST_NEWP1B_Pos)
#define PWMG_IRAWST_NEWP2A_Pos		4		//写1清零
#define PWMG_IRAWST_NEWP2A_Msk		(0x01 << PWMG_IRAWST_NEWP2A_Pos)
#define PWMG_IRAWST_NEWP2B_Pos		5		//写1清零
#define PWMG_IRAWST_NEWP2B_Msk		(0x01 << PWMG_IRAWST_NEWP2B_Pos)
#define PWMG_IRAWST_HEND0A_Pos		12		//写1清零
#define PWMG_IRAWST_HEND0A_Msk		(0x01 << PWMG_IRAWST_HEND0A_Pos)
#define PWMG_IRAWST_HEND0B_Pos		13		//写1清零
#define PWMG_IRAWST_HEND0B_Msk		(0x01 << PWMG_IRAWST_HEND0B_Pos)
#define PWMG_IRAWST_HEND1A_Pos		14		//写1清零
#define PWMG_IRAWST_HEND1A_Msk		(0x01 << PWMG_IRAWST_HEND1A_Pos)
#define PWMG_IRAWST_HEND1B_Pos		15		//写1清零
#define PWMG_IRAWST_HEND1B_Msk		(0x01 << PWMG_IRAWST_HEND1B_Pos)
#define PWMG_IRAWST_HEND2A_Pos		16		//写1清零
#define PWMG_IRAWST_HEND2A_Msk		(0x01 << PWMG_IRAWST_HEND2A_Pos)
#define PWMG_IRAWST_HEND2B_Pos		17		//写1清零
#define PWMG_IRAWST_HEND2B_Msk		(0x01 << PWMG_IRAWST_HEND2B_Pos)
#define PWMG_IRAWST_HALT_Pos		24		//写1清零
#define PWMG_IRAWST_HALT_Msk		(0x01 << PWMG_IRAWST_HALT_Pos)




typedef struct {
	__IO uint32_t EN;
    
	__IO uint32_t IE;						//只有IE[n]为1时，IF[n]在DMA传输结束时才能变为1
    
	__IO uint32_t IM;						//只有IM[n]为0时，IF[n]变成1时才能触发DMA中断
    
	__IO uint32_t IF;
    
	struct {
		__IO uint32_t CR;
		__IO uint32_t SRC;					//源地址
		__IO uint32_t DST;					//目的地址
	} CH[6];								//[0] SPI发送    [1] SPI接收    [2] 读ADC通道    [5] 读CAN通道
} DMA_TypeDef;


#define DMA_IE_CAN_Pos		    	0		//读CAN通道中断使能		
#define DMA_IE_CAN_Msk		    	(0x01 << DMA_IE_CAN_Pos)
#define DMA_IE_ADC_Pos			    2		//读ADC通道中断使能
#define DMA_IE_ADC_Msk			    (0x01 << DMA_IE_ADC_Pos)
#define DMA_IE_SPIRX_Pos			4		//读SPI通道中断使能
#define DMA_IE_SPIRX_Msk			(0x01 << DMA_IE_SPIRX_Pos)
#define DMA_IE_SPITX_Pos			5		//写SPI通道中断使能
#define DMA_IE_SPITX_Msk			(0x01 << DMA_IE_SPITX_Pos)

#define DMA_IM_CAN_Pos		    	0
#define DMA_IM_CAN_Msk		    	(0x01 << DMA_IM_CAN_Pos)
#define DMA_IM_ADC_Pos			    2
#define DMA_IM_ADC_Msk			    (0x01 << DMA_IM_ADC_Pos)
#define DMA_IM_SPIRX_Pos			4
#define DMA_IM_SPIRX_Msk			(0x01 << DMA_IM_SPIRX_Pos)
#define DMA_IM_SPITX_Pos			5
#define DMA_IM_SPITX_Msk			(0x01 << DMA_IM_SPITX_Pos)

#define DMA_IF_CAN_Pos		    	0		//写1清零
#define DMA_IF_CAN_Msk		    	(0x01 << DMA_IF_CAN_Pos)
#define DMA_IF_ADC_Pos			    2		//写1清零
#define DMA_IF_ADC_Msk			    (0x01 << DMA_IF_ADC_Pos)
#define DMA_IF_SPIRX_Pos			4
#define DMA_IF_SPIRX_Msk			(0x01 << DMA_IF_SPIRX_Pos)
#define DMA_IF_SPITX_Pos			5
#define DMA_IF_SPITX_Msk			(0x01 << DMA_IF_SPITX_Pos)

#define DMA_CR_LEN_Pos				0		//DMA传输字节个数
#define DMA_CR_LEN_Msk				(0xFFF << DMA_CR_LEN_Pos)
#define DMA_CR_REN_Pos				16		//读SPI通道、读ADC通道、读CAN通道的通道使能位
#define DMA_CR_REN_Msk				(0x01 << DMA_CR_REN_Pos)
#define DMA_CR_WEN_Pos				16		//写SPI通道的通道使能位，注意：写SPI通道的发送使能也在16位；其他通道的发送使能在第17位，但其他通道都是读通道，不使用发送使能位	
#define DMA_CR_WEN_Msk				(0x01 << DMA_CR_WEN_Pos)




typedef struct {
	__IO uint32_t CR;						//Control Register
	
	__O  uint32_t CMD;						//Command Register
	
	__I  uint32_t SR;						//Status Register
	
	__I  uint32_t IF;						//Interrupt Flag
	
	__IO uint32_t IE;						//Interrupt Enable
	
	     uint32_t RESERVED;
	
	__IO uint32_t BT0;						//Bit Time Register 0
	
	__IO uint32_t BT1;						//Bit Time Register 1
	
	     uint32_t RESERVED2[3];
	
	__I  uint32_t ALC;						//Arbitration Lost Capture, 仲裁丢失捕捉
	
	__I  uint32_t ECC;						//Error code capture, 错误代码捕捉
	
	__IO uint32_t EWLIM;					//Error Warning Limit, 错误报警限制
	
	__IO uint32_t RXERR;					//RX错误计数
	
	__IO uint32_t TXERR;					//TX错误计数
	
	union {
		struct {							//在复位时可读写，正常工作模式下不可访问
			__IO uint32_t ACR[4];			//Acceptance Check Register, 验收寄存器
			
			__IO uint32_t AMR[4];			//Acceptance Mask Register, 验收屏蔽寄存器；0 must match    1 don't care
			
				 uint32_t RESERVED[5];
		} FILTER;
		
		union {								//在正常工作模式下可读写，复位时不可访问
			struct {
				__O  uint32_t INFO;
				
				__O  uint32_t DATA[12];
			} TXFRAME;
			
			struct {
				__I  uint32_t INFO;
				
				__I  uint32_t DATA[12];
			} RXFRAME;
		};
	};
	
	__I  uint32_t RMCNT;					//Receive Message Count
	
		 uint32_t RESERVED3[66];
	
	struct {								//TXFRAME的读接口
		__I  uint32_t INFO;
		
		__I  uint32_t DATA[12];
	} TXFRAME_R;
} CAN_TypeDef;


#define CAN_CR_RST_Pos				0
#define CAN_CR_RST_Msk				(0x01 << CAN_CR_RST_Pos)
#define CAN_CR_LOM_Pos				1		//Listen Only Mode
#define CAN_CR_LOM_Msk				(0x01 << CAN_CR_LOM_Pos)
#define CAN_CR_STM_Pos				2		//Self Test Mode, 此模式下即使没有应答，CAN控制器也可以成功发送
#define CAN_CR_STM_Msk				(0x01 << CAN_CR_STM_Pos)
#define CAN_CR_AFM_Pos				3		//Acceptance Filter Mode, 1 单个验收滤波器（32位）   0 两个验收滤波器（16位）
#define CAN_CR_AFM_Msk				(0x01 << CAN_CR_AFM_Pos)
#define CAN_CR_SLEEP_Pos			4		//写1进入睡眠模式，有总线活动或中断时唤醒并自动清零此位
#define CAN_CR_SLEEP_Msk			(0x01 << CAN_CR_SLEEP_Pos)
#define CAN_CR_DMAEN_Pos			5
#define CAN_CR_DMAEN_Msk			(0x01 << CAN_CR_DMAEN_Pos)

#define CAN_CMD_TXREQ_Pos			0		//Transmission Request
#define CAN_CMD_TXREQ_Msk			(0x01 << CAN_CMD_TXREQ_Pos)
#define CAN_CMD_ABTTX_Pos			1		//Abort Transmission
#define CAN_CMD_ABTTX_Msk			(0x01 << CAN_CMD_ABTTX_Pos)
#define CAN_CMD_RRB_Pos				2		//Release Receive Buffer
#define CAN_CMD_RRB_Msk				(0x01 << CAN_CMD_RRB_Pos)
#define CAN_CMD_CLROV_Pos			3		//Clear Data Overrun
#define CAN_CMD_CLROV_Msk			(0x01 << CAN_CMD_CLROV_Pos)
#define CAN_CMD_SRR_Pos				4		//Self Reception Request
#define CAN_CMD_SRR_Msk				(0x01 << CAN_CMD_SRR_Pos)

#define CAN_SR_RXDA_Pos				0		//Receive Data Available，接收FIFO中有完整消息可以读取
#define CAN_SR_RXDA_Msk				(0x01 << CAN_SR_RXDA_Pos)
#define CAN_SR_RXOV_Pos				1		//Receive FIFO Overrun，新接收的信息由于接收FIFO已满而丢掉
#define CAN_SR_RXOV_Msk				(0x01 << CAN_SR_RXOV_Pos)
#define CAN_SR_TXBR_Pos				2		//Transmit Buffer Release，0 正在处理前面的发送，现在不能写新的消息    1 可以写入新的消息发送
#define CAN_SR_TXBR_Msk				(0x01 << CAN_SR_TXBR_Pos)
#define CAN_SR_TXOK_Pos				3		//Transmit OK，successfully completed
#define CAN_SR_TXOK_Msk				(0x01 << CAN_SR_TXOK_Pos)
#define CAN_SR_RXBUSY_Pos			4		//Receive Busy，正在接收
#define CAN_SR_RXBUSY_Msk			(0x01 << CAN_SR_RXBUSY_Pos)
#define CAN_SR_TXBUSY_Pos			5		//Transmit Busy，正在发送
#define CAN_SR_TXBUSY_Msk			(0x01 << CAN_SR_TXBUSY_Pos)
#define CAN_SR_ERRWARN_Pos			6		//1 至少一个错误计数器达到 Warning Limit
#define CAN_SR_ERRWARN_Msk			(0x01 << CAN_SR_ERRWARN_Pos)
#define CAN_SR_BUSOFF_Pos			7		//1 CAN 控制器处于总线关闭状态，没有参与到总线活动
#define CAN_SR_BUSOFF_Msk			(0x01 << CAN_SR_BUSOFF_Pos)

#define CAN_IF_RXDA_Pos				0		//IF.RXDA = SR.RXDA & IE.RXDA
#define CAN_IF_RXDA_Msk				(0x01 << CAN_IF_RXDA_Pos)
#define CAN_IF_TXBR_Pos				1		//当IE.TXBR=1时，SR.TXBR由0变成1将置位此位
#define CAN_IF_TXBR_Msk				(0x01 << CAN_IF_TXBR_Pos)
#define CAN_IF_ERRWARN_Pos			2		//当IE.ERRWARN=1时，SR.ERRWARN或SR.BUSOFF 0-to-1 或 1-to-0将置位此位
#define CAN_IF_ERRWARN_Msk			(0x01 << CAN_IF_ERRWARN_Pos)
#define CAN_IF_RXOV_Pos				3		//IF.RXOV = SR.RXOV & IE.RXOV
#define CAN_IF_RXOV_Msk				(0x01 << CAN_IF_RXOV_Pos)
#define CAN_IF_WKUP_Pos				4		//当IE.WKUP=1时，在睡眠模式下的CAN控制器检测到总线活动时硬件置位
#define CAN_IF_WKUP_Msk				(0x01 << CAN_IF_WKUP_Pos)
#define CAN_IF_ERRPASS_Pos			5		//
#define CAN_IF_ERRPASS_Msk			(0x01 << CAN_IF_ERRPASS_Pos)
#define CAN_IF_ARBLOST_Pos			6		//Arbitration Lost，当IE.ARBLOST=1时，CAN控制器丢失仲裁变成接收方时硬件置位
#define CAN_IF_ARBLOST_Msk			(0x01 << CAN_IF_ARBLOST_Pos)
#define CAN_IF_BUSERR_Pos			7		//当IE.BUSERR=1时，CAN控制器检测到总线错误时硬件置位
#define CAN_IF_BUSERR_Msk			(0x01 << CAN_IF_BUSERR_Pos)

#define CAN_IE_RXDA_Pos				0
#define CAN_IE_RXDA_Msk				(0x01 << CAN_IE_RXDA_Pos)
#define CAN_IE_TXBR_Pos				1
#define CAN_IE_TXBR_Msk				(0x01 << CAN_IE_TXBR_Pos)
#define CAN_IE_ERRWARN_Pos			2
#define CAN_IE_ERRWARN_Msk			(0x01 << CAN_IE_ERRWARN_Pos)
#define CAN_IE_RXOV_Pos				3
#define CAN_IE_RXOV_Msk				(0x01 << CAN_IE_RXOV_Pos)
#define CAN_IE_WKUP_Pos				4
#define CAN_IE_WKUP_Msk				(0x01 << CAN_IE_WKUP_Pos)
#define CAN_IE_ERRPASS_Pos			5
#define CAN_IE_ERRPASS_Msk			(0x01 << CAN_IE_ERRPASS_Pos)
#define CAN_IE_ARBLOST_Pos			6
#define CAN_IE_ARBLOST_Msk			(0x01 << CAN_IE_ARBLOST_Pos)
#define CAN_IE_BUSERR_Pos			7
#define CAN_IE_BUSERR_Msk			(0x01 << CAN_IE_BUSERR_Pos)

#define CAN_BT0_BRP_Pos				0		//Baud Rate Prescaler，CAN时间单位=2*Tsysclk*(BRP+1)
#define CAN_BT0_BRP_Msk				(0x3F << CAN_BT0_BRP_Pos)
#define CAN_BT0_SJW_Pos				6		//Synchronization Jump Width
#define CAN_BT0_SJW_Msk				(0x03 << CAN_BT0_SJW_Pos)

#define CAN_BT1_TSEG1_Pos			0		//t_tseg1 = CAN时间单位 * (TSEG1+1)
#define CAN_BT1_TSEG1_Msk			(0x0F << CAN_BT1_TSEG1_Pos)
#define CAN_BT1_TSEG2_Pos			4		//t_tseg2 = CAN时间单位 * (TSEG2+1)
#define CAN_BT1_TSEG2_Msk			(0x07 << CAN_BT1_TSEG2_Pos)
#define CAN_BT1_SAM_Pos				7		//采样次数  0: sampled once  1: sampled three times
#define CAN_BT1_SAM_Msk				(0x01 << CAN_BT1_SAM_Pos)

#define CAN_ECC_SEGCODE_Pos			0		//Segment Code
#define CAN_ECC_SEGCODE_Msk			(0x1F << CAN_ECC_SEGCODE_Pos)
#define CAN_ECC_DIR_Pos				5		//0 error occurred during transmission   1 during reception
#define CAN_ECC_DIR_Msk				(0x01 << CAN_ECC_DIR_Pos)
#define CAN_ECC_ERRCODE_Pos			6		//Error Code：0 Bit error   1 Form error   2 Stuff error   3 other error
#define CAN_ECC_ERRCODE_Msk			(0x03 << CAN_ECC_ERRCODE_Pos)

#define CAN_INFO_DLC_Pos			0		//Data Length Control
#define CAN_INFO_DLC_Msk			(0x0F << CAN_INFO_DLC_Pos)
#define CAN_INFO_RTR_Pos			6		//Remote Frame，1 远程帧    0 数据帧
#define CAN_INFO_RTR_Msk			(0x01 << CAN_INFO_RTR_Pos)
#define CAN_INFO_FF_Pos				7		//Frame Format，0 标准帧格式    1 扩展帧格式
#define CAN_INFO_FF_Msk				(0x01 << CAN_INFO_FF_Pos)




typedef struct {
	__IO uint32_t LOAD;						//喂狗使计数器装载LOAD值
	
	__I  uint32_t VALUE;
	
	__IO uint32_t CR;
	
	__IO uint32_t IF;						//计数到0时硬件置位，软件写0清除标志
	
	__IO uint32_t FEED;						//写0x55喂狗
} WDT_TypeDef;


#define WDT_CR_EN_Pos				0
#define WDT_CR_EN_Msk				(0x01 << WDT_CR_EN_Pos)
#define WDT_CR_RSTEN_Pos			1
#define WDT_CR_RSTEN_Msk			(0x01 << WDT_CR_RSTEN_Pos)




typedef struct {
	__IO uint32_t CR;
	
	__IO uint32_t SR;
	
	     uint32_t RESERVED[2];
	
	__IO uint32_t DIVIDEND;					//被除数
	
	__IO uint32_t DIVISOR;					//除数
	
	__IO uint32_t QUO;						//商
	
	__IO uint32_t REMAIN;					//余数
	
	__IO uint32_t RADICAND;					//被开方数
	
	__IO uint32_t ROOT;						//平方根，低16位为小数部分，高16位为整数部分
} DIV_TypeDef;


#define DIV_CR_DIVGO_Pos			0		//写1启动除法运算，运算完成后自动清零
#define DIV_CR_DIVGO_Msk			(0x01 << DIV_CR_DIVGO_Pos)
#define DIV_CR_ROOTGO_Pos			8		//写1启动开平方根运算，运算完成后自动清零
#define DIV_CR_ROOTGO_Msk			(0x01 << DIV_CR_ROOTGO_Pos)
#define DIV_CR_ROOTMOD_Pos			9		//开平方根模式：0 结果为整数    1 结果既有整数部分又有小数部分
#define DIV_CR_ROOTMOD_Msk			(0x01 << DIV_CR_ROOTMOD_Pos)

#define DIV_SR_DIVEND_Pos			0		//除法运算完成标志，写1清零
#define DIV_SR_DIVEND_Msk			(0x01 << DIV_SR_DIVEND_Pos)
#define DIV_SR_DIVBUSY_Pos			1		//1 除法运算计算中
#define DIV_SR_DIVBUSY_Msk			(0x01 << DIV_SR_DIVBUSY_Pos)
#define DIV_SR_ROOTENDI_Pos			8		//开方整数运算完成标志，写1清零
#define DIV_SR_ROOTENDI_Msk			(0x01 << DIV_SR_ROOTENDI_Pos)
#define DIV_SR_ROOTENDF_Pos			9		//开方小数运算完成标志，写1清零
#define DIV_SR_ROOTENDF_Msk			(0x01 << DIV_SR_ROOTENDF_Pos)
#define DIV_SR_ROOTBUSY_Pos			10		//1 开方运算计算中
#define DIV_SR_ROOTBUSY_Msk			(0x01 << DIV_SR_ROOTBUSY_Pos)




typedef struct {
    __IO uint32_t MINSEC;                   //分秒计数
    
    __IO uint32_t DATHUR;                   //日时计数
    
    __IO uint32_t MONDAY;                   //月周计数
    
    __IO uint32_t YEAR;                     //[11:0] 年计数
    
    __IO uint32_t MINSECAL;                 //分秒闹铃设置
    
    __IO uint32_t DAYHURAL;                 //周时闹铃设置
    
    __IO uint32_t LOAD;
    
    __IO uint32_t IE;
    
    __IO uint32_t IF;                       //写1清零
    
    __IO uint32_t EN;                       //[0] 1 RTC使能
    
    __IO uint32_t CFGABLE;                  //[0] 1 RTC可配置
    
    __IO uint32_t TRIM;                     //时钟调整
    
    __IO uint32_t TRIMM;                    //时钟微调整
	
	     uint32_t RESERVED[11];
	
	__IO uint32_t CALIBREFCNT;				//[23:0] 校准基准时钟频率的一半，校准基准时钟取值范围2.2~4.1MHz
	
	__IO uint32_t CALIBEN;					//[0] 启动校准，校准完成后自动清零
	
	__I  uint32_t CALIBST;
} RTC_TypeDef;


#define RTC_MINSEC_SEC_Pos			0       //秒计数，取值0--59
#define RTC_MINSEC_SEC_Msk		    (0x3F << RTC_MINSEC_SEC_Pos)
#define RTC_MINSEC_MIN_Pos			6       //分钟计数，取值0--59
#define RTC_MINSEC_MIN_Msk		    (0x3F << RTC_MINSEC_MIN_Pos)

#define RTC_DATHUR_HOUR_Pos			0       //小时计数，取值0--23
#define RTC_DATHUR_HOUR_Msk		    (0x1F << RTC_DATHUR_HOUR_Pos)
#define RTC_DATHUR_DATE_Pos			5       //date of month，取值1--31
#define RTC_DATHUR_DATE_Msk		    (0x1F << RTC_DATHUR_DATE_Pos)

#define RTC_MONDAY_DAY_Pos			0       //day of week，取值0--6
#define RTC_MONDAY_DAY_Msk		    (0x07 << RTC_MONDAY_DAY_Pos)
#define RTC_MONDAY_MON_Pos			3       //月份计数，取值1--12
#define RTC_MONDAY_MON_Msk		    (0x0F << RTC_MONDAY_MON_Pos)

#define RTC_MINSECAL_SEC_Pos		0       //闹钟秒设置
#define RTC_MINSECAL_SEC_Msk		(0x3F << RTC_MINSECAL_SEC_Pos)
#define RTC_MINSECAL_MIN_Pos	    6       //闹钟分钟设置
#define RTC_MINSECAL_MIN_Msk		(0x3F << RTC_MINSECAL_MIN_Pos)

#define RTC_DAYHURAL_HOUR_Pos		0       //闹钟小时设置
#define RTC_DAYHURAL_HOUR_Msk		(0x1F << RTC_DAYHURAL_HOUR_Pos)
#define RTC_DAYHURAL_SUN_Pos		5       //周日闹钟有效
#define RTC_DAYHURAL_SUN_Msk		(0x01 << RTC_DAYHURAL_SUN_Pos)
#define RTC_DAYHURAL_MON_Pos		6       //周一闹钟有效
#define RTC_DAYHURAL_MON_Msk		(0x01 << RTC_DAYHURAL_MON_Pos)
#define RTC_DAYHURAL_TUE_Pos		7       //周二闹钟有效
#define RTC_DAYHURAL_TUE_Msk		(0x01 << RTC_DAYHURAL_TUE_Pos)
#define RTC_DAYHURAL_WED_Pos		8       //周三闹钟有效
#define RTC_DAYHURAL_WED_Msk		(0x01 << RTC_DAYHURAL_WED_Pos)
#define RTC_DAYHURAL_THU_Pos		9       //周四闹钟有效
#define RTC_DAYHURAL_THU_Msk		(0x01 << RTC_DAYHURAL_THU_Pos)
#define RTC_DAYHURAL_FRI_Pos		10      //周五闹钟有效
#define RTC_DAYHURAL_FRI_Msk		(0x01 << RTC_DAYHURAL_FRI_Pos)
#define RTC_DAYHURAL_SAT_Pos		11      //周六闹钟有效
#define RTC_DAYHURAL_SAT_Msk		(0x01 << RTC_DAYHURAL_SAT_Pos)

#define RTC_LOAD_TIME_Pos			0		//将时间、定时、校准相关寄存器中的值加载到RTC时钟域
#define RTC_LOAD_TIME_Msk			(0x01 << RTC_LOAD_TIME_Pos)
#define RTC_LOAD_ALARM_Pos			1		//将闹钟相关寄存器中的值加载到RTC时钟域
#define RTC_LOAD_ALARM_Msk			(0x01 << RTC_LOAD_ALARM_Pos)

#define RTC_IE_SEC_Pos		        0       //秒中断使能
#define RTC_IE_SEC_Msk		        (0x01 << RTC_IE_SEC_Pos)
#define RTC_IE_MIN_Pos		        1
#define RTC_IE_MIN_Msk		        (0x01 << RTC_IE_MIN_Pos)
#define RTC_IE_HOUR_Pos		        2
#define RTC_IE_HOUR_Msk		        (0x01 << RTC_IE_HOUR_Pos)
#define RTC_IE_DATE_Pos		        3
#define RTC_IE_DATE_Msk		        (0x01 << RTC_IE_DATE_Pos)
#define RTC_IE_ALARM_Pos		    4
#define RTC_IE_ALARM_Msk		    (0x01 << RTC_IE_ALARM_Pos)

#define RTC_IF_SEC_Pos		        0       //写1清零
#define RTC_IF_SEC_Msk		        (0x01 << RTC_IF_SEC_Pos)
#define RTC_IF_MIN_Pos		        1
#define RTC_IF_MIN_Msk		        (0x01 << RTC_IF_MIN_Pos)
#define RTC_IF_HOUR_Pos		        2
#define RTC_IF_HOUR_Msk		        (0x01 << RTC_IF_HOUR_Pos)
#define RTC_IF_DATE_Pos		        3
#define RTC_IF_DATE_Msk		        (0x01 << RTC_IF_DATE_Pos)
#define RTC_IF_ALARM_Pos		    4
#define RTC_IF_ALARM_Msk		    (0x01 << RTC_IF_ALARM_Pos)

#define RTC_TRIM_ADJ_Pos		    0       //用于调整BASECNT的计数周期，默认为32768，如果DEC为1，则计数周期调整为32768-ADJ，否则调整为32768+ADJ
#define RTC_TRIM_ADJ_Msk		    (0xFF << RTC_TRIM_ADJ_Pos)
#define RTC_TRIM_DEC_Pos		    8
#define RTC_TRIM_DEC_Msk		    (0x01 << RTC_TRIM_DEC_Pos)

#define RTC_TRIMM_CYCLE_Pos		    0       //用于计数周期微调，如果INC为1，则第n个计数周期调整为(32768±ADJ)+1,否则调整为(32768±ADJ)-1
                                            //cycles=0时，不进行微调整；cycles=1，则n为2；cycles=7，则n为8；以此类推
#define RTC_TRIMM_CYCLE_Msk		    (0x07 << RTC_TRIMM_CYCLE_Pos)
#define RTC_TRIMM_INC_Pos		    3
#define RTC_TRIMM_INC_Msk		    (0x01 << RTC_TRIMM_INC_Pos)




/******************************************************************************/
/*						 Peripheral memory map							  */
/******************************************************************************/
#define RAM_BASE		   	0x20000000
#define AHB_BASE			0x40000000
#define APB_BASE		 	0x50000000

/* AHB Peripheral memory map */
#define SYS_BASE			(AHB_BASE + 0x0000000)
#define DMA_BASE			(AHB_BASE + 0x1000000)
#define DIV_BASE			(AHB_BASE + 0x6000000)

/* APB Peripheral memory map */
#define PORTA_BASE			(APB_BASE +	0x0000)
#define PORTB_BASE			(APB_BASE +	0x0010)
#define PORTC_BASE			(APB_BASE +	0x0020)
#define PORTD_BASE			(APB_BASE +	0x0030)

#define GPIOA_BASE			(APB_BASE + 0x01000)
#define GPIOB_BASE			(APB_BASE + 0x02000)
#define GPIOC_BASE			(APB_BASE + 0x03000)
#define GPIOD_BASE			(APB_BASE + 0x04000)

#define TIMR0_BASE			(APB_BASE +	0x07000)
#define TIMR1_BASE			(APB_BASE +	0x0700C)
#define TIMR2_BASE			(APB_BASE +	0x07018)
#define TIMR3_BASE			(APB_BASE +	0x07024)
#define TIMRG_BASE			(APB_BASE +	0x07060)

#define WDT_BASE			(APB_BASE + 0x09000)

#define PWM0_BASE			(APB_BASE + 0x0A000)
#define PWM1_BASE			(APB_BASE + 0x0A020)
#define PWM2_BASE			(APB_BASE + 0x0A040)
#define PWMG_BASE			(APB_BASE + 0x0A170)

#define RTC_BASE			(APB_BASE + 0x0B000)

#define ADC_BASE			(APB_BASE + 0x0D000)

#define UART0_BASE			(APB_BASE + 0x10000)
#define UART1_BASE			(APB_BASE + 0x11000)
#define UART2_BASE			(APB_BASE + 0x12000)
#define UART3_BASE			(APB_BASE + 0x13000)

#define I2C0_BASE			(APB_BASE + 0x18000)
#define I2C1_BASE			(APB_BASE + 0x19000)

#define SPI0_BASE			(APB_BASE + 0x1C000)
#define SPI1_BASE			(APB_BASE + 0x1E000)

#define CAN_BASE			(APB_BASE + 0x20000)


/******************************************************************************/
/*						 Peripheral declaration							 */
/******************************************************************************/
#define SYS					((SYS_TypeDef  *) SYS_BASE)

#define PORTA				((PORT_TypeDef *) PORTA_BASE)
#define PORTB				((PORT_TypeDef *) PORTB_BASE)
#define PORTC				((PORT_TypeDef *) PORTC_BASE)
#define PORTD				((PORT_TypeDef *) PORTD_BASE)

#define GPIOA				((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB				((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC				((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD				((GPIO_TypeDef *) GPIOD_BASE)

#define TIMR0				((TIMR_TypeDef *) TIMR0_BASE)
#define TIMR1				((TIMR_TypeDef *) TIMR1_BASE)
#define TIMR2				((TIMR_TypeDef *) TIMR2_BASE)
#define TIMR3				((TIMR_TypeDef *) TIMR3_BASE)
#define TIMRG				((TIMRG_TypeDef*) TIMRG_BASE)

#define UART0				((UART_TypeDef *) UART0_BASE)
#define UART1				((UART_TypeDef *) UART1_BASE)
#define UART2				((UART_TypeDef *) UART2_BASE)
#define UART3   			((UART_TypeDef *) UART3_BASE)

#define SPI0				((SPI_TypeDef  *) SPI0_BASE)
#define SPI1				((SPI_TypeDef  *) SPI1_BASE)

#define I2C0				((I2C_TypeDef  *) I2C0_BASE)
#define I2C1				((I2C_TypeDef  *) I2C1_BASE)

#define ADC 				((ADC_TypeDef  *) ADC_BASE)

#define PWM0				((PWM_TypeDef  *) PWM0_BASE)
#define PWM1				((PWM_TypeDef  *) PWM1_BASE)
#define PWM2				((PWM_TypeDef  *) PWM2_BASE)
#define PWMG				((PWMG_TypeDef *) PWMG_BASE)

#define DMA 				((DMA_TypeDef  *) DMA_BASE)

#define CAN 				((CAN_TypeDef  *) CAN_BASE)

#define WDT					((WDT_TypeDef  *) WDT_BASE)

#define	DIV					((DIV_TypeDef  *) DIV_BASE)

#define	RTC					((RTC_TypeDef  *) RTC_BASE)


#include "SWM160_port.h"
#include "SWM160_gpio.h"
#include "SWM160_exti.h"
#include "SWM160_timr.h"
#include "SWM160_uart.h"
#include "SWM160_spi.h"
#include "SWM160_i2c.h"
#include "SWM160_pwm.h"
#include "SWM160_adc.h"
#include "SWM160_dma.h"
#include "SWM160_can.h"
#include "SWM160_flash.h"
#include "SWM160_wdt.h"
#include "SWM160_rtc.h"
#include "SWM160_div.h"
#include "SWM160_sleep.h"

#endif //__SWM160_H__
