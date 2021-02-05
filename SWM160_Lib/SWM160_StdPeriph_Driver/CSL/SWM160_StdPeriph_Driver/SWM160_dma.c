/****************************************************************************************************************************************** 
* 文件名称: SWM160_dma.c
* 功能说明:	SWM160单片机的DMA功能驱动库
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项: 在不使能中断的情况下，也可以调用DMA_CH_INTStat()查询数据搬运是否完成，并调用DMA_CH_INTClr()清除完成标志
* 版本日期:	V1.0.0		2016年1月30日
* 升级记录:  
*
*
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
#include "SWM160_dma.h"


/****************************************************************************************************************************************** 
* 函数名称: DMA_CH_Config()
* 功能说明:	DMA通道配置
* 输    入: uint32_t chn			指定要配置的通道，有效值有DMA_CHW_SPI、DMA_CHR_SPI、DMA_CHR_ADC、DMA_CHR_CAN
*			uint32_t ram_addr		数据要被搬运到RAM中的地址，必须字对齐
*			uint32_t num_word		要搬运的数据字数，注意，单位是字，不是字节，最大值1024
*			uint32_t int_en			中断使能，1 数据搬运完成后产生中断    0 数据搬运完成后不产生中断
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_Config(uint32_t chn, uint32_t ram_addr, uint32_t num_word, uint32_t int_en)
{
	DMA->EN = 1;			//每个通道都有自己独立的开关控制，所以总开关可以是一直开启的
	
	DMA_CH_Close(chn);		//配置前先关闭该通道
	
	switch(chn)
	{
	case DMA_CHW_SPI:
		SPI0->CTRL |= (1 << SPI_CTRL_DMAEN_Pos);
		
		DMA->CH[chn].SRC = ram_addr;
		DMA->CH[chn].DST = (uint32_t)&SPI0->DATA;		//0x5001C004
		break;
	
	case DMA_CHR_SPI:
		SPI0->CTRL |= (1 << SPI_CTRL_DMAEN_Pos);
		
		DMA->CH[chn].SRC = (uint32_t)&SPI0->DATA;		//0x5001C004
		DMA->CH[chn].DST = ram_addr;
		break;
	
	case DMA_CHR_ADC:
		ADC->CTRL |= (0x01 << ADC_CTRL_DMAEN_Pos) | (0x01 << ADC_CTRL_RES2FF_Pos);
		
		DMA->CH[chn].SRC = (uint32_t)&ADC->FFDATA;		//0x5000D094
		DMA->CH[chn].DST = ram_addr;
		break;
	
	case DMA_CHR_CAN:
		CAN->CR |= (0x01 << CAN_CR_DMAEN_Pos);
		
		DMA->CH[chn].SRC = (uint32_t)&CAN->RXFRAME;		//0x50020040
		DMA->CH[chn].DST = ram_addr;
		break;
	}
	
	DMA->CH[chn].CR = ((num_word*4-1) << DMA_CR_LEN_Pos);
	
	DMA->IE = 0x35;			//即使不使能中断，也可以查询状态/标志
	DMA_CH_INTClr(chn);		//清除中断标志
	if(int_en) DMA_CH_INTEn(chn);
	else	   DMA_CH_INTDis(chn);
	
	if(int_en)
	{
		NVIC_EnableIRQ(DMA_IRQn);
	}
	else
	{		
		//不能NVIC_DisableIRQ(DMA_IRQn); 因为其他通道可能使用中断
	}
}

/****************************************************************************************************************************************** 
* 函数名称: DMA_CH_Open()
* 功能说明:	DMA通道打开
* 输    入: uint32_t chn			指定要配置的通道，有效值有DMA_CHW_SPI、DMA_CHR_SPI、DMA_CHR_ADC、DMA_CHR_CAN
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_Open(uint32_t chn)
{
	switch(chn)
	{
	case DMA_CHW_SPI:
		DMA->CH[chn].CR |= (1 << DMA_CR_WEN_Pos);
		break;
	
	case DMA_CHR_SPI:
	case DMA_CHR_ADC:		
	case DMA_CHR_CAN:
		DMA->CH[chn].CR |= (1 << DMA_CR_REN_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: DMA_CH_Close()
* 功能说明:	DMA通道关闭
* 输    入: uint32_t chn			指定要配置的通道，有效值有DMA_CHW_SPI、DMA_CHR_SPI、DMA_CHR_ADC、DMA_CHR_CAN
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_Close(uint32_t chn)
{
	switch(chn)
	{
	case DMA_CHW_SPI:
		DMA->CH[chn].CR &= ~(1 << DMA_CR_WEN_Pos);
		break;
	
	case DMA_CHR_SPI:
	case DMA_CHR_ADC:		
	case DMA_CHR_CAN:
		DMA->CH[chn].CR &= ~(1 << DMA_CR_REN_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: DMA_CH_INTEn()
* 功能说明:	DMA中断使能，数据搬运完成后触发中断
* 输    入: uint32_t chn			指定要配置的通道，有效值有DMA_CHW_SPI、DMA_CHR_SPI、DMA_CHR_ADC、DMA_CHR_CAN
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_INTEn(uint32_t chn)
{
	switch(chn)
	{
	case DMA_CHW_SPI:
		DMA->IM &= ~(1 << DMA_IM_SPITX_Pos);
		break;
	
	case DMA_CHR_SPI:
		DMA->IM &= ~(1 << DMA_IM_SPIRX_Pos);
		break;
	
	case DMA_CHR_ADC:
		DMA->IM &= ~(1 << DMA_IM_ADC_Pos);
		break;
	
	case DMA_CHR_CAN:
		DMA->IM &= ~(1 << DMA_IM_CAN_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: DMA_CH_INTDis()
* 功能说明:	DMA中断禁止，数据搬运完成后不触发中断
* 输    入: uint32_t chn			指定要配置的通道，有效值有DMA_CHW_SPI、DMA_CHR_SPI、DMA_CHR_ADC、DMA_CHR_CAN
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_INTDis(uint32_t chn)
{
	switch(chn)
	{
	case DMA_CHW_SPI:
		DMA->IM |= (1 << DMA_IM_SPITX_Pos);
		break;
	
	case DMA_CHR_SPI:
		DMA->IM |= (1 << DMA_IM_SPIRX_Pos);
		break;
	
	case DMA_CHR_ADC:
		DMA->IM |= (1 << DMA_IM_ADC_Pos);
		break;
	
	case DMA_CHR_CAN:
		DMA->IM |= (1 << DMA_IM_CAN_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: DMA_CH_INTClr()
* 功能说明:	DMA中断标志清除
* 输    入: uint32_t chn			指定要配置的通道，有效值有DMA_CHW_SPI、DMA_CHR_SPI、DMA_CHR_ADC、DMA_CHR_CAN
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void DMA_CH_INTClr(uint32_t chn)
{
	switch(chn)
	{
	case DMA_CHW_SPI:
		DMA->IF = (1 << DMA_IF_SPITX_Pos);
		break;
	
	case DMA_CHR_SPI:
		DMA->IF = (1 << DMA_IF_SPIRX_Pos);
		break;
	
	case DMA_CHR_ADC:
		DMA->IF = (1 << DMA_IF_ADC_Pos);
		break;
	
	case DMA_CHR_CAN:
		DMA->IF = (1 << DMA_IF_CAN_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: DMA_CH_INTStat()
* 功能说明:	DMA中断状态查询
* 输    入: uint32_t chn			指定要配置的通道，有效值有DMA_CHW_SPI、DMA_CHR_SPI、DMA_CHR_ADC、DMA_CHR_CAN
* 输    出: uint32_t				1 数据搬运完成    0 数据搬运未完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t DMA_CH_INTStat(uint32_t chn)
{
	uint32_t stat = 0;
	
	switch(chn)
	{
	case DMA_CHW_SPI:
		stat = (DMA->IF >> DMA_IF_SPITX_Pos) & 1;
		break;
	
	case DMA_CHR_SPI:
		stat = (DMA->IF >> DMA_IF_SPIRX_Pos) & 1;
		break;
	
	case DMA_CHR_ADC:
		stat = (DMA->IF >> DMA_IF_ADC_Pos)   & 1;
		break;
	
	case DMA_CHR_CAN:
		stat = (DMA->IF >> DMA_IF_CAN_Pos)   & 1;
		break;
	}
	
	return stat;
}
