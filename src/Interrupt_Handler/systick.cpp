/*
 * systick.cpp
 *
 *  Created on: 31.1.2016
 *      Author: krl
 */
#include "systick.h"
#include "chip.h"
#include "../Sensor/TemperatureSensor.h"
#include <stdio.h>

static volatile unsigned int s_delay;
static volatile unsigned int systicks;
static volatile bool adcdone = false;
static volatile bool adcstart = false;
static volatile int counter = 0;
TemperatureSensor temperature;

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
uint32_t a0,d0,a3,d3;
void SysTick_Handler(void){
	semaphore = true;
	counter++;
	if(s_delay) s_delay--;
	if (counter > 100){
		counter = 0;
		temperature.toValue();
	}

}
}

void Sleep(uint16_t delay){
	s_delay = delay;
	while(s_delay);
}
