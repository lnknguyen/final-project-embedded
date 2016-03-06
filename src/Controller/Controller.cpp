/*
 * Controller.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */
#include"Controller.h"

Controller::Controller(float _incrementValue, float _tolerance){
	incrementValue = _incrementValue;
	tolerance = _tolerance;
}

void Controller::setIncrement(float value){
	incrementValue = value;
}

float Controller::getIncrement(){
	return incrementValue;
}

void Controller::setTolerance(float value){
	tolerance = value;
}

float Controller::getTolerance(){
	return tolerance;
}

float Controller::increment(float error){
	if (error>tolerance){
		return incrementValue;
	}else if (error<(-tolerance)){
		return (-incrementValue);
	}else{
		return 0;
	}
}
