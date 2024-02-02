#ifndef _GSCIMAGE_HPP_
#define _GSCIMAGE_HPP_
#include "GSCPixel.hpp"
#include "RGBImage.hpp"

class GSCImage : public Image {
    private :
        GSCPixel** gsc_image;
    public :
        GSCImage(); //constructor
        GSCImage(const GSCImage& img); //copy constructor
        ~GSCImage(); //destructor
        GSCImage(const RGBImage& grayscaled); //constructor that takes a rgb image and converts it to a grayscale image
        GSCImage(istream& stream); //constructor that takes an input stream/file and puts the information of the image into the class
        GSCImage& operator=(const GSCImage& img); //function for overloading of operator =
        
        virtual Image& operator+=(int ) override; //function for overloading of operator +=
        virtual Image& operator*=(double factor) override; //function for overloading of operator *=
        virtual Image& operator!() override; //function for overloading of operator !
        virtual Image& operator~() override; //function for overloading of operator ~
        virtual Image& operator*() override; //function for overloading of operator *

        virtual Pixel& getPixel(int row,int col) const override; //returns the pixel in specific row and column from the image
        GSCPixel** getGSCImage() const { return this->gsc_image; } //returns the array of the image with the pixels
        void makeRightLeftTurns(int times); //function that helps in rotation of the image right or left
        void clip(RGBPixel** rgb, int c, int d, int e, int row, int col); //function that helps for the convertion from yuv to rgb
        friend ostream& operator<<(ostream& out, Image& image); //friend function for overloading of operator <<
};
#endif
