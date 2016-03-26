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

#include "Buttons/DebouncedInput.h"
#include "Buttons/DigitalIoPin.h"
#include "Buttons/PinEvent.h"

#include <cr_section_macros.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdio>


#define TICKRATE_HZ (100)
#define MAXBUTTONS 4

void systemInit(){
#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
#endif
#endif
	/* Set up SWO to PIO1_2 */
	//Chip_SWM_MovablePortPinAssign(SWM_SWO_O, 1, 2);

	/* Setup ADC for 12-bit mode and normal power */
	Chip_ADC_Init(LPC_ADC0, 0);

	/* Setup for maximum ADC clock rate */
	Chip_ADC_SetClockRate(LPC_ADC0, ADC_MAX_SAMPLE_RATE);

	/* For ADC0, sequencer A will be used without threshold events.
	   It will be triggered manually  */
	Chip_ADC_SetupSequencer(LPC_ADC0, ADC_SEQA_IDX, (ADC_SEQ_CTRL_CHANSEL(0) | ADC_SEQ_CTRL_CHANSEL(3) | ADC_SEQ_CTRL_MODE_EOS));

	/* For ADC0, select analog input pint for channel 0 on ADC0 */
	Chip_ADC_SetADC0Input(LPC_ADC0, 0);

	/* Use higher voltage trim for both ADC */
	Chip_ADC_SetTrim(LPC_ADC0, ADC_TRIM_VRANGE_HIGHV);

	/* Assign ADC0_0 to PIO1_8 via SWM (fixed pin) and ADC0_3 to PIO0_5 */
	Chip_SWM_EnableFixedPin(SWM_FIXED_ADC0_0);
	Chip_SWM_EnableFixedPin(SWM_FIXED_ADC0_3);

	/* Need to do a calibration after initialization and trim */
	Chip_ADC_StartCalibration(LPC_ADC0);
	while (!(Chip_ADC_IsCalibrationDone(LPC_ADC0))) {}

	/* Clear all pending interrupts and status flags */
	Chip_ADC_ClearFlags(LPC_ADC0, Chip_ADC_GetFlags(LPC_ADC0));

	/* Enable sequence A completion interrupts for ADC0 */
	Chip_ADC_EnableInt(LPC_ADC0, ADC_INTEN_SEQA_ENABLE);

	/* Enable related ADC NVIC interrupts */
	NVIC_EnableIRQ(ADC0_SEQA_IRQn);

	/* Enable sequencer */
	Chip_ADC_EnableSequencer(LPC_ADC0, ADC_SEQA_IDX);

	/* Configure systick timer */
	SysTick_Config((Chip_Clock_GetSysTickClockRate() / TICKRATE_HZ));

	/* Enable RIT*/
	Chip_RIT_Init(LPC_RITIMER);
	NVIC_EnableIRQ(RITIMER_IRQn);
}

void handleRunning(RunningMode mode, SensorInterface* sensor, ValueEdit desired, float &diff){
	diff = desired.getValue()-sensor->toValue();
	//Display Desired CO2 value in Running Mode
	mode.setDesiredValue(desired.getValue());
	//Display Actual Sensor CO2, CO2 Difference, and Frequency Increment
	mode.displayValue(sensor->toValue() ,0 ,0 ,1);
	mode.displayValue(desired.getValue() ,0 ,12, 1);

	//mode.displayValue(diff ,0 ,4, 1);
	//runningPressure.displayValue(frequencyIncrement ,1 ,8, 1);
}

int main(void) {

	systemInit();

	LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
	lcd.begin(16, 2);
	lcd.setCursor(0,0);


	DebouncedInput up_btn(4,1);
	DebouncedInput down_btn(5,1);
	DebouncedInput ok_btn(6,1);
	DebouncedInput back_btn(7,1);

	PinEvent up(up_btn),down(down_btn),ok(ok_btn),back(back_btn);

	ComplexMenu mainMenu;

	SimpleMenu menuPressure(lcd, "Pressure");
	SimpleMenu menuTemperature(lcd, "Temperature");
	SimpleMenu menuCO2(lcd, "CO2");

	RunningMode runningPressure(lcd);
	RunningMode runningTemperature(lcd);
	RunningMode runningCO2(lcd);

	ValueEdit pressureDesired(lcd, std::string("Pressure"),30,0,135,1.0);
	ValueEdit temperatureDesired(lcd, std::string("Temperature"), 28,0.0,100.0,0.1);
	ValueEdit co2Desired(lcd, std::string("CO2"),400,100.0,5000.0,10.0);

	menuPressure.addItem(new MenuItem(pressureDesired));
	menuPressure.addItem(new MenuItem(runningPressure));
	menuTemperature.addItem(new MenuItem(temperatureDesired));
	menuTemperature.addItem(new MenuItem(runningTemperature));
	menuCO2.addItem(new MenuItem(co2Desired));
	menuCO2.addItem(new MenuItem(runningCO2));

	mainMenu.addItem(new ComplexItem(menuPressure));
	mainMenu.addItem(new ComplexItem(menuTemperature));
	mainMenu.addItem(new ComplexItem(menuCO2));

	I2C i2c(0, 100000);
	PressureSensor* pressureSensor = new PressureSensor(i2c);
	TemperatureSensor* temperatureSensor = new TemperatureSensor();
	CO2Sensor* co2Sensor = new CO2Sensor();


	ModbusMaster node(2);
	ABBDrive abbDrive(node);
	abbDrive.init();


	float frequency=0;
	float frequencyIncrement=0;

	Controller controller(.1,5);

	float valueDifference;
	lcd.printString("Welcome");
	while(1) {
		if(mainMenu.getPosition()==0){
			//////PRESSURE//////
			//lcd.clear();
			handleRunning(runningPressure,pressureSensor,pressureDesired,valueDifference);
		}else if(mainMenu.getPosition()==1){
			//////TEMPERATURE//////
			handleRunning(runningTemperature,temperatureSensor,temperatureDesired,valueDifference);
		}else if(mainMenu.getPosition()==2){
			//////CO2//////
			handleRunning(runningCO2,co2Sensor,co2Desired,valueDifference);
		}


		frequencyIncrement = controller.increment(valueDifference);
		//Add Frequency Increment to Current Frequency;
		frequency += frequencyIncrement;
		//Set Current Frequency to ABB Drive
		abbDrive.setFrequency(frequency);
		//Read and print Frequency Feedback from ABB Drive
		//frequency = abbDrive.getFrequency();

		Sleep(15);

		if(up_btn.read()){
			mainMenu.baseEvent(ComplexItem::up);
		}
		if(down_btn.read()){
			mainMenu.baseEvent(ComplexItem::down);
		}
		if(ok_btn.read()){
			mainMenu.baseEvent(ComplexItem::ok);
		}
		if(back_btn.read()){
			mainMenu.baseEvent(ComplexItem::back);
		}
		//printf("%d\n", mainMenu.getPosition() );
	}


	return 0 ;
}
