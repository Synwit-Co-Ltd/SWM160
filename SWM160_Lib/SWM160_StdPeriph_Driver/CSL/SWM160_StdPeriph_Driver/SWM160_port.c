/****************************************************************************************************************************************** 
* 文件名称: SWM160_port.c
* 功能说明:	SWM160单片机的端口引脚功能选择库函数
* 技术支持:	http://www.synwit.com.cn/e/tool/gbook/?bid=1
* 注意事项:
* 版本日期: V1.0.0		2016年1月30日
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
#include "SWM160_port.h"


/****************************************************************************************************************************************** 
* 函数名称: PORT_Init()
* 功能说明:	端口引脚功能选择，可用的功能见"SWM160_port.h"文件
* 输    入: PORT_TypeDef * PORTx	指定PORT端口，有效值包括PORTA、PORTB、PORTC、PORTD	
*			uint32_t n		   		指定PORT引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
*			uint32_t func	   		指定端口引脚要设定的功能，其可取值见"SWM160_port.h"文件
*			uint32_t digit_in_en	数字输入使能
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PORT_Init(PORT_TypeDef * PORTx, uint32_t n, uint32_t func, uint32_t digit_in_en)
{
	PORTx->FUNSEL &= ~(0x03 << (n*2));
	PORTx->FUNSEL |= func << (n*2);
	
	PORTx->INEN &= ~(0x01 << n);
	PORTx->INEN |= (digit_in_en << n);
}
