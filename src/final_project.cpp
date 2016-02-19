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

#include <vector>

#include "LCD/LiquidCrystal.h"
#include "LCD/lcd_port.h"
#include "UI_Helper/MenuItem.h"
#include "UI_Helper/IntegerEdit.h"
#include "UI_Helper/SimpleMenu.h"
#include "UI_Helper/BarGraph.h"

#include "Button_Handler/DebouncedInput.h"
#include "Button_Handler/PinEvent.h"

#include "Protocol/SceneProtocol.h"

#include "Menu_Scene/menu_scene.h"

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
	/*
	SimpleMenu menu;
	BarGraph bg( LiquidCrystal::Instance(),50,false);

	IntegerEdit temperature(LiquidCrystal::Instance(),bg, std::string("Temperature"), 0 ,80);
	IntegerEdit pressure( LiquidCrystal::Instance(),bg, std::string("Pressure"),0, 30);
	menu.addItem(new MenuItem(temperature));
	menu.addItem(new MenuItem(pressure));

	temperature.setValue(80);
	pressure.setValue(69);

	menu.event(MenuItem::show);
*/
	DebouncedInput up_btn(4,100);
	DebouncedInput down_btn(5,100);
	DebouncedInput ok_btn(6,100);
	DebouncedInput back_btn(7,100);

	PinEvent up(up_btn),down(down_btn),ok(ok_btn),back(back_btn);

	std::vector<DebouncedInput> btn;
	btn.push_back(up_btn);
	btn.push_back(down_btn);
	btn.push_back(ok_btn);
	btn.push_back(back_btn);

	SimpleMenu* menu = new SimpleMenu();

	MenuScene* scene = new MenuScene(menu,btn);
	scene->setup();
	scene->show();
	//menu.event(MenuItem::show);

	while(1) {
		scene->start();

	}
	return 0 ;
}
