#include <iostream>
#include "LinkedListBarco.h"


using namespace std;

#ifndef NODOCATEGORIA_H
#define NODOCATEGORIA_H

class NodoCategoria{
public:
    string categoria;
    LinkedListBarco* barcos;
public:
    NodoCategoria* sig;
    NodoCategoria* ant;
    NodoCategoria();
    NodoCategoria(string);
};

NodoCategoria::NodoCategoria(){
    this->categoria = "";
    this->barcos = NULL;
    this->sig = NULL;
    this->ant = NULL;
}

NodoCategoria::NodoCategoria(string categoria){
    this->categoria = categoria;
    this->barcos = new LinkedListBarco();
    this->sig = NULL;
    this->ant = NULL;
}

#endif