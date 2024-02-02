#ifndef _RGBIMAGE_HPP_
#define _RGBIMAGE_HPP_
#include "RGBPixel.hpp"
#include "Image.hpp"

class RGBImage : public Image {
    private :
        RGBPixel** rgb_image;
    public :
        RGBImage(); //constructor
        RGBImage(const RGBImage& img); //copy constructor
        ~RGBImage(); //destructor
        RGBImage(istream& stream); //constructor that takes an input stream/file and puts the information of the image into the class
        RGBImage& operator=(const RGBImage& img); //function for overloading of operator =
        
        virtual Image& operator+=(int ) override; //function for overloading of operator +=
        virtual Image& operator*=(double factor) override; //function for overloading of operator *=
        virtual Image& operator!() override; //function for overloading of operator !
        virtual Image& operator~() override; //function for overloading of operator ~
        virtual Image& operator*() override; //function for overloading of operator *

        virtual Pixel& getPixel(int row,int col) const override; //returns the pixel in specific row and column from the image
        RGBPixel** getRGBImage() const { return this->rgb_image; } //returns the array of the image with the pixels
        void makeRightLeftTurns(int times); //function that helps in rotation of the image right or left
        void clip(int c, int d, int e, int row, int col); //function that helps for the convertion from yuv to rgb
        friend ostream& operator<<(ostream& out, Image& image); //friend function for overloading of operator <<
};
#endif