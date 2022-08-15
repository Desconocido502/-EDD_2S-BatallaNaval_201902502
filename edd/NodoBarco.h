#include <iostream>
#include <string>
#include "ArticleB.h"

using namespace std;
#ifndef NODOBARCO_H
#define NODOBARCO_H

class NodoBarco{
public:
    ArticleB* barco;
public:
    NodoBarco* sig;
    NodoBarco* ant;
    NodoBarco();
    NodoBarco(int, int, string, string);
    void mostrarDatos();
};

NodoBarco::NodoBarco(){
    this->barco = NULL;
    this->sig = NULL;
    this->ant = NULL;
}

NodoBarco::NodoBarco(int id, int precio, string nombre, string src){
    this->barco = new ArticleB(id, precio, nombre, src);
    this->sig = NULL;
    this->ant = NULL;
}

void NodoBarco::mostrarDatos(){
    this->barco->mostrarDatos();
}

#endif