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
#include <math.h>
#include "ValueEdit.h"
using namespace std;

ValueEdit::ValueEdit(LiquidCrystal& lcd_, std::string editTitle, float value): lcd(lcd_), title(editTitle),value(value) {
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
	if (edit <=upperLimit-0.1 ){
		edit=edit + 0.1;
	} else if(99.9<= edit && edit <=99.91){
		edit = 0; // because 0.1 is actually 0.998...
	}
}

void ValueEdit::decrement() {
	if (edit >=lowerLimit+0.1){
		edit=edit - 0.1;
	} else if(0.09<= edit && edit <=0.1){
		edit = 0; // because 0.1 is actually 0.998...
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
		if((9.8<= edit && edit <=10) || (99.8<= edit && edit <=100) ||(0.8<= edit && edit <=1)){
			lcd.clear();
		}
		lcd.setCursor(5,1);
		lcd_display << "["<< std::fixed <<std::setprecision(1)<<edit <<"]" ;
	}
	else {
		lcd.clear();
		lcd.setCursor(6,1);
		lcd_display << std::fixed <<std::setprecision(1)<<edit ;
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


float ValueEdit::getValue() {
	return value;
}
void ValueEdit::setValue(float value) {
	edit = value;
	save();
}
