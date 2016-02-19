/*
 * IntegerEdit.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef INTEGEREDIT_H_
#define INTEGEREDIT_H_

#include "../Protocol/PropertyEdit.h"
#include "../LCD/LiquidCrystal.h"

class IntegerEdit:public PropertyEdit {
public:
	IntegerEdit(LiquidCrystal& lcd_, std::string editTitle, int value);
	virtual ~IntegerEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	int getValue();
	void setValue(int value);
private:
	void save();
	void displayEditValue();
	LiquidCrystal& lcd;
	std::string title;
	int value;
	int edit;
	bool focus;
	int upperLimit = 100;
	int lowerLimit = 0;
};

#endif /* INTEGEREDIT_H_ */
