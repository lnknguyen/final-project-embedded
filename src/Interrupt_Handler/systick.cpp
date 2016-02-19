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
static volatile bool semaphore;
void SysTick_Handler(void){
	semaphore = true;
}
}
