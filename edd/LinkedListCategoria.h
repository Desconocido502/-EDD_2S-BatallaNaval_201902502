#include <iostream>
#include <string>
#include <fstream>
#include "NodoCategoria.h"
#include "LinkedListBarco.h"
#include "NodoBarco.h"
#include "generacionImg.h"

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
    NodoBarco* buyArticle(int);
    void printL();
    void printLTienda();
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

NodoBarco* LinkedListCategoria::buyArticle(int id){
    if(this->isEmpty()) return NULL;
    NodoCategoria* aux = this->primero;
    NodoBarco* encontrado = NULL;
    while(aux != nullptr){
        encontrado = aux->barcos->searchBoat(id);
        if(encontrado != NULL){
            return encontrado;
        }
        aux = aux->sig;
    }
    return NULL;
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
        this->primero->barcos->insertAtEnd(id, precio, nombre, src, categoria);
        return;
    }else{
        //*Comparamos el valor para saber si existe la categoria en la lista
        if(this->search(categoria) == false){
            NodoCategoria* nuevo = new NodoCategoria(categoria);
            nuevo->barcos->insertAtEnd(id, precio, nombre, src, categoria);
            this->ultimo->sig = nuevo;
            nuevo->ant = this->ultimo;
            this->ultimo = nuevo;
            return;
        }else{
            NodoCategoria* temp = this->get(categoria);
            temp->barcos->insertAtEnd(id,precio, nombre,src, categoria);
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

void LinkedListCategoria::printLTienda(){
    //*Tendremos que usar una lista de tipo barco, para mostrar la informacion ordenada por precios
    LinkedListBarco* auxBarcos = new LinkedListBarco();
    NodoBarco* aux_barco;
    NodoCategoria* aux = this->primero;
    while (aux != nullptr){
        //printf("Categoria:%s \n",aux->categoria.c_str());
        aux_barco = aux->barcos->returnHead();
        while(aux_barco != NULL){ //*Se insertan todos los barcos de cualquier tipo de barco en una sola lista de tipo barcos
            auxBarcos->insertAtEnd(aux_barco->getId(), aux_barco->getPrecio(), aux_barco->getNombre(), aux_barco->getSrc(), aux_barco->categoria);
            aux_barco = aux_barco->sig;
        }
        aux_barco = nullptr;
        aux = aux->sig;
    }
    //*Falta ordenarlo ascendente o descendente por el precio
    auxBarcos->sort();
    auxBarcos->displayList();
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

    //cout<<cadena<<endl;.
    generacionImg("Articles", cadena);
}

#endif