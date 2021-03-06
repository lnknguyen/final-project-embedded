/*
 * CO2Sensor.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nmv
 */

#include "CO2Sensor.h"
#include "chip.h"
#include <stdio.h>



CO2Sensor::CO2Sensor(){
	CO2 = 0;
	a3 = 0;
	d3 = 0;
}
float CO2Sensor::toHz(){
	return 0;
}

float CO2Sensor::toValue(){

	a3 = Chip_ADC_GetDataReg(LPC_ADC0, 3);
	d3 = ADC_DR_RESULT(a3);

	if(d3 >= 1800){
		CO2 = -4.037731276 * d3 + 8250.731195;
	}else{
		CO2 = -13.31942789 * d3 + 24782.03218;
	}
	//Sleep(10);
	return CO2;
}
