#ifndef _GSCPIXEL_HPP_
#define _GSCPIXEL_HPP_
#include "Pixel.hpp"

class GSCPixel : public Pixel {
    private :
        unsigned char gray;
    public :
        GSCPixel() = default; //default constructor
        GSCPixel(const GSCPixel& p); //copy constructor
        GSCPixel(unsigned char value); //constructor with initialization of gray value
        unsigned char getValue(); //returns the value gray
        void setValue(unsigned char value); //sets the value gray
};
#endif