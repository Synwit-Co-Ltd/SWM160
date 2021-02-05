/****************************************************************************************************************************************** 
* 文件名称:	SWM160_flash.c
* 功能说明:	使用芯片的IAP功能将片上Flash模拟成EEPROM来保存数据，掉电后不丢失
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.0.0		2016年1月30日
* 升级记录: 
*******************************************************************************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION 
* REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE 
* FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT 
* OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
* -ECTION WITH THEIR PRODUCTS.
*
* COPYRIGHT 2012 Synwit Technology  
*******************************************************************************************************************************************/
#include "SWM160.h"
#include "SWM160_flash.h"

typedef uint32_t (*IAPFunc1)(uint32_t addr);
typedef uint32_t (*IAPFunc2)(uint32_t faddr, uint32_t raddr, uint32_t cnt);

IAPFunc1 FLASH_PageErase = (IAPFunc1)0x1000501;

IAPFunc2 FLASH_PageWrite = (IAPFunc2)0x1000601;


/****************************************************************************************************************************************** 
* 函数名称:	FLASH_Erase()
* 功能说明:	FLASH页擦除，每个页1K字节
* 输    入: uint32_t addr		要擦除页的地址，必须1K对齐，即addr%1024 == 0
* 输    出: uint32_t			0 擦除成功    1 擦除失败
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t FLASH_Erase(uint32_t addr)
{
	uint32_t status;
	
	__disable_irq();
	status = FLASH_PageErase(addr/1024);
	__enable_irq();
	
	return status;
}

/****************************************************************************************************************************************** 
* 函数名称:	FLASH_Write()
* 功能说明:	FLASH数据写入
* 输    入: uint32_t addr		数据要写入到Flash中的地址，字对齐
*			uint32_t buff[]		要写入Flash中的数据
*			uint32_t cnt		要写的数据的个数，以字为单位，最大取值256
* 输    出: uint32_t			0 写入成功    1 写入失败
* 注意事项: 要写入的数据必须全部在同一页内，即addr/1024 == (addr+(cnt-1)*4)/1024
******************************************************************************************************************************************/
uint32_t FLASH_Write(uint32_t addr, uint32_t buff[], uint32_t cnt)
{	
	uint32_t status;
	
	__disable_irq();
	status = FLASH_PageWrite(addr, (uint32_t)buff, cnt);
	__enable_irq();
	
	return status;
}

#if   defined ( __CC_ARM )

/****************************************************************************************************************************************** 
* 函数名称:	FlashSpeedX2()
* 功能说明:	Flash读取速度提高一倍
*			Flash最高速度25MHz，CPU最高速度48MHz，为了使单片机在任意速度下都能读取Flash，默认CPU每两个时钟周期对Flash读取一次，
*			执行此函数后CPU一个周期读取Flash一次，程序执行速度提升60%
* 输    入: 无
* 输    出: 无
* 注意事项: 只能在单片机速度小于25MHz的情况下执行此函数
******************************************************************************************************************************************/
uint16_t Code_FlashSpeedX2[] = {
	0x6901,     // LDR      r1,[r0,#0x10]
	0x2201,     // MOVS     r2,#0x01
	0x0412,     // LSLS     r2,r2,#16
	0x4311,     // ORRS     r1,r1,r2
	0x6101,     // STR      r1,[r0,#0x10]
	0xBF00,		// NOP
	0xBF00,		// NOP
	0x4770,		// BX LR
};
__asm void FlashSpeedX2(void)
{
	IMPORT Code_FlashSpeedX2
	PUSH {LR}
	LDR R0,=0x50028000		// Flash Controller
	LDR R1,=Code_FlashSpeedX2
    ADDS R1, R1, #1
	NOP
	BLX R1
	POP {R0}
	BX R0
}

#elif defined ( __ICCARM__ )

#endif

__attribute__((section("PlaceInRAM")))
void AppToIsp(void)
{
	uint8_t i = 0;
	__disable_irq();
	(*(volatile unsigned int *)0x40000500) = 0x12345678;
	(*(volatile unsigned int *)0x50028018) = 0x04;  //将flash切换到Info区
	__DMB();  //保证上条指令和下条指令能按顺序执行
	for(i=0; i<5; i++);	
	SYS->CLKEN = 0x0;  //关闭所有外设时钟	
//	__enable_irq();  //下面执行软件复位可以不使能总中断	
	SCB->AIRCR = ((0x5FA<<SCB_AIRCR_VECTKEY_Pos)|SCB_AIRCR_SYSRESETREQ_Msk);  //系统软件复位
	__DSB();  /* Ensure completion of memory access */              
	while(1);		
}
