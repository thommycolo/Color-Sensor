//color_sensor implementation 

#include "color_sensor.h"
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_TCS34725.h>
#include "Types.h"


using namespace std;

void starting_calibration_print(Adafruit_SSD1306 &display){
    display.clearDisplay();       
    display.setCursor(0, 0);  

    delay(2000);
    Serial.println("Starting calibration process!");
    Serial.println("point your sensor to a white surface");
    display.println("Starting calibration process!");
    display.println("point your sensor to a white surface");
    delay(5000);    
    display.clearDisplay();       
    display.setCursor(0, 0);    
    Serial.println("Calibration starting in:");
    display.println("Calibration starting in:");
    display.clearDisplay();       
    display.setCursor(0, 0);    
    Serial.println("5");
    display.println("5");
    display.clearDisplay();       
    display.setCursor(0, 0);
    Serial.println("4");
    display.println("4");
    display.clearDisplay();       
    display.setCursor(0, 0);    
    Serial.println("3");
    display.println("3");
    display.clearDisplay();       
    display.setCursor(0, 0);    
    Serial.println("2");
    display.println("2");
    display.clearDisplay();       
    display.setCursor(0, 0);    
    Serial.println("1");
    display.println("1");
    display.clearDisplay();       
    display.setCursor(0, 0);    
    Serial.println("Calibrating!!");
    display.println("Calibrating!!");
}

/***
 * This function allow the sensor calibration.
 * it does a loop of L cycles in order to have a precise white reading
 */
const RGB_coef SensorHandler::Calibration()
{
    starting_calibration_print(display);

    RGB_coef coef;
    int L =50; //number of cycles for the sampling
    
    
    // temporary variable for all the 3 color
    uint32_t tot_r=0;
    uint32_t tot_g=0;
    uint32_t tot_b=0;
    uint16_t tmp_r,tmp_g,tmp_b,tmp_c;

    for(int i=0; i<L ; i++){
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
    tot_r /= L;
    tot_g /= L;
    tot_b /= L;    

    //evaluating the real white
    Serial.print("Max value:");Serial.print(max(tot_r,max(tot_g,tot_b)));
    coef.realwhite = max(tot_r,max(tot_g,tot_b)); //real_white saving


    
    coef.r = (float)coef.realwhite / (float)tot_r;
    coef.g = (float)coef.realwhite / (float)tot_g;
    coef.b = (float)coef.realwhite / (float)tot_b;

    Serial.print("\n\n");
    Serial.print("color adjustation: ");Serial.print(coef.r);Serial.print(coef.g);Serial.println(coef.b);
    Serial.print("\n\n");   
    display.clearDisplay();       
    display.setCursor(0, 0);
    Serial.println("Calibration Done");
    display.println("Calibration Done");

    return coef;
}




const RGB SensorHandler::GetColor(RGB_coef &rgb_coef){
    uint32_t r=0, g=0, b=0, c=0;
    RGB rgb;
    

    for(int i=0; i<10 ; i++){
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
    rgb.r = (int)((((float)r / 10.0) * rgb_coef.r / (float)rgb_coef.realwhite * 255.0) + 0.5);
    rgb.g = (int)((((float)g / 10.0) * rgb_coef.g / (float)rgb_coef.realwhite * 255.0) + 0.5);
    rgb.b = (int)((((float)b / 10.0) * rgb_coef.b / (float)rgb_coef.realwhite * 255.0) + 0.5);
    if(rgb_coef.r>255)
        rgb_coef.r=255;
    if(rgb_coef.g>255)
        rgb_coef.g=255;
    if(rgb_coef.b>255)
        rgb_coef.b=255;

    Serial.println("COLORI CALIBRATI:");
    Serial.print("R: ");Serial.print(rgb_coef.r);Serial.print(" G: ");Serial.print(rgb_coef.g);Serial.print(" B: ");Serial.print(rgb_coef.b);
    Serial.print("\n\n\n");
    return rgb;

}
