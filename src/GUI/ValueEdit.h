/*
 * ValueEdit.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef VALUEEDIT_H_
#define VALUEEDIT_H_

#include "../Protocol/PropertyEdit.h"
#include "../LCD/LiquidCrystal.h"
#include <string>

class ValueEdit:public PropertyEdit {
public:
	ValueEdit(LiquidCrystal& lcd_, std::string editTitle, float value);
	virtual ~ValueEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	float getValue();
	void setValue(float value);
	string name();
private:
	void save();
	void displayEditValue();
	LiquidCrystal& lcd;
	std::string title;
	float value;
	float edit;
	bool focus;
	float upperLimit = 100;
	float lowerLimit = 0;
};

#endif /* VALUEEDIT_H_ */
