/* ----------------------- System includes ----------------------------------*/

/* ----------------------- Modbus includes ----------------------------------*/
#include "port.h"
#include "mb.h"
#include "mbport.h"


BOOL xMBPortTimersInit(USHORT usTim1Timerout50us)
{
   TIMR_Init(TIMR0, TIMR_MODE_TIMER, SystemCoreClock*50/1000000 * usTim1Timerout50us, 1);

    return TRUE;
}

void vMBPortTimerClose(void)
{
	
}

void vMBPortTimersEnable(void)
{
	TIMR_Stop(TIMR0);
    TIMR_Start(TIMR0);	//关闭再打开，重新计数，复位
}

void vMBPortTimersDisable(void)
{
    TIMR_Stop(TIMR0);
}

void TIMR0_Handler( void )
{
    TIMR_INTClr(TIMR0);

    pxMBPortCBTimerExpired();
}




void vMBPortTimersDelay(USHORT usTimeOutMS)
{
    SysTick->CTRL = 0;
    SysTick->LOAD = SystemCoreClock / 1000;
    SysTick->VAL = 0;    // Clear COUNTFLAG
    SysTick->CTRL = ( 1 << SysTick_CTRL_CLKSOURCE_Pos) | ( 1<< SysTick_CTRL_ENABLE_Pos);
    while(usTimeOutMS)
    {
        while( 0 == ( SysTick->CTRL & ( 1 << SysTick_CTRL_COUNTFLAG_Pos ) ) );
        SysTick->VAL = 0;

        usTimeOutMS--;
    }
}
