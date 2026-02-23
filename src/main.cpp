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
#include "ColorTable/color_table.h"
#include "ColorSensor/color_sensor.h"

// ESP32 Config
// --------------------------------------------------
#define SDA_PIN 21
#define SCL_PIN 22
// 3.3V 
// --------------------------------------------------
// Screen dimension
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//global varaible for sites
int global_last_red =0;
int global_last_green =0;
int global_last_blue =0;
String global_last_colorName ="no color";

// WiFi configuration
// Board Network
String ssid_esp32 = "Color Reader";
String psw_esp32 = "12345678";
// External Network
String ssid_ext = "aaa"; 
String psw_ext = "12345678";

int num_of_sample = 10;

// TCS34725 sensor config
Adafruit_TCS34725 tcs(
  TCS34725_INTEGRATIONTIME_50MS,  
  TCS34725_GAIN_4X                 
);
// Screen config
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Esp32 Server
WebServer server(80);

//WIFI JSON-----------------------------------------
//Json path
String json_wifi_path = "/json_wifi.json";

void SaveWiFiJson(String new_ssid_esp32, String new_psw_esp32, String new_ssid_ext, String new_psw_ext) {
  Serial.println("--- JSON Saving ---");
  
  // Build a temporary JSON
  JsonDocument json;

  json["ssid_esp32"] = new_ssid_esp32;
  json["psw_esp32"] = new_psw_esp32;
  json["ssid_ext"] = new_ssid_ext;
  json["psw_ext"] = new_psw_ext;

  // Open, write and rewrite JSON
  File file = LittleFS.open(json_wifi_path, "w");
  if (!file) {
    Serial.println("Error while wrinting JSON file");
    return;
  }

  // Writing the file into the json
  serializeJson(json, file);
  file.close();
  
  // Aggiorna anche le variabili in memoria
  ssid_esp32 = new_ssid_esp32;
  psw_esp32 = new_psw_esp32;
  ssid_ext = new_ssid_ext;
  psw_ext = new_psw_ext;
  Serial.println("Wifi Configuration Saved!");
}

void LoadWiFiJson() {
  Serial.println("--- Loading Json ---");

  // Check if Json exist, if not build it 
  if (!LittleFS.exists(json_wifi_path)) {
    Serial.println("File path not found! File creation in progress...");
    SaveWiFiJson(ssid_esp32, psw_esp32, ssid_ext, psw_ext); // write actual value
    return; 
  }

  // Open File in read mode
  File file = LittleFS.open(json_wifi_path, "r");
  if (!file) {
    Serial.println("Cannot read file");
    return;
  }

  //JSON Decode
  JsonDocument json;
  DeserializationError error = deserializeJson(json, file);

  if (error) {
    Serial.println("Error while reading JSON");
  } else {
    // 5. Se tutto ok, sovrascrive le variabili con quelle del file
    ssid_esp32  = json["ssid_esp32"].as<String>();
    psw_esp32  = json["psw_esp32"].as<String>();
    ssid_ext  = json["ssid_ext"].as<String>();
    psw_ext  = json["psw_ext"].as<String>();

    
    Serial.println("Configuration loaded succesfully:");
    Serial.println("ESP32_SSID: " + ssid_esp32);
    Serial.println("ESP32_PSW: " + psw_esp32);
    Serial.println("EXT_SSID: " + ssid_ext);
    Serial.println("EXT_PSW: " + psw_ext);
  }
  file.close();
}

//print all files in LittleFS
void listDir(const char * dirname, uint8_t levels) {
  
  File root = LittleFS.open(dirname,"r"); 

  if (!root) {
    Serial.println("- Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    
    for (int i = 0; i < levels; i++) {
        Serial.print("  "); 
    }

    if (file.isDirectory()) {
      Serial.print("[DIR]  "); //stands for Directory
      Serial.println(file.name());
      
      
      if (levels) {
        String path = String(dirname);
        if (path != "/") path += "/";
        path += String(file.name());

        if (String(file.name()).startsWith("/")) path = String(file.name());
        
        listDir(path.c_str(), levels - 1);
      } 

    } else {
      Serial.print("[FILE] "); //stands for File
      Serial.print(file.name());
      Serial.print("\t| SIZE: ");
      Serial.print(file.size());
      Serial.println(" bytes");
    }

    file = root.openNextFile();
  }
}

void ListFS() {
  Serial.println("---- LittleFS FILESYSTEM TREE ----");
  
  listDir("/", 3);
  
  Serial.println("---- END OF FILE LIST ----");
}

//--------------------------------------------------

// ESP32 WEBAPP-------------------------------------
//handle not found
void handleNotFound() {
  String message = "404 Not Found\nURI: "; message += server.uri();
  server.send(404, "text/plain", message);
}
//send json to the esp32_webapp
void Esp32_HandleGetConfig() {
  File file = LittleFS.open(json_wifi_path, "r");
  if (file) {
    server.streamFile(file, "application/json");
    file.close();
  } else {
    server.send(200, "application/json", "{}");
  }
}
//receive new data from the webaap
void Esp32_HandleSaveConfig() {
  // check if the request have something in response
  if (server.hasArg("plain") == false) {
    server.send(400, "text/plain", "Body not received");
    return;
  }

  String body = server.arg("plain");
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, body);

  if (error) {
    server.send(400, "text/plain", "Invalid JSON");
    return;
  }

  // get new data for the external network
  ssid_ext = doc["ssid_ext"].as<String>();
  psw_ext = doc["psw_ext"].as<String>();

  // save updated data in the JSON
  SaveWiFiJson(ssid_esp32, psw_esp32, ssid_ext, psw_ext);

  // 2.OLED Feedback
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Connecting to: ");display.println(ssid_ext.c_str());
  display.println(ssid_ext);
  display.display();
  
  Serial.print("Connecting to: ");Serial.println(ssid_ext.c_str());

  WiFi.disconnect();
  delay(100);
  WiFi.begin(ssid_ext.c_str(), psw_ext.c_str());
  
  display.clearDisplay();
  display.setCursor(0,0);
  int tries = 0;
  while (WiFi.status() != WL_CONNECTED && tries < 10) {
    Serial.print(".");
    display.print(".");
    display.display();
    delay(1000);
    tries++;
  }

  display.clearDisplay();
  display.setCursor(0,0);
  //sending server response
  if (WiFi.status() == WL_CONNECTED) {
    display.println("Device succesflully connected to: ");
    display.println(ssid_ext);
    
    Serial.print("Device succesflully connected to: ");Serial.println(ssid_ext);
    String successJson = "{\"status\":\"connected\", \"ssid_ext\":\"" + ssid_ext + "\"}";
    server.send(200, "application/json", successJson);
    Serial.println( "WiFi connection Done!");

  } else {
    display.println("WIFI CONNECTION FAILED!");
    display.println("Check Password or wifi name");
    
    server.send(401, "application/json", "{\"status\":\"failed\", \"message\":\"Password errata o rete non trovata\"}");
    Serial.println("WiFi conneciton Failed!");
  }
  display.display();
  delay(2000);
}
//this function get called by the sites every 1s in order to take the new data
void Esp32_HandleGetColorData() {
  JsonDocument doc;
  doc["r"] = global_last_red;
  doc["g"] = global_last_green;
  doc["b"] = global_last_blue;
  doc["name"] = global_last_colorName;
  
  String response;
  serializeJson(doc, response);
  server.send(200, "application/json", response);
}
//--------------------------------------------------

// Hardwares Config
void sens_config() {
  while (!tcs.begin()) {
    Serial.println("Sensor not found");
    delay(200);
  }
}

void disp_config(){
  while(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("Display not found");
    delay(200);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}



// Serial Printing
void Print_value(int* colors_rgb) {
  
  global_last_red = colors_rgb[0];
  global_last_green = colors_rgb[1];
  global_last_blue = colors_rgb[2];

  global_last_colorName = TableHandler::getColor(global_last_red, global_last_green, global_last_blue);


  display.clearDisplay();       
  display.setCursor(0, 0);
  display.print("R=");display.print(colors_rgb[0]);display.print(" G=");display.print(colors_rgb[1]);display.print(" B=");display.println(colors_rgb[2]);;      
  display.print(TableHandler::getColor(colors_rgb[0],colors_rgb[1],colors_rgb[2]));display.display();
}

//This function help the routing beetwen the two possible sites based on the given IP
void serveSmartFile(String internalPath, String externalPath, String mimeType) {
    IPAddress clientIP = server.client().localIP();
    IPAddress apIP = WiFi.softAPIP(); // usually 192.168.4.1
    
    String path = externalPath; // Default: MONITOR 
    
    // if the user is connected to the ESP32 Hotspot -> Cofniguration
    if (clientIP == apIP) {
        path = internalPath;
    }
    
    File file = LittleFS.open(path, "r");
    if (file) {
        server.streamFile(file, mimeType);
        file.close();
    } else {
        server.send(404, "text/plain", "File not found: " + path);
    }
}



// SETUP
void setup() {
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
