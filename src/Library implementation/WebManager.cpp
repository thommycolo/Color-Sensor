#include "WebManager.h"
#include <ArduinoJson.h>

/**
 * Initializes the server, static files, and WebSocket events.
 */
WebManager::WebType WebManager::begin(const char* folderPath) {
    // Serve static files (HTML, CSS, JS) from LittleFS
    server.serveStatic("/", LittleFS, folderPath).setDefaultFile("index.html");

    // Configure the WebSocket event handler
    ws.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
        if (type == WS_EVT_DATA) {
            this->handleWebSocketMessage(arg, data, len);
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

/**
 * Sends color data to all connected clients using JSON format.
 * Matches the JS 'COLOR_JSON:' prefix.
 */
WebManager::WebType WebManager::updateColor(int r, int g, int b, String name) {
    StaticJsonDocument<128> doc;
    doc["r"] = r;
    doc["g"] = g;
    doc["b"] = b;
    doc["name"] = name;

    String jsonResponse;
    serializeJson(doc, jsonResponse);
    
    // Send with prefix so JS knows how to parse it
    ws.textAll("COLOR_JSON:" + jsonResponse);
    
    Serial.print("Color broadcasted: ");
    Serial.println(name);
    return COLOR_UPDATED;
}

/**
 * Parses incoming JSON messages from the website (replaces your old getData).
 */
void WebManager::handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, data, len);

    if (error) {
        Serial.print("JSON Deserialization failed: ");
        Serial.println(error.f_str());
        return;
    }

    const char* type = doc["type"]; 

    if (type && strcmp(type, "SET_WIFI") == 0) {
        const char* ssid = doc["ssid"];
        const char* psw = doc["psw"];

        Serial.printf("Received WiFi Config -> SSID: %s\n", ssid);

        // Logic to connect/save WiFi should go here
        
        // Notify the client that the command was received
        ws.textAll("STATUS:connected");
    } 
    else if (type && strcmp(type, "START_CALIBRATION") == 0) {
        Serial.println("Calibration triggered from web.");
        // Call your calibration function here
    }
}

/**
 * Cleans up disconnected clients to free up RAM.
 */
void WebManager::cleanup() {
    ws.cleanupClients();
}