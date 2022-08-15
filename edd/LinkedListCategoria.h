#include <iostream>
#include <string>
#include <fstream>
#include "NodoCategoria.h"
#include "NodoBarco.h"

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

void LinkedListCategoria::drawList(){
    string cadena = "";
    int cont = 0, cont2 = 0;
    NodoCategoria* vertical;
    NodoBarco* horizontal;
    cadena = cadena + "digraph G { \n";
    vertical = this->primero;
    while(vertical != NULL){
        cadena += "\""+to_string(0) + vertical->categoria + "\""+ "[shape=box, rankdir=UD, style=filled, label=\"" + vertical->categoria + "\""+ ", pos=\"0,-"+to_string(cont)+"!\"];\n";
        horizontal = vertical->barcos->returnHead();
        cont2 = 0;
        while(horizontal != NULL){
            cadena += "\""+to_string(cont) + "Node" + to_string(horizontal->getId()) + "_" + to_string(cont2) + "\"[shape=box, rankdir=LR, style=filled, label=\"Id:" + to_string(horizontal->getId()) + "\\n, Precio:"+ to_string(horizontal->getPrecio()) + "\\n, Nombre:" + horizontal->getNombre() + "\\n, Src:" + horizontal->getSrc()  + "\", pos=\""+to_string(cont2)+",-"+to_string(cont)+"!\"];\n";
            cont2 += 1;
            horizontal = horizontal->sig;
        }
        cont += 1;
        vertical = vertical->sig;
    }
    //*Enlazar nodos verticales
    vertical = this->primero;
    while(vertical != NULL){
        if(vertical == this->primero){
            cadena += "\""+to_string(0) + vertical->categoria+"\"";
        }else{
            cadena += "->\""+to_string(0) + vertical->categoria+"\"";
        }
        vertical = vertical->sig;
    }
    //*Enlazamos nodos horizontales
    cadena += "\n";
    cont = 0;
    vertical = this->primero;
    while(vertical != NULL){
        horizontal = vertical->barcos->returnHead();
        if(horizontal != NULL){
            cont2 = 0;
            cadena += "\""+to_string(0) + vertical->categoria+"\"->"; //+ to_string(cont)+"Node"+to_string(horizontal->getId())+"_"+to_string(cont2) + "\""
            while(horizontal != NULL){
                if(horizontal == vertical->barcos->returnHead()){
                    cadena += "\""+to_string(cont)+"Node"+to_string(horizontal->getId())+"_"+to_string(cont2)+ "\"";
                }else{
                    cadena += "->\"" + to_string(cont)+"Node"+to_string(horizontal->getId())+"_"+to_string(cont2)+"\"";
                }
                cont2 += 1;
                horizontal = horizontal->sig;
            }
            cont += 1;
        }
        cadena += "\n";
        vertical = vertical->sig;
    }
    //*Colocamos los nodos de la lista principal a la misma altura
    vertical = this->primero;
    cadena += "\n{rank=same;";
    while(vertical != this->ultimo){
        cadena += "\""+to_string(0)+ vertical->categoria+"\",";
        vertical = vertical->sig;
    }
    cadena += "\""+to_string(0)+vertical->categoria+"\"";
    cadena += "};\n";
    cadena += "}\n";

    //cout<<cadena<<endl;
    try{
        ofstream file;
        file.open("Articles.dot", std::ios::out);

        if(file.fail()){
            exit(1);
        }
        file << cadena;
        file.close();
        string command = "dot -Tpng Articles.dot -o Articles.png";
        system(command.c_str());
    }catch(const std::exception& e){
        cout<<"No se pudo crear la imagen :("<<endl;
    }
}

#endif