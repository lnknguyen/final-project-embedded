/*
 * SensorInterface.h
 *
 *  Created on: Mar 1, 2016
 *      Author: nguyenluong
 */

#ifndef SCENE_CONTROLLER_SENSORINTERFACE_H_
#define SCENE_CONTROLLER_SENSORINTERFACE_H_

class SensorInterface{
public:
	SensorInterface() {}
	virtual ~SensorInterface() {};
	virtual float toHz() =0;
	virtual float toValue() =0;


};



#endif /* SCENE_CONTROLLER_SENSORINTERFACE_H_ */
