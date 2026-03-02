//ColorSensor implementation 

#include "SensorHandler.h"
#include "DisplayHandler.h"
#include <Arduino.h>
#include <Adafruit_TCS34725.h>
#include "Types.h"
#include "TableHandler.h"

#define COLOR_CALIBRATION_CYCLES 50
#define GET_COLOR_CYCLES 10

using namespace std;

void starting_calibration_print(DisplayHandler display){
    
    delay(2000);
    Serial.println("Starting calibration process!");
    Serial.println("point your sensor to a white surface");
    display.print("Starting calibration process!","point your sensor to a white surface");

    delay(5000);        
    Serial.println("Calibration starting in:");
    display.print("Calibration starting in:");
      
    Serial.println("5");
    display.print("5");
    delay(1000);

    Serial.println("4");
    display.print("4");
    delay(1000);

    Serial.println("3");
    display.print("3");
    delay(1000);

    Serial.println("2");
    display.print("2");
    delay(1000);

    Serial.println("1");
    display.print("1");
    delay(1000);

    Serial.println("Calibrating!!");
    display.print("Calibrating!!");
}

void SensorHandler :: begin(){
    display.begin();
    while (!tcs.begin()) {
            display.print("Sensor not found");
            delay(100);
    }
}

/***
 * This function allow the sensor calibration.
 * it does a loop of L cycles in order to have a precise white reading
 */
const bool SensorHandler::Calibration()
{
    starting_calibration_print(display);

    RGB_coef coef;
    
    
    // temporary variable for all the 3 color
    uint32_t tot_r=0;
    uint32_t tot_g=0;
    uint32_t tot_b=0;
    uint16_t tmp_r,tmp_g,tmp_b,tmp_c;

    for(int i=0; i<COLOR_CALIBRATION_CYCLES ; i++){
        tcs.enable();
        delay(10);
        tcs.getRawData(&tmp_r,&tmp_g,&tmp_b,&tmp_c);
        delay(10);
        tcs.disable();
        tot_r += tmp_r;
        tot_g += tmp_g;
        tot_b += tmp_b;   
        Serial.print(tmp_r);Serial.print(tmp_g);Serial.println(tmp_b);
    }   
    tot_r /= COLOR_CALIBRATION_CYCLES;
    tot_g /= COLOR_CALIBRATION_CYCLES;
    tot_b /= COLOR_CALIBRATION_CYCLES;    

    //evaluating the real white
    Serial.print("Max value:");Serial.print(max(tot_r,max(tot_g,tot_b)));
    coef.realwhite = max(tot_r,max(tot_g,tot_b)); //real_white saving


    
    coef.r = (float)coef.realwhite / (float)tot_r;
    coef.g = (float)coef.realwhite / (float)tot_g;
    coef.b = (float)coef.realwhite / (float)tot_b;

    Serial.print("\n\n");
    Serial.print("color adjustation: ");Serial.print(coef.r);Serial.print(coef.g);Serial.println(coef.b);
    Serial.print("\n\n"); 
    
    Serial.println("Calibration Done");
    display.print("Calibration Done");
    
    SensorHandler ::rgb_coef = coef;
    return true;
}




const RGB SensorHandler::GetColor(){
    uint32_t r=0, g=0, b=0, c=0;
    RGB rgb;
    
    display.print("getting color");
    Serial.print("getting color");
    delay(100);
    for(int i=0; i<GET_COLOR_CYCLES ; i++){
    tcs.enable();
        delay(10);
        uint16_t r_tmp,g_tmp,b_tmp,c_tmp;
        tcs.getRawData(&r_tmp,&g_tmp,&b_tmp,&c_tmp);
        r += r_tmp;
        g += g_tmp;
        b += b_tmp;
        c += c_tmp;
        delay(10);
        tcs.disable();
        Serial.print("R: ");Serial.print(r);Serial.print(" G: ");Serial.print(g);Serial.print(" B: ");Serial.print(b);Serial.print(" C: ");Serial.println(c);
    }
    Serial.print("\n\n\n"); 
    //adding 0.5 in order to permform a round up
    rgb.r = (int)((((float)r / (float)GET_COLOR_CYCLES) * rgb_coef.r / (float)rgb_coef.realwhite * 255.0) + 0.5); 
    rgb.g = (int)((((float)g / (float)GET_COLOR_CYCLES) * rgb_coef.g / (float)rgb_coef.realwhite * 255.0) + 0.5);
    rgb.b = (int)((((float)b / (float)GET_COLOR_CYCLES) * rgb_coef.b / (float)rgb_coef.realwhite * 255.0) + 0.5);
    if(rgb.r>255)
        rgb.r=255;
    if(rgb.g>255)
        rgb.g=255;
    if(rgb.b>255)
        rgb.b=255;


    TableHandler colorTB;
    rgb = colorTB.getColor(rgb);

    Serial.println("COLORI CALIBRATI:");
    Serial.print("R: ");Serial.print(rgb.r);Serial.print(" G: ");Serial.print(rgb.g);Serial.print(" B: ");Serial.print(rgb.b);
    display.print("COLORE: " + rgb.color_name , "R: " + (String)rgb.r + " G: " + (String)rgb.g + " B: " + (String)rgb.b);
    Serial.print("\n\n\n");
    return rgb;

}
