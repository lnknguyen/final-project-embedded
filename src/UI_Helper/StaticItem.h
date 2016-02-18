/*
 * StaticItem.h
 *
 *  Created on: Feb 17, 2016
 *      Author: nguyenluong
 */

#ifndef UI_HELPER_STATICITEM_H_
#define UI_HELPER_STATICITEM_H_


#include <iostream>
#include "BarGraph.h"
#include "../LCD/LiquidCrystal.h"
#include <string>
#include "../Protocol/PropertyEdit.h"

class StaticItem :  public PropertyEdit{
private:
	LiquidCrystal& lcd;
	std::string title;
	void save();
	bool focus;
public:
	StaticItem(LiquidCrystal& lcd_, std::string editTitle);
	virtual ~StaticItem();
	void increment() {}
	void decrement() {}
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	void load();
};

#endif /* UI_HELPER_STATICITEM_H_ */
