/*
 * HWTemperatureSensor.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */

#include "HWTemperatureSensor.h"

#define SCALE_FACTOR 16382.0
#define SENSOR_ADDR 0x27

HWTemperatureSensor::HWTemperatureSensor(I2C& i2c_): i2c(i2c_){
	readDataCmd = 0x1;
	temperature = 0;
}

float HWTemperatureSensor::toHz(){
	return 0;
}

float HWTemperatureSensor::toValue(){
	if (i2c.transaction(SENSOR_ADDR, &readDataCmd, 1, data, 4)) {
		/* Output temperature. */
		temperature = (data[2] << 8 | data[3]) >> 2;
	}else {
		//DEBUGOUT("Error reading pressure.\r\n")
		assert(data!=NULL);
	}
	return float(temperature/SCALE_FACTOR*165-40);
}
