/*
 * systick.cpp
 *
 *  Created on: 31.1.2016
 *      Author: krl
 */
#include "../InterruptHandler/systick.h"

#include "chip.h"
#include <stdio.h>

static volatile unsigned int s_delay;
static volatile unsigned int systicks;
volatile bool adcdone = false;
volatile bool adcstart = false;
volatile int RIT_flag=0;

/*
 * Note: Systick handler must be declared with C-linkage otherwise the linker
 * can't set the interrupt vectors correctly
 */
#ifdef __cplusplus
extern "C" {
#endif

static volatile bool semaphore;
void SysTick_Handler(void){
	systicks++;
	semaphore = true;
	if(s_delay) s_delay--;
	if (systicks >= 100) {
		systicks = 0;
		adcstart = true;
	}
	Chip_ADC_StartSequencer(LPC_ADC0, ADC_SEQA_IDX);
}


void ADC0A_IRQHandler(void)
{
	uint32_t pending;

	/* Get pending interrupts */
	pending = Chip_ADC_GetFlags(LPC_ADC0);

	/* Sequence A completion interrupt */
	if (pending & ADC_FLAGS_SEQA_INT_MASK) {
		adcdone = true;
	}

	/* Clear any pending interrupts */
	Chip_ADC_ClearFlags(LPC_ADC0, pending);
}

void RIT_IRQHandler(void)
{
	// Acknowledge interrupt by clearing RIT interrupt flag
	Chip_RIT_ClearIntStatus(LPC_RITIMER);
	// disable RIT – we want a single interrupt after the wait is over
	Chip_RIT_Disable(LPC_RITIMER);
	// set a flag to notify main program
	RIT_flag=1;
}

}


void Sleep(uint16_t delay){
	s_delay = delay;
	while(s_delay);
}

uint32_t millis() {
	return systicks;
}

unsigned int GetSysticks()
{
	return systicks;
}
