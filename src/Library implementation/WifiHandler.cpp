//WifiHandler.h implementation

#include "WifiHandler.h"
#include "DisplayHandler.h"
#include <wifi.h>


void WifiHandler :: begin(){
    {
            
            LittleFSHandler fs;
            Serial.println("loading data");
            std :: vector<String> data = fs.loadFS_json({"ssid_ac","psw_ac","ssid_wifi","psw_wifi"},"/wifi.json");
            while(data.size()<4){
                JsonDocument json;
                json["ssid_ac"] = "ESP32_ACCES";
                json["psw_ac"] = "ESP32_PSW";
                json["ssid_wifi"] ="";
                json["psw_wifi"] ="";
                fs.new_file(json,"/wifi.json");
                data = fs.loadFS_json({"ssid_ac","psw_ac","ssid_wifi","psw_wifi"},"/wifi.json");
            }

            this->ssid = data[0];
            this->psw = data[1];
            Serial.print("ssid_ac   ");Serial.println(ssid);
            Serial.print("psw_ac   ");Serial.println(psw);
            Serial.print("ssid_wifi   ");Serial.println(data[2]);
            Serial.print("psw_wifi   ");Serial.println(data[3]);
            WiFi.mode(WIFI_AP_STA); //act as an AccesPoint as a Client

            if(!ACturnOn(ssid,psw))
                display.print("Something went wrong, please restart","");
            if(data[2] != "")
                WifiConnect(data[2], data[3]);
            
        }
}

bool WifiHandler :: ACturnOn(String ssid, String psw){
    
    display.print("Starting AC ");
    
    int start=millis();
    
    while(WiFi.softAP(ssid,psw)){
        display.print(".");
        delay(500);
        if(millis()-start > 10000)
            return false;
    }
    
    display.print("AC online!","IP : "+WiFi.softAPIP() );

    return true;
}   

bool WifiHandler :: WifiConnect(String ssid, String psw){
  
    display.print("Connecting to WiFi ");

    int start=millis();

    while(WiFi.status() != WL_CONNECTED){
        display.print(".");
        delay(500);
        if(millis()-start > 10000)
            return false;
    }

    display.print("Succesfully connceted to WIFI");
    
    return true;
}