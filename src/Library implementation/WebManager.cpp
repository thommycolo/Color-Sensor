#include "WebManager.h"


#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <Arduino.h>
#include "LittleFSHandler.h"
#include "WifiHandler.h"


WebManager::WebType WebManager::begin() {

    server.on("/",HTTP_GET, [this](AsyncWebServerRequest *request){
        if (request->client()->localIP() == WiFi.softAPIP())
            request->redirect(String(ac_webapp_path.c_str()) + "/index.html");
        else
            request->redirect(String(wifi_webapp_path.c_str()) + "/index.html");
    });
    server.on("/test", HTTP_GET, [](AsyncWebServerRequest *request){
             request->send(200, "text/plain", "Il server funziona, il problema è LittleFS!");});
    // Serve static files (CSS, JS) from LittleFS
    server.serveStatic(ac_webapp_path.c_str(), LittleFS, ac_webapp_path.c_str());
    server.serveStatic(wifi_webapp_path.c_str(), LittleFS, wifi_webapp_path.c_str());
    server.serveStatic("/", LittleFS, "/");

    // Configure the WebSocket event handler
    ws.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
        
        if (type == WS_EVT_CONNECT) {
            Serial.printf("WebSocket client #%u connesso da %s\n", client->id(), client->remoteIP().toString().c_str());
            client->text("STATUS:online");
        } 
        
        else if (type == WS_EVT_DISCONNECT) {
            Serial.printf("WebSocket client #%u disconnesso\n", client->id());
        } 
        
        else if (type == WS_EVT_DATA) {
            AwsFrameInfo *info = (AwsFrameInfo*)arg;
            
            if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
                data[len] = 0; 
                this->getData(arg, data, len);
            }
        }
        
        else if (type == WS_EVT_PONG) {
            Serial.printf("WebSocket client #%u ha risposto al ping\n", client->id());
        }

        

    });

    server.addHandler(&ws);
    server.begin();
    return SERVER_ONLINE;
}


WebManager::WebType WebManager::updateColor(RGB rgb) {
    JsonDocument doc;
    doc["r"] = rgb.r;
    doc["g"] = rgb.g;
    doc["b"] = rgb.b;
    doc["name"] = (rgb.color_name != "") ? rgb.color_name : "Unknown";

    String msg;
    serializeJson(doc, msg); 
    
    msg = "COLOR_JSON:" + msg;

    Serial.println("Sending to WS: " + msg);
    
    ws.textAll(msg);
    
    
    return COLOR_UPDATED;
}

void WebManager::getData(void *arg, uint8_t *data, size_t len) {
    JsonDocument doc;

    // Deserializzation with error check
    DeserializationError error = deserializeJson(doc, data, len);
    if (error) {
        Serial.print("JSON Deserialization failed: ");
        Serial.println(error.f_str());
        return;
    }

    const char* type = doc["type"]; 

    if (type && strcmp(type, "SET_WIFI") == 0) {
        String ssid = doc["ssid"] | "";
        String psw = doc["psw"] | "";

        if (ssid != "") {
            LittleFSHandler fs;
            JsonDocument json;
            json["ssid_wifi"] =ssid.c_str();
            json["psw_wifi"] = psw.c_str();
            fs.saveFS_json(json, "/wifi.json");
            
            new_credentials = true;

            ws.textAll("STATUS:connected");
            
            Serial.println("Credenziali salvate e conferma inviata al client.");
        } else {
            ws.textAll("STATUS:error_empty_ssid");
        }
    } 
    else {
        Serial.println("Tipo di pacchetto sconosciuto");
    }
}


void WebManager::cleanup() {
    ws.cleanupClients();
}