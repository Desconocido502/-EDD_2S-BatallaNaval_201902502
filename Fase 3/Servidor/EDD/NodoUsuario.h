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
    NodoUsuario(int, string, string, int, int);
    string mostrarDatos();
    User* getUsuario();

};


NodoUsuario::NodoUsuario(){
    this->user = NULL;
    this->sig = NULL;
    this->ant = NULL;
}

NodoUsuario::NodoUsuario(int id, string nick, string password, int money, int age){
    this->user = new User(id, nick, password, money, age);
    this->sig = NULL;
    this->ant = NULL;
}

string NodoUsuario::mostrarDatos(){
    return this->user->mostrarDatos2();
}


User* NodoUsuario::getUsuario(){
    return this->user;
}

#endif