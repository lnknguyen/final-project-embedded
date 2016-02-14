/*
 * lcd_port.h
 *
 *  Created on: 26.1.2016
 *      Author: krl
 */

#ifndef LCD_PORT_H_
#define LCD_PORT_H_

#ifndef INTERRUPT_HANDLER_H_
#endif

/* Definitions needed by Arduino LiquidCrystal library
 *
 * This file must be included after chip.h and/or board.h if either of them is also included
 * */
#define OUTPUT 1
#define HIGH 1
#define LOW 0

volatile static bool RIT_flag;

void digitalWrite(uint8_t pin, uint8_t val);
void pinMode(uint8_t pin, uint8_t mode);
void delayMicroseconds(int us);
extern "C" void RIT_IRQHandler(void);


#endif /* LCD_PORT_H_ */
