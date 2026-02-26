//WifiHandler.h implementation

#include "WifiHandler.h"
#include <wifi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

bool WifiHandler :: ACturnOn(const char* ssid, const char*psw){
    display.clearDisplay();
    display.setCursor(0,0);
    
    display.print("Starting AC ");

    int start=millis();
    
    while(WiFi.softAP(ssid,psw)){
        display.print(".");
        delay(500);
        if(millis()-start > 10000)
            return false;
    }
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("AC online!");
    display.setCursor(0,1);
    display.print("IP :"); display.print(WiFi.softAPIP());
    return true;
}   

bool WifiHandler :: WifiConnect(const char* ssid, const char* psw){
    display.clearDisplay();
    display.setCursor(0,0);
    
    display.print("Connecting to WiFi ");

    int start=millis();

    while(WiFi.status() != WL_CONNECTED){
        display.print(".");
        delay(500);
        if(millis()-start > 10000)
            return false;
    }
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Succesfully connceted to WIFI");
    return true;
}