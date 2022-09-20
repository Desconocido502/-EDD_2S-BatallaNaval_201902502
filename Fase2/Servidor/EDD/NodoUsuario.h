#include <iostream>
#include <map>
#include <vector>

#include "User.h"
#include "../lib/crow_all.h"

using namespace std;

#ifndef NODOUSUARIO_H
#define NODOUSUARIO_H

class NodoUsuario{
public:
    User* user;
public:
    NodoUsuario* sig;
    NodoUsuario* ant;
    NodoUsuario();
    NodoUsuario(string, string, int, int);
    void mostrarDatos();
    User* getUsuario();

};


NodoUsuario::NodoUsuario(){
    this->user = NULL;
    this->sig = NULL;
    this->ant = NULL;
}

NodoUsuario::NodoUsuario(string nick, string password, int money, int age){
    this->user = new User(nick, password, money, age);
    this->sig = NULL;
    this->ant = NULL;
}

void NodoUsuario::mostrarDatos(){
    this->user->mostrarDatos();
}


User* NodoUsuario::getUsuario(){
    return this->user;
}

#endif