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
    string categoria;
    NodoBarco* sig;
    NodoBarco* ant;
    NodoBarco();
    NodoBarco(int, int, string, string, string);
    void mostrarDatos();

    int getId(){
        return this->barco->getId();
    }

    int getPrecio(){
        return this->barco->getPrecio();
    }

    string getNombre(){
        return this->barco->getNombre();
    }

    string getSrc(){
        return this->barco->getSrc();
    }
};

NodoBarco::NodoBarco(){
    this->barco = NULL;
    this->sig = NULL;
    this->ant = NULL;
}

NodoBarco::NodoBarco(int id, int precio, string nombre, string src, string categoria){
    this->categoria = categoria;
    this->barco = new ArticleB(id, precio, nombre, src);
    this->sig = NULL;
    this->ant = NULL;
}

void NodoBarco::mostrarDatos(){
    this->barco->mostrarDatos();
}

#endif