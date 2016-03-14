/*
 * systick.h
 *
 *  Created on: 31.1.2016
 *      Author: krl
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_
#include <stdint.h>

extern volatile bool adcdone;
extern volatile bool adcstart;
extern volatile int RIT_flag;


void Sleep(uint16_t delay);
uint32_t millis();
unsigned int GetSysticks();

#endif /* SYSTICK_H_ */
