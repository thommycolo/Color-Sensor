#ifndef TYPES_H
#define TYPES_H

#include<Arduino.h>

#pragma once

struct RGB_coef
{
    int realwhite;
    float r=1.0,g=1.0,b=1.0;
};
struct RGB
{
    int r=0,g=0,b=0;
    String color_name = "";
};



#endif