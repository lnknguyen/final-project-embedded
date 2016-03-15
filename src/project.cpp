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
	Chip_SWM_MovablePortPinAssign(SWM_SWO_O, 1, 2);

	// TODO: insert code here
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

	InitButton();
}


int main(void) {

	systemInit();



	LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
	lcd.begin(16, 2);
	lcd.setCursor(0,0);
	int k;

	ComplexMenu mainMenu;

	SimpleMenu menuTemperature(lcd, "Temperature");
	SimpleMenu menuPressure(lcd, "Pressure");
	SimpleMenu menuCO2(lcd, "CO2");

	RunningMode runningTemperature(lcd,11);
	RunningMode runningPressure(lcd,80);
	RunningMode runningCO2(lcd,400);

	ValueEdit temperatureDesired(lcd, std::string("Temperature"), 11);
	ValueEdit pressureDesired(lcd, std::string("Pressure"),80);
	ValueEdit co2Desired(lcd, std::string("CO2"),400);

	menuTemperature.addItem(new MenuItem(temperatureDesired));
	menuTemperature.addItem(new MenuItem(runningTemperature));
	menuPressure.addItem(new MenuItem(pressureDesired));
	menuPressure.addItem(new MenuItem(runningPressure));
	menuCO2.addItem(new MenuItem(co2Desired));
	menuCO2.addItem(new MenuItem(runningCO2));

	mainMenu.addItem(new ComplexItem(menuTemperature));
	mainMenu.addItem(new ComplexItem(menuPressure));
	mainMenu.addItem(new ComplexItem(menuCO2));

	I2C i2c(0, 100000);
	TemperatureSensor temperatureSensor;
	PressureSensor pressureSensor(i2c);
	CO2Sensor co2Sensor;


	ModbusMaster node(2);
	ABBDrive abbDrive(node);
	abbDrive.init();
	float frequency=0;
	float frequencyIncrement=0;

	Controller controller(1.5,10);


	printf("Start\n");
	int temperatureDifference;
	int pressureDifference;
	int co2Difference;

	lcd.printString("Welcome");
	while(1) {

		if(mainMenu.getPosition()==0){
			//////TEMPERATURE//////
			//Calculate difference between Desired Temperature and Actual Sensor Temperature
			temperatureDifference = int(temperatureDesired.getValue()-temperatureSensor.toValue());
			//Controller output the ABB Drive frequency increment based on Temperature Difference
			frequencyIncrement = -controller.increment(temperatureDifference);
			//Display Desired Temperature value in Running Mode
			runningTemperature.setDesiredValue(temperatureDesired.getValue());
			//Display Actual Sensor Temperature, Temperature Difference, and Frequency Increment
			runningTemperature.displaySensorValue(temperatureSensor.toValue() ,temperatureDifference, frequencyIncrement);
			//runningTemperature.displaySensorValue(temperatureSensor.toValue() ,temperatureDifference, 0);
		}else if(mainMenu.getPosition()==1){
			//////PRESSURE//////
			//Calculate difference between Desired Pressure and Actual Sensor Pressure
			pressureDifference = int(pressureDesired.getValue()-pressureSensor.toValue());
			//Controller output the ABB Drive frequency increment based on Pressure Difference
			frequencyIncrement = controller.increment(pressureDifference);
			//Display Desired Pressure value in Running Mode
			runningPressure.setDesiredValue(pressureDesired.getValue());
			//Display Actual Sensor Pressure, Pressure Difference, and Frequency Increment
			runningPressure.displaySensorValue(int(pressureSensor.toValue()) ,pressureDifference, frequencyIncrement);
			//runningPressure.displaySensorValue(pressureSensor.toValue() ,pressureDifference, -1);
		}else if(mainMenu.getPosition()==2){
			//////CO2//////
			//Calculate difference between Desired CO2 and Actual Sensor CO2
			co2Difference = int(co2Desired.getValue()-co2Sensor.toValue());
			//Controller output the ABB Drive frequency increment based on CO2 Difference
			frequencyIncrement = controller.increment(co2Difference);
			//Display Desired CO2 value in Running Mode
			runningCO2.setDesiredValue(co2Desired.getValue());
			//Display Actual Sensor CO2, CO2 Difference, and Frequency Increment
			runningPressure.displaySensorValue(int(pressureSensor.toValue()) ,pressureDifference, frequencyIncrement);
			//runningCO2.displaySensorValue(int(co2Sensor.toValue()) ,co2Difference, -1);
		}



		//Add Frequency Increment to Current Frequency;
		frequency += frequencyIncrement;
		//Set Current Frequency to ABB Drive
		if (abbDrive.setFrequency(frequency)==0 ){
		//Read and print Frequency Feedback from ABB Drive
			//if (frequencyIncrement>0)
				frequency < abbDrive.getFrequency() ? frequency = frequency : frequency = abbDrive.getFrequency();
			//else
				//frequency > abbDrive.getFrequency() ? frequency = frequency : frequency = abbDrive.getFrequency();
		}
		//printf("Current frequency: %d\n",frequency);

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
		printf("%d\n", mainMenu.getPosition() );
	}


	return 0 ;
}
