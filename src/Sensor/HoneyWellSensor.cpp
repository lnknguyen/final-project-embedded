/*
 * HoneyWellSensor.cpp
 *
 *  Created on: Mar 24, 2016
 *      Author: nguyenluong
 */


#include "HoneyWellSensor.h"

#define SCALE_FACTOR (1 << 14) - 1
#define SENSOR_ADDR 0x27

HoneyWellSensor::HoneyWellSensor(I2C& i2c_): i2c(i2c_){
	readPressureCmd = 0x1;
	humidity = 0;
	temperature = 0;
}

float HoneyWellSensor::toHz(){
	return 0;
}

float HoneyWellSensor::toValue(){
	if (i2c.transaction(SENSOR_ADDR, &readPressureCmd, 1, pressureData, 4)) {
		/* Output temperature. */
		humidity = (bufferData[0] << 6) | pressureData[1];
	}else {
		//DEBUGOUT("Error reading pressure.\r\n")

	}
	//Sleep(1000);
	return (float)humidity/SCALE_FACTOR;

}

float HoneyWellSensor::toValueTemperature(){
	if (i2c.transaction(SENSOR_ADDR, &readPressureCmd, 1, pressureData, 4)) {
		/* Output temperature. */
		temperature = ((bufferData[2] << 8) | bufferData[3])>>2;
	}else {
		//DEBUGOUT("Error reading pressure.\r\n")

	}
	//Sleep(1000);
	return (float)temperature/SCALE_FACTOR*165-40;
}

