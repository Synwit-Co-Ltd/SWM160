#include "mb.h"
#include "mbport.h"


static ULONG ulNesting;


void vMBPortEnterCritical( void )
{
    __disable_irq();

    ulNesting++;
}

void vMBPortExitCritical( void )
{
    ulNesting--;

    if(ulNesting == 0)  __enable_irq();
}

void vMBPortClose( void )
{
extern void vMBPortSerialClose(void);
extern void vMBPortTimerClose(void);
    vMBPortSerialClose();
    vMBPortTimerClose();
}
