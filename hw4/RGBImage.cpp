#include "RGBImage.hpp"

RGBImage::RGBImage() {
    this->setWidth(0);
    this->setHeight(0);
    this->setMaxLuminocity(0);
    this->rgb_image=nullptr;
}

RGBImage::RGBImage(const RGBImage& img) {
    this->height=img.getHeight();
    this->width=img.getWidth();
    this->max_luminocity=img.getMaxLuminocity();
    this->rgb_image = new RGBPixel*[img.getHeight()];

    for(int i=0; i<img.getHeight(); i++) {
        this->rgb_image[i] = new RGBPixel[img.getWidth()];
        for(int j=0; j<img.getWidth(); j++) {
            this->rgb_image[i][j].setRed(img.getRGBImage()[i][j].getRed());
            this->rgb_image[i][j].setGreen(img.getRGBImage()[i][j].getGreen());
            this->rgb_image[i][j].setBlue(img.getRGBImage()[i][j].getBlue());
        }
    }
}

RGBImage::~RGBImage() {
    for(int i=0; i<this->getHeight(); i++) {
        delete[] this->rgb_image[i];
    }

    delete[] this->rgb_image;
}

RGBImage::RGBImage(istream& stream) {
    string word;
    int i=1, row_index=0, col_index=0;

    //knows that is rgb the image and P3 in the beginning has read
    while(!stream.eof()) {
        if(i==1) {
            stream >> word;
            this->width=stoi(word);
        } else if(i==2) {
            stream >> word;
            this->height=stoi(word);
        } else if(i==3) {
            stream >> word;
            this->max_luminocity=stoi(word);
            this->rgb_image = new RGBPixel*[this->getHeight()];

            for(int i=0; i<this->getHeight(); i++) {
                this->rgb_image[i] = new RGBPixel[this->getWidth()];
            }
        } else {
            if(row_index==this->height) {
                break;
            }
            if(col_index==this->width) {
                row_index++;
                col_index=0;
            }
            else {
                stream >> word;
                this->rgb_image[row_index][col_index].setRed(stoi(word));
                stream >> word;
                this->rgb_image[row_index][col_index].setGreen(stoi(word));
                stream >> word;
                this->rgb_image[row_index][col_index].setBlue(stoi(word));
                col_index++;
            }
        }
        i++;
    }
}

RGBImage& RGBImage::operator=(const RGBImage& img) {
    this->height=img.getHeight();
    this->width=img.getWidth();
    this->max_luminocity=img.getMaxLuminocity();
    this->rgb_image = new RGBPixel*[img.getHeight()];

    for(int i=0; i<img.getHeight(); i++) {
        this->rgb_image[i] = new RGBPixel[img.getWidth()];
        for(int j=0; j<img.getWidth(); j++) {
            this->rgb_image[i][j].setRed(img.getRGBImage()[i][j].getRed());
            this->rgb_image[i][j].setGreen(img.getRGBImage()[i][j].getGreen());
            this->rgb_image[i][j].setBlue(img.getRGBImage()[i][j].getBlue());
        }
    }

    return *this;
}

void RGBImage::makeRightLeftTurns(int times) {
    int count;

    if(times>0) {
        count=times%4;
    }
    else {
        count=abs(times)%4;
        if(count==1) { //count=1 for left turn is 3 right turns
            count=3;
        } else if(count==3) { //3 left turns are 1 right turn
            count=1;
        }
    }

    while(count!=0) { //so left and right turns they are the same thing but the opposite between them except from 2 right and 2 left turns that they have the same result
        RGBImage rgb;
        rgb.setHeight(this->getWidth());
        rgb.setWidth(this->getHeight());
        rgb.setMaxLuminocity(this->getMaxLuminocity());
        rgb.rgb_image=new RGBPixel*[rgb.getHeight()];
        for(int i=0; i<rgb.getHeight(); i++) {
            rgb.rgb_image[i] = new RGBPixel[rgb.getWidth()];
            for(int j=0,k=0; j<rgb.getWidth(); j++,k++) {
                rgb.rgb_image[i][j].setRed(this->getRGBImage()[this->getHeight()-1-k][i].getRed());
                rgb.rgb_image[i][j].setGreen(this->getRGBImage()[this->getHeight()-1-k][i].getGreen());
                rgb.rgb_image[i][j].setBlue(this->getRGBImage()[this->getHeight()-1-k][i].getBlue());
            }
        }
        for(int i=0; i<this->getHeight(); i++) {
            delete[] this->rgb_image[i];
        }
        delete[] this->rgb_image;
        *this=rgb;
        count--;
    }
}

Image& RGBImage::operator+=(int times) {
    
    if(abs(times)%4==0) { //if times is divided with 4 exactly there is no need to do any action
        return *this;
    }
    this->makeRightLeftTurns(times);
    
    return *this;
}

Image& RGBImage::operator*=(double factor) {
    RGBImage rgb;
    RGBPixel p11,p12,p21,p22;
    int r1,r2,c1,c2;
    unsigned char result_r, result_g, result_b;

    rgb.setHeight(factor*this->getHeight());
    rgb.setWidth(factor*this->getWidth());
    rgb.setMaxLuminocity(this->getMaxLuminocity());
    rgb.rgb_image = new RGBPixel*[rgb.getHeight()];

    for(int i=0; i<rgb.getHeight(); i++) {
        rgb.rgb_image[i] = new RGBPixel[rgb.getWidth()];
        for(int j=0; j<rgb.getWidth(); j++) {
            r1 = min((int)floor((double)i/factor),this->getHeight()-1);
            r2 = min((int)ceil((double)i/factor),this->getHeight()-1);
            c1 = min((int)floor((double)j/factor),this->getWidth()-1);
            c2 = min((int)ceil((double)j/factor),this->getWidth()-1);
            
            p11=(RGBPixel&)this->getPixel(r1,c1);
            p12=(RGBPixel&)this->getPixel(r1,c2);
            p21=(RGBPixel&)this->getPixel(r2,c1);
            p22=(RGBPixel&)this->getPixel(r2,c2);

            result_r = (p11.getRed()+p12.getRed()+p21.getRed()+p22.getRed())/4;
            result_g = (p11.getGreen()+p12.getGreen()+p21.getGreen()+p22.getGreen())/4;
            result_b = (p11.getBlue()+p12.getBlue()+p21.getBlue()+p22.getBlue())/4;
            rgb.rgb_image[i][j].setRed(result_r);
            rgb.rgb_image[i][j].setGreen(result_g);
            rgb.rgb_image[i][j].setBlue(result_b);
        }
    }
    for(int i=0; i<this->getHeight(); i++) {
        delete[] this->rgb_image[i];
    }
    delete[] this->rgb_image;
    *this=rgb;
    return *this;
}

Image& RGBImage::operator!() {
    
    for(int i=0; i<this->getHeight(); i++) {
        for(int j=0; j<this->getWidth(); j++) {
            this->rgb_image[i][j].setRed( this->max_luminocity - this->rgb_image[i][j].getRed());
            this->rgb_image[i][j].setGreen( this->max_luminocity - this->rgb_image[i][j].getGreen());
            this->rgb_image[i][j].setBlue( this->max_luminocity - this->rgb_image[i][j].getBlue());
        }
    }
    return *this;
}

void RGBImage::clip(int c, int d, int e, int row, int col) {
    int r, g, b;

    r=(298*c+409*e+128)>>8;
    if(r<0) {
        r=0;
    } else if(r>255) {
        r=255;
    }
    g=(298*c-100*d-208*e+128)>>8;
    if(g<0) {
        g=0;
    } else if(g>255) {
        g=255;
    }
    b=(298*c+516*d+128)>>8;
    if(b<0) {
        b=0;
    } else if(b>255) {
        b=255;
    }
    this->getRGBImage()[row][col].setRed(r);
    this->getRGBImage()[row][col].setGreen(g);
    this->getRGBImage()[row][col].setBlue(b);
}

Image& RGBImage::operator~() {
    int yuv_max_lumi = 235;
    double* array_of_probability = new double[yuv_max_lumi+1];
    int* luminocity = new int[yuv_max_lumi+1];
    int* histogram = new int[yuv_max_lumi+1];
    int c,d,e;

    //initialization of histogram
    for(int i=0; i<yuv_max_lumi+1; i++) {
        histogram[i]=0;
    }

    //rgb to yuv and counts histogram
    for(int i=0; i<this->getHeight(); i++) {
        for(int j=0; j<this->getWidth(); j++) {
            this->getRGBImage()[i][j].setRed(((66*(int)this->getRGBImage()[i][j].getRed()+129*(int)this->getRGBImage()[i][j].getGreen()+25*(int)this->getRGBImage()[i][j].getBlue()+128)>>8)+16);
            this->getRGBImage()[i][j].setGreen(((-38*(int)this->getRGBImage()[i][j].getRed()-74*(int)this->getRGBImage()[i][j].getGreen()+112*(int)this->getRGBImage()[i][j].getBlue()+128)>>8)+128);
            this->getRGBImage()[i][j].setBlue(((112*(int)this->getRGBImage()[i][j].getRed()-94*(int)this->getRGBImage()[i][j].getGreen()-18*(int)this->getRGBImage()[i][j].getBlue()+128)>>8)+128);
            histogram[(int)this->getRGBImage()[i][j].getRed()]++;
        }
    }

    //equalize of histogram
    for(int i=0; i<yuv_max_lumi+1; i++) {
        array_of_probability[i]=(double)histogram[i]/(double)(this->getHeight()*this->getWidth());
        if(i==0) {
            luminocity[i]=yuv_max_lumi*array_of_probability[i];
            continue;
        }
        array_of_probability[i]+=array_of_probability[i-1];
        luminocity[i]=yuv_max_lumi*array_of_probability[i];
    }

    //puts the new values in the pixels
    for(int i=0; i<this->getHeight(); i++) {
        for(int j=0; j<this->getWidth(); j++) {
            this->getRGBImage()[i][j].setRed(luminocity[(int)this->getRGBImage()[i][j].getRed()]); 
        }
    }

    //rgb to yuv
    for(int i=0; i<this->getHeight(); i++) {
        for(int j=0; j<this->getWidth(); j++) {
            c=(int)this->getRGBImage()[i][j].getRed()-16;
            d=(int)this->getRGBImage()[i][j].getGreen()-128;
            e=(int)this->getRGBImage()[i][j].getBlue()-128;
            this->clip(c,d,e,i,j);
        }
    }

    delete[] array_of_probability;
    delete[] luminocity;
    delete[] histogram;
    return *this;
}

Pixel& RGBImage::getPixel(int row,int col) const {

    return this->rgb_image[row][col];
}

Image& RGBImage::operator*() {
    RGBPixel temp;

    for(int i=0; i<this->getHeight(); i++) {
        for(int j=0; j<this->getWidth()/2; j++) {
            temp=(RGBPixel&)this->getPixel(i,j);
            (RGBPixel&)this->getPixel(i,j)=(RGBPixel&)this->getPixel(i,this->getWidth()-1-j);
            (RGBPixel&)this->getPixel(i,this->getWidth()-1-j)=temp;
        }
    }
    return *this;
}