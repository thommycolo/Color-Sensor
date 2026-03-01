// ColorSensor.h

#ifndef COLORSENSOR_H
#define COLORSENSOR_H

//#include <stddef.h>
#include <arduino.h>

#include <Adafruit_TCS34725.h>
#include "DisplayHandler.h"
#include "Types.h"


#pragma once



class SensorHandler{
        private:
        DisplayHandler display;
        Adafruit_TCS34725 tcs;

	public:	
        SensorHandler() : tcs(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X){                
                while (!tcs.begin()) {
                        display.print("Sensor not found");
                        delay(100);
                }
        } 
        

        const RGB_coef Calibration();
        const RGB GetColor(RGB_coef &rgb_coef);

};




#endif