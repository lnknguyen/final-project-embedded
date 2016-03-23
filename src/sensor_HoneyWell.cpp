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

#include <math.h>
#include <cr_section_macros.h>
#include <stdlib.h>
#include <cstdio>
#include "I2C.h"

static volatile int counter;

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{
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


void i2cTest() {
	I2C i2c(0, 100000);
	uint8_t humidityData[6];
	uint8_t readHumidityCmd = 0x1;
	uint16_t humidity = 0;
	int16_t temperature = 0;
	int16_t scale_factor = (1 << 14) -1;

	while(1) {

		//int scale_factor = pow(2,14) -2;

		if (i2c.transaction(0x27, &readHumidityCmd, 1, humidityData, 4)) {
			/* Output temperature. */
			//humidity = (((~0 >> 10) & humidityData[0]) << 8) | humidityData[1];
			humidity = (  humidityData[0] << 6) | humidityData[1];
			temperature = ((humidityData[2] << 8) | humidityData[3])>>2;
			DEBUGOUT("Humidity: %.3f %\r\n",	(float)humidity/scale_factor);
			//DEBUGOUT("Humidity: %d %\r\n",	humidityData[0][2]);
			//DEBUGOUT("fff: %d Pa\r\n",	(humidityData[0] & ( 1 << 7 )) >> 6);
			DEBUGOUT("Temp: %.3f C\r\n",	(float)temperature/scale_factor*165-40);
		}
		else {
			DEBUGOUT("Error reading pressure.\r\n");
		}
		Sleep(1000);
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

	i2cTest();

	return 1;
}
