/*
 * ComplexItem.h
 *
 *  Created on: 1.2.2016
 *      Author: krl
 */

#ifndef ComplexItem_H_
#define ComplexItem_H_

#include "../GUI/SimpleMenu.h"

class ComplexItem {
public:
	enum menuBaseEvent {
		up,
		down,
		ok,
		back,
		show
	};
	ComplexItem(SimpleMenu& menu);
	virtual ~ComplexItem();
	virtual bool baseEvent(menuBaseEvent e);
	bool getFocus();
private:
	bool focus;
	bool lock;
	SimpleMenu& mn ;
};

#endif /* ComplexItem_H_ */
