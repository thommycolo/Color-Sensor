#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "LittleFSHandler.h"
#include <ArduinoJson.h>
#pragma once

class WifiHandler{
    private:
        Adafruit_SSD1306 &display;
        const char* ssid ;
        const char* psw ;
    public:
        WifiHandler(Adafruit_SSD1306 &display): display(display) {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);

            LittleFSHandler fs;
            std :: vector<String> data = fs.loadFS_json({"ssid_ac","psw_ac"},"/wifi.json");
            while(data.empty()){
                JsonDocument json;
                json["ssid_ac"] = "ESP32_ACCES";
                json["psw_ac"] = "ESP32_PSW";
                json["ssid_wifi"] ="";
                json["psw_wifi"] ="";
                fs.new_file(json,"/wifi.json");
                data = fs.loadFS_json({"ssid_ac","psw_ac"},"/wifi.json");
            }

            if(!ACturnOn(ssid,psw))
                display.print("Something went wrong, please restart");
            WiFi.mode(WIFI_AP_STA); //act as an AccesPoint as a Client
        }
        
        bool ACturnOn(const char* ssid, const char* psw);
        bool WifiConnect(const char* ssid, const char* psw);

};





#endif