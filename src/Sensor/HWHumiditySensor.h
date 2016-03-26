/*
 * HWHumiditySensor.h
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */

#ifndef SENSOR_HWHUMIDITYSENSOR_H_
#define SENSOR_HWHUMIDITYSENSOR_H_

#include <stdint.h>

#include "../InterruptHandler/systick.h"
#include "SensorInterface.h"
#include "I2C.h"
class HWHumiditySensor : public SensorInterface{
public:
	HWHumiditySensor(I2C &i2c);
	virtual ~HWHumiditySensor() {};
	float toHz();
	float toValue();
private:
	uint8_t data[4];
	uint8_t readDataCmd ;
	int16_t humidity;
	I2C& i2c;
};



#endif /* SENSOR_HWHUMIDITYSENSOR_H_ */
