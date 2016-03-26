/*
 * PressureSensor.h
 *
 *  Created on: Mar 1, 2016
 *      Author: nguyenluong
 */

#ifndef SENSOR_HWTEMPERATURESENSOR_H_
#define SENSOR_HWTEMPERATURESENSOR_H_

#include <stdint.h>

#include "../InterruptHandler/systick.h"
#include "SensorInterface.h"
#include "I2C.h"
class HWTemperatureSensor : public SensorInterface{
public:
	HWTemperatureSensor(I2C &i2c);
	virtual ~HWTemperatureSensor() {};
	float toHz();
	float toValue();
private:
	uint8_t data[4];
	uint8_t readDataCmd ;
	int16_t temperature;
	I2C& i2c;
};



#endif /* SENSOR_HWTEMPERATURESENSOR_H_ */
