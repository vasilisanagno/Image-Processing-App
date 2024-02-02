#ifndef _IMAGE_HPP_
#define _IMAGE_HPP_
#include "Pixel.hpp"
#include <cmath>
#include <iostream>
using namespace std;

class Image {
    protected :
        int width;
        int height;
        int max_luminocity;
    public :
        int getWidth() const { return width; } //returns the width of the image
        int getHeight() const { return height; } //returns the height of the image
        int getMaxLuminocity() const { return max_luminocity; } //returns the max luminocity of the image
        void setWidth(int width) { this->width=width; } //sets the width of the image
        void setHeight(int height) { this->height=height; } //sets the height of the image
        void setMaxLuminocity(int lum) { this->max_luminocity=lum; } //sets the max luminocity of the image
        Image() = default; //default constructor
        virtual ~Image() {} //destructor

        virtual Image& operator+=(int times) = 0; //abstract function for overloading of operator +=
        virtual Image& operator*=(double factor) = 0; //abstract function for overloading of operator *=
        virtual Image& operator!() = 0; //abstract function for overloading of operator !
        virtual Image& operator~() = 0; //abstract function for overloading of operator ~
        virtual Image& operator*() = 0; //abstract function for overloading of operator *
        virtual Pixel& getPixel(int row,int col) const = 0; //abstract function returns the pixel in specific row and column from the image
        friend ostream& operator<<(ostream& out, Image& image); //friend function for overloading of operator <<
};
#endif
