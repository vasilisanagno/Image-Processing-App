#ifndef _TOKEN_HPP_
#define _TOKEN_HPP_
#include <string>
#include <iostream>
#include "Image.hpp"
#include "GSCImage.hpp"
using namespace std;

class Token {
    private :
        string name;
        Image* ptr;
    public :
        Token(const string& = "", Image* = nullptr); //constructor
        Token(const Token& t); //copy constructor
        ~Token(); //destructor
        string getName() const; //returns the name of the image
        Image* getPtr() const; //returns a pointer to the image
        void setName(const string& ); //sets a name in the image
        void setPtr(Image* ptr); //sets the pointer of the image
};
#endif