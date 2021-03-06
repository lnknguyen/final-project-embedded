	/*
 * MenuItem.cpp
 *
 *  Created on: 1.2.2016
 *      Author: krl
 */

#include "../GUI/MenuItem.h"

#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

MenuItem::MenuItem(PropertyEdit& property): focus(false), pe(property){

}

MenuItem::~MenuItem() {

}
string MenuItem::name(){
	return pe.name();
}

bool MenuItem::returnFocus(){
	return this->focus;
}
void MenuItem::cancel(){
	pe.cancel();
}
bool MenuItem::event(menuEvent e){
	bool handled = true;
	switch(e) {
	case ok:
		if(focus) {
			pe.accept();
			focus = false;
		}
		else {
			focus = true;
		}
		pe.setFocus(focus);
		break;
	case back:
		if(focus) {
			focus = false;
			pe.cancel();
		}
		else {
			handled = false;
		}
		pe.setFocus(focus);
		break;
	case show:
		pe.setFocus(focus);
		break;
	case up:
		if(focus) pe.increment();
		else handled = false;
		break;
	case down:
		if(focus) pe.decrement();
		else handled = false;
		break;
	}
	if(handled) pe.display();
	return handled;
}

