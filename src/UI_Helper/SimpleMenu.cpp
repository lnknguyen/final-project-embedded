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

bool SimpleMenu::returnFocus(){
	return items[position]->returnFocus();
}

void SimpleMenu::cancel(){
	items[position]->cancel();
}

void SimpleMenu::display() {
	lcd.clear();
	lcd.setCursor(0,0);
	stringstream lcd_display;
	if(focus) {
		//lcd_display<<items[index]->name();
		items[position]->event(MenuItem::show);
	}
	else {
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
string SimpleMenu::childName(int position){
	return items[position]->name();
}

void SimpleMenu::addItem(MenuItem *item) {
	items.push_back(item);
}

void SimpleMenu::event(MenuItem::menuEvent e) {
	if(items.size() <= 0) return;

	if(!items[position]->event(e)) {
		if(e == MenuItem::up) {
			position++;
		}
		else if(e == MenuItem::down){
			position--;
		}

		if(position < 0) position = items.size() - 1;
		if(position >= (int) items.size()) position = 0;

		items[position]->event(MenuItem::show);
	}
}
