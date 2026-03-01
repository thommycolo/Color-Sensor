#ifndef WIFIHANDLER_H
#define WIFIHANDLER_H

#include <WiFi.h>
#include "DisplayHandler.h"
#include "LittleFSHandler.h"
#include <ArduinoJson.h>
#pragma once

class WifiHandler{
    private:
        DisplayHandler display;
        String ssid ;
        String psw ;
    public:
        void begin();
        
        bool ACturnOn(String ssid, String psw);
        bool WifiConnect(String ssid, String psw);

};





#endif