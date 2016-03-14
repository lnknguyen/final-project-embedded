/*
 * ComplexMenu.h
 *
 *  Created on: 3.2.2016
 *      Author: krl
 */

#ifndef ComplexMenu_H_
#define ComplexMenu_H_
#include <vector>

#include "../GUI/ComplexItem.h"

class ComplexMenu {
public:
	ComplexMenu();
	~ComplexMenu();
	void addItem(ComplexItem *item);
	void baseEvent(ComplexItem::menuBaseEvent e);
	int getPosition();
private:
	std::vector<ComplexItem *> items;
	int position;
};

#endif /* ComplexMenu_H_ */
