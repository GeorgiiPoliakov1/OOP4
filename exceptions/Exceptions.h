#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <iostream>

using namespace std;

class InvalidArgumentException : public invalid_argument {
public: 
    InvalidArgumentException(const char* msg) : invalid_argument(msg) {}
};

class GoingOutOfBordersException : public InvalidArgumentException {
public:
    GoingOutOfBordersException(const char* msg, int widthField, int heightField) : 
    InvalidArgumentException(msg), widthField(widthField), heightField(heightField) {}
    int getHeight() {return heightField; }
    int getWidth() {return widthField; }
private:
    int heightField;
    int widthField;
};

class InсorrectShipPositioningException  : public InvalidArgumentException {
public:
    InсorrectShipPositioningException(const char* msg, int incorrectX, int incorrectY) : 
    InvalidArgumentException(msg), cellX(incorrectX), cellY(incorrectY) {}
    int getY() {return cellY; }
    int getX() {return cellX; }
private:
    int cellX;
    int cellY;
};

class InсorrectShipLayoutException  : public InvalidArgumentException {
public:
    InсorrectShipLayoutException(const char* msg) :
    InvalidArgumentException(msg){}
};

class NoAbilitiesException : public InvalidArgumentException {
public:
    NoAbilitiesException(const char* msg) : InvalidArgumentException(msg) {}
};

#endif