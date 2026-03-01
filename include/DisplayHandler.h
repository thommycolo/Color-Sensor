#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#pragma once

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64



class DisplayHandler{
    private:
        Adafruit_SSD1306 display{SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1};

    
    public:
        DisplayHandler(){
            Serial.println("bebbo");
            display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
            display.clearDisplay();
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
        }
        void print(String row1);
        void print(String row1, String row2);

};



#endif