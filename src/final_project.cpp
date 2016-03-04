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
#include "UI_Helper/ValueEdit.h"
#include "UI_Helper/RunningMode.h"
#include "UI_Helper/SimpleMenu.h"
#include "UI_Helper/BarGraph.h"
#include "UI_Helper/ComplexMenu.h"
#include "UI_Helper/ComplexItem.h"
#include "Interrupt_Handler/systick.h"
#include "Sensor/TemperatureSensor.h"

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

#ifdef __cplusplus
    extern "C"
    {
#endif
    	char *  itoa ( int value, char * str, int base );
#ifdef __cplusplus
    }
#endif

void printScreen(LiquidCrystal &lcd,std::string a){
	int length = a.length();
	length = (16-length)/2;
	lcd.setCursor(length,0);
	lcd.Print(a);
}

#ifdef __cplusplus
extern "C" {
#endif
void ADC0A_IRQHandler(void)
{
	uint32_t pending;

	/* Get pending interrupts */
	pending = Chip_ADC_GetFlags(LPC_ADC0);

	/* Sequence A completion interrupt */
	if (pending & ADC_FLAGS_SEQA_INT_MASK) {
		//adcdone = true;
	}

	/* Clear any pending interrupts */
	Chip_ADC_ClearFlags(LPC_ADC0, pending);
}
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

	Chip_ADC_Init(LPC_ADC0, 0);
	Chip_ADC_SetClockRate(LPC_ADC0, ADC_MAX_SAMPLE_RATE);
	Chip_ADC_SetupSequencer(LPC_ADC0, ADC_SEQA_IDX, (ADC_SEQ_CTRL_CHANSEL(0) | ADC_SEQ_CTRL_CHANSEL(3) | ADC_SEQ_CTRL_MODE_EOS));
	Chip_ADC_SetADC0Input(LPC_ADC0, 0);
	Chip_ADC_SetTrim(LPC_ADC0, ADC_TRIM_VRANGE_HIGHV);
	Chip_SWM_EnableFixedPin(SWM_FIXED_ADC0_0);
	Chip_SWM_EnableFixedPin(SWM_FIXED_ADC0_3);
	Chip_ADC_StartCalibration(LPC_ADC0);
	while (!(Chip_ADC_IsCalibrationDone(LPC_ADC0))) {}
	Chip_ADC_ClearFlags(LPC_ADC0, Chip_ADC_GetFlags(LPC_ADC0));
	Chip_ADC_EnableInt(LPC_ADC0, ADC_INTEN_SEQA_ENABLE);
	NVIC_EnableIRQ(ADC0_SEQA_IRQn);
	Chip_ADC_EnableSequencer(LPC_ADC0, ADC_SEQA_IDX);

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

	SimpleMenu menuTemp(lcd, "Temperature");
	SimpleMenu menuPress(lcd, "Pressure");
	SimpleMenu menuCO(lcd, "CO2");

	RunningMode runningTemp(lcd,21);
	RunningMode runningPress(lcd,80);
	RunningMode runningCO(lcd,40);

	ValueEdit temperature(lcd, std::string("Temperature"), 21);
	ValueEdit pressure(lcd, std::string("Pressure"),80);
	ValueEdit co(lcd, std::string("CO2"),40);

	menuTemp.addItem(new MenuItem(temperature));
	menuTemp.addItem(new MenuItem(runningTemp));
	menuPress.addItem(new MenuItem(pressure));
	menuPress.addItem(new MenuItem(runningPress));
	menuCO.addItem(new MenuItem(co));
	menuCO.addItem(new MenuItem(runningCO));

	mainMenu.addItem(new ComplexItem(menuTemp));
	mainMenu.addItem(new ComplexItem(menuPress));
	mainMenu.addItem(new ComplexItem(menuCO));

	TemperatureSensor temperatureSensor;
	printScreen(lcd, "Welcome!");
	while(1) {
		Chip_ADC_StartSequencer(LPC_ADC0, ADC_SEQA_IDX);
		runningTemp.setValue(temperature.getValue());
		runningTemp.displayValue(temperatureSensor.toValue());
		//display current Temp
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
