//WifiHandler.h implementation
#include "WifiHandler.h"


void WifiHandler :: begin(){
    {
            display.begin();

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
            delay(100);
            if(!ACturnOn(ssid,psw))
                display.print("Something went wrong, please restart","");
            delay(1000);
            if(data[2] != "")
                WifiConnect(data[2], data[3]);
            
        }
}

bool WifiHandler :: ACturnOn(String ssid, String psw){
    
    display.print("Starting AC ");
    
    int start=millis();
    
    if(WiFi.softAP(ssid.c_str(),psw.c_str())){
        display.print("AC online!","IP : "+WiFi.softAPIP().toString() );        
        return true;
    }
    
    return false;
}   



bool WifiHandler :: WifiConnect(String ssid, String psw){
    WiFi.disconnect();
    Serial.println("WIFI CONNECTION");
    display.print("WIFI CONNECTING");
    if (ssid.length() == 0) {
        display.print("WiFi Error:", "SSID is empty");
        return false;
    }

    display.print("Connecting to ",ssid);
    ssid.trim();
    psw.trim();

    WiFi.begin(ssid.c_str(), psw.c_str());
    
    Serial.print("**");Serial.print(ssid);Serial.print("**");
    Serial.print("**");Serial.print(psw);Serial.print("**");

    int start=millis();
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(WiFi.status());
        display.print(".");
        delay(500);
        if(millis()-start > 20000)
            return false;
    }

    display.print("Succesfully connceted to WIFI!", "IP: " + WiFi.localIP().toString());
    return true;
}
