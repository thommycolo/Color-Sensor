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
        RGB_coef rgb_coef;
        SensorHandler() : tcs(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X){}; 
        
        void begin();
        const bool Calibration();
        const RGB GetColor();

};




#endif