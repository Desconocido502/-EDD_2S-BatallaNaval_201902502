#include <iostream>
#include "NodoBarco.h"

using namespace std;

#ifndef NODOAVL_H
#define NODOAVL_H

class NodoAvl{
public:
    NodoBarco* nodoBarco;
    NodoAvl* left;
    NodoAvl* right;
    int alturaN;
public:
    NodoAvl();
    NodoAvl(NodoBarco*);
    ~NodoAvl();
};

NodoAvl::NodoAvl(NodoBarco* nodoBarco){
    this->nodoBarco = nodoBarco;
    left = right = nullptr;
}

NodoAvl::NodoAvl(){
    this->nodoBarco = nullptr;
    left = right = nullptr;
}

NodoAvl::~NodoAvl(){
    
}



#endif