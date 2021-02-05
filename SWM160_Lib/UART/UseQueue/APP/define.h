#ifndef	_DEFINE_H
#define	_DEFINE_H

#include  "SWM160.h"

/* ------------------------------------------------------------------------------------------------
 *                                        Interrupt Macros
 * ------------------------------------------------------------------------------------------------
 */
#define HAL_ENABLE_INTERRUPTS()         			__enable_irq() 
#define HAL_DISABLE_INTERRUPTS()        			__disable_irq()
#define HAL_INTERRUPTS_ARE_ENABLED()    		(__get_PRIMASK() == 1)

typedef unsigned int halIntState_t;

#define HAL_ENTER_CRITICAL_SECTION(x)   		do { x = __get_PRIMASK();  \
													HAL_DISABLE_INTERRUPTS(); \
												} while (0)
												
#define HAL_EXIT_CRITICAL_SECTION(x)    	 	__set_PRIMASK(x)

#define HAL_CRITICAL_STATEMENT(x)       		do { halIntState_t _s; \
													HAL_ENTER_CRITICAL_SECTION(_s);\
													x; HAL_EXIT_CRITICAL_SECTION(_s);\
												}while(0)

#define WATCHDOG_RESET()				wdt->feed = 0x55

#include <stdio.h>

#ifndef NDEBUG
	#define PRINT		printf
	#define TRACE		PRINT
	#define assert(e)		do {\
							if (!(e)) \
							{\
								PRINT("ASSERT FAIL: %s, filename %s, line %d", #e, __FILE__, __LINE__); \
								while (1);\
							}\
						}while(0)
#else
	#define PRINT(...)
	#define TRACE(...)
	#define assert(x)
#endif

#endif

