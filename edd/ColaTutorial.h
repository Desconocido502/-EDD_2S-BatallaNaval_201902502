#include <iostream>
#include <string>

#include "NodoCola.h"
#include "generacionImg.h"
using namespace std;

#ifndef COLATUTORIAL_H
#define COLATUTORIAL_H

class ColaTutorial{
private:
    NodoCola* frente;
    NodoCola* final;
    int tamanio;
public:
    bool isEmpty();
    int length();
    void enqueue(int, int);
    NodoCola* dequeue();
    string in_front();
    void displayQueue();
    void drawQueue();
    ColaTutorial();
    ~ColaTutorial();
};

ColaTutorial::ColaTutorial(){
    this->frente = this->final = NULL;
    this->tamanio = 0;
}

bool ColaTutorial::isEmpty(){
    return this->frente == NULL;
}

int ColaTutorial::length(){
    return this->tamanio;
}

void ColaTutorial::enqueue(int anchoX, int altoY){
    NodoCola* nuevo = new NodoCola(anchoX, altoY);
    if(this->isEmpty()){
        this->frente = nuevo;
    }else{
        this->final->setSiguiente(nuevo);
    }
    this->final = nuevo;
    this->tamanio += 1;
}

NodoCola* ColaTutorial::dequeue(){
    NodoCola* nuevo = this->frente;
    this->frente = this->frente->getSiguiente();

    if(this->isEmpty()){
        this->final = NULL;
    }
    this->tamanio -= 1;
    return nuevo;
}

string ColaTutorial::in_front(){
    return "anchoX:" + to_string(this->frente->getAnchoX()) + ", altoY:" + to_string(this->frente->getAltoY());
}

void ColaTutorial::displayQueue(){
    if(this->isEmpty()){
        cout<<"La cola esta vacia"<<endl;
        return;
    }
    NodoCola* actual = this->frente;
    cout<<"Ancho:" + to_string(this->frente->getAnchoX()) + ",\nAlto:" + to_string(this->frente->getAltoY()) +"\n";
    if(actual->getSiguiente() == NULL){
        cout<<"Sin coordenadas de movimientos"<<endl;
        return;
    }
    actual = actual->getSiguiente(); //*Se obtiene el primer nodo de coordenadas
    while(actual != NULL){
        cout<<"(X:" + to_string(actual->getAnchoX()) + ", Y:" + to_string(actual->getAltoY()) +")->";
        actual = actual->getSiguiente();
    }
    cout<<"Fin coordenadas"<<endl;
}

void ColaTutorial::drawQueue(){
    NodoCola* temp = this->frente;
    string cadena = "";
    int cont = 0;
    cadena += "digraph G { \n";
    cadena += "rankdir=LR; \nnode [shape=box, color=black , style=filled, fillcolor=gray93];\n";

    if(temp->getSiguiente() == NULL){
        cout<<"No se puede graficar por falta de coordenadas"<<endl;
        return;
    }

    while(temp != NULL){
        if(temp == this->frente){
            cadena += "Node" + to_string(cont) + "[label=\"" + "Ancho: " + to_string(temp->getAnchoX()) + ",\\nAlto: " + to_string(temp->getAltoY())+"\"];\n";
        }else{
            cadena += "Node" + to_string(cont) + "[label=\"" + "X: " + to_string(temp->getAnchoX()) + ",\\nY: " + to_string(temp->getAltoY())+"\"];\n";
        }

        if(temp != this->frente){
            cadena += "Node" + to_string(cont) + "->" + "Node" + to_string(cont - 1) + ";\n";
        }
        temp = temp->getSiguiente();
        cont += 1;
    }
    cadena += "}";
    //cout<<cadena<<endl;
    generacionImg("ColaTutorial", cadena);
}


ColaTutorial::~ColaTutorial(){
}


#endif