#include <iostream>
#include <string>

using namespace std;

#ifndef NODOP_H
#define NODOP_H

class NodoP{
public:
    int coordenadaX;
    int coordenadaY;
    NodoP* sig;
public:
    NodoP();
    NodoP(int, int);
    void setCoordenadaX(int);
    int getCoordenadaX();
    void setCoordenadaY(int);
    int getCoordenadaY();
    NodoP* getSiguiente(){
        return this->sig;
    }

    void setSiguiente(NodoP* sig){
        this->sig = sig;
    }
};

NodoP::NodoP(){
	this->coordenadaX = 0;
	this->coordenadaY = 0;
	this->sig = NULL;
}

NodoP::NodoP(int coordenadaX, int coordenadaY){
	this->coordenadaX = coordenadaX;
	this->coordenadaY = coordenadaY;
	this->sig = NULL;
}

int NodoP::getCoordenadaX(){
    return this->coordenadaX;
}

void NodoP::setCoordenadaX(int coordenadaX){
    this->coordenadaX = coordenadaX;
}

int NodoP::getCoordenadaY(){
    return this->coordenadaY;
}

void NodoP::setCoordenadaY(int coordenadaY){
    this->coordenadaY = coordenadaY;
}


#endif