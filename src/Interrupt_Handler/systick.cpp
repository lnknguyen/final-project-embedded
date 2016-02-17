/*
 * systick.cpp
 *
 *  Created on: 31.1.2016
 *      Author: krl
 */
#include "systick.h"
#include "chip.h"

static volatile unsigned int counter;
static volatile unsigned int systicks;

/*
 * Note: Systick handler must be declared with C-linkage otherwise the linker
 * can't set the interrupt vectors correctly
 */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	systicks++;
	if(counter > 0) counter--;
}
#ifdef __cplusplus
}
#endif

unsigned int GetSysticks()
{
	return systicks;
}


void Sleep(unsigned int ms)
{
	counter = ms + 1; // add one to guarantee specified wait time
	while(counter > 0) {
		__WFI();
	}
}
