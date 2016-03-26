/*
 * HWHumiditySensor.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */

#include "HWHumiditySensor.h"

#define SCALE_FACTOR 16382.0
#define SENSOR_ADDR 0x27

HWHumiditySensor::HWHumiditySensor(I2C& i2c_): i2c(i2c_){
	readDataCmd = 0x1;
	humidity = 0;
}

float HWHumiditySensor::toHz(){
	return 0;
}

float HWHumiditySensor::toValue(){
	if (i2c.transaction(SENSOR_ADDR, &readDataCmd, 1, data, 4)) {
		/* Output humidity. */
		humidity = (((data[0] << 8) | data[1]) & 0b0011111111111111);
	}else {
		//DEBUGOUT("Error reading pressure.\r\n")
		assert(data!=NULL);
	}
	return float(humidity/SCALE_FACTOR*100);
}
