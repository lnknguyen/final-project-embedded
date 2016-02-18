/*
 * menu_scene_1.h
 *
 *  Created on: Feb 17, 2016
 *      Author: nguyenluong
 */

#ifndef MENU_SCENE_MENU_SCENE_H_
#define MENU_SCENE_MENU_SCENE_H_

#include "../Protocol/SceneProtocol.h"

class MenuScene : public SceneProtocol{
private:
	//SimpleMenu& s_menu;
public:
	MenuScene(){}
	virtual ~MenuScene(){}
	void setup(SimpleMenu& menu);
	void Next_scene();
	void Prev_scene();
	void display();
	void show();
};



#endif /* MENU_SCENE_MENU_SCENE_H_ */
