
#ifndef GEOMETRIC_H_
#define GEOMETRIC_H_

#include "define.h"

#define K_EPXILON_2  0.01
#define K_EPXILON_3  0.001
#define K_EPXILON_4  0.0001
#define K_EPXILON_5  0.00001
#define K_EPXILON_6  0.000001

class GeoFormat
{
public:
    GeoFormat() 
    { 
        rect_ = { 0, 0, 0, 0 };
        color_ = { 255, 255, 255, 0 };
    }

    GeoFormat(SDL_Rect rt, const SDL_Color& color)
    {
        rect_ = rt;
        color_ = color;
    }

    SDL_Rect rect_;
    SDL_Color color_;
};


class Gemometric
{
public:
   static void RenderRectange(const GeoFormat& geo_data, SDL_Renderer* screen);
   static void RenderOutline(const GeoFormat& geo_data,  SDL_Renderer* screen);
};


#endif