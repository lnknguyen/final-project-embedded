/*
 * systick.cpp
 *
 *  Created on: 31.1.2016
 *      Author: krl
 */
#include "systick.h"
#include "chip.h"

static volatile unsigned int s_delay;
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
static volatile bool semaphore;
void SysTick_Handler(void){
	semaphore = true;
	if(s_delay) s_delay--;
}
}

void Sleep(uint16_t delay){
	s_delay = delay;
	while(s_delay);
}
