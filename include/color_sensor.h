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
        private:
        Adafruit_SSD1306 &display;
        Adafruit_TCS34725 &tcs;

	public:	
        SensorHandler(Adafruit_SSD1306 &display , Adafruit_TCS34725 &tcs) : display(display), tcs(tcs) {
                display.clearDisplay();
                while (!tcs.begin()) {
                        display.setCursor(0,0);
                        display.print("Sensor not found");
                        delay(100);
                }
        } 

        const RGB_coef Calibration();
        const RGB GetColor(RGB_coef &rgb_coef);

};




#endif