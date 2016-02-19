/*
 * IntegerEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "IntegerEdit.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

IntegerEdit::IntegerEdit(LiquidCrystal& lcd_, std::string editTitle, int value): lcd(lcd_), title(editTitle),value(value) {
	if (value <=upperLimit && value >= lowerLimit){
		setValue(value);
	} else{
		setValue(lowerLimit);
	}
	focus = false;
}

IntegerEdit::~IntegerEdit() {
}

void IntegerEdit::increment() {
	if (edit <=upperLimit-1){
		edit++;
	}
}

void IntegerEdit::decrement() {
	if (edit >=lowerLimit+1){
		edit--;
	}
}

void IntegerEdit::accept() {
	save();
}

void IntegerEdit::cancel() {
	edit = value;
}


void IntegerEdit::setFocus(bool focus) {
	this->focus = focus;
}

void IntegerEdit::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.Print(title);
	stringstream lcd_display;
	if(focus) {
		lcd.setCursor(6,1);
		lcd_display << "["<< edit <<"]" ;
	}
	else {
		lcd.setCursor(7,1);
		lcd_display <<edit ;
	}
	string str = lcd_display.str();
	lcd.Print(str);
}


void IntegerEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
}


int IntegerEdit::getValue() {
	return value;
}
void IntegerEdit::setValue(int value) {
	edit = value;
	save();
}
