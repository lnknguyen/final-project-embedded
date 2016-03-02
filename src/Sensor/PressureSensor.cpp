/*
 * PressureSensor.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nguyenluong
 */

#include "PressureSensor.h"

#define SCALE_FACTOR 240.0
#define SENSOR_ADDR 0x40
PressureSensor::PressureSensor(I2C& i2c_): i2c(i2c_){
	readPressureCmd = 0xF1;
	pressure = 0;
}

float PressureSensor::toHz(){
	return 0;
}

int PressureSensor::toValue(){
	if (i2c.transaction(SENSOR_ADDR, &readPressureCmd, 1, pressureData, 3)) {
		/* Output temperature. */
		pressure = (pressureData[0] << 8) | pressureData[1];
	}else {
		//DEBUGOUT("Error reading pressure.\r\n")
		assert(pressureData!=NULL);
	}
	//Sleep(1000);
	return pressure/SCALE_FACTOR;
}



