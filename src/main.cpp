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

  WebManager web_manager();

}

// LOOP
void loop() {
  
  

}
