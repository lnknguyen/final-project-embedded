/*
 * CO2Sensor.h
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */

#ifndef SENSOR_CO2SENSOR_H_
#define SENSOR_CO2SENSOR_H_

#include <stdint.h>

#include "../InterruptHandler/systick.h"
#include "SensorInterface.h"

class CO2Sensor : public SensorInterface{
public:
	CO2Sensor();
	virtual ~CO2Sensor() {};
	int toValue();
	float toHz();
private:
	float CO2;
	uint32_t a3,d3;
};

#endif /* SENSOR_PRESSURESENSOR_H_ */
