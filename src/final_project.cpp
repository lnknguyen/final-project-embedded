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
#include "GUI/MenuItem.h"
#include "GUI/ValueEdit.h"
#include "GUI/RunningMode.h"
#include "GUI/SimpleMenu.h"
#include "GUI/BarGraph.h"
#include "GUI/ComplexMenu.h"
#include "GUI/ComplexItem.h"
#include "InterruptHandler/systick.h"
#include "Sensor/TemperatureSensor.h"
#include "Sensor/PressureSensor.h"
#include "Sensor/CO2Sensor.h"
#include "ABBDrive/ABBDrive.h"
#include "Controller/Controller.h"

#include <cr_section_macros.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdio>


#define TICKRATE_HZ (100)
#define MAXBUTTONS 4
volatile static int preventOverlap = 0;
volatile static int menuLayout = 0;
static const uint8_t buttonport[] = {0,0,1,0};
static const uint8_t buttonpins[] = {10,16,3,0};

void InitButton(void)
{
	int idx;
	for (idx = 0; idx < MAXBUTTONS; idx++) {
		Chip_IOCON_PinMuxSet(LPC_IOCON, buttonport[idx], buttonpins[idx], (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, buttonport[idx],  buttonpins[idx]);
	}
}

int isPressed(void){
	if(Chip_GPIO_GetPinState(LPC_GPIO, buttonport[0], buttonpins[0])==1){
		return 1;
	}
	else if(Chip_GPIO_GetPinState(LPC_GPIO, buttonport[1], buttonpins[1])==1){
		return 2;
	}
	else if (Chip_GPIO_GetPinState(LPC_GPIO, buttonport[2], buttonpins[2])==1){
		return 3;
	}
	else if ( Chip_GPIO_GetPinState(LPC_GPIO, buttonport[3], buttonpins[3])==1){
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

void init_ADC(void){
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
	init_ADC();
	Chip_Clock_SetSysTickClockDiv(1);
	sysTickRate = Chip_Clock_GetSysTickClockRate();
	SysTick_Config(sysTickRate / TICKRATE_HZ);
	I2C i2c(0, 100000);

	LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
	lcd.begin(16, 2);
	lcd.setCursor(0,0);
	int k;

	ComplexMenu mainMenu;

	SimpleMenu menuTemperature(lcd, "Temperature");
	SimpleMenu menuPressure(lcd, "Pressure");
	SimpleMenu menuCO2(lcd, "CO2");

	RunningMode runningTemperature(lcd,21);
	RunningMode runningPressure(lcd,80);
	RunningMode runningCO2(lcd,40);

	ValueEdit temperatureDesired(lcd, std::string("Temperature"), 21);
	ValueEdit pressureDesired(lcd, std::string("Pressure"),80);
	ValueEdit co2Desired(lcd, std::string("CO2"),40);

	menuTemperature.addItem(new MenuItem(temperatureDesired));
	menuTemperature.addItem(new MenuItem(runningTemperature));
	menuPressure.addItem(new MenuItem(pressureDesired));
	menuPressure.addItem(new MenuItem(runningPressure));
	menuCO2.addItem(new MenuItem(co2Desired));
	menuCO2.addItem(new MenuItem(runningCO2));

	mainMenu.addItem(new ComplexItem(menuTemperature));
	mainMenu.addItem(new ComplexItem(menuPressure));
	mainMenu.addItem(new ComplexItem(menuCO2));

	TemperatureSensor temperatureSensor;
	PressureSensor pressureSensor(i2c);
	CO2Sensor co2Sensor;

	/*
	ABBDrive abbDrive;
	abbDrive.init();
	int freq;
	 */
	Controller controller(2,1);

	printf("Start\n");
	int temperatureDifference;

	int pressureDifference;


	printScreen(lcd, "Welcome!");
	while(1) {
		/*abbDrive.setFrequency(12.5);
		freq = abbDrive.getFrequency();
		printf("Freq: %d\n", freq);
		printf("CO2: %d\n", co2.getValue());*/

		Chip_ADC_StartSequencer(LPC_ADC0, ADC_SEQA_IDX);

		temperatureDifference = temperatureDesired.getValue()-temperatureSensor.toValue();

		pressureDifference = pressureDesired.getValue()-pressureSensor.toValue();
		runningTemperature.setDesiredValue(temperatureDesired.getValue());
		runningTemperature.displaySensorValue(temperatureSensor.toValue(),controller.increment(temperatureDifference),temperatureDifference);
		runningPressure.setDesiredValue(pressureDesired.getValue());
		runningPressure.displaySensorValue(pressureSensor.toValue(),controller.increment(pressureDifference),pressureDifference);

		runningTemperature.setDesiredValue(temperatureDesired.getValue());
		runningTemperature.displaySensorValue(temperatureSensor.toValue(),controller.increment(temperatureDifference),temperatureDifference);
		runningPressure.setDesiredValue(pressureDesired.getValue());

		//runningPressure.displaySensorValue(pressureSensor.toValue());

		runningCO2.setDesiredValue(co2Desired.getValue());
		//runningCO2.displaySensorValue(co2Sensor.toValue());

		k = isPressed();
		if(k >0) {
			preventOverlap++;
			if(preventOverlap==1 || preventOverlap >7){
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
		Sleep(10);
	}
	return 0 ;
}
