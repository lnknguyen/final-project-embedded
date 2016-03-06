/*
 * RunningMode.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef RUNNINGMODE_H_
#define RUNNINGMODE_H_

#include "../Protocol/PropertyEdit.h"
#include "../LCD/LiquidCrystal.h"
#include <string>

class RunningMode:public PropertyEdit {
public:
	RunningMode(LiquidCrystal& lcd_, int value);
	virtual ~RunningMode();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	void displaySensorValue(int value);
	void displayDifferenceValue(int value);
	void displayIncrementValue(int value);
	void setDesiredValue(int value);
	std::string name();
private:
	std::string run ="Run now?";
	std::string running = "Running...";
	void save();
	void displayEditValue();
	LiquidCrystal& lcd;
	int value;
	int edit;
	bool focus;
};

#endif /* RUNNINGMODE_H_ */
