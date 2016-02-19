/*
 * menu_scene_1.h
 *
 *  Created on: Feb 17, 2016
 *      Author: nguyenluong
 */

#ifndef MENU_SCENE_MENU_SCENE_H_
#define MENU_SCENE_MENU_SCENE_H_

#include "../Protocol/SceneProtocol.h"
#include "../Manual_Scene/manual_scene.h"
#include <vector>
class MenuScene : public SceneProtocol{
private:
	SimpleMenu* menu;
	std::vector<DebouncedInput> button;
public:
	MenuScene(SimpleMenu* menu_, std::vector<DebouncedInput> button_);
	virtual ~MenuScene(){}
	void start();
	void setup();
	void Next_scene();
	void Prev_scene();
	void display();
	void show();
	void up();
	void down();
	void ok();
	void left();
};



#endif /* MENU_SCENE_MENU_SCENE_H_ */
