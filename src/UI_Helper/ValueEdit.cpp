/*
 * ValueEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "ValueEdit.h"
using namespace std;

ValueEdit::ValueEdit(LiquidCrystal& lcd_, std::string editTitle, int value): lcd(lcd_), title(editTitle),value(value) {
	if (value <=upperLimit && value >= lowerLimit){
		setValue(value);
	} else{
		setValue(lowerLimit);
	}
	focus = false;
}

ValueEdit::~ValueEdit() {
}

void ValueEdit::increment() {
	if (edit <=upperLimit-1){
		edit++;
	}
}

void ValueEdit::decrement() {
	if (edit >=lowerLimit+1){
		edit--;
	}
}

void ValueEdit::accept() {
	save();
}

void ValueEdit::cancel() {
	edit = value;
}


void ValueEdit::setFocus(bool focus) {
	this->focus = focus;
}

string ValueEdit::name(){
	return title;
}

void ValueEdit::display() {
	//lcd.clear();
	stringstream lcd_display;
	if(focus) {
		if(edit==9 ||edit ==99 ||edit ==1){
			lcd.clear();
		}
		lcd.setCursor(6,1);
		lcd_display << "["<< edit <<"]" ;
	}
	else {
		lcd.clear();
		lcd.setCursor(7,1);
		lcd_display <<edit ;
	}
	string str = lcd_display.str();
	lcd.Print(str);
	lcd.setCursor(0,0);
	lcd.Print(title);
}


void ValueEdit::save() {
	// set current value to be same as edit value
	value = edit;
	// todo: save current value for example to EEPROM for permanent storage
}


int ValueEdit::getValue() {
	return value;
}
void ValueEdit::setValue(int value) {
	edit = value;
	save();
}
