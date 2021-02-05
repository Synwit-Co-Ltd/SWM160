#include "SWM160.h"
#include "serial_port.h"

int main(void)
{
	uint8_t chr;
	
	SystemInit();
	
	SPort_Init(115200);
   	
	while(1==1)
	{
		if (SPort_GetByte(&chr))
			SPort_PutByte(chr);
	}
}

