#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "LittleFSHandler.h"
#include <ArduinoJson.h>
#pragma once

class wifi_handler{
    private:
        Adafruit_SSD1306 &display;
        const char* ssid ;
        const char* psw ;
    public:
        wifi_handler(Adafruit_SSD1306 &display): display(display) {
            display.setTextSize(1);
            display.setTextColor(SSD1306_WHITE);
            LittleFS_Handler fs;
            vector<String> data = fs.loadFS_json({"ssid_ac","psw_ac"},"/wifi.json");
            while(data.empty()){
                JsonDocument json;
                json["ssid_ac"] = "ESP32_ACCES";
                json["psw_ac"] = "ESP32_PSW";
                json["ssid_wifi"] ="";
                json["psw_wifi"] ="";
                fs.new_file(json,"/wifi.json");
                data = fs.loadFS_json({"ssid_ac","psw_ac"},"/wifi.json");
            }

            ACturnOn(ssid,psw);
            WiFi.mode(WIFI_AP_STA); //act as AccesPoint as Client
        }
        
        bool ACturnOn(const char* ssid, const char* psw);
        bool WifiConnect(const char* ssid, const char* psw);

};





#endif