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
	ABBDrive();
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


