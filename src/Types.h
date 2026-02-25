#ifndef TYPES_H
#define TYPES_H

#pragma once

struct RGB_coef
{
    int realwhite;
    float r=1.0,g=1.0,b=1.0;
};
struct RGB
{
    int r,g,b;
    std :: string color_name ;
};



#endif