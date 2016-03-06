/*
 * RunningMode.cpp
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#include "RunningMode.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

RunningMode::RunningMode(LiquidCrystal& lcd_,float value): lcd(lcd_), value(value) {
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
	/*display the layout only value, use in the state machine*/
	lcd.clear();
	lcd.setCursor(0,0);
	if(focus) {
		lcd.Print(running);
	} else{
		lcd.Print(run);
	}
	stringstream lcd_display;
	lcd.setCursor(0,1);
	lcd_display << std::fixed <<std::setprecision(1)<<value;;
	string str = lcd_display.str();
	lcd.Print(str);

}

void RunningMode::setValue(float value) {
	/*display set value in main loop*/
	this->value = value;
	if(focus){
		//handle the code for RPM here.
		stringstream lcd_display;
		if(value<=9){
			lcd.setCursor(13,1);
		} else if(value >9 && value <=99){
			lcd.setCursor(12,1);
		} else if(value>99){
			lcd.setCursor(11,1);
		}
		lcd_display << std::fixed <<std::setprecision(1)<<value;
		string str = lcd_display.str();
		lcd.Print(str);
	}
}

void RunningMode::displayValue(float value) {
	/*display current value in main loop*/
	if(focus){
		if(this->value!=value){
			if((9.8<= edit && edit <=10) || (99.8<= edit && edit <=100) ||(0.8<= edit && edit <=1)){
				lcd.clear();
			}
			stringstream lcd_display;
			lcd.setCursor(0,1);
			lcd_display << std::fixed <<std::setprecision(1)<<value;
			string str = lcd_display.str();
			lcd.Print(str);
		}
	}
}

std::string RunningMode::name(){
}
