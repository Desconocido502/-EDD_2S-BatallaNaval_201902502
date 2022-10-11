#include <iostream>
#include <string>

#include "NodoLP.h"
#include "PilaMov.h"
#include "generacionImg.h"
#include "../lib/replace.h"
using namespace std;

#ifndef LISTAPILAMOV_H
#define LISTAPILAMOV_H

class ListaPilaMov{
private:
    int tamanio;
    NodoLP* primero;
    NodoLP* ultimo;
public:
    bool estaVacio();
    int largo();
    void insertarAlFinal(string, PilaMov*);
    bool eliminarNodo(string);
    void desplegarLista(); 
    void drawListStacks(string);
    ListaPilaMov();
    ~ListaPilaMov();
};

ListaPilaMov::ListaPilaMov(){
    this->tamanio = 0;
    this->primero = this->ultimo = NULL;
}

bool ListaPilaMov::estaVacio(){
    return this->primero == NULL;
}

int ListaPilaMov::largo(){
    return this->tamanio;
}

void ListaPilaMov::insertarAlFinal(string nombreNodoPila, PilaMov* pilaMovimientos){
    NodoLP* nuevo = new NodoLP(nombreNodoPila, pilaMovimientos);
    NodoLP* aux = new NodoLP();

    if(this->estaVacio()){
        this->primero = this->ultimo = nuevo;
    }else{
        aux = this->ultimo;
        this->ultimo = aux->sig = nuevo;
        this->ultimo->setAnterior(aux);
    }
    this->tamanio +=1;
}

bool ListaPilaMov::eliminarNodo(string nombreNodoPila){
    NodoLP* actual = new NodoLP();
    actual = this->primero;
    bool check = false;
    if(this->primero != NULL && check != true){
        do{
            if((actual->getNombreNodoPila().compare(nombreNodoPila)) == 0){
                check = true;
                (actual->getAnterior())->setSiguiente(actual->getSiguiente());
            }
            actual = actual->getSiguiente();
        } while (actual != NULL && check == false);
        if(!check) return false;
        return true;
    }
    return false;
}

void ListaPilaMov::desplegarLista(){
    string cadena = "", pilas = "";
    if(this->estaVacio()){
        cout<<"La lista esta vacia"<<endl;
        return;
    }
    NodoLP* aux = new NodoLP();
    aux = this->primero;
    while (aux !=  NULL){        
        cout<<"Pila: "<<aux->getNombreNodoPila()<<endl;
        cout<<aux->getPilaMov()->displayStack()<<endl;
        // cout<<aux->getPilaMov()->drawStack(aux->getNombreNodoPila());
        aux = aux->getSiguiente();
    }
}

void ListaPilaMov::drawListStacks(string userName){
    NodoLP* temp = this->primero;
    int cont = 0;
    string cadena = "", aux = "", apuntadores = "";
    cadena += "digraph G { \nlabel=\"\n" + userName + "\";";

    while (temp != NULL){
        
        cadena += temp->getNombreNodoPila() + "_"+to_string(cont) +  "[shape=box, rankdir=UD, style=filled, label=\""  + replace(temp->getNombreNodoPila(),"_"," ") +  "\"" +",pos=\"0,-"+ to_string(cont) + "!\"];\n";
        
        if(temp->getSiguiente() == NULL){
            aux += temp->getNombreNodoPila() + "_"+to_string(cont) + "};\n";
            apuntadores += temp->getNombreNodoPila() + "_"+to_string(cont)+";\n";
        }else{
            aux += temp->getNombreNodoPila() + "_"+to_string(cont) + ",";
            apuntadores += temp->getNombreNodoPila() + "_"+to_string(cont) + "->";
        }
        cont += 1;
        temp = temp->getSiguiente();
    }
    cadena += apuntadores +"\n";
    cadena += "{rank=same;" + aux;
    
    temp = this->primero;
    cont = 0;
    while(temp!=NULL){
        cadena += temp->getPilaMov()->drawStack(temp->getNombreNodoPila() + "_"+to_string(cont));
        cadena += temp->getNombreNodoPila() + "_"+to_string(cont) + "->Nodo_"+temp->getNombreNodoPila() + "_"+to_string(cont) + ";\n";
        cont += 1;
        temp = temp->getSiguiente();
    }
    cadena += "}";
    //cout<<cadena<<endl;
    generacionImg("ListaPilas"+userName, cadena);
}

ListaPilaMov::~ListaPilaMov(){
}



#endif