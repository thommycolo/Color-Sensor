//implementation of LittleFSHandler.h

#include "LittleFSHandler.h"

#include <LittleFS.h>
#include <Arduino.h>
#include <string.h>
#include <vector>


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
LittleFS_Handler :: fs_status LittleFS_Handler :: saveFS_json(const char* path[], const char* data){

    Serial.println("--- JSON Saving ---");

    for(int i =0; i<strlen(path);i++){

        char str = path[i];
        int separator = strchr(str,' ');

    }

}
