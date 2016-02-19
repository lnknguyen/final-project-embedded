/*
 * TextEdit.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "TextEdit.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

TextEdit::TextEdit(LiquidCrystal& lcd_, std::string mode, std::string modeExplain): lcd(lcd_), mode(mode),modeExplain(modeExplain) {
	focus = false;
	current = 1;
}

TextEdit::~TextEdit() {
}

void TextEdit::increment() {
	/*if (current <=numberOfMode){
		current++;
	}else{
		current=1;
	}*/
}

void TextEdit::decrement() {
	/*if (current >0){
		current--;
	}else{
		current=numberOfMode;
	}*/
}
void TextEdit::accept() {
}

void TextEdit::cancel() {
}

void TextEdit::setFocus(bool focus) {
	this->focus = focus;
}

void TextEdit::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.Print(mode);
	stringstream lcd_display;
	lcd.setCursor(0,1);
	lcd_display << modeExplain;

	string str = lcd_display.str();
	lcd.Print(str);
}
