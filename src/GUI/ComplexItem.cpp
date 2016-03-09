	/*
 * ComplexItem.cpp
 *
 *  Created on: 1.2.2016
 *      Author: krl
 */

#include "../GUI/ComplexItem.h"

ComplexItem::ComplexItem(SimpleMenu& menu): focus(false), mn(menu){

}

ComplexItem::~ComplexItem() {

}
bool ComplexItem::getFocus(){
	return focus;
}

bool ComplexItem::baseEvent(menuBaseEvent e){
	bool handled = true;
	switch(e) {
	case ok:
		if(focus){
			mn.event(MenuItem::ok);
		}else{
			focus =true;
		}
		mn.setFocus(focus);
		break;
	case back:
		if(mn.returnFocus()){
			mn.cancel();
			mn.event(MenuItem::ok);
		}else{
			focus = false;
			mn.event(MenuItem::back);
		}
		handled = false;
		break;
	case show:
		mn.setFocus(focus);
		break;
	case up:
		if(focus){
			mn.event(MenuItem::up);
		}
		else handled = false;
		break;
	case down:
		if(focus){
			mn.event(MenuItem::down);
		}
		else handled = false;
		break;
	}
	if(handled) mn.display();
	return handled;
}

