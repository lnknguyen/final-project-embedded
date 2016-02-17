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

#include "LCD/LiquidCrystal.h"
#include "LCD/lcd_port.h"
#include "LCD/MenuItem.h"
#include "LCD/IntegerEdit.h"
#include "LCD/SimpleMenu.h"
#include "LCD/BarGraph.h"

#include "Button_Handler/DebouncedInput.h"
#include "Button_Handler/PinEvent.h"

#include "Interrupt_Handler/systick.h"
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
	Init_RIT();

	//LiquidCrystal lcd(8,9,10,11,12,13);
	//lcd.begin(16,2);
	//lcd.clear();

	SimpleMenu menu;
	BarGraph bg( LiquidCrystal::Instance(),50,false);

	IntegerEdit temperature(LiquidCrystal::Instance(),bg, std::string("Temperature"), 0 ,80);
	IntegerEdit pressure( LiquidCrystal::Instance(),bg, std::string("Pressure"),0, 30);
	menu.addItem(new MenuItem(temperature));
	menu.addItem(new MenuItem(pressure));

	temperature.setValue(80);
	pressure.setValue(69);

	DebouncedInput up_btn(4,100);
	DebouncedInput down_btn(5,100);
	DebouncedInput ok_btn(6,100);
	DebouncedInput back_btn(7,100);

	PinEvent up(up_btn),down(down_btn),ok(ok_btn),back(back_btn);


	menu.event(MenuItem::show); // display first menu item
	while(1) {
		if (down_btn.read()){
			menu.event(MenuItem::down);
			Sleep(100);
		}
		if (up_btn.read()){
			menu.event(MenuItem::up);
			Sleep(100);
		}
		if (ok_btn.read()){
			menu.event(MenuItem::ok);
			Sleep(100);
		}
		if (back_btn.read()){
			menu.event(MenuItem::back);
			Sleep(100);
		}

	}
	return 0 ;
}
