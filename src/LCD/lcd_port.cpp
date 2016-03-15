
#include "board.h"
#include "lcd_port.h"
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;

static const int dPort[] = { 1, 1, 0, 0, 0, 0, 1, 0,  0, 1, 0, 0, 0, 0 };
static const int dPin[] = { 10, 9, 29, 9, 10, 16, 3, 0, 24, 0, 27, 28, 12, 14 };

void digitalWrite(uint8_t pin, uint8_t val)
{
	if(pin > 13) return;
	Chip_GPIO_SetPinState(LPC_GPIO, dPort[pin], dPin[pin], val);
}


void pinMode(uint8_t pin, uint8_t mode)
{
	if(mode == OUTPUT) {
		Chip_IOCON_PinMuxSet(LPC_IOCON, dPort[pin], dPin[pin], (IOCON_DIGMODE_EN));
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, dPort[pin], dPin[pin]);
	}
	else {
		Chip_IOCON_PinMuxSet(LPC_IOCON, dPort[pin], dPin[pin], (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN));
		Chip_GPIO_SetPinDIRInput(LPC_GPIO, dPort[pin], dPin[pin]);
	}
}


void delayMicroseconds(int us)
{
	// calculate compare value
	uint64_t cmp_value;
	cmp_value = us * 72;
	// disable RIT – compare value may only be changed when RIT is disabled
	// clear wait flag (the variable that ISR will set)
	Chip_RIT_Disable(LPC_RITIMER);
	RIT_flag=0;
	// set compare value to RIT
	Chip_RIT_SetCompareValue(LPC_RITIMER, cmp_value);
	// clear RIT counter (so that counting starts from zero)
	Chip_RIT_SetCounter(LPC_RITIMER, 0);
	// enable RIT
	Chip_RIT_Enable(LPC_RITIMER);
	// wait until flag is set
	while(!RIT_flag);

}
