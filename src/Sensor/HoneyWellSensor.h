/*
 * HoneyWellSensor.h
 *
 *  Created on: Mar 24, 2016
 *      Author: nguyenluong
 */

#ifndef SENSOR_HONEYWELLSENSOR_H_
#define SENSOR_HONEYWELLSENSOR_H_


#include <stdint.h>

#include "../InterruptHandler/systick.h"
#include "SensorInterface.h"
#include "I2C.h"
class HoneyWellSensor : public SensorInterface{
public:
	HoneyWellSensor(I2C &i2c);
	virtual ~HoneyWellSensor() {};
	float toHz();
	float toValue();
	float toValueTemperature();
private:
	uint8_t bufferData[3];
	uint8_t readCmd ;
	uint16_t humidity;
	int16_t temperature;
	I2C& i2c;
};






#endif /* SENSOR_HONEYWELLSENSOR_H_ */
