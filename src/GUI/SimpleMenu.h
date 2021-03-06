/*
 * SimpleMenu.h
 *
 *  Created on: 3.2.2016
 *      Author: krl
 */

#ifndef SIMPLEMENU_H_
#define SIMPLEMENU_H_
#include <vector>

#include "../GUI/MenuItem.h"

#include "../LCD/LiquidCrystal.h"

class SimpleMenu {
public:
	SimpleMenu(LiquidCrystal& lcd,std::string giveName);
	virtual ~SimpleMenu();
	void addItem(MenuItem *item);
	void event(MenuItem::menuEvent e);
	int itemsNumber();
	void setFocus(bool focus);
	bool returnFocus();
	void increment();
	void decrement();
	void display();
	void cancel();
	std::string childName(int index);
private:
	LiquidCrystal& lcd;
	bool focus;
	std::string name;
	std::vector<MenuItem *> items;
	int position;
	int index=0;
};

#endif /* SIMPLEMENU_H_ */
