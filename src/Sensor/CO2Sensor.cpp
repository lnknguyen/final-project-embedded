/*
 * CO2Sensor.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */

#include "CO2Sensor.h"
#include "chip.h"
#include <stdio.h>



CO2Sensor::CO2Sensor(){
	CO2 = 0;
	a3 = 0;
	d3 = 0;
}
float CO2Sensor::toHz(){
	return 0;
}

float CO2Sensor::toValue(){
	a3 = Chip_ADC_GetDataReg(LPC_ADC0, 3);
	d3 = ADC_DR_RESULT(a3);
	//CO2 = d3;
	CO2 = -4.899 * d3 + 12014;
	return CO2;
}
