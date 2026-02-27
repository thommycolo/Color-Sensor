// ColorSensor.h

#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <stddef.h>
#include <arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_TCS34725.h>

#include "Types.h"


#pragma once



class SensorHandler{
        private:
        Adafruit_SSD1306 &display;
        Adafruit_TCS34725 tcs;

	public:	
        SensorHandler(Adafruit_SSD1306 &display);

        const RGB_coef Calibration();
        const RGB GetColor(RGB_coef &rgb_coef);

};




#endif