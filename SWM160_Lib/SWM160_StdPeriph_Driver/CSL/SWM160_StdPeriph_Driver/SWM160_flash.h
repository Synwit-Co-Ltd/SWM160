#ifndef __SWM160_FLASH_H__
#define __SWM160_FLASH_H__


uint32_t FLASH_Erase(uint32_t addr);
uint32_t FLASH_Write(uint32_t addr, uint32_t buff[], uint32_t cnt);

#define FLASH_Read(addr)  *((volatile uint32_t *)(addr))

#if   defined ( __CC_ARM )

__asm void FlashSpeedX2(void);

#elif defined ( __ICCARM__ )

#endif

#endif //__SWM160_FLASH_H__
