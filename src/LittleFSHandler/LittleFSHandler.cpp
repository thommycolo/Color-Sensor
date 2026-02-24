//implementation of LittleFSHandler.h

#include "LittleFSHandler.h"

#include <LittleFS.h>
#include <Arduino.h>
#include <string.h>
#include <vector>
#include <ArduinoJson.h>

using namespace std;


LittleFS_Handler ::fs_status LittleFS_Handler :: printFS(const char* dirname, int depth){
    Serial.println("---- LittleFS FILESYSTEM TREE ----");

    if ( !LittleFS.open(dirname,"r")) return FS_NOT_FOUND;
    if (!LittleFS.open(dirname,"r").isDirectory()) return CANNOT_OPEN_DIRECTORY;
 
    File file = LittleFS.open(dirname,"r").openNextFile();
    while (file) {

        for (int i = 0; i < depth; i++) {
            Serial.print("  "); 
        }

        if (file.isDirectory()) {
            Serial.print("[DIR]  "); 
            Serial.println(file.name());


            if (depth) {
                String path = String(dirname);
                if (path != "/") 
                    path += "/";
                path += String(file.name());

                if (String(file.name()).startsWith("/")) 
                    path = String(file.name());
                
                printFS(path.c_str(), depth - 1);
            }           

        } else {
            Serial.print("[FILE] ");
            Serial.print(file.name());
            Serial.print("\t| SIZE: ");
            Serial.print(file.size());
            Serial.println(" bytes");
        }

        file = file.openNextFile();
    }
    Serial.println("---- END OF FILE LIST ----");
    return OPERATION_DONE;
}
// USA LA VECTOR PER PASSARE PATH!
LittleFS_Handler :: fs_status LittleFS_Handler :: saveFS_json(vector<String> data, const char* path){

    Serial.println("--- JSON Saving ---");

    JsonDocument json;
    for(const String& d : data){

        int spacePos = d.indexOf(' ');

        if(spacePos == -1) return WRONG_INPUT_FORMAT;
        json[d.substring(0 , spacePos)] = d.substring(spacePos +1);
        
    }
    // Open, write and rewrite JSON
    File file = LittleFS.open(path, "w");
    if (!file) return FAILED_WRITING;

    //Saving the json
    serializeJson(json, file);
    file.close();
    Serial.println("--- JSON Saved ---");  
    return OPERATION_DONE;
}
