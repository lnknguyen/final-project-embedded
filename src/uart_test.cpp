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

#include <cr_section_macros.h>
#include <cstring>
#include <cstdio>

#include "ModbusMaster.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/


/*****************************************************************************
 * Public functions
 ****************************************************************************/
static volatile int counter;
static volatile uint32_t systicks;

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
	systicks++;
	if(counter > 0) counter--;
}
#ifdef __cplusplus
}
#endif

void Sleep(int ms)
{
	counter = ms;
	while(counter > 0) {
		__WFI();
	}
}

/* this function is required by the modbus library */
uint32_t millis() {
	return systicks;
}

/**
 * @brief	Main UART program body
 * @return	Always returns 1
 */

void printRegister(ModbusMaster& node, uint16_t reg) {
	uint8_t result;
	// slave: read 16-bit registers starting at reg to RX buffer
	result = node.readHoldingRegisters(reg, 1);
}

void setFrequency(ModbusMaster& node, uint16_t freq) {


	node.writeSingleRegister(1, freq); // set motor frequency

	//printf("Set freq = %.1f\n", float(freq/400.00)); // for debugging

}


void abbModbusTest() {
	ModbusMaster node(2); // Create modbus object that connects to slave id 2

	node.begin(9600); // set transmission rate - other parameters are set inside the object and can't be changed here

	printRegister(node, 3); // for debugging

	node.writeSingleRegister(0, 0x0406); // prepare for starting

	printRegister(node, 3); // for debugging

	Sleep(1000); // give converter some time to set up
	// note: we should have a startup state machine that check converter status and acts per current status
	//       but we take the easy way out and just wait a while and hope that everything goes well

	printRegister(node, 3); // for debugging

	node.writeSingleRegister(0, 0x047F); // set drive to start mode

	printRegister(node, 3); // for debugging

	Sleep(1000); // give converter some time to set up
	// note: we should have a startup state machine that check converter status and acts per current status
	//       but we take the easy way out and just wait a while and hope that everything goes well

	printRegister(node, 3); // for debugging

	int i = 0;
	int j = 0;
	const uint16_t fa[20] = { 1000, 2000, 3000, 3500, 4000, 5000, 7000, 8000, 8300, 10000, 10000, 9000, 8000, 7000, 6000, 5000, 4000, 3000, 2000, 1000 };

	while (1) {
		uint8_t result;

		// slave: read (2) 16-bit registers starting at register 102 to RX buffer
		j = 0;
		do {
			result = node.readHoldingRegisters(102, 2);
			j++;
		} while(j < 3 && result != node.ku8MBSuccess);
		// note: sometimes we don't succeed on first read so we try up to threee times
		// if read is successful print frequency and current (scaled values)
		if (result == node.ku8MBSuccess) {
			printf("F=%4d, I=%4d  (ctr=%d)\n", node.getResponseBuffer(0), node.getResponseBuffer(1),j);
		}
		else {
			printf("ctr=%d\n",j);
		}

		Sleep(5000);
		i++;
		if(i >= 20) {
			i=0;
		}
		// frequency is scaled:
		// 20000 = 50 Hz, 0 = 0 Hz, linear scale 400 units/Hz
		setFrequency(node, fa[i]);
	}
}

void fanControl(int scaledFreq) {
	ModbusMaster node(2); // Create modbus object that connects to slave id 2

	node.begin(9600); // set transmission rate - other parameters are set inside the object and can't be changed here

	node.writeSingleRegister(0, 0x0406); // prepare for starting

	Sleep(1000); // give converter some time to set up
	// note: we should have a startup state machine that check converter status and acts per current status
	//       but we take the easy way out and just wait a while and hope that everything goes well

	node.writeSingleRegister(0, 0x047F); // set drive to start mode

	Sleep(1000); // give converter some time to set up
	// note: we should have a startup state machine that check converter status and acts per current status
	//       but we take the easy way out and just wait a while and hope that everything goes well


	// frequency is scaled:
	// 20000 = 50 Hz, 0 = 0 Hz, linear scale 400 units/Hz
	setFrequency(node, scaledFreq);
	Sleep(1000);
	node.writeSingleRegister(0, 1151);
	while (1) {

		//node.readHoldingRegisters(0, 6);
		/*
		printf("CW: %d\n",  node.getResponseBuffer(0));
		printf("R1: %d\n",  node.getResponseBuffer(1));
		printf("SW: %d\n",  node.getResponseBuffer(3));
		printf("F: %d\n",  node.getResponseBuffer(4));
		printf("I: %d\n\n",  node.getResponseBuffer(5));
		*/
		//printf("F: %.1f, I: %.1f \n",  float(node.getResponseBuffer(4)/10.0), float(node.getResponseBuffer(5)/10.0));
		//Sleep(1000);
		scaledFreq+=200;
		if(scaledFreq>5000) scaledFreq = 5000;

		setFrequency(node, scaledFreq);
		Sleep(3000);
		node.writeSingleRegister(0, 1151);
		//Sleep(1000);
		//node.writeSingleRegister(0, 1151);
	}
}


int main(void)
{

#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	// Set the LED to the state of "On"
	Board_LED_Set(0, true);
#endif
#endif

	/* Set up SWO to PIO1_2 */
	Chip_SWM_MovablePortPinAssign(SWM_SWO_O, 1, 2); // Needed for SWO printf

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / 1000);

	Board_LED_Set(0, false);
	Board_LED_Set(1, true);
	printf("Started\n");

	//abbModbusTest();
	fanControl(0);
	return 1;
}

