#ifndef _RGBPIXEL_HPP_
#define _RGBPIXEL_HPP_
#include "Pixel.hpp"

class RGBPixel : public Pixel {
    private :
        unsigned char red;
        unsigned char green;
        unsigned char blue;
    public :
        RGBPixel() = default; //default constructor
        RGBPixel(const RGBPixel& p); //copy constructor
        RGBPixel(unsigned char r,unsigned char g,unsigned char b); //constructor with initialization of values red,green,blue
        unsigned char getRed() const; //returns the value red
        unsigned char getGreen() const; //returns the value green
        unsigned char getBlue() const; //returns the value blue
        void setRed(unsigned char r); //sets the value red
        void setGreen(unsigned char g); //sets the value green
        void setBlue(unsigned char b); //sets the value blue
};
#endif