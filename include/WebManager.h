#ifndef WEBMANAGER_H
#define WEBMANAGER_H

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "Types.h"
#include "LittleFSHandler.h"

#pragma once

/**
 * @class WebManager
 * @brief Handles WebSocket communication and HTTP serving for the web interface.
 * * This class manages the asynchronous web server and WebSocket events,
 * allowing real-time data exchange between the microcontroller and a web client.
 */
class WebManager {
private:
    AsyncWebServer server;
    AsyncWebSocket ws;

public:
    /**
     * @brief Construct a new Web Manager object.
     * Initializes the server on port 80 and the WebSocket on the "/ws" endpoint.
     */
    WebManager() : server(80), ws("/ws") {}

    /**
     * @brief Return types for WebManager operations.
     */
    typedef enum {
        SERVER_ONLINE,      ///< Server started successfully
        FAILED_TO_CONNECT,  ///< Reserved for connection errors
        COLOR_UPDATED       ///< Color data was successfully broadcasted
    } WebType;

    /**
     * @brief Initializes the web server and WebSocket handlers.
     * * Sets up LittleFS to serve static files from the provided path and 
     * attaches event listeners for WebSocket connections, disconnections, and data.
     * * @param folderPath The directory in LittleFS containing the web files (e.g., "/www").
     * @return WebType SERVER_ONLINE upon successful setup.
     */
    WebType begin(const char* folderPath);
    
    /**
     * @brief Broadcasts an RGB color update to all connected WebSocket clients.
     * * Encapsulates the RGB data into a JSON object prefixed with "COLOR_JSON:".
     * * @param rgb A struct containing red, green, blue values and the color name.
     * @return WebType COLOR_UPDATED.
     */
    WebType updateColor(RGB rgb);

    /**
     * @brief Processes incoming WebSocket data packets.
     * * Parses incoming JSON messages. Currently supports:
     * - "SET_WIFI": Saves SSID and Password to LittleFS via LittleFS_Handler.
     * * @param arg Pointer to the client session or event context.
     * @param data Pointer to the raw byte buffer received.
     * @param len Length of the data buffer.
     */
    void getData(void *arg, uint8_t *data, size_t len);

    /**
     * @brief Performs maintenance on WebSocket clients.
     * * Should be called periodically (usually in the main loop) to clear 
     * closed connections and free up memory.
     */
    void cleanup();
};

#endif