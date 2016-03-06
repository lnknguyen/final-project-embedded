/*
 * RunningMode.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "../GUI/RunningMode.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

RunningMode::RunningMode(LiquidCrystal& lcd_,int value): lcd(lcd_), value(value) {
	focus = false;
}

RunningMode::~RunningMode() {
}

void RunningMode::increment() {
}

void RunningMode::decrement() {
}

void RunningMode::accept() {
}

void RunningMode::cancel() {
}

void RunningMode::setFocus(bool focus) {
	this->focus = focus;
}

void RunningMode::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	if(focus) {
		lcd.Print(running);
	} else{
		lcd.Print(run);
	}
	stringstream lcd_display;
	lcd.setCursor(0,1);
	lcd_display << value;
	string str = lcd_display.str();
	lcd.Print(str);

}

void RunningMode::setDesiredValue(int value) {
	this->value = value;
	if(focus){
		//handle the code for RPM here.
		stringstream lcd_display;
		lcd.setCursor(10,1);
		lcd_display << value;
		string str = lcd_display.str();
		lcd.Print(str);
	}
}

void RunningMode::displaySensorValue(int value) {
	if(focus){
		if(this->value!=value){
			if(value==9 ||value ==99 ||value ==1){
				lcd.clear();
			}
			stringstream lcd_display;
			lcd.setCursor(0,1);
			lcd_display << value;
			string str = lcd_display.str();
			lcd.Print(str);
		}
	}
}

void RunningMode::displayDifferenceValue(int value) {
	if(focus){
		if(this->value!=value){
			if(value==9 ||value ==99 ||value ==1){
				lcd.clear();
			}
			stringstream lcd_display;
			lcd.setCursor(3,1);
			lcd_display << value;
			string str = lcd_display.str();
			lcd.Print(str);
		}
	}
}

void RunningMode::displayIncrementValue(int value) {
	if(focus){
		if(this->value!=value){
			if(value==9 ||value ==99 ||value ==1){
				lcd.clear();
			}
			stringstream lcd_display;
			lcd.setCursor(6,1);
			lcd_display << value;
			string str = lcd_display.str();
			lcd.Print(str);
		}
	}
}

std::string RunningMode::name(){
}
