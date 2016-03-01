/*
 * TemperatureSensor.h
 *
 *  Created on: Mar 1, 2016
 *      Author: nguyenluong
 */

#ifndef SENSOR_TEMPERATURESENSOR_H_
#define SENSOR_TEMPERATURESENSOR_H_

#include <stdint.h>
#include "SensorInterface.h"
#include "../Interrupt_Handler/systick.h"

class TemperatureSensor : public SensorInterface{
public:
	TemperatureSensor();
	virtual ~TemperatureSensor() {};
	float toValue();
	float toHz();
private:
	uint8_t temperatureData[3];
	int16_t temperature;
	uint32_t a0,d0;
};

#endif /* SENSOR_PRESSURESENSOR_H_ */
