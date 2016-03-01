/*
 * TemperatureSensor.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nguyenluong
 */

#include "PressureSensor.h"

#define SCALE_FACTOR 240.0
PressureSensor::PressureSensor(I2C& i2c_): i2c(i2c_){

	readPressureCmd = 0xF1;
	pressure = 0;
}

float PressureSensor::toValue(){
	if (i2c.transaction(0x40, &readPressureCmd, 1, pressureData, 3)) {
				/* Output temperature. */
				pressure = (pressureData[0] << 8) | pressureData[1];

				//printf("Pressure read over I2C is %.1f Pa\r\n",	pressure/240.0);
			}
			else {
				//DEBUGOUT("Error reading pressure.\r\n");
			}
			Sleep(1000);
	return pressure/SCALE_FACTOR;
}



