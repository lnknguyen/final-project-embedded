/*
 * IntegerEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "IntegerEdit.h"
#include <cstdio>

IntegerEdit::IntegerEdit(LiquidCrystal& lcd_,BarGraph& bg_, std::string editTitle): lcd(lcd_), bg(bg_),title(editTitle) {
	value = 0;
	edit = 0;
	focus = false;
	upper_lim = 0;
	lower_lim = 0;
}

IntegerEdit::IntegerEdit(LiquidCrystal& lcd_,BarGraph& bg_, std::string editTitle,int lower, int upper): lcd(lcd_), bg(bg_),
		title(editTitle),lower_lim(lower), upper_lim(upper) {
	value = 0;
	edit = 0;
	focus = false;
}

IntegerEdit::~IntegerEdit() {
}

void IntegerEdit::increment() {
	if(edit<upper_lim)
		edit++;
}

void IntegerEdit::decrement() {
	if(edit>lower_lim)
		edit--;
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
	lcd.setCursor(0,1);
	char s[10];
	if(focus) {
		snprintf(s, 10,"[%2d]", edit);
	}
	else {
		snprintf(s, 10,"%2d", edit);
	}
	lcd.Print(s);
	bg.draw(edit*50/upper_lim);
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
	if(value>upper_lim)
		edit = upper_lim;
	else if (value<lower_lim)
		edit = lower_lim;
	else
		edit = value;
	save();
}
