#include <Arduino.h>

//project library
#include "SensorHandler.h"
#include "ColorTable.h"
#include "LittleFSHandler.h"
#include "WebManager.h"
#include "WifiHandler.h"
#include "DisplayHandler.h"


// ESP32 Config
// --------------------------------------------------
#define SDA_PIN 21
#define SCL_PIN 22
// 3.3V 
// --------------------------------------------------

//INITIALIZZATION
DisplayHandler display; //     Display
LittleFSHandler fs_handler; // LittleFS_Handler
WifiHandler wifi_handler; //   WifiHandler
WebManager web_manager; //     WebManager




// SETUP
void setup() {

  //main configuration

  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);  // I2C
  
  

  display.print("Welcome!");
  
  fs_handler.begin(); 

  wifi_handler.begin(); 

  web_manager.begin();

}

// LOOP
void loop() {
  

}
