/*
 * ABBDrive.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */


#include "ABBDrive.h"

<<<<<<< HEAD
ABBDrive::ABBDrive(){
	ModbusMaster node(2);
=======
ABBDrive::ABBDrive(ModbusMaster _node){
	node = _node;
>>>>>>> c49298ebfbb3e76d20cbffb852cb531db09976c9
}

void ABBDrive::init(){
	node.begin(9600);
	node.writeSingleRegister(0, 0x0406);
	Sleep(4000);
	node.writeSingleRegister(0, 0x047F);
	Sleep(4000);
}

void ABBDrive::setSingleRegister(int startAddress, int value){
	node.writeSingleRegister(startAddress, value);
}

int  ABBDrive::getSingleRegister(int startAddress){
	node.readHoldingRegisters(startAddress, 1);
	return node.getResponseBuffer(0);
}

void ABBDrive::setFrequency(float frequency){
<<<<<<< HEAD
	int scaleFrequency = int((frequency/50.0)*20000);
=======
	int scaleFrequency = int(frequency*400);
>>>>>>> c49298ebfbb3e76d20cbffb852cb531db09976c9
	node.writeSingleRegister(1, scaleFrequency);
}

int ABBDrive::getFrequency(){
<<<<<<< HEAD
	return node.readHoldingRegisters(102, 1);
	return node.getResponseBuffer(0);
=======
	node.readHoldingRegisters(102, 1);
	return int(node.getResponseBuffer(0)/10);
>>>>>>> c49298ebfbb3e76d20cbffb852cb531db09976c9
}

void ABBDrive::setControlWord(int value){
	node.writeSingleRegister(0, value);
}
int  ABBDrive::getStatusWord(){
<<<<<<< HEAD
	return node.readHoldingRegisters(3, 1);
=======
	node.readHoldingRegisters(3, 1);
>>>>>>> c49298ebfbb3e76d20cbffb852cb531db09976c9
	return node.getResponseBuffer(0);
}
