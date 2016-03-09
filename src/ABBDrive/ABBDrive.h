/*
 * ABBDrive.h
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */


#include "ModbusMaster.h"

#include "../InterruptHandler/systick.h"

class ABBDrive {
public:
<<<<<<< HEAD
	ABBDrive();
=======
	ABBDrive(ModbusMaster _node);
>>>>>>> c49298ebfbb3e76d20cbffb852cb531db09976c9
	virtual ~ABBDrive() {};
	void init();
	void setSingleRegister(int startAddress, int value);
	int  getSingleRegister(int startAddress);
	void setFrequency(float frequency);
	int  getFrequency();
	void setControlWord(int value);
	int  getStatusWord();

private:
	ModbusMaster node;
};


