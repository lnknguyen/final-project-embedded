/*
 * ScenePrototype.h
 *
 *  Created on: Feb 17, 2016
 *      Author: nguyenluong
 */

#ifndef PROTOCOL_SCENEPROTOCOL_H_
#define PROTOCOL_SCENEPROTOCOL_H_

#include "../UI_Helper/SimpleMenu.h"
#include "../UI_Helper/MenuItem.h"
#include "../UI_Helper/IntegerEdit.h"
#include "../UI_Helper/BarGraph.h"

class SceneProtocol{
public:
	SceneProtocol() {}
	virtual ~SceneProtocol(){}
	virtual void Next_scene() =0;
	virtual void Prev_scene() =0;
	virtual void display() =0;

};




#endif /* PROTOCOL_SCENEPROTOCOL_H_ */
