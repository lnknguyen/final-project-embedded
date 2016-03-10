/*
 * ABBDrive.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */


#include "ABBDrive.h"


ABBDrive::ABBDrive(ModbusMaster _node){
	node = _node;

}

void ABBDrive::init(){
	node.begin(9600);
	node.writeSingleRegister(0, 0x0406);
	Sleep(1000);
	node.writeSingleRegister(0, 0x047F);
	Sleep(1000);
}

void ABBDrive::setSingleRegister(int startAddress, int value){
	node.writeSingleRegister(startAddress, value);
}

int  ABBDrive::getSingleRegister(int startAddress){
	node.readHoldingRegisters(startAddress, 1);
	return node.getResponseBuffer(0);
}

void ABBDrive::setFrequency(float frequency){



	int scaleFrequency = int(frequency*400);

	node.writeSingleRegister(1, scaleFrequency);
}

int ABBDrive::getFrequency(){

	return node.readHoldingRegisters(102, 1);
	return node.getResponseBuffer(0);

	node.readHoldingRegisters(102, 1);
	return int(node.getResponseBuffer(0)/10);

}

void ABBDrive::setControlWord(int value){
	node.writeSingleRegister(0, value);
}
int  ABBDrive::getStatusWord(){

	return node.readHoldingRegisters(3, 1);

	node.readHoldingRegisters(3, 1);

	return node.getResponseBuffer(0);
}
