/*
 * menu_scene_1.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: nguyenluong
 */


#include "menu_scene.h"



void MenuScene::setup(SimpleMenu& menu){
	BarGraph bg( LiquidCrystal::Instance(),50,false);
	IntegerEdit temp(LiquidCrystal::Instance(),bg,std::string("Temp"),0,90);
	IntegerEdit pressure(LiquidCrystal::Instance(),bg,std::string("Pressure"),0,90);
	//StaticItem temp(LiquidCrystal::Instance(),std::string("Temperature"));
	//StaticItem pressure(LiquidCrystal::Instance(),"Pressure");
	menu.addItem(new MenuItem(temp));
	menu.addItem(new MenuItem(pressure));
}

void MenuScene::display(){
//	s_menu.event(MenuItem::show);
}

void MenuScene::show(){
//	s_menu.event(MenuItem::show);
}

void MenuScene::Next_scene(){

}

void MenuScene::Prev_scene(){

}
