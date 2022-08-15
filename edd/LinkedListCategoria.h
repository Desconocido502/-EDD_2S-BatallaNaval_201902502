#include <iostream>
#include <string>
#include <fstream>
#include "NodoCategoria.h"

using namespace std;

#ifndef LINKEDLISTCATEGORIA_H
#define LINKEDLISTCATEGORIA_H

class LinkedListCategoria{
private:
    int tam;
    NodoCategoria* primero;
    NodoCategoria* ultimo;
public:
    bool isEmpty();
    int length();
    void insert(int, string, int, string, string);
    NodoCategoria* get(string);
    bool search(string);
    void printL();
    void drawList();
    LinkedListCategoria();
    ~LinkedListCategoria();
};

LinkedListCategoria::LinkedListCategoria(){
    this->tam = 0;
    this->primero = NULL;
    this->ultimo = NULL;
}

bool LinkedListCategoria::isEmpty(){
    return this->primero == NULL;
}

int LinkedListCategoria::length(){
    return this->tam;
}

bool LinkedListCategoria::search(string categoria){
    if(this->isEmpty()){
        return false;
    }
    NodoCategoria* aux = this->primero;
    while(aux != nullptr){
        if(aux->categoria.compare(categoria) == 0){
            return true;
        }
        aux = aux->sig;
    }
    return false;
}

NodoCategoria* LinkedListCategoria::get(string categoria){
    if(this->isEmpty()) return NULL;
    NodoCategoria* aux = this->primero;
    while(aux != NULL){
        if(aux->categoria.compare(categoria)== 0){
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}

void LinkedListCategoria::insert(int id, string categoria, int precio, string nombre, string src){
    if(this->isEmpty()){
        this->primero = this->ultimo = new NodoCategoria(categoria);
        this->primero->barcos->insertAtEnd(id, precio, nombre, src);
        return;
    }else{
        //*Comparamos el valor para saber si existe la categoria en la lista
        if(this->search(categoria) == false){
            NodoCategoria* nuevo = new NodoCategoria(categoria);
            nuevo->barcos->insertAtEnd(id, precio, nombre, src);
            this->ultimo->sig = nuevo;
            nuevo->ant = this->ultimo;
            this->ultimo = nuevo;
            return;
        }else{
            NodoCategoria* temp = this->get(categoria);
            temp->barcos->insertAtEnd(id,precio, nombre,src);
            return;
        }
    }
}

void LinkedListCategoria::printL(){
    NodoCategoria* aux = this->primero;
    while (aux != nullptr){
        printf("Categoria:%s \n",aux->categoria.c_str());
        aux->barcos->displayList();
        aux = aux->sig;
    }
}


#endif