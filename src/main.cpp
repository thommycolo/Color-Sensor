#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <WebServer.h>
#include <ESPmDNS.h>

//project library
#include "ColorSensor.h"
#include "ColorTable.h"
#include "LittleFSHandler.h"
#include "WebManager.h"
#include "WifiHandler.h"


// ESP32 Config
// --------------------------------------------------
#define SDA_PIN 21
#define SCL_PIN 22
// 3.3V 
// --------------------------------------------------


// DISPLAY CONFIG
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);




//WIFI JSON-----------------------------------------
//Json path
String json_wifi_path = "/json_wifi.json";





// SETUP
void setup() {

  //main configuration
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN);  // I2C

  LittleFSHandler fs_handler; // Initialize LittleFS_Handler
  fs_handler.begin(); 

  WifiHandler wifi_handler(display); // Initialize WifiHandler

  




  /*
  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN);  // I2C 

  sens_config();
  disp_config();

  
  //WIFI Config
  // Check if json is correct
  if (!LittleFS.begin(true)) {
    Serial.println("Error: could not build LittleFS correctly");
    return;
  }
  else
  {
    LoadWiFiJson();
    ListFS();
  }
  //Uncomment this line for update
  //SaveWiFiJson(ssid_esp32, psw_esp32, ssid_ext, psw_ext); // write actual value
  

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid_esp32.c_str(), psw_esp32.c_str()); //create his own network
  WiFi.begin(ssid_ext.c_str(), psw_ext.c_str()); //connect to a third network

  if (MDNS.begin("color-reader")) {
    Serial.println("MDNS responder started (color-reader.local)");
  }

  //Esp32 webapp config
  server.on("/", HTTP_GET, []() {
      serveSmartFile("/esp32_webapp/index.html", "/external_webapp/index.html", "text/html");
  });

  // 2. CSS (/style.css): Serve lo stile corretto per il sito visualizzato
  server.on("/style.css", HTTP_GET, []() {
      serveSmartFile("/esp32_webapp/style.css", "/external_webapp/style.css", "text/css");
  });

  // 3. JS (/script.js): Serve lo script corretto
  server.on("/script.js", HTTP_GET, []() {
      serveSmartFile("/esp32_webapp/script.js", "/external_webapp/script.js", "application/javascript");
  });

  // API Standard
  server.on("/api/Esp32_GetConfig", HTTP_GET, Esp32_HandleGetConfig);
  server.on("/api/Esp32_SaveConfig", HTTP_POST, Esp32_HandleSaveConfig);
  server.on("/api/Esp32_GetColor", HTTP_GET, Esp32_HandleGetColorData);
  
  // Se vuoi ancora accedere esplicitamente alla config da esterno
  server.serveStatic("/config", LittleFS, "/esp32_webapp/index.html");
  
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Web server started");


  WhiteCalibration();
  */
}

// LOOP
void loop() {
  //create server
  server.handleClient();

  int colors_rgb[3];
  
  //GetColor(colors_rgb);

  //Print_value(colors_rgb);
  
  GetColor2();
  delay(500);
}
