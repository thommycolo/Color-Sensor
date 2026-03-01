
#include "DisplayHandler.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



void DisplayHandler :: print(String row1){
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(row1);
    display.display();
}
void DisplayHandler :: print(String row1, String row2){
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(row1);
    display.setCursor(0,1);
    display.print(row2);
    display.display();
}