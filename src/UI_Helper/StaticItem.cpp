/*
 * StaticItem.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: nguyenluong
 */

#include "StaticItem.h"
#include <cstdio>

StaticItem::StaticItem(LiquidCrystal& lcd_, std::string editTitle): lcd(lcd_),title(editTitle){

}

StaticItem::~StaticItem(){

}

void StaticItem::accept(){

}

void StaticItem::display(){
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.Print(title);
}

void StaticItem::setFocus(bool focus){
	this->focus = focus;
}
