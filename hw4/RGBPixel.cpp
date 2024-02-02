#include "RGBPixel.hpp"
#include <iostream>
using namespace std;

RGBPixel::RGBPixel(const RGBPixel& p) {
    red=p.red;
    green=p.green;
    blue=p.blue;
}

RGBPixel::RGBPixel(unsigned char r,unsigned char g,unsigned char b) {
    this->red=r;
    this->green=g;
    this->blue=b;
}

unsigned char RGBPixel::getRed() const {
    return this->red;
}

unsigned char RGBPixel::getGreen() const {
    return this->green;
}

unsigned char RGBPixel::getBlue() const {
    return this->blue;
}

void RGBPixel::setRed(unsigned char r) {
    this->red=r;
}

void RGBPixel::setGreen(unsigned char g) {
    this->green=g;
}

void RGBPixel::setBlue(unsigned char b) {
    this->blue=b;
}
