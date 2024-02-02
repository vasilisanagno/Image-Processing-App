#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "Token.hpp"
#include "GSCImage.hpp"
#include "RGBImage.hpp"
using namespace std;

int countWords(const string& str,const char delimeter) { //count the words of the command that was given
    int countingWords=0;

    for(size_t i=0; i<str.length(); i++) {
        if(str[i]==delimeter) {
            if(i!=0&&str[i-1]!=delimeter) {
                countingWords++;
            }
        }
        if(i==str.length()-1&&str[i]!=delimeter) {
            countingWords++;
        }
    }

    return countingWords;
}

void split(const string& str,const char delimeter,string* words) { //split a string into substrings and put them into an array of strings
    string temp;
    int index=0;

    for(size_t i=0; i<str.length(); i++) {
        if(str[i]!=delimeter) {
            temp=temp+str[i];
        }
        else {
            if(i!=0&&str[i-1]!=delimeter) {
                words[index]=temp;
                temp.clear();
                index++;
            }
        }
        if(i==str.length()-1&&str[i]!=delimeter) {
            words[index]=temp;
            temp.clear();
        }
    }
}

Image* readNetpbmImage(const char* filename) { //read data from a .pgm or .ppm files
    ifstream f(filename);
    if(!f.is_open()) {
        cout << "[ERROR] Unable to open " << filename << endl;
    }
    Image* img_ptr = nullptr;
    string type;

    if(f.good() && !f.eof())
        f >> type;
    if(!type.compare("P3")) {
        img_ptr = new RGBImage(f);
    } else if(!type.compare("P2")) {
        img_ptr = new GSCImage(f);
    }
    else if(f.is_open()) {
        cout << "[ERROR] Invalid file format" << endl;
    }

    return img_ptr;
}

list<Token>::iterator checkToken(list<Token>& list_of_images,string token) { //check token if there is inside the list
    list<Token>::iterator it;

    for(it=list_of_images.begin(); it!=list_of_images.end(); it++) {
        if(it->getName().compare(token)==0) {
            break;
        }
    }
    if(it==list_of_images.end()) {
        cout << "[ERROR] Token " << token << " not found!" << endl;
    }
    return it;
}

int main() {
    string choice;
    string* words;
    Image* img;
    list<Token> list_of_images;
    int counting_words, error_check=0;
    list<Token>::iterator it;

    while(true) {
        getline(cin,choice);

        counting_words=countWords(choice,' ');
        if(counting_words==0) {
            continue;
        }
        words = new string[counting_words];
        split(choice,' ',words);

        //checks become with the same way as the first which is the option 'i'
        if(words[0].compare("i")==0) {
            if(counting_words!=4||words[2].compare("as")!=0||words[3][0]!='$'||words[3].length()==1) { //ckecks if the number of the words in the command is correct and contains the keyword "as" and token starts with '$' and it is not only the '$' the name of the token
                cout << "\n-- Invalid command! --" << endl;
                delete[] words;
                continue;
            }

            img = readNetpbmImage(words[1].c_str());
            if(img==nullptr) {
                delete[] words;
                continue;
            }

            for(it=list_of_images.begin(); it!=list_of_images.end(); it++) {
                if(it->getName().compare(words[3])==0) {
                    error_check=1;
                    break;
                }
            }

            if(error_check==1) {
                cout << "[ERROR] Token " << words[3] << " exists" << endl;
                error_check=0;
                delete img;
                delete[] words;
                continue;
            }
            
            list_of_images.push_back(Token(words[3],img));
            
            cout << "[OK] Import " << words[3] << endl;
            
        } else if(words[0].compare("e")==0) {
            if(counting_words!=4||words[2].compare("as")!=0||words[1][0]!='$'||words[1].length()==1) {
                cout << "\n-- Invalid command! --" << endl;
                delete[] words;
                continue;
            }
            
            it = checkToken(list_of_images,words[1]);
            if(it==list_of_images.end()) {
                delete[] words;
                continue;
            }
            else {
                ifstream check_file(words[3].c_str());
                if(check_file.is_open()) {
                    cout << "[ERROR] File exists" << endl;
                    check_file.close();
                }
                else {
                    ofstream output_file(words[3].c_str(),ios::out);
                    if(output_file.fail()||output_file.bad()||!output_file.is_open()) {
                        cout << "[ERROR] Unable to create file" << endl;
                        output_file.close();
                    }
                    else {
                        output_file << *it->getPtr();
                        cout << "[OK] Export " << words[1] << endl;
                    }
                }
            }

        } else if(words[0].compare("d")==0) {
            if(counting_words!=2||words[1][0]!='$'||words[1].length()==1) {
                cout << "\n-- Invalid command! --" << endl;
                delete[] words;
                continue;
            }

            it = checkToken(list_of_images,words[1]);
            if(it==list_of_images.end()) {
                delete[] words;
                continue;
            }
            else {
                list_of_images.erase(it);
                cout << "[OK] Delete " << words[1] << endl;
            }

        } else if(words[0].compare("n")==0) {
            if(counting_words!=2||words[1][0]!='$'||words[1].length()==1) {
                cout << "\n-- Invalid command! --" << endl;
                delete[] words;
                continue;
            }

            it = checkToken(list_of_images,words[1]);
            if(it==list_of_images.end()) {
                delete[] words;
                continue;
            }
            else {
                it->setPtr(&!*it->getPtr());
                cout << "[OK] Color Inversion " << words[1] << endl;
            }
            
        } else if(words[0].compare("z")==0) {
            if(counting_words!=2||words[1][0]!='$'||words[1].length()==1) {
                cout << "\n-- Invalid command! --" << endl;
                delete[] words;
                continue;
            }
            
            it = checkToken(list_of_images,words[1]);
            if(it==list_of_images.end()) {
                delete[] words;
                continue;
            }
            else {
                it->setPtr(&~*it->getPtr());
                cout << "[OK] Equalize " << words[1] << endl;
            }

        } else if(words[0].compare("m")==0) {
            if(counting_words!=2||words[1][0]!='$'||words[1].length()==1) {
                cout << "\n-- Invalid command! --" << endl;
                delete[] words;
                continue;
            }

            it = checkToken(list_of_images,words[1]);
            if(it==list_of_images.end()) {
                delete[] words;
                continue;
            }
            else {
                it->setPtr(&**it->getPtr());
                cout << "[OK] Mirror " << words[1] << endl;
            }
            
        } else if(words[0].compare("g")==0) {
            if(counting_words!=2||words[1][0]!='$'||words[1].length()==1) {
                cout << "\n-- Invalid command! --" << endl;
                delete[] words;
                continue;
            }

            it = checkToken(list_of_images,words[1]);
            if(it==list_of_images.end()) {
                delete[] words;
                continue;
            }
            else {
                if(dynamic_cast<GSCImage*>(it->getPtr())!=nullptr) {
                    cout << "[NOP] Already grayscale " << words[1] << endl;
                }
                else {
                    RGBImage* rgb = dynamic_cast<RGBImage*>(it->getPtr());
                    Image* img_ptr = new GSCImage(*rgb);
                    
                    delete rgb;
                    it->setPtr(img_ptr);
                    cout << "[OK] Grayscale " << words[1] << endl;
                }
            }
            
        } else if(words[0].compare("s")==0) {
            if(counting_words!=4||words[2].compare("by")!=0||words[1][0]!='$'||words[1].length()==1) {
                cout << "\n-- Invalid command! --" << endl;
                delete[] words;
                continue;
            }

            it = checkToken(list_of_images,words[1]);
            if(it==list_of_images.end()) {
                delete[] words;
                continue;
            }
            else {
                double factor = stod(words[3]);
                it->setPtr(&(*it->getPtr()*=factor));
                cout << "[OK] Scale " << words[1] << endl;
            }
            
        } else if(words[0].compare("r")==0) {
            if(counting_words!=5||words[2].compare("clockwise")!=0||words[4].compare("times")!=0||words[1][0]!='$'||words[1].length()==1) {
                cout << "\n-- Invalid command! --" << endl;
                delete[] words;
                continue;
            }

            it = checkToken(list_of_images,words[1]);
            if(it==list_of_images.end()) {
                delete[] words;
                continue;
            }
            else {
                int times = stoi(words[3]);
                it->setPtr(&(*it->getPtr()+=times));
                cout << "[OK] Rotate " << words[1] << endl;
            }
            
        } else if(words[0].compare("q")==0) {
            delete[] words;
            return 0;
        }
        delete[] words;
    }
}

