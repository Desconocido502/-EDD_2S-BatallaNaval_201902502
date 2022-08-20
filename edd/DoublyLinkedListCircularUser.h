#include <iostream>
#include <string.h>
#include "NodoUsuario.h"
#include "generacionImg.h"
#include "../lib/VariadicTable.h" 

using namespace std;

#ifndef DOUBLYLINKEDLISTCIRCULASUSER_H
#define DOUBLYLINKEDLISTCIRCULASUSER_H

int const MAXVALUE = 1; //Esta constante es para definir cuantas vueltas puede dar la lista para mostrar sus datos

class DoublyLinkedListCircularUser{
private:
    int tam;
    NodoUsuario* primero;
    NodoUsuario* ultimo;
    void __joinNodes();

public:
    bool isEmpty();
    int length();
    void insertAtStart(string, string, int, int);
    void insertAtEnd(string, string, int, int);
    void deleteAtStart();
    void deleteAtEnd();
    bool deleteNode(string);
    void displayListSE();
    void displayListES();
    NodoUsuario* searchUser(string, string);
    bool updateUser();
    void sort();
    void drawList();
    DoublyLinkedListCircularUser();
};

DoublyLinkedListCircularUser::DoublyLinkedListCircularUser(){
    this->tam = 0;
    this->primero = NULL;
    this->ultimo = NULL;
}

bool DoublyLinkedListCircularUser::isEmpty(){
    return this->primero == NULL;
}

int DoublyLinkedListCircularUser::length(){
    return this->tam;
}

void DoublyLinkedListCircularUser::__joinNodes(){
    if(this->primero != NULL){
        this->primero->ant = this->ultimo;
        this->ultimo->sig = this->primero;
    }
}

void DoublyLinkedListCircularUser::insertAtStart(string nick, string password, int money, int age){
    NodoUsuario* nuevo = new NodoUsuario(nick, password, money, age);
    NodoUsuario* aux = new NodoUsuario();

    if(this->isEmpty()){
        this->primero = this->ultimo = nuevo;
    }else{
        aux = nuevo;
        aux->sig = this->primero;
        this->primero->ant = aux;
        this->primero = aux;
    }
    this->__joinNodes();
    this->tam += 1;
    //delete aux;
}

void DoublyLinkedListCircularUser::insertAtEnd(string nick, string password, int money, int age){
    NodoUsuario* nuevo = new NodoUsuario(nick, password, money, age);
    NodoUsuario* aux = new NodoUsuario();


    if(this->isEmpty()){
        this->primero = this->ultimo = nuevo;
    }else{
        aux = this->ultimo;
        this->ultimo = aux->sig = nuevo;
        this->ultimo->ant = aux;
    }
    this->__joinNodes();
    this->tam += 1;
    //delete aux;
}

void DoublyLinkedListCircularUser::deleteAtStart(){
    if(this->isEmpty()){
        cout<<"Lista vacias"<<endl;
        return;
    }else if(this->primero == this->ultimo){
        this->primero = this->ultimo = NULL;
        this->tam = 0;
    }else{
        this->primero = this->primero->sig;
        this->tam -= 1;
    }
    this->__joinNodes();
}

void DoublyLinkedListCircularUser::deleteAtEnd(){
    if(this->isEmpty()){
        cout<<"Lista vacias"<<endl;
        return;
    }else if(this->primero == this->ultimo){
        this->primero = this->ultimo = NULL;
        this->tam = 0;
    }else{
        this->ultimo = this->ultimo->ant;
        this->tam -= 1;
    }
    this->__joinNodes();
}

void DoublyLinkedListCircularUser::displayListSE(){
    if(this->isEmpty()){
        cout<<"Lista vacia"<<endl;
        return;
    }
    VariadicTable<std::string, std::string , int, int> ut({"nick", "password", "monedas", "edad"});
    NodoUsuario* aux = new NodoUsuario();
    aux = this->primero;
    while (aux != NULL){
        ut.addRow(aux->user->getNick(),aux->user->getPassword(), aux->user->getMoney(), aux->user->getAge());
        aux = aux->sig;

        if(aux == this->primero){
            break;
        }
    }
    ut.print(cout);
    //delete aux;
    cout<<"\n";
}

void DoublyLinkedListCircularUser::displayListES(){
    if(this->isEmpty()){
        cout<<"Lista vacia"<<endl;
        return;
    }

    NodoUsuario* aux = new NodoUsuario();
    aux = this->ultimo;
    while (aux != NULL){
        aux->mostrarDatos();
        aux = aux->ant;

        if(aux == this->ultimo){
            break;
        }
    }
    //delete aux;
    cout<<"\n";
}

void DoublyLinkedListCircularUser::drawList(){
    if(this->isEmpty()){
        cout<<"Lista vacia, no se puede graficar la lista!!!"<<endl;
        return;
    }
    int cont = 0, cont_aux = 0;
    string datos = "digraph G {\nrankdir=LR;\nnode [shape=box, color=black , style=filled, fillcolor=gray93];\n";
    NodoUsuario* aux = new NodoUsuario();
    aux = this->primero;
    while (aux != NULL){
        datos += "Node" + to_string(cont) + "[label=\""+ "Nick: " + aux->user->getNick() + ", \\n"+ "Password: " +aux->user->getPassword() + ", \\n" + "Money: " + to_string(aux->user->getMoney()) + ", \\n" + "Age: " + to_string(aux->user->getAge()) + "\"];\n";
        cont += 1;
        aux = aux->sig;
        if(aux == this->primero){
            cont_aux += 1;
            if (cont_aux == MAXVALUE) break;
        }
    }
    cont = 0, cont_aux = 0;
    while(aux != NULL){
        datos += "Node" + to_string(cont) + "->" + "Node" + to_string(cont + 1) + ";\n";
        datos += "Node" + to_string(cont+1) + "->" + "Node" + to_string(cont) + ";\n";
        cont += 1;
        aux = aux->sig;
        if(aux == this->ultimo){
            cont_aux += 1;
            if (cont_aux == MAXVALUE) break;
        }
    }
    datos += "Node"+ to_string(cont) + ":sn->" + "Node" + to_string(0) + ":se;\n";
    datos += "Node"+ to_string(0) + ":s->" + "Node" + to_string(cont) + ":sc;\n";
    datos += "}";
    generacionImg("ListUsers", datos);
    aux = NULL;
}

bool DoublyLinkedListCircularUser::deleteNode(string nick){
    NodoUsuario* actual = new NodoUsuario();
    actual = this->primero;
    bool check = false;
    if(this->primero != NULL && check != true){
        do{
            if(actual->user->getNick() == nick){
                check = true;
                (actual->ant)->sig = actual->sig;
            }
            actual = actual->sig;
        } while (actual != this->primero && check == false); //*mientras el nodo actual sea diferente de primero, entre al ciclo.
        if(!check) return false;
        return true;
    }else{
        return false;
    }
}

NodoUsuario* DoublyLinkedListCircularUser::searchUser(string nick, string password){
    if(this->isEmpty()) return NULL; //*Retorna nulo en caso de que la lista este no contenga usuarios
    NodoUsuario* actual = this->primero;
    while (actual != NULL){
        if( (actual->user->getNick().compare(nick) == 0) && (actual->user->getPassword().compare(password) == 0)) return actual; //*retorna el nodo del usuario en caso de encontrarlo
        actual = actual->sig;
        if(actual == this->primero) return NULL; //*Retorna nulo en caso de no encontrar al usuario
    }
}


void DoublyLinkedListCircularUser::sort(){
    NodoUsuario* aux = new NodoUsuario();
    NodoUsuario* actual = new NodoUsuario();
    NodoUsuario* temp = new NodoUsuario();

    if(!this->isEmpty()){
        actual = this->primero;
        while(actual->sig != this->primero){
            aux = actual->sig;
            while(aux != this->primero){
                if(aux->user->getAge() < actual->user->getAge()){
                    temp->user = actual->user;
                    actual->user = aux->user;
                    aux->user = temp->user;
                }
                aux = aux->sig;
            }
            actual = actual->sig;
        }
    }
    return; //*Llegados aqui se ordeno todo
}

#endif