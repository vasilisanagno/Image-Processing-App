#include "GSCImage.hpp"

GSCImage::GSCImage() {
    this->setWidth(0);
    this->setHeight(0);
    this->setMaxLuminocity(0);
    this->gsc_image=nullptr;
}

GSCImage::GSCImage(const GSCImage& img) {
    this->height=img.getHeight();
    this->width=img.getWidth();
    this->max_luminocity=img.getMaxLuminocity();
    this->gsc_image = new GSCPixel*[img.getHeight()];

    for(int i=0; i<img.getHeight(); i++) {
        this->gsc_image[i] = new GSCPixel[img.getWidth()];
        for(int j=0; j<img.getWidth(); j++) {
            this->gsc_image[i][j].setValue(img.getGSCImage()[i][j].getValue());
        }
    }
}

GSCImage::~GSCImage() {

    for(int i=0; i<this->getHeight(); i++) {
        delete[] this->gsc_image[i];
    }

    delete[] this->gsc_image;
}

GSCImage::GSCImage(const RGBImage& grayscaled) {
    this->height=grayscaled.getHeight();
    this->width=grayscaled.getWidth();
    this->max_luminocity=grayscaled.getMaxLuminocity();
    this->gsc_image = new GSCPixel*[this->getHeight()];

    for(int i=0; i<this->getHeight(); i++) {
        this->gsc_image[i] = new GSCPixel[this->getWidth()];
        for(int j=0; j<this->getWidth(); j++) {
            this->gsc_image[i][j].setValue(grayscaled.getRGBImage()[i][j].getRed()*0.3 + grayscaled.getRGBImage()[i][j].getGreen()*0.59 + grayscaled.getRGBImage()[i][j].getBlue()*0.11);
        }
    }
}

GSCImage::GSCImage(istream& stream) {
    string word;
    int i=1, row_index=0, col_index=0;

    //knows that is grayscale the image and P2 in the beginning has read
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
            this->gsc_image = new GSCPixel*[this->getHeight()];

            for(int i=0; i<this->getHeight(); i++) {
                this->gsc_image[i] = new GSCPixel[this->getWidth()];
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
                this->gsc_image[row_index][col_index].setValue(stoi(word));
                col_index++;
            }
        }
        i++;
    }
}

GSCImage& GSCImage::operator=(const GSCImage& img) {
    this->height=img.getHeight();
    this->width=img.getWidth();
    this->max_luminocity=img.getMaxLuminocity();
    this->gsc_image = new GSCPixel*[img.getHeight()];

    for(int i=0; i<img.getHeight(); i++) {
        this->gsc_image[i] = new GSCPixel[img.getWidth()];
        for(int j=0; j<img.getWidth(); j++) {
            this->gsc_image[i][j].setValue(img.getGSCImage()[i][j].getValue());
        }
    }
    return *this;
}

void GSCImage::makeRightLeftTurns(int times) {
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

    while(count!=0) { //so left and right turns its the same thing but the opposite
        GSCImage gsc;
        gsc.setHeight(this->getWidth());
        gsc.setWidth(this->getHeight());
        gsc.setMaxLuminocity(this->getMaxLuminocity());
        gsc.gsc_image=new GSCPixel*[gsc.getHeight()];
        for(int i=0; i<gsc.getHeight(); i++) {
            gsc.gsc_image[i] = new GSCPixel[gsc.getWidth()];
            for(int j=0,k=0; j<gsc.getWidth(); j++,k++) {
                gsc.gsc_image[i][j].setValue(this->getGSCImage()[this->getHeight()-1-k][i].getValue());
            }
        }
        for(int i=0; i<this->getHeight(); i++) {
            delete[] this->gsc_image[i];
        }
        delete[] this->gsc_image;
        *this=gsc;
        count--;
    }
}

Image& GSCImage::operator+=(int times) {

    if(abs(times)%4==0) { //if times is divided with 4 exactly there is no need to do any action
        return *this;
    }
    this->makeRightLeftTurns(times);

    return *this;
}

Image& GSCImage::operator*=(double factor) {
    GSCImage gsc;
    GSCPixel p11,p12,p21,p22;
    int r1,r2,c1,c2;
    unsigned char result;

    gsc.setHeight(factor*this->getHeight());
    gsc.setWidth(factor*this->getWidth());
    gsc.setMaxLuminocity(this->getMaxLuminocity());
    gsc.gsc_image = new GSCPixel*[gsc.getHeight()];

    for(int i=0; i<gsc.getHeight(); i++) {
        gsc.gsc_image[i] = new GSCPixel[gsc.getWidth()];
        for(int j=0; j<gsc.getWidth(); j++) {
            r1 = min((int)floor((double)i/factor),this->getHeight()-1);
            r2 = min((int)ceil((double)i/factor),this->getHeight()-1);
            c1 = min((int)floor((double)j/factor),this->getWidth()-1);
            c2 = min((int)ceil((double)j/factor),this->getWidth()-1);
            
            p11=(GSCPixel&)this->getPixel(r1,c1);
            p12=(GSCPixel&)this->getPixel(r1,c2);
            p21=(GSCPixel&)this->getPixel(r2,c1);
            p22=(GSCPixel&)this->getPixel(r2,c2);

            result = (p11.getValue()+p12.getValue()+p21.getValue()+p22.getValue())/4;
            gsc.gsc_image[i][j].setValue(result);
        }
    }
    for(int i=0; i<this->getHeight(); i++) {
        delete[] this->gsc_image[i];
    }
    delete[] this->gsc_image;
    *this=gsc;
    return *this;
}

Image& GSCImage::operator!() {

    for(int i=0; i<this->getHeight(); i++) {
        for(int j=0; j<this->getWidth(); j++) {
            this->gsc_image[i][j].setValue(this->max_luminocity - this->gsc_image[i][j].getValue());
        }
    }
    return *this;
}

void GSCImage::clip(RGBPixel** rgb, int c, int d, int e, int row, int col) {
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
    rgb[row][col].setRed(r);
    rgb[row][col].setGreen(g);
    rgb[row][col].setBlue(b);
}

Image& GSCImage::operator~() {
    double* array_of_probability = new double[this->getMaxLuminocity()+1];
    int* luminocity = new int[this->getMaxLuminocity()+1];
    int* histogram = new int[this->getMaxLuminocity()+1];

    //initialization of histogram
    for(int i=0; i<this->getMaxLuminocity()+1; i++) {
        histogram[i]=0;
    }

    //counts histogram
    for(int i=0; i<this->getHeight(); i++) {
        for(int j=0; j<this->getWidth(); j++) {
            histogram[this->getGSCImage()[i][j].getValue()]++;
        }
    }

    //equalization of histogram
    for(int i=0; i<this->getMaxLuminocity()+1; i++) {
        array_of_probability[i]=(double)histogram[i]/(double)(this->getHeight()*this->getWidth());
        if(i==0) {
            luminocity[i]=255*array_of_probability[i];
            continue;
        }
        array_of_probability[i]+=array_of_probability[i-1];
        luminocity[i]=255*array_of_probability[i];
    }

    //puts the new values in the pixels
    for(int i=0; i<this->getHeight(); i++) {
        for(int j=0; j<this->getWidth(); j++) {
            this->getGSCImage()[i][j].setValue(luminocity[(int)this->getGSCImage()[i][j].getValue()]);
        }
    }

    delete[] array_of_probability;
    delete[] luminocity;
    delete[] histogram;
    return *this;
}

Pixel& GSCImage::getPixel(int row,int col) const {

    return this->gsc_image[row][col];
}

Image& GSCImage::operator*() {
    GSCPixel temp;

    for(int i=0; i<this->getHeight(); i++) {
        for(int j=0; j<this->getWidth()/2; j++) {
            temp=(GSCPixel&)this->getPixel(i,j);
            (GSCPixel&)this->getPixel(i,j)=(GSCPixel&)this->getPixel(i,this->getWidth()-1-j);
            (GSCPixel&)this->getPixel(i,this->getWidth()-1-j)=temp;
        }
    }
    return *this;
}

ostream& operator<<(ostream& out, Image& image) {

    if(dynamic_cast<GSCImage*>(&image)!=nullptr) { //this code refers to grayscale image and write it to the destination file
        GSCImage* grayscale_image = dynamic_cast<GSCImage*>(&image);
        out << "P2" << endl;
        out << grayscale_image->getWidth() << " " << grayscale_image->getHeight() << " " << grayscale_image->getMaxLuminocity() << endl;
        for(int i=0; i<grayscale_image->getHeight(); i++) {
            for(int j=0; j<grayscale_image->getWidth(); j++) {
                out << (int)grayscale_image->getGSCImage()[i][j].getValue() << endl;
            }
        }
    }
    else { //this code refers to rgb image and write it to the destination file
        RGBImage* rgb_image = dynamic_cast<RGBImage*>(&image);
        out << "P3" << endl;
        out << rgb_image->getWidth() << " " << rgb_image->getHeight() << " " << rgb_image->getMaxLuminocity() << endl;
        for(int i=0; i<rgb_image->getHeight(); i++) {
            for(int j=0; j<rgb_image->getWidth(); j++) {
                out << (int)rgb_image->getRGBImage()[i][j].getRed() << " ";
                out << (int)rgb_image->getRGBImage()[i][j].getGreen() << " ";
                out << (int)rgb_image->getRGBImage()[i][j].getBlue() << endl;
            }
        }
    }
    return out;
}
