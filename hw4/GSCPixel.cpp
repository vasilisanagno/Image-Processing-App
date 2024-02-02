#include "GSCPixel.hpp"
#include <iostream>
using namespace std;

GSCPixel::GSCPixel(const GSCPixel& p) {
    gray=p.gray;
}

GSCPixel::GSCPixel(unsigned char value) {
    this->gray=value;
}

unsigned char GSCPixel::getValue() {
    return this->gray;
}

void GSCPixel::setValue(unsigned char value) {
    this->gray=value;
}