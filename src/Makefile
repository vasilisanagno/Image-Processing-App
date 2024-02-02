FLAGS = -Wall -g -std=c++11 -fsanitize=address

all: GSCPixel.o RGBPixel.o GSCImage.o RGBImage.o Token.o
	g++ $(FLAGS) imageProcessingApp.cpp GSCPixel.o RGBPixel.o GSCImage.o RGBImage.o Token.o -o imageProcessingApp

GSCPixel.o: Pixel.hpp GSCPixel.hpp GSCPixel.cpp
	g++ $(FLAGS) -c GSCPixel.cpp

RGBPixel.o: Pixel.hpp RGBPixel.hpp RGBPixel.cpp
	g++ $(FLAGS) -c RGBPixel.cpp

GSCImage.o: Image.hpp GSCImage.hpp GSCImage.cpp
	g++ $(FLAGS) -c GSCImage.cpp

RGBImage.o: Image.hpp RGBImage.hpp RGBImage.cpp
	g++ $(FLAGS) -c RGBImage.cpp

Token.o: Token.hpp Token.cpp
	g++ $(FLAGS) -c Token.cpp

clean:
	rm *.o hw4


