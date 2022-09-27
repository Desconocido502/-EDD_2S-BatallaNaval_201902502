#include <iostream>
#include <string>
#include "Barco.h"

using namespace std;
#ifndef NODOBARCO_H
#define NODOBARCO_H

class NodoBarco{
public:
    Barco* barco;
public:
    string categoria;
    NodoBarco* sig;
    NodoBarco* ant;
    NodoBarco();
    NodoBarco(string, int, string, string, string);
    void mostrarDatos();

    void setBarco(Barco* barco){
        this->barco = barco;
    }

    Barco* getBarco(){
        return this->barco;
    }

    void setId(string id){
        this->barco->setId(id);
    }

    string getId(){
        return this->barco->getId();
    }

    void setPrecio(int precio){
        this->barco->setPrecio(precio);
    }

    int getPrecio(){
        return this->barco->getPrecio();
    }

    void setNombre(string nombre){
        this->barco->setNombre(nombre);
    }

    string getNombre(){
        return this->barco->getNombre();
    }

    void setSrc(string src){
        this->barco->setSrc(src);
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

NodoBarco::NodoBarco(string id, int precio, string nombre, string src, string categoria){
    this->categoria = categoria;
    this->barco = new Barco(id, precio, nombre, src);
    this->sig = NULL;
    this->ant = NULL;
}

void NodoBarco::mostrarDatos(){
    this->barco->mostrarDatos();
}

#endif