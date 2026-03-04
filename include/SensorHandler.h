// ColorSensor.h

#ifndef COLORSENSOR_H
#define COLORSENSOR_H


#include <Adafruit_TCS34725.h>
#include "DisplayHandler.h"
#include "Types.h"
#include "TableHandler.h"
#include "LittleFSHandler.h"




#pragma once



class SensorHandler{
        private:
        DisplayHandler display;
        Adafruit_TCS34725 tcs;
        RGB_coef calibration_coef;
        RGB rgb;
        void calib_saving();

	public:	
        //RGB_coef rgb_coef;
        SensorHandler() : tcs(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X){}; 
        
        sensor_status begin();
        const bool Calibration();
        const RGB GetColor();

};




#endif