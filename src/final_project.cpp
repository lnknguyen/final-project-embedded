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
#include "UI_Helper/MenuItem.h"
#include "UI_Helper/IntegerEdit.h"
#include "UI_Helper/TextEdit.h"
#include "UI_Helper/SimpleMenu.h"
#include "UI_Helper/BarGraph.h"
#include "UI_Helper/ComplexMenu.h"
#include "UI_Helper/ComplexItem.h"
#include "Interrupt_Handler/systick.h"

#include <cr_section_macros.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>


#define TICKRATE_HZ (100)
#define MAXBUTTONS 4
volatile static int preventOverlap = 0;
volatile static int menuLayout = 0;
static const uint8_t buttonport[] = {1,0,0,0};
static const uint8_t buttonpins[] = {9,29,9,10};

void InitButton(void)
{
	int idx;
	for (idx = 0; idx < MAXBUTTONS; idx++) {
		Chip_IOCON_PinMuxSet(LPC_IOCON, buttonport[idx], buttonpins[idx], (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, buttonport[idx],  buttonpins[idx]);
	}
}

int isPressed(void){
	if(Chip_GPIO_GetPinState(LPC_GPIO, 1, 9)==1){
		return 1;
	}
	else if(Chip_GPIO_GetPinState(LPC_GPIO, 0, 29)==1){
		return 2;
	}
	else if (Chip_GPIO_GetPinState(LPC_GPIO, 0, 9)==1){
		return 3;
	}
	else if ( Chip_GPIO_GetPinState(LPC_GPIO, 0, 10)==1){
		return 4;
	}
	else {
		preventOverlap =0;
		return -1;
	}
}

void printScreen(LiquidCrystal &lcd,std::string a){
	int length = a.length();
	length = (16-length)/2;
	lcd.setCursor(length,0);
	lcd.Print(a);
}


int main(void) {

	#if defined (__USE_LPCOPEN)
		// Read clock settings and update SystemCoreClock variable
		SystemCoreClockUpdate();
		#if !defined(NO_BOARD_LIB)
			// Set up and initialize all required blocks and
			// functions related to the board hardware
			Board_Init();
			Chip_RIT_Init(LPC_RITIMER);
			Chip_RIT_Enable(LPC_RITIMER);
			NVIC_EnableIRQ(RITIMER_IRQn);
		#endif
	#endif

	uint32_t sysTickRate;
	InitButton();
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / TICKRATE_HZ);


	LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
	lcd.begin(16, 2);
	lcd.setCursor(0,0);
	int k;

	ComplexMenu mainMenu;

	SimpleMenu menu(lcd, "Auto Mode");
	SimpleMenu menuAuto(lcd, "Manual Setting");
	SimpleMenu menuTime(lcd, "Time Setting");

	TextEdit autoMode(lcd, std::string("Auto Mode"), std::string("Default Setting"));

	IntegerEdit temperature(lcd, std::string("Temperature"), 21);
	IntegerEdit pressure(lcd, std::string("Pressure"),80);
	IntegerEdit humidity(lcd, std::string("Humidity"),40);
	IntegerEdit brightness(lcd, std::string("Brightness"),10);

	IntegerEdit timeModeEx1(lcd, std::string("Time Mode 1"), 21);
	IntegerEdit timeModeEx2(lcd, std::string("Time Mode 2"),80);


	menu.addItem(new MenuItem(autoMode));

	menuAuto.addItem(new MenuItem(temperature));
	menuAuto.addItem(new MenuItem(pressure));
	menuAuto.addItem(new MenuItem(humidity));
	menuAuto.addItem(new MenuItem(brightness));

	menuTime.addItem(new MenuItem(timeModeEx1));
	menuTime.addItem(new MenuItem(timeModeEx2));

	mainMenu.addItem(new ComplexItem(menu));
	mainMenu.addItem(new ComplexItem(menuAuto));
	mainMenu.addItem(new ComplexItem(menuTime));


	printScreen(lcd, "Welcome!");
	while(1) {
		k = isPressed();
		if(k >0) {
			preventOverlap++;
			if(preventOverlap==1 || preventOverlap >500000){

				if(k==1){
					mainMenu.baseEvent(ComplexItem::up);
				}
				else if(k==2){
					mainMenu.baseEvent(ComplexItem::down);
				}
				else if(k==3){
					if(preventOverlap==1) mainMenu.baseEvent(ComplexItem::ok);
				}
				else if(k==4){
					if(preventOverlap==1) mainMenu.baseEvent(ComplexItem::back);
				}
			}
		}
	}
	return 0 ;
}
