#include <iostream>
#include <string>

#include "PilaMov.h"
using namespace std;

#ifndef NODOLP_H
#define NODOLP_H

class NodoLP{
private:
    string nombreNodoPila;
    PilaMov* pilaMovimientos;
public:
    NodoLP* sig;
    NodoLP* ant;
    void setPilaMov(PilaMov*);
    PilaMov* getPilaMov();
    void setNombreNodoPila(string);
    string getNombreNodoPila();
    void setSiguiente(NodoLP*);
    NodoLP* getSiguiente();
    void setAnterior(NodoLP*);
    NodoLP* getAnterior();
    NodoLP();
    NodoLP(string, PilaMov*);
    ~NodoLP();
};

void NodoLP::setPilaMov(PilaMov* pilaMovimientos){
    this->pilaMovimientos = pilaMovimientos;
}

PilaMov* NodoLP::getPilaMov(){
    return this->pilaMovimientos;
}

void NodoLP::setNombreNodoPila(string nombreNodoPila){
    this->nombreNodoPila = nombreNodoPila;
}

string NodoLP::getNombreNodoPila(){
    return this->nombreNodoPila;
}

void NodoLP::setSiguiente(NodoLP* sig){
    this->sig = sig;
}

NodoLP* NodoLP::getSiguiente(){
    return this->sig;
}

void NodoLP::setAnterior(NodoLP* ant){
    this->ant = ant;
}

NodoLP* NodoLP::getAnterior(){
    return this->ant;
}

NodoLP::NodoLP(string nombreNodoPila, PilaMov* pilaMovimientos){
    this->pilaMovimientos = pilaMovimientos;
    this->nombreNodoPila = nombreNodoPila;
    this->sig = this->ant = NULL;
}

NodoLP::NodoLP(){
    this->pilaMovimientos = NULL;
    this->nombreNodoPila = "";
    this->sig = this->ant = NULL;
}

NodoLP::~NodoLP(){

}

#endif