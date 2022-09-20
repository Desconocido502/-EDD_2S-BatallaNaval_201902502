#include <iostream>
#include <string>

#include "NodoP.h"

using namespace std;

#ifndef PILAMOV_H
#define PILAMOV_H

class PilaMov{
private:
    string nombrePilaMov;
    int tamanio;
    NodoP* start;
public:
    void setNombrePilaMov(string);
    string getNombrePilaMov();
    bool isEmpty();
    int length();
    void push(int, int);
    NodoP* pop();
    string top();
    string displayStack();
    string drawStack(string);
    PilaMov();
    ~PilaMov();
};

void PilaMov::setNombrePilaMov(string nombrePilaMov){
    this->nombrePilaMov = nombrePilaMov;
}

string PilaMov::getNombrePilaMov(){
    return this->nombrePilaMov;
}

bool PilaMov::isEmpty(){
    return this->start == NULL;
}

int PilaMov::length(){
    return this->tamanio;
}

void PilaMov::push(int coordenadaX, int coordenadaY){
    NodoP* nuevo = new NodoP(coordenadaX, coordenadaY);
    if(this->isEmpty()){
        this->start = nuevo;
    }else{
        nuevo->setSiguiente(this->start);
        this->start = nuevo;
    }
    this->tamanio += 1;
}

NodoP* PilaMov::pop(){
    NodoP* tope= NULL;
    if(!this->isEmpty()){
        tope = this->start;
        this->start = this->start->sig;
        this->tamanio -=1;
    }
    return tope;
}

string PilaMov::top(){
    if(!this->isEmpty()){
        return "X: " + to_string(this->start->coordenadaX) + ", Y: " + to_string(this->start->coordenadaY);
    }else{
        return "pila vacia";
    }
}


PilaMov::PilaMov(){
    this->nombrePilaMov = "";
    this->tamanio = 0;
    this->start = NULL;
}

string PilaMov::displayStack(){
    string cadena = "";
    NodoP* aux = this->start;
    cadena += "-------------------------\n";
    while(aux != NULL){
        cadena += "|\tX: " + to_string(aux->coordenadaX) + ", Y: " + to_string(aux->coordenadaY) + "\t|\n";
        cadena += "-------------------------\n";
        aux = aux->getSiguiente();
    }
    return cadena;
}
//*Metodo listo
string PilaMov::drawStack(string nombreNodo){
    NodoP* temp = this->start;
    string cadena = "", nodo = "";
    
    cadena += "Nodo_"+nombreNodo+"[\n\tlabel=<\n";
    cadena += "\t<table border=\"1\" cellborder=\"1\" cellspacing=\"0\">\n";

    while(temp != NULL){
        cadena = cadena + "\t\t<tr><td bgcolor=\"yellow\"><font color=\"#0000ff\">" + "X: " + to_string(temp->coordenadaX) + ", Y: " + to_string(temp->coordenadaY) + "</font></td></tr>\n";
        temp = temp->getSiguiente();
    }
    cadena += "\t</table>>\n ,shape=plaintext];\n";
    return cadena;
}

PilaMov::~PilaMov(){

}


#endif