#ifndef WEBSERVER_H
#define WEBSERVER_H



#include <ESPAsyncWebServer.h>
#include "Types.h"
#include "LittleFSHandler.h"
#pragma once


class WebManager {
private:
    AsyncWebServer server;
    AsyncWebSocket ws;

public:
    WebManager() : server(80), ws("/ws") {}

    public static enum class WebType {
        SERVER_ONLINE,
        FAILED_TO_CONNECT,
        COLOR_UPDATED,
    };

    WebType begin(const char* folderPath);
    
    WebType updateColor(String hexColor) ;

    
    void getData(void *arg, uint8_t *data, size_t len) ;

    void cleanup();
};



#endif