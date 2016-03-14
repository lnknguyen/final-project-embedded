/*
 * lcd_port.h
 *
 *  Created on: 26.1.2016
 *      Author: krl
 */

#ifndef LCD_PORT_H_
#define LCD_PORT_H_
#include "../InterruptHandler/systick.h"

/* Definitions needed by Arduino LiquidCrystal library
 *
 * This file must be included after chip.h and/or board.h if either of them is also included
 * */
#define OUTPUT 1
#define HIGH 1
#define LOW 0
#define TICKRATE_HZ (1000)
#include <string>
#include <cstring>
using namespace std;


void digitalWrite(uint8_t pin, uint8_t val);
void pinMode(uint8_t pin, uint8_t mode);
void delayMicroseconds(int us);


#endif /* LCD_PORT_H_ */
