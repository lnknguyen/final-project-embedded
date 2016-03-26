/*
 * RunningMode.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef RUNNINGMODE_H_
#define RUNNINGMODE_H_

#include "PropertyEdit.h"
#include "../LCD/LiquidCrystal.h"
#include <string>

class RunningMode:public PropertyEdit {
public:
	RunningMode(LiquidCrystal& lcd_);
	virtual ~RunningMode();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	void displayValue(float value,int precision,int lcdCol,int lcdRow);
	void setDesiredValue(float value);
	std::string name();
private:
	std::string startRun ="Start now?";
	std::string running = "Running...";
	void save();
	void displayEditValue();
	LiquidCrystal& lcd;
	float value;
	float edit;
	bool focus;
};

#endif /* RUNNINGMODE_H_ */
