/****************************************************************************************************************************************** 
* 文件名称: SWM160_timr.c
* 功能说明:	SWM160单片机的计数器/定时器功能驱动库
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
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
#include "SWM160_timr.h"


/****************************************************************************************************************************************** 
* 函数名称: TIMR_Init()
* 功能说明:	TIMR定时器/计数器初始化
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，有效值包括TIMR0、TIMR1、TIMR2、TIMR3
*			uint32_t mode			TIMR_MODE_TIMER 定时器模式    TIMR_MODE_COUNTER 计数器模式
*			uint32_t period			定时/计数周期，24位，最大值约16000000
*			uint32_t int_en			中断使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Init(TIMR_TypeDef * TIMRx, uint32_t mode, uint32_t period, uint32_t int_en)
{
	SYS->CLKEN |= (0x01 << SYS_CLKEN_TIMR_Pos);
	
	TIMR_Stop(TIMRx);	//一些关键寄存器只能在定时器停止时设置
	
	TIMRx->CTRL &= ~TIMR_CTRL_CLKSRC_Msk;
	TIMRx->CTRL |= mode << TIMR_CTRL_CLKSRC_Pos;
	
	TIMRx->LDVAL = period;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMR_INTClr(TIMR0);
		TIMRG->IE0 |= (1 << TIMRG_IE_IF_Pos);
		if(int_en) 
		{
			TIMRG->IM0 &= ~(1 << TIMRG_IM_IF_Pos);
			
			NVIC_EnableIRQ(TIMR0_IRQn);
		}
		else
		{
			TIMRG->IM0 |=  (1 << TIMRG_IM_IF_Pos);
			
			NVIC_DisableIRQ(TIMR0_IRQn);
		}
		break;
	
	case ((uint32_t)TIMR1):
		TIMR_INTClr(TIMR1);
		TIMRG->IE1 |= (1 << TIMRG_IE_IF_Pos);
		if(int_en)
		{
			TIMRG->IM1 &= ~(1 << TIMRG_IM_IF_Pos);
			
			NVIC_EnableIRQ(TIMR1_IRQn);
		}
		else
		{
			TIMRG->IM1 |=  (1 << TIMRG_IM_IF_Pos);
			
			NVIC_DisableIRQ(TIMR1_IRQn);
		}
		break;
	
	case ((uint32_t)TIMR2):
		TIMR_INTClr(TIMR2);
		TIMRG->IE2 |= (1 << TIMRG_IE_IF_Pos);
		if(int_en)
		{
			TIMRG->IM2 &= ~(1 << TIMRG_IM_IF_Pos);
			
			NVIC_EnableIRQ(TIMR2_IRQn);
		}
		else
		{
			TIMRG->IM2 |=  (1 << TIMRG_IM_IF_Pos);
			
			NVIC_DisableIRQ(TIMR2_IRQn);
		}
		break;
	
	case ((uint32_t)TIMR3):
		TIMR_INTClr(TIMR3);
		TIMRG->IE3 |= (1 << TIMRG_IE_IF_Pos);
		if(int_en)
		{
			TIMRG->IM3 &= ~(1 << TIMRG_IM_IF_Pos);
			
			NVIC_EnableIRQ(TIMR3_IRQn);
		}
		else
		{
			TIMRG->IM3 |=  (1 << TIMRG_IM_IF_Pos);
			
			NVIC_DisableIRQ(TIMR3_IRQn);
		}
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Start()
* 功能说明:	启动定时器，从初始值开始计时/计数
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Start(TIMR_TypeDef * TIMRx)
{
	TIMRx->CTRL |= (1 << TIMR_CTRL_EN_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Stop()
* 功能说明:	停止定时器
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Stop(TIMR_TypeDef * TIMRx)
{
	TIMRx->CTRL &= ~(1 << TIMR_CTRL_EN_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Halt()
* 功能说明:	暂停定时器，计数值保持不变
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Halt(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->HALT |= (0x01 << TIMRG_HALT_TIMR3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_Resume()
* 功能说明:	恢复定时器，从暂停处继续计数
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_Resume(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->HALT &= ~(0x01 << TIMRG_HALT_TIMR3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_SetPeriod()
* 功能说明:	设置定时/计数周期
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
*			uint32_t period			定时/计数周期
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_SetPeriod(TIMR_TypeDef * TIMRx, uint32_t period)
{
	TIMRx->LDVAL = period;
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_GetPeriod()
* 功能说明:	获取定时/计数周期
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t				当前定时/计数周期
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_GetPeriod(TIMR_TypeDef * TIMRx)
{
	return TIMRx->LDVAL; 
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_GetCurValue()
* 功能说明:	获取当前计数值
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t				当前计数值
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_GetCurValue(TIMR_TypeDef * TIMRx)
{
	return TIMRx->CVAL;
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_INTEn()
* 功能说明:	使能中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTEn(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IM0 &= ~(1 << TIMRG_IM_IF_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IM1 &= ~(1 << TIMRG_IM_IF_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IM2 &= ~(1 << TIMRG_IM_IF_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IM3 &= ~(1 << TIMRG_IM_IF_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_INTDis()
* 功能说明:	禁能中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTDis(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IM0 |= (1 << TIMRG_IM_IF_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IM1 |= (1 << TIMRG_IM_IF_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IM2 |= (1 << TIMRG_IM_IF_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IM3 |= (1 << TIMRG_IM_IF_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_INTClr()
* 功能说明:	清除中断标志
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_INTClr(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IF0 = (0x01 << TIMRG_IF_IF_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IF1 = (0x01 << TIMRG_IF_IF_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IF2 = (0x01 << TIMRG_IF_IF_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IF3 = (0x01 << TIMRG_IF_IF_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_INTStat()
* 功能说明:	获取中断状态
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t 				0 TIMRx未产生中断    1 TIMRx产生了中断
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_INTStat(TIMR_TypeDef * TIMRx)
{
	uint32_t stat = 0;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		stat = ((TIMRG->IF0 >> TIMRG_IF_IF_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR1):
		stat = ((TIMRG->IF1 >> TIMRG_IF_IF_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR2):
		stat = ((TIMRG->IF2 >> TIMRG_IF_IF_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR3):
		stat = ((TIMRG->IF3 >> TIMRG_IF_IF_Pos) & 1);
		break;
	}
	
	return stat;
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_OC_Init()
* 功能说明:	输出比较功能初始化
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
*			uint16_t match			当计数器的值递减到match时引脚输出电平翻转
*			uint32_t match_int_en	当计数器的值递减到match时是否产生中断
*			uint32_t init_lvl		初始输出电平
* 输    出: 无
* 注意事项: 使用Output Compare功能时TIMRx只有16位
******************************************************************************************************************************************/
void TIMR_OC_Init(TIMR_TypeDef * TIMRx, uint16_t match, uint32_t match_int_en, uint32_t init_lvl)
{
	TIMRx->CTRL &= ~(TIMR_CTRL_OC_MODE_Msk | TIMR_CTRL_OC_INILVL_Msk);
	TIMRx->CTRL |= (0 << TIMR_CTRL_OC_MODE_Pos) |
				   (init_lvl << TIMR_CTRL_OC_INILVL_Pos);
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->OCEN |= (1 << TIMRG_OCEN_TIMR0_Pos);
		TIMRG->OCMSK &= ~(1 << TIMRG_OCMSK_TIMR0_Pos);
		TIMRG->OCMAT0 = ((TIMR0->LDVAL) << 16) | match;
		TIMR_OC_INTClr(TIMR0);
		TIMRG->IE0 |= (1 << TIMRG_IE_OCMAT1_Pos);
		if(match_int_en) TIMRG->IM0 &= ~(1 << TIMRG_IM_OCMAT1_Pos);
		else			 TIMRG->IM0 |=  (1 << TIMRG_IM_OCMAT1_Pos);
		if(match_int_en | ((TIMRG->IM0 & TIMRG_IM_IF_Msk) == 0)) 
		{
			NVIC_EnableIRQ(TIMR0_IRQn);
		}
		else
		{
			NVIC_DisableIRQ(TIMR0_IRQn);
		}
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->OCEN |= (1 << TIMRG_OCEN_TIMR1_Pos);
		TIMRG->OCMSK &= ~(1 << TIMRG_OCMSK_TIMR1_Pos);
		TIMRG->OCMAT1 =  ((TIMR1->LDVAL) << 16) | match;
		TIMR_OC_INTClr(TIMR1);
		TIMRG->IE1 |= (1 << TIMRG_IE_OCMAT1_Pos);
		if(match_int_en) TIMRG->IM1 &= ~(1 << TIMRG_IM_OCMAT1_Pos);
		else			 TIMRG->IM1 |=  (1 << TIMRG_IM_OCMAT1_Pos);
		if(match_int_en | ((TIMRG->IM1 & TIMRG_IM_IF_Msk) == 0)) 
		{
			NVIC_EnableIRQ(TIMR1_IRQn);
		}
		else
		{
			NVIC_DisableIRQ(TIMR1_IRQn);
		}
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->OCEN |= (1 << TIMRG_OCEN_TIMR2_Pos);
		TIMRG->OCMSK &= ~(1 << TIMRG_OCMSK_TIMR2_Pos);
		TIMRG->OCMAT2 =  ((TIMR2->LDVAL) << 16) | match;
		TIMR_OC_INTClr(TIMR2);
		TIMRG->IE2 |= (1 << TIMRG_IE_OCMAT1_Pos);
		if(match_int_en) TIMRG->IM2 &= ~(1 << TIMRG_IM_OCMAT1_Pos);
		else			 TIMRG->IM2 |=  (1 << TIMRG_IM_OCMAT1_Pos);
		if(match_int_en | ((TIMRG->IM2 & TIMRG_IM_IF_Msk) == 0)) 
		{
			NVIC_EnableIRQ(TIMR2_IRQn);
		}
		else
		{
			NVIC_DisableIRQ(TIMR2_IRQn);
		}
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->OCEN |= (1 << TIMRG_OCEN_TIMR3_Pos);
		TIMRG->OCMSK &= ~(1 << TIMRG_OCMSK_TIMR3_Pos);
		TIMRG->OCMAT3 =  ((TIMR3->LDVAL) << 16) | match;
		TIMR_OC_INTClr(TIMR3);
		TIMRG->IE3 |= (1 << TIMRG_IE_OCMAT1_Pos);
		if(match_int_en) TIMRG->IM3 &= ~(1 << TIMRG_IM_OCMAT1_Pos);
		else			 TIMRG->IM3 |=  (1 << TIMRG_IM_OCMAT1_Pos);
		if(match_int_en | ((TIMRG->IM3 & TIMRG_IM_IF_Msk) == 0)) 
		{
			NVIC_EnableIRQ(TIMR3_IRQn);
		}
		else
		{
			NVIC_DisableIRQ(TIMR3_IRQn);
		}
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_OC_OutputEn()
* 功能说明:	使能输出比较功能的波形输出
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_OutputEn(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->OCMSK &= ~(1 << TIMRG_OCMSK_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->OCMSK &= ~(1 << TIMRG_OCMSK_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->OCMSK &= ~(1 << TIMRG_OCMSK_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->OCMSK &= ~(1 << TIMRG_OCMSK_TIMR3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_OC_OutputDis()
* 功能说明:	禁止输出比较功能的波形输出，且让输出比较功能引脚保持level电平
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
*			uint32_t level			禁止输出波形后在引脚上保持的电平
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_OutputDis(TIMR_TypeDef * TIMRx, uint32_t level)
{
	TIMRx->CTRL &= ~TIMR_CTRL_OC_INILVL_Msk;
	TIMRx->CTRL |= (level << TIMR_CTRL_OC_INILVL_Pos);
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->OCMSK |= (1 << TIMRG_OCMSK_TIMR0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->OCMSK |= (1 << TIMRG_OCMSK_TIMR1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->OCMSK |= (1 << TIMRG_OCMSK_TIMR2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->OCMSK |= (1 << TIMRG_OCMSK_TIMR3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_OC_SetMatch()
* 功能说明:	设置输出比较功能的比较值
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
*			uint16_t match			输出比较功能的比较值
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_SetMatch(TIMR_TypeDef * TIMRx, uint16_t match)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->OCMAT0 = ((TIMR0->LDVAL) << 16) | match;
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->OCMAT1 = ((TIMR1->LDVAL) << 16) | match;
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->OCMAT2 = ((TIMR2->LDVAL) << 16) | match;
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->OCMAT3 = ((TIMR3->LDVAL) << 16) | match;
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_OC_GetMatch()
* 功能说明:	获取输出比较功能的比较值
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint16_t				输出比较功能的比较值
* 注意事项: 无
******************************************************************************************************************************************/
uint16_t TIMR_OC_GetMatch(TIMR_TypeDef * TIMRx)
{
	uint16_t match = 0;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		match = TIMRG->OCMAT0;
		break;
	
	case ((uint32_t)TIMR1):
		match = TIMRG->OCMAT1;
		break;
	
	case ((uint32_t)TIMR2):
		match = TIMRG->OCMAT2;
		break;
	
	case ((uint32_t)TIMR3):
		match = TIMRG->OCMAT3;
		break;
	}
	
	return match;
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_OC_INTEn()
* 功能说明:	使能输出比较中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_INTEn(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IM0 &= ~(1 << TIMRG_IM_OCMAT1_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IM1 &= ~(1 << TIMRG_IM_OCMAT1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IM2 &= ~(1 << TIMRG_IM_OCMAT1_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IM3 &= ~(1 << TIMRG_IM_OCMAT1_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_OC_INTDis()
* 功能说明:	禁能输出比较中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_INTDis(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IM0 |= (1 << TIMRG_IM_OCMAT1_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IM1 |= (1 << TIMRG_IM_OCMAT1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IM2 |= (1 << TIMRG_IM_OCMAT1_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IM3 |= (1 << TIMRG_IM_OCMAT1_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_OC_INTClr()
* 功能说明:	清除输出比较中断标志
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_OC_INTClr(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IF0 = (0x01 << TIMRG_IF_OCMAT1_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IF1 = (0x01 << TIMRG_IF_OCMAT1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IF2 = (0x01 << TIMRG_IF_OCMAT1_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IF3 = (0x01 << TIMRG_IF_OCMAT1_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_OC_INTStat()
* 功能说明:	获取输出比较中断状态
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t 				0 输出比较match未发生   1 输出比较match发生
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_OC_INTStat(TIMR_TypeDef * TIMRx)
{
	uint32_t stat = 0;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		stat = ((TIMRG->IF0 >> TIMRG_IF_OCMAT1_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR1):
		stat = ((TIMRG->IF1 >> TIMRG_IF_OCMAT1_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR2):
		stat = ((TIMRG->IF2 >> TIMRG_IF_OCMAT1_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR3):
		stat = ((TIMRG->IF3 >> TIMRG_IF_OCMAT1_Pos) & 1);
		break;
	}
	
	return stat;
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_Init()
* 功能说明:	输入捕获功能初始化
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
*			uint32_t start_lvl		0 起始测量低电平长度    1 起始测量高电平长度
*			uint32_t captureH_int_en	测量高电平长度完成中断使能
*			uint32_t captureL_int_en	测量低电平长度完成中断使能
*			uint32_t captureOV_int_en	测量高/低电平长度溢出中断使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_Init(TIMR_TypeDef * TIMRx, uint32_t start_lvl, uint32_t captureH_int_en, uint32_t captureL_int_en, uint32_t captureOV_int_en)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->ICCR &= ~(TIMRG_ICCR_EN0_Msk | TIMRG_ICCR_POL0_Msk);
		TIMRG->ICCR |= (1 << TIMRG_ICCR_EN0_Pos) |
					   (start_lvl << TIMRG_ICCR_POL0_Pos);
		TIMRG->IE0 |= (1 << TIMRG_IE_ICH_Pos) |
					  (1 << TIMRG_IE_ICL_Pos) |
					  (1 << TIMRG_IE_ICOV_Pos);
		TIMR_IC_CaptureH_INTClr(TIMR0);
		if(captureH_int_en)  TIMRG->IM0 &= ~(1 << TIMRG_IM_ICH_Pos);
		else                 TIMRG->IM0 |=  (1 << TIMRG_IM_ICH_Pos);
		TIMR_IC_CaptureL_INTClr(TIMR0);
		if(captureL_int_en)  TIMRG->IM0 &= ~(1 << TIMRG_IM_ICL_Pos);
		else                 TIMRG->IM0 |=  (1 << TIMRG_IM_ICL_Pos);
		TIMR_IC_CaptureOV_INTClr(TIMR0);
		if(captureOV_int_en) TIMRG->IM0 &= ~(1 << TIMRG_IM_ICOV_Pos);
		else                 TIMRG->IM0 |=  (1 << TIMRG_IM_ICOV_Pos);
		if(captureH_int_en | captureL_int_en | captureOV_int_en | ((TIMRG->IM0 & TIMRG_IM_IF_Msk) == 0)) 
		{
			NVIC_EnableIRQ(TIMR0_IRQn);
		}
		else
		{
			NVIC_DisableIRQ(TIMR0_IRQn);
		}
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->ICCR &= ~(TIMRG_ICCR_EN1_Msk | TIMRG_ICCR_POL1_Msk);
		TIMRG->ICCR |= (1 << TIMRG_ICCR_EN1_Pos) |
					   (start_lvl << TIMRG_ICCR_POL1_Pos);
		TIMRG->IE1 |= (1 << TIMRG_IE_ICH_Pos) |
					  (1 << TIMRG_IE_ICL_Pos) |
					  (1 << TIMRG_IE_ICOV_Pos);
		TIMR_IC_CaptureH_INTClr(TIMR1);
		if(captureH_int_en)  TIMRG->IM1 &= ~(1 << TIMRG_IM_ICH_Pos);
		else                 TIMRG->IM1 |=  (1 << TIMRG_IM_ICH_Pos);
		TIMR_IC_CaptureL_INTClr(TIMR1);
		if(captureL_int_en)  TIMRG->IM1 &= ~(1 << TIMRG_IM_ICL_Pos);
		else                 TIMRG->IM1 |=  (1 << TIMRG_IM_ICL_Pos);
		TIMR_IC_CaptureOV_INTClr(TIMR1);
		if(captureOV_int_en) TIMRG->IM1 &= ~(1 << TIMRG_IM_ICOV_Pos);
		else                 TIMRG->IM1 |=  (1 << TIMRG_IM_ICOV_Pos);
		if(captureH_int_en | captureL_int_en | captureOV_int_en | ((TIMRG->IM1 & TIMRG_IM_IF_Msk) == 0)) 
		{
			NVIC_EnableIRQ(TIMR1_IRQn);
		}
		else
		{
			NVIC_DisableIRQ(TIMR1_IRQn);
		}
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->ICCR &= ~(TIMRG_ICCR_EN2_Msk | TIMRG_ICCR_POL2_Msk);
		TIMRG->ICCR |= (1 << TIMRG_ICCR_EN2_Pos) |
					   (start_lvl << TIMRG_ICCR_POL2_Pos);
		TIMRG->IE2 |= (1 << TIMRG_IE_ICH_Pos) |
					  (1 << TIMRG_IE_ICL_Pos) |
					  (1 << TIMRG_IE_ICOV_Pos);
		TIMR_IC_CaptureH_INTClr(TIMR2);
		if(captureH_int_en)  TIMRG->IM2 &= ~(1 << TIMRG_IM_ICH_Pos);
		else                 TIMRG->IM2 |=  (1 << TIMRG_IM_ICH_Pos);
		TIMR_IC_CaptureL_INTClr(TIMR2);
		if(captureL_int_en)  TIMRG->IM2 &= ~(1 << TIMRG_IM_ICL_Pos);
		else                 TIMRG->IM2 |=  (1 << TIMRG_IM_ICL_Pos);
		TIMR_IC_CaptureOV_INTClr(TIMR2);
		if(captureOV_int_en) TIMRG->IM2 &= ~(1 << TIMRG_IM_ICOV_Pos);
		else                 TIMRG->IM2 |=  (1 << TIMRG_IM_ICOV_Pos);
		if(captureH_int_en | captureL_int_en | captureOV_int_en | ((TIMRG->IM2 & TIMRG_IM_IF_Msk) == 0)) 
		{
			NVIC_EnableIRQ(TIMR2_IRQn);
		}
		else
		{
			NVIC_DisableIRQ(TIMR2_IRQn);
		}
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->ICCR &= ~(TIMRG_ICCR_EN3_Msk | TIMRG_ICCR_POL3_Msk);
		TIMRG->ICCR |= (1 << TIMRG_ICCR_EN3_Pos) |
					   (start_lvl << TIMRG_ICCR_POL3_Pos);
		TIMRG->IE3 |= (1 << TIMRG_IE_ICH_Pos) |
					  (1 << TIMRG_IE_ICL_Pos) |
					  (1 << TIMRG_IE_ICOV_Pos);
		TIMR_IC_CaptureH_INTClr(TIMR3);
		if(captureH_int_en)  TIMRG->IM3 &= ~(1 << TIMRG_IM_ICH_Pos);
		else                 TIMRG->IM3 |=  (1 << TIMRG_IM_ICH_Pos);
		TIMR_IC_CaptureL_INTClr(TIMR3);
		if(captureL_int_en)  TIMRG->IM3 &= ~(1 << TIMRG_IM_ICL_Pos);
		else                 TIMRG->IM3 |=  (1 << TIMRG_IM_ICL_Pos);
		TIMR_IC_CaptureOV_INTClr(TIMR3);
		if(captureOV_int_en) TIMRG->IM3 &= ~(1 << TIMRG_IM_ICOV_Pos);
		else                 TIMRG->IM3 |=  (1 << TIMRG_IM_ICOV_Pos);
		if(captureH_int_en | captureL_int_en | captureOV_int_en | ((TIMRG->IM3 & TIMRG_IM_IF_Msk) == 0)) 
		{
			NVIC_EnableIRQ(TIMR3_IRQn);
		}
		else
		{
			NVIC_DisableIRQ(TIMR3_IRQn);
		}
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_Start()
* 功能说明:	输入捕获功能启动，只有当系统中只使用一路输入捕获时使用此函数启动，当系统中使用多路输入捕获时须使用TIMR_IC_Start_Multi()启动
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 只有当系统中只使用一路输入捕获时使用此函数启动，当系统中使用多路输入捕获时须使用TIMR_IC_Start_Multi()启动
******************************************************************************************************************************************/
void TIMR_IC_Start(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->ICCR |= (1 << TIMRG_ICCR_GO0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->ICCR |= (1 << TIMRG_ICCR_GO1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->ICCR |= (1 << TIMRG_ICCR_GO2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->ICCR |= (1 << TIMRG_ICCR_GO3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_Start_Multi()
* 功能说明:	输入捕获功能启动，同时启动多路
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
*			uint32_t timr0			是否启动TIMR0输入捕获功能，0 不启动   1 启动
*			uint32_t timr1			是否启动TIMR1输入捕获功能，0 不启动   1 启动
*			uint32_t timr2			是否启动TIMR2输入捕获功能，0 不启动   1 启动
*			uint32_t timr3			是否启动TIMR3输入捕获功能，0 不启动   1 启动
* 输    出: 无
* 注意事项: 系统中使用多路输入捕获时须使用TIMR_IC_Start_Multi()启动
******************************************************************************************************************************************/
void TIMR_IC_Start_Multi(uint32_t timr0, uint32_t timr1, uint32_t timr2, uint32_t timr3)
{
	TIMRG->ICCR |= (timr0 << TIMRG_ICCR_GO0_Pos) | 
				   (timr1 << TIMRG_ICCR_GO1_Pos) | 
				   (timr2 << TIMRG_ICCR_GO2_Pos) | 
				   (timr3 << TIMRG_ICCR_GO3_Pos);
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_Stop()
* 功能说明:	输入捕获功能停止
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_Stop(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->ICCR &= ~(1 << TIMRG_ICCR_GO0_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->ICCR &= ~(1 << TIMRG_ICCR_GO1_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->ICCR &= ~(1 << TIMRG_ICCR_GO2_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->ICCR &= ~(1 << TIMRG_ICCR_GO3_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_GetCaptureH()
* 功能说明:	获取高电平长度测量结果
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t				高电平长度测量结果
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_IC_GetCaptureH(TIMR_TypeDef * TIMRx)
{
	uint32_t capture = 0;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		capture = TIMRG->ICVAL0H;
		break;
	
	case ((uint32_t)TIMR1):
		capture = TIMRG->ICVAL1H;
		break;
	
	case ((uint32_t)TIMR2):
		capture = TIMRG->ICVAL2H;
		break;
	
	case ((uint32_t)TIMR3):
		capture = TIMRG->ICVAL3H;
		break;
	}
	
	return capture;
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_GetCaptureL()
* 功能说明:	获取低电平长度测量结果
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t				低电平长度测量结果
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_IC_GetCaptureL(TIMR_TypeDef * TIMRx)
{
	uint32_t capture = 0;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		capture = TIMRG->ICVAL0L;
		break;
	
	case ((uint32_t)TIMR1):
		capture = TIMRG->ICVAL1L;
		break;
	
	case ((uint32_t)TIMR2):
		capture = TIMRG->ICVAL2L;
		break;
	
	case ((uint32_t)TIMR3):
		capture = TIMRG->ICVAL3L;
		break;
	}
	
	return capture;
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_IC_CaptureH_INTEn()
* 功能说明:	使能输入捕获高电平长度测量完成中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureH_INTEn(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IM0 &= ~(1 << TIMRG_IM_ICH_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IM1 &= ~(1 << TIMRG_IM_ICH_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IM2 &= ~(1 << TIMRG_IM_ICH_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IM3 &= ~(1 << TIMRG_IM_ICH_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_CaptureH_INTDis()
* 功能说明:	禁能输入捕获高电平长度测量完成中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureH_INTDis(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IM0 |= (1 << TIMRG_IM_ICH_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IM1 |= (1 << TIMRG_IM_ICH_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IM2 |= (1 << TIMRG_IM_ICH_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IM3 |= (1 << TIMRG_IM_ICH_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_IC_CaptureH_INTClr()
* 功能说明:	清除输入捕获高电平长度测量完成中断标志
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureH_INTClr(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IF0 = (0x01 << TIMRG_IF_ICH_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IF1 = (0x01 << TIMRG_IF_ICH_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IF2 = (0x01 << TIMRG_IF_ICH_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IF3 = (0x01 << TIMRG_IF_ICH_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_CaptureH_INTStat()
* 功能说明:	获取输入捕获高电平长度测量完成中断状态
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t 				0 高电平长度测量未完成    1 高电平长度测量完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_IC_CaptureH_INTStat(TIMR_TypeDef * TIMRx)
{
	uint32_t stat = 0;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		stat = ((TIMRG->IF0 >> TIMRG_IF_ICH_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR1):
		stat = ((TIMRG->IF1 >> TIMRG_IF_ICH_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR2):
		stat = ((TIMRG->IF2 >> TIMRG_IF_ICH_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR3):
		stat = ((TIMRG->IF3 >> TIMRG_IF_ICH_Pos) & 1);
		break;
	}
	
	return stat;
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_IC_CaptureL_INTEn()
* 功能说明:	使能输入捕获低电平长度测量完成中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureL_INTEn(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IM0 &= ~(1 << TIMRG_IM_ICL_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IM1 &= ~(1 << TIMRG_IM_ICL_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IM2 &= ~(1 << TIMRG_IM_ICL_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IM3 &= ~(1 << TIMRG_IM_ICL_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_CaptureL_INTDis()
* 功能说明:	禁能输入捕获低电平长度测量完成中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureL_INTDis(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IM0 |= (1 << TIMRG_IM_ICL_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IM1 |= (1 << TIMRG_IM_ICL_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IM2 |= (1 << TIMRG_IM_ICL_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IM3 |= (1 << TIMRG_IM_ICL_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_IC_CaptureL_INTClr()
* 功能说明:	清除输入捕获低电平长度测量完成中断标志
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureL_INTClr(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IF0 = (0x01 << TIMRG_IF_ICL_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IF1 = (0x01 << TIMRG_IF_ICL_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IF2 = (0x01 << TIMRG_IF_ICL_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IF3 = (0x01 << TIMRG_IF_ICL_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_CaptureL_INTStat()
* 功能说明:	获取输入捕获低电平长度测量完成中断状态
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t 				0 低电平长度测量未完成    1 低电平长度测量完成
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_IC_CaptureL_INTStat(TIMR_TypeDef * TIMRx)
{
	uint32_t stat = 0;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		stat = ((TIMRG->IF0 >> TIMRG_IF_ICL_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR1):
		stat = ((TIMRG->IF1 >> TIMRG_IF_ICL_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR2):
		stat = ((TIMRG->IF2 >> TIMRG_IF_ICL_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR3):
		stat = ((TIMRG->IF3 >> TIMRG_IF_ICL_Pos) & 1);
		break;
	}
	
	return stat;
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_IC_CaptureOV_INTEn()
* 功能说明:	使能输入捕获溢出中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureOV_INTEn(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IM0 &= ~(1 << TIMRG_IM_ICOV_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IM1 &= ~(1 << TIMRG_IM_ICOV_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IM2 &= ~(1 << TIMRG_IM_ICOV_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IM3 &= ~(1 << TIMRG_IM_ICOV_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_CaptureOV_INTDis()
* 功能说明:	禁能输入捕获溢出中断
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureOV_INTDis(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IM0 |= (1 << TIMRG_IM_ICOV_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IM1 |= (1 << TIMRG_IM_ICOV_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IM2 |= (1 << TIMRG_IM_ICOV_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IM3 |= (1 << TIMRG_IM_ICOV_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称:	TIMR_IC_CaptureOV_INTClr()
* 功能说明:	清除输入捕获溢出中断标志
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void TIMR_IC_CaptureOV_INTClr(TIMR_TypeDef * TIMRx)
{
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		TIMRG->IF0 = (0x01 << TIMRG_IF_ICOV_Pos);
		break;
	
	case ((uint32_t)TIMR1):
		TIMRG->IF1 = (0x01 << TIMRG_IF_ICOV_Pos);
		break;
	
	case ((uint32_t)TIMR2):
		TIMRG->IF2 = (0x01 << TIMRG_IF_ICOV_Pos);
		break;
	
	case ((uint32_t)TIMR3):
		TIMRG->IF3 = (0x01 << TIMRG_IF_ICOV_Pos);
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: TIMR_IC_CaptureOV_INTStat()
* 功能说明:	获取输入捕获溢出中断状态
* 输    入: TIMR_TypeDef * TIMRx	指定要被设置的定时器，可取值包括TIMR0、TIMR1、TIMR2、TIMR3
* 输    出: uint32_t 				0 未发生溢出    1 发生溢出
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t TIMR_IC_CaptureOV_INTStat(TIMR_TypeDef * TIMRx)
{
	uint32_t stat = 0;
	
	switch((uint32_t)TIMRx)
	{
	case ((uint32_t)TIMR0):
		stat = ((TIMRG->IF0 >> TIMRG_IF_ICOV_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR1):
		stat = ((TIMRG->IF1 >> TIMRG_IF_ICOV_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR2):
		stat = ((TIMRG->IF2 >> TIMRG_IF_ICOV_Pos) & 1);
		break;
	
	case ((uint32_t)TIMR3):
		stat = ((TIMRG->IF3 >> TIMRG_IF_ICOV_Pos) & 1);
		break;
	}
	
	return stat;
}
