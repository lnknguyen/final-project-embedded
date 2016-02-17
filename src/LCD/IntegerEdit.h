/*
 * IntegerEdit.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef INTEGEREDIT_H_
#define INTEGEREDIT_H_

#include <iostream>
#include "PropertyEdit.h"
#include "BarGraph.h"
#include "LiquidCrystal.h"
#include "eeprom.h"
#include "iap.h"
#include <string>



#define EEPROM_ADDRESS 0x00000100
#define NUM_BYTES_TO_READ_WRITE 32

class IntegerEdit: public PropertyEdit {
public:
	IntegerEdit(LiquidCrystal& lcd_, BarGraph& bg, std::string editTitle);
	IntegerEdit(LiquidCrystal& lcd_, BarGraph& bg, std::string editTitle, int upper, int lower);
	virtual ~IntegerEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	void load();
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
	int upper_lim;
	int lower_lim;
	BarGraph bg;
	uint32_t buffer[NUM_BYTES_TO_READ_WRITE / sizeof(uint32_t)];
};

#endif /* INTEGEREDIT_H_ */
