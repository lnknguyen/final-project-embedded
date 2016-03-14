/*
 * ComplexMenu.cpp
 *
 *  Created on: 3.2.2016
 *      Author: krl
 */

#include "../GUI/ComplexMenu.h"

ComplexMenu::ComplexMenu() {
	position = 0;
}

ComplexMenu::~ComplexMenu() {
	// TODO Auto-generated destructor stub
}

void ComplexMenu::addItem(ComplexItem *item) {
	items.push_back(item);
}

void ComplexMenu::baseEvent(ComplexItem::menuBaseEvent e) {
	if(items.size() <= 0) return;

	if(!items[position]->baseEvent(e)) {
		if(e == ComplexItem::up) position++;
		else if(e == ComplexItem::down) position--;

		if(position < 0) position = items.size() - 1;
		if(position >= (int) items.size()) position = 0;

		items[position]->baseEvent(ComplexItem::show);
	}
}

int ComplexMenu::getPosition(){
	return position;
}
