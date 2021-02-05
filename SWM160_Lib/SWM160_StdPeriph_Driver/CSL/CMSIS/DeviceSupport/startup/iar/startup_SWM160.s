;******************************************************************************************************************************************
; 文件名称:    startup_SWM160.s
; 功能说明:    SWM160单片机的启动文件
; 技术支持:    http://www.synwit.com.cn/e/tool/gbook/?bid=1
; 注意事项:
; 版本日期: V1.0.0        2016年1月30日
; 升级记录:
;
;
;******************************************************************************************************************************************
; @attention
;
; THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
; REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
; FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
; OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
; -ECTION WITH THEIR PRODUCTS.
;
; COPYRIGHT 2012 Synwit Technology
;******************************************************************************************************************************************

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler
        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     0
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     GPIOA0_Handler
        DCD     WDT_Handler
        DCD     TIMR3_Handler
        DCD     PWMNC_Handler
        DCD     ADC_Handler
        DCD     TIMR2_Handler
        DCD     RTC_Handler
        DCD     GPIOA1_Handler
        DCD     SPI1_Handler
        DCD     GPIOD1_Handler
        DCD     CAN_Handler
        DCD     UART0_Handler
        DCD     I2C0_Handler
        DCD     SPI0_Handler
        DCD     GPIOA_Handler
        DCD     TIMR1_Handler
        DCD     GPIOB0_Handler
        DCD     UART1_Handler
        DCD     GPIOB_Handler
        DCD     TIMR0_Handler
        DCD     GPIOB1_Handler
        DCD     PWMHE_Handler
        DCD     UART2_Handler
        DCD     BOD_Handler
        DCD     I2C1_Handler
        DCD     GPIOC0_Handler
        DCD     GPIOC1_Handler
        DCD     UART3_Handler
        DCD     PWMHALT_Handler
        DCD     GPIOC_Handler
        DCD     GPIOD_Handler
        DCD     DMA_Handler


        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =__iar_program_start
        BX      R0
        
        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK GPIOA0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA0_Handler
        B GPIOA0_Handler

        PUBWEAK WDT_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
WDT_Handler
        B WDT_Handler

        PUBWEAK TIMR3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR3_Handler
        B TIMR3_Handler

        PUBWEAK PWMNC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWMNC_Handler
        B PWMNC_Handler

        PUBWEAK ADC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC_Handler
        B ADC_Handler

        PUBWEAK TIMR2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR2_Handler
        B TIMR2_Handler

        PUBWEAK RTC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_Handler
        B RTC_Handler

        PUBWEAK GPIOA1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA1_Handler
        B GPIOA1_Handler

        PUBWEAK SPI1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_Handler
        B SPI1_Handler

        PUBWEAK GPIOD1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOD1_Handler
        B GPIOD1_Handler

        PUBWEAK CAN_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN_Handler
        B CAN_Handler

        PUBWEAK UART0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART0_Handler
        B UART0_Handler

        PUBWEAK I2C0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C0_Handler
        B I2C0_Handler

        PUBWEAK SPI0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI0_Handler
        B SPI0_Handler

        PUBWEAK GPIOA_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOA_Handler
        B GPIOA_Handler

        PUBWEAK TIMR1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR1_Handler
        B TIMR1_Handler

        PUBWEAK GPIOB0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB0_Handler
        B GPIOB0_Handler

        PUBWEAK UART1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART1_Handler
        B UART1_Handler

        PUBWEAK GPIOB_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB_Handler
        B GPIOB_Handler

        PUBWEAK TIMR0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMR0_Handler
        B TIMR0_Handler

        PUBWEAK GPIOB1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOB1_Handler
        B GPIOB1_Handler

        PUBWEAK PWMHE_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWMHE_Handler
        B PWMHE_Handler

        PUBWEAK UART2_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART2_Handler
        B UART2_Handler

        PUBWEAK BOD_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BOD_Handler
        B BOD_Handler

        PUBWEAK I2C1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_Handler
        B I2C1_Handler

        PUBWEAK GPIOC0_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC0_Handler
        B GPIOC0_Handler

        PUBWEAK GPIOC1_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC1_Handler
        B GPIOC1_Handler

        PUBWEAK UART3_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART3_Handler
        B UART3_Handler

        PUBWEAK PWMHALT_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWMHALT_Handler
        B PWMHALT_Handler

        PUBWEAK GPIOC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOC_Handler
        B GPIOC_Handler

        PUBWEAK GPIOD_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIOD_Handler
        B GPIOD_Handler

        PUBWEAK DMA_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA_Handler
        B DMA_Handler

        END
