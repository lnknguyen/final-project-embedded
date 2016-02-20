/*
 * SimpleMenu.cpp
 *
 *  Created on: 3.2.2016
 *      Author: krl
 */

#include "SimpleMenu.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

SimpleMenu::SimpleMenu(LiquidCrystal& lcd,std::string giveName):lcd(lcd),name(giveName){
	position = 0;
}

SimpleMenu::~SimpleMenu() {
	// TODO Auto-generated destructor stub
}
void SimpleMenu::increment() {
	if (position <=itemsNumber()-1){
		position++;
	}
}

void SimpleMenu::decrement() {
	if (position >=1){
		position--;
	}
}

void SimpleMenu::display() {
	lcd.clear();
	stringstream lcd_display;
	if(focus) {
		lock = true;
		items[index]->event(MenuItem::ok);
		lcd.setCursor(0,1);
		//lcd_display << childName(index);
	}
	else {
		lock = false;
		lcd.setCursor(0,0);
		lcd.Print(name);

	}
	string str = lcd_display.str();
	lcd.Print(str);
}

void SimpleMenu::setFocus(bool focus) {
	this->focus = focus;
}

int SimpleMenu::itemsNumber(){
	return items.size();
}
string SimpleMenu::childName(int index){
	return items[index]->name();
}

void SimpleMenu::addItem(MenuItem *item) {
	items.push_back(item);
}

void SimpleMenu::event(MenuItem::menuEvent e) {
	if(items.size() <= 0) return;

	if(!items[position]->event(e)) {
		if(e == MenuItem::up) {
			position++;
			index++;
		}

		else if(e == MenuItem::down){
			position--;
			index++;
		}
		if(index < 0) index = items.size() - 1;
		if(index >= (int) items.size()) index = 0;

		if(position < 0) position = items.size() - 1;
		if(position >= (int) items.size()) position = 0;

		items[position]->event(MenuItem::show);
	}
}
