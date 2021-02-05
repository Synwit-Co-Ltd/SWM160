#ifndef __SWM160_WDT_H__
#define	__SWM160_WDT_H__

#define WDT_MODE_RESET			  0			//计数器减小到0时产生复位
#define WDT_MODE_INTERRUPT		  1			//计数器减小到LOAD/4时产生中断
#define WDT_MODE_INTERRUPT_RESET  2			//计数器减小到LOAD/4时产生中断，减小到0时产生复位

void WDT_Init(WDT_TypeDef * WDTx, uint32_t peroid, uint32_t mode);	//WDT看门狗初始化
void WDT_Start(WDT_TypeDef * WDTx);			//启动指定WDT，开始倒计时
void WDT_Stop(WDT_TypeDef * WDTx);			//关闭指定WDT，停止倒计时

void WDT_Feed(WDT_TypeDef * WDTx);			//喂狗，重新从装载值开始倒计时

int32_t WDT_GetValue(WDT_TypeDef * WDTx);	//获取指定看门狗定时器的当前倒计时值


void WDT_INTClr(WDT_TypeDef * WDTx);		//中断标志清除
uint32_t WDT_INTStat(WDT_TypeDef * WDTx);	//中断状态查询
 
#endif //__SWM160_WDT_H__
