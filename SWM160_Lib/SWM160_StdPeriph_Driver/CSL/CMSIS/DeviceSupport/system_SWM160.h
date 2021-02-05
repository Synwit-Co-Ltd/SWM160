#ifndef __SYSTEM_SWM160_H__
#define __SYSTEM_SWM160_H__

#ifdef __cplusplus
 extern "C" {
#endif



extern uint32_t SystemCoreClock;		// System Clock Frequency (Core Clock)
extern uint32_t CyclesPerUs;			// Cycles per micro second


/* Setup the microcontroller system Initialise GPIO directions and values */
extern void SystemInit(void);


/* Updates the SystemCoreClock with current core Clock retrieved from cpu registers */
extern void SystemCoreClockUpdate (void);

#ifdef __cplusplus
}
#endif

#endif //__SYSTEM_SWM160_H__
