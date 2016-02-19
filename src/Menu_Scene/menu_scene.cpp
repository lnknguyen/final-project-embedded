/*
 * menu_scene_1.cpp
 *
 *  Created on: Feb 17, 2016
 *      Author: nguyenluong
 */


#include "menu_scene.h"

MenuScene::MenuScene(SimpleMenu* menu_,std::vector<DebouncedInput> button_):menu(menu_),button(button_){

}

void MenuScene::setup(){
	static BarGraph s_bg( LiquidCrystal::Instance(),50,false);
	//static IntegerEdit s_temp(LiquidCrystal::Instance(),s_bg,std::string("Temp"),0,90);
	//static IntegerEdit s_pressure(LiquidCrystal::Instance(),s_bg,std::string("Pressure"),0,90);
	static StaticItem s_temp(LiquidCrystal::Instance(),std::string("Manual"));
	static StaticItem s_pressure(LiquidCrystal::Instance(),std::string("Auto"));
	menu->addItem(new MenuItem(s_temp));
	menu->addItem(new MenuItem(s_pressure));
}

void MenuScene::display(){
	menu->event(MenuItem::show);
}

void MenuScene::show(){
	menu->event(MenuItem::show);
}

void MenuScene::up(){
	menu->event(MenuItem::up);
}

void MenuScene::down(){
	menu->event(MenuItem::down);
}

void MenuScene::ok(){
	Next_scene();
	//menu.event(MenuItem::ok);
}

void MenuScene::start(){
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

void MenuScene::Next_scene(){
	SimpleMenu _menu;
	ManualScene* scene = new ManualScene(_menu,button);
	scene->setup();
	scene->show();
	scene->start();
	//delete menu;
}

void MenuScene::Prev_scene(){

}
