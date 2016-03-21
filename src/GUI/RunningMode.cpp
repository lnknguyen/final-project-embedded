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

RunningMode::RunningMode(LiquidCrystal& lcd_): lcd(lcd_){
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
			lcd.Print(startRun);
		}
		displayValue(value,0,0,1);

}

void RunningMode::setDesiredValue(float value) {
	/*display set value in main loop*/
		this->value = value;

}


void RunningMode::displayValue(float value,int precision,int lcdCol,int lcdRow) {
	/*display current value in main loop*/
	//lcd.clear();
	if(focus){
			stringstream lcd_display;
			lcd.setCursor(lcdCol,lcdRow);
			lcd_display<<std::fixed <<std::setprecision(precision)<<value;
			string str = lcd_display.str();
			lcd.Print(str);
	}
}

std::string RunningMode::name(){
}
