// color_sensor.h

#ifndef COLOR_SENSOR_H
#define COLOR_SENSOR_H

#include <stddef.h>
#include <arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_TCS34725.h>

#include "Types.h"


#pragma once



class SensorHandler{
	public:	
        static const RGB_coef Calibration(Adafruit_SSD1306 &display, Adafruit_TCS34725 &tcs);
        static const RGB GetColor(Adafruit_SSD1306 &display , Adafruit_TCS34725 &tcs, RGB_coef &rgb_coef);

};




#endif