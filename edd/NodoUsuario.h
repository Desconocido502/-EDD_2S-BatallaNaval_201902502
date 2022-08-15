#include <iostream>
#include "User.h"

using namespace std;

class NodoUsuario{
public:
    User* user;
public:
    NodoUsuario* sig;
    NodoUsuario* ant;
    NodoUsuario();
    NodoUsuario(string, string, int, int);
    void mostrarDatos();
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