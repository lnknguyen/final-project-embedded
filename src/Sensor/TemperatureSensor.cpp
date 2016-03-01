/*
 * TemperatureSensor.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nguyenluong
 */

#include "TemperatureSensor.h"
#include "chip.h"
#include <stdio.h>

#define SCALE_FACTOR 240.0
#define SENSOR_ADDR 0x40
TemperatureSensor::TemperatureSensor(){
	temperature = 0;
	a0 = 0;
	d0 = 0;
}
float TemperatureSensor::toHz(){
}

float TemperatureSensor::toValue(){
	a0 = Chip_ADC_GetDataReg(LPC_ADC0, 0);
	d0 = ADC_DR_RESULT(a0);
	printf("a0 = %08X, d0 = %d\n", a0, d0);
	Sleep(1000);
	return temperature;
}
