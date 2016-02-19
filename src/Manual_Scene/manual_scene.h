/*
 * manual_scene.h
 *
 *  Created on: Feb 18, 2016
 *      Author: nguyenluong
 */

#ifndef MANUAL_SCENE_MANUAL_SCENE_H_
#define MANUAL_SCENE_MANUAL_SCENE_H_



#include "../Protocol/SceneProtocol.h"

#include <vector>
class ManualScene : public SceneProtocol{
private:
	SimpleMenu& menu;
	std::vector<DebouncedInput> button;
public:
	ManualScene(SimpleMenu& menu_, std::vector<DebouncedInput> button_);
	virtual ~ManualScene(){}
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



#endif /* MANUAL_SCENE_MANUAL_SCENE_H_ */
