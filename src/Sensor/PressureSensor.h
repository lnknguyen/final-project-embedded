/*
 * PressureSensor.h
 *
 *  Created on: Mar 1, 2016
 *      Author: nguyenluong
 */

#ifndef SENSOR_PRESSURESENSOR_H_
#define SENSOR_PRESSURESENSOR_H_

#include <stdint.h>
#include "SensorInterface.h"
#include "I2C.h"
#include "../Interrupt_Handler/systick.h"
class PressureSensor : public SensorInterface{
public:
	PressureSensor(I2C &i2c);
	virtual ~PressureSensor() {};
	float toHz();
	int toValue();
private:
	uint8_t pressureData[3];
	uint8_t readPressureCmd ;
	int16_t pressure;
	I2C& i2c;
};



#endif /* SENSOR_PRESSURESENSOR_H_ */
