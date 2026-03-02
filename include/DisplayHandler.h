#ifndef DISPLAYHANDLER_H
#define DISPLAYHANDLER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#pragma once

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64



class DisplayHandler{
    private:
        Adafruit_SSD1306 display;

    
    public:
        DisplayHandler(): display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1){};
        void begin();
        void print(String row1);
        void print(String row1, String row2);

};



#endif