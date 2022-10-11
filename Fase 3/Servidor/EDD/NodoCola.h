#include <iostream>

using namespace std;

#ifndef NODOCOLA_H
#define NODOCOLA_H

class NodoCola{
private:
    int anchoX;
    int altoY;
    NodoCola* sig;
public:
    NodoCola(int, int);
    NodoCola();
    ~NodoCola();
    void setAnchoX(int);
    int getAnchoX();
    void setAltoY(int);
    int getAltoY();
    void setSiguiente(NodoCola* sig);
    NodoCola* getSiguiente();
};

NodoCola::NodoCola(int anchoX, int altoY){
    this->anchoX = anchoX;
    this->altoY = altoY;
    this->sig = NULL;
}

NodoCola::NodoCola(){
    this->anchoX = 0;
    this->altoY = 0;
    this->sig = NULL;
}

void NodoCola::setAnchoX(int anchoX){
    this->anchoX = anchoX;
}

int NodoCola::getAnchoX(){
    return this->anchoX;
}

void NodoCola::setAltoY(int altoY){
    this->altoY = altoY;
}

int NodoCola::getAltoY(){
    return this->altoY;
}

void NodoCola::setSiguiente(NodoCola* sig){
    this->sig = sig;
}

NodoCola* NodoCola::getSiguiente(){
    return this->sig;
}

NodoCola::~NodoCola(){

}

#endif