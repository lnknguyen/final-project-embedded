/*
 * Controller.h
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */

class Controller {
public:
	Controller(float _incrementValue, float _tolerance);
	virtual ~Controller() {};
	void 	setIncrement(float value);
	float  	getIncrement();
	void 	setTolerance(float value);
	float  	getTolerance();
	float 	increment(float error);

private:
	float incrementValue;
	float tolerance;
};


