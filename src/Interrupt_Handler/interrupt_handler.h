/*
 * interrupt_handler.h
 *
 *  Created on: Feb 14, 2016
 *      Author: nguyenluong
 */

#ifndef INTERRUPT_HANDLER_INTERRUPT_HANDLER_H_
#define INTERRUPT_HANDLER_INTERRUPT_HANDLER_H_


volatile static uint32_t s_delay;

extern "C" void Systick_Handler(void);
extern "C" void RIT_IRQHandler(void);

extern void Sleep(uint32_t delay);


#endif /* INTERRUPT_HANDLER_INTERRUPT_HANDLER_H_ */
