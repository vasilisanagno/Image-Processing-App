#include "Token.hpp"

Token::Token(const string& name,Image* ptr) {
    this->name=name;
    this->ptr=ptr;
}

Token::Token(const Token& t) {
    this->name=t.name;
    if(dynamic_cast<GSCImage*>(t.getPtr())!=nullptr) { //calls the copy constructor or of GSCImage or of RGBImage
        this->ptr = new GSCImage(*dynamic_cast<GSCImage*>(t.getPtr()));
    }
    else {
        this->ptr = new RGBImage(*dynamic_cast<RGBImage*>(t.getPtr()));
    }
}

Token::~Token() {
    delete this->ptr;
}

string Token::getName() const {
    return this->name;
}

Image* Token::getPtr() const {
    return this->ptr;
}

void Token::setName(const string& name) {
    this->name=name;
}

void Token::setPtr(Image* ptr) {
    this->ptr=ptr;
}