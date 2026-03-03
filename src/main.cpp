#include <Arduino.h>

//project library
#include "SensorHandler.h"
#include "LittleFSHandler.h"
#include "WebManager.h"
#include "WifiHandler.h"
#include "DisplayHandler.h"


// ESP32 Config
// --------------------------------------------------
#define SDA_PIN 21
#define SCL_PIN 22
#define SCAN_TRIGGER 19 //gray-yellow
#define CALI_TRIGGER 18 //purple-green
// 3.3V 
// --------------------------------------------------
//INITIALIZZATION
DisplayHandler display;       //Display
LittleFSHandler fs_handler;   //LittleFS_Handler
WifiHandler wifi_handler;     //WifiHandler
WebManager web_manager;       //WebManager
SensorHandler sensor;         //Sensor



// SETUP
void setup() {

  Serial.begin(115200);

  pinMode(SCAN_TRIGGER, INPUT_PULLUP);
  pinMode(CALI_TRIGGER, INPUT_PULLUP);
  
  //Everything that need a .begin()
  Wire.begin(SDA_PIN, SCL_PIN);  // I2C
  display.begin();
  fs_handler.begin(); 
  wifi_handler.begin(); 
  web_manager.begin();
  sensor.begin();


  display.print("Welcome!");
  delay(1000);

  
}

// LOOP
void loop() {
  if(web_manager.new_credentials == true){
    std:: vector<String> value = fs_handler.loadFS_json({"ssid_wifi","psw_wifi"},"/wifi.json");
    wifi_handler.WifiConnect(value[0],value[1]);
    web_manager.new_credentials = false;
  }
  if (digitalRead(CALI_TRIGGER) == LOW) {
    if(!sensor.Calibration())
      Serial.println("Error while calibrating");
    delay(50); 
  }
  if (digitalRead(SCAN_TRIGGER) == LOW) {
    web_manager.updateColor(sensor.GetColor());
    delay(50);
  }
  
}
