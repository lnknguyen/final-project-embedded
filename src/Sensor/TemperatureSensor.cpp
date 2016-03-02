/*
 * TemperatureSensor.cpp
 *
 *  Created on: Mar 1, 2016
 *      Author: nguyenluong
 */

#include "TemperatureSensor.h"
#include "chip.h"
#include <stdio.h>

#define SCALE_FACTOR 240.0
#define SENSOR_ADDR 0x40

float temperatureArray[] = {0,10,20,25,30,40,50,60,70,80,90,100};
float resistorMin[] = {1603,1748,1901,1980,2057,2217,2383,2557,2737,2924,3118,3318};
float resistorMax[] = {1630,1772,1922,2000,2080,2245,2417,2597,2785,2980,3182,3392};
float tempMin = -100;
float tempMax = 200;
int count_temp_sections = sizeof(temperatureArray)/sizeof(float);
float resistor = 1500;

TemperatureSensor::TemperatureSensor(){
	temperature = 0;
	a0 = 0;
	d0 = 0;
}
float TemperatureSensor::toHz(){
	return 0;
}

int TemperatureSensor::toValue(){

	a0 = Chip_ADC_GetDataReg(LPC_ADC0, 0);
	d0 = ADC_DR_RESULT(a0);

	float resistance = resistor * d0/(4095-d0) -450;
	float temp = 0;
	for (int i = 1; i<count_temp_sections; i++){
		if (resistance >= resistorMin[i] && resistance<=resistorMax[i]) {
			temp = temperatureArray[i];
		}else{
			  if (resistance >= resistorMin[i-1] && resistance <=resistorMin[i]){
				  tempMin = temperatureArray[i-1];
			  }
			  if (resistance >= resistorMax[i-1] && resistance <=resistorMax[i]){
				  tempMax = temperatureArray[i];
			  }
			  temp = tempMin + (tempMax - tempMin) * 2*resistance/ (resistorMin[i-1]+ resistorMax[i-1]);
		}
	}
	if (resistance > resistorMax[count_temp_sections-1]){
		temp = tempMax;
	}
	printf("min = %.2f, max = %.2f, resistance = %.2f, temp = %.2f \n",  tempMin, tempMax,resistance, temp);
	//Sleep(100);
	return (int)temp;
	//printf("temp = %.2f \n", temp);
}
