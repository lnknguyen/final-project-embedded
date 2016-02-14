/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
 */

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

#define TICKRATE_HZ (1000)

void Init_ADC();

void Init_RIT(){
	Chip_RIT_Init(LPC_RITIMER);
	//enable RIT interrupt
	NVIC_EnableIRQ(RITIMER_IRQn);
}


int main(void) {

#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
#endif
#endif

	SysTick_Config(Chip_Clock_GetSysTickClockRate() / TICKRATE_HZ);

	while(1) {

	}
	return 0 ;
}
