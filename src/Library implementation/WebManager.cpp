#include "WebManager.h"


#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include "LittleFSHandler.h"
#include <WiFi.h>


WebManager::WebType WebManager::begin() {

    server.on("/",HTTP_GET, [this](AsyncWebServerRequest *request){
        if (request->client()->localIP() == WiFi.softAPIP())
            request->redirect(String(ac_webapp_path.c_str()) + "/index.html");
        else
            request->redirect(String(wifi_webapp_path.c_str()) + "/index.html");
    });

    // Serve static files (CSS, JS) from LittleFS
    server.serveStatic(ac_webapp_path.c_str(), LittleFS, ac_webapp_path.c_str());
    server.serveStatic(wifi_webapp_path.c_str(), LittleFS, wifi_webapp_path.c_str());


    // Configure the WebSocket event handler
    ws.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
        if (type == WS_EVT_DATA) {
            this->getData(arg, data, len);
        } else if (type == WS_EVT_CONNECT) {
            Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        } else if (type == WS_EVT_DISCONNECT) {
            Serial.printf("WebSocket client #%u disconnected\n", client->id());
        }
    });

    server.addHandler(&ws);
    server.begin();
    return SERVER_ONLINE;
}


WebManager::WebType WebManager::updateColor(RGB rgb) {
    StaticJsonDocument<128> doc;
    doc["r"] = rgb.r;
    doc["g"] = rgb.g;
    doc["b"] = rgb.b;
    doc["name"] = rgb.color_name;

    String jsonResponse;
    serializeJson(doc, jsonResponse);
    
    // Send with prefix so JS knows how to parse it
    ws.textAll("COLOR_JSON:" + jsonResponse);
    
    
    return COLOR_UPDATED;
}


void WebManager::getData(void *arg, uint8_t *data, size_t len) {
    StaticJsonDocument<256> doc;

    if (deserializeJson(doc, data, len)) {
        Serial.print("JSON Deserialization failed: ");
        Serial.println(deserializeJson(doc, data, len).f_str());
        return;
    }

    const char* type = doc["type"]; 

    if (type && strcmp(type, "SET_WIFI") == 0) {

        LittleFSHandler fs;
        std :: vector<String> data;
        data.push_back(doc["ssid"]);
        data.push_back(doc["psw"]);

        fs.saveFS_json(data , "/json_wifi.json" );

        ws.textAll("STATUS:data saved correctly");
    } 
    else {
        Serial.println("Error while saving data");
    }
}


void WebManager::cleanup() {
    ws.cleanupClients();
}