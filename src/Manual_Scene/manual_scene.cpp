/*
 * manual_scene.cpp
 *
 *  Created on: Feb 18, 2016
 *      Author: nguyenluong
 */



#include "manual_scene.h"

ManualScene::ManualScene(SimpleMenu& menu_,std::vector<DebouncedInput> button_):menu(menu_),button(button_){

}

void ManualScene::setup(){
	static BarGraph s_bg( LiquidCrystal::Instance(),50,false);
	static IntegerEdit s_temp(LiquidCrystal::Instance(),s_bg,std::string("Temp"),0,90);
	static IntegerEdit s_pressure(LiquidCrystal::Instance(),s_bg,std::string("Pressure"),0,90);

	menu.addItem(new MenuItem(s_temp));
	menu.addItem(new MenuItem(s_pressure));
}

void ManualScene::display(){
	menu.event(MenuItem::show);
}

void ManualScene::show(){
	menu.event(MenuItem::show);
}

void ManualScene::up(){
	menu.event(MenuItem::up);
}

void ManualScene::down(){
	menu.event(MenuItem::down);
}

void ManualScene::ok(){
	Next_scene();
	//menu.event(MenuItem::ok);
}

void ManualScene::start(){
	if(button[0].read()){
		up();
		Sleep(100);
	}
	if(button[1].read()){
		down();
		Sleep(100);
	}
	if(button[2].read()){
		ok();
		Sleep(100);
	}

}

void ManualScene::Next_scene(){

}

void ManualScene::Prev_scene(){

}


