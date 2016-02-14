#include "interrupt_handler.h"

extern "C" {
	void SysTick_Handler(void){
		flag = true;
	}
}
