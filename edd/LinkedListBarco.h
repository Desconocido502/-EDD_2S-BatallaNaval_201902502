#include <iostream>
#include "NodoBarco.h"
#include "../lib/VariadicTable.h"

using namespace std;
#ifndef LINKEDLISTBARCO_H
#define LINKEDLISTBARCO_H

class LinkedListBarco{
private:
    int tam;
    NodoBarco* primero;
    NodoBarco* ultimo;
public:
    bool isEmpty();
    int length();
    NodoBarco* returnHead();
    void insertAtStart(int, int, string, string, string);
    void insertAtEnd(int, int, string, string, string);
    NodoBarco* searchBoat();
    void displayList();
    bool updateBoat();
    void sort();
    void drawList();
    LinkedListBarco();
};

LinkedListBarco::LinkedListBarco(){
    this->tam = 0;
    this->primero = NULL;
    this->ultimo = NULL;
}

bool LinkedListBarco::isEmpty(){
    return this->primero == NULL;
}

int LinkedListBarco::length(){
    return this->tam;
}

NodoBarco* LinkedListBarco::returnHead(){
    return this->primero;
}

void LinkedListBarco::insertAtStart(int id,  int precio, string nombre, string src, string categoria){
    NodoBarco* nuevo = new NodoBarco(id, precio, nombre, src, categoria);
    NodoBarco* aux = new NodoBarco();

    if(this->isEmpty()){
        this->primero = this->ultimo = nuevo;
    }else{
        aux = nuevo;
        aux->sig = this->primero;
        this->primero->ant = aux;
        this->primero = aux;
    }
    this->tam += 1;
}

void LinkedListBarco::insertAtEnd(int id,  int precio, string nombre, string src, string categoria){
    NodoBarco* nuevo = new NodoBarco(id, precio, nombre, src, categoria);
    NodoBarco* aux = new NodoBarco();

    if(this->isEmpty()){
        this->primero = this->ultimo = nuevo;
    }else{
        aux = this->ultimo;
        this->ultimo = aux->sig = nuevo;
        this->ultimo->ant = aux;
    }
    this->tam += 1;
}

void LinkedListBarco::displayList(){
    if(this->isEmpty()){
        cout<<"La lista se encuentra vacia"<<endl;
    }
    VariadicTable<int, std::string, std::string, int > ut({"ID", "Nombre", "Categoria", "Precio"});
    NodoBarco* aux = new NodoBarco();
    aux = this->primero;
    while(aux != nullptr){
        ut.addRow(aux->barco->getId(), aux->barco->getNombre(), aux->categoria, aux->barco->getPrecio());
        //aux->barco->mostrarDatos();
        aux = aux->sig;
    }
    ut.print(cout);
    cout<<"\n"<<endl;
}


#endif