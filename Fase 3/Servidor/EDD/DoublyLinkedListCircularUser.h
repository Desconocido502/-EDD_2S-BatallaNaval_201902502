#include <iostream>
#include <string.h>
#include <map>
#include <vector>
#include "NodoUsuario.h"
#include "generacionImg.h"
#include "../lib/VariadicTable.h"
#include "../lib/crow_all.h"

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
    void insertAtStart(int, string, string, int, int);
    NodoUsuario* insertAtEnd(int, string, string, int, int);
    void deleteAtStart();
    void deleteAtEnd();
    bool deleteNode(string);
    bool deleteNode2(string);
    void displayListSE();
    void displayListES();
    NodoUsuario* searchUser(string, string);
    NodoUsuario* searchUser2(string); //*busca por el nick y devuelve el nodo usuario
    bool searchUserForNick(string);
    bool updateUser();
    void sort();
    void sortReverse();
    void drawList();
    DoublyLinkedListCircularUser();
    vector<crow::json::wvalue> to_vector();
};

vector<crow::json::wvalue> DoublyLinkedListCircularUser::to_vector(){
    std::vector<crow::json::wvalue> datos;
    if(isEmpty()){
        cout<<"NO hay elementos enla lista"<<endl;
    }else{
        NodoUsuario* aux = primero;
        while(aux != NULL){
            crow::json::wvalue x;
            x["nick"] = aux->getUsuario()->getNick();
            x["password"] = aux->getUsuario()->getPassword();
            x["monedas"] = aux->getUsuario()->getMoney();
            x["edad"] = aux->getUsuario()->getAge();
            datos.push_back(x);
            aux = aux->sig;

            if(aux == primero){
               break;
            }
        }
    }
    return datos;
}

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

void DoublyLinkedListCircularUser::insertAtStart(int id, string nick, string password, int money, int age){
    NodoUsuario* nuevo = new NodoUsuario(id, nick, password, money, age);
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

NodoUsuario* DoublyLinkedListCircularUser::insertAtEnd(int id, string nick, string password, int money, int age){
    NodoUsuario* nuevo = new NodoUsuario(id, nick, password, money, age);
    //cout<<"\n-------------------"<<endl;
    //cout<<nuevo<<"| "<<nick<<endl;
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
    aux = NULL;
    //cout<<"\n-------------------"<<endl;
    //cout<<nuevo<<endl;
    return nuevo;
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
    aux = NULL;
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
    datos += "Node"+ to_string(cont) + ":s->" + "Node" + to_string(0) + ":s;\n";
    datos += "Node"+ to_string(0) + ":s->" + "Node" + to_string(cont) + ":s;\n";
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
                if(actual == this->ultimo || actual == this->primero){
                    this->__joinNodes();
                }
            }
            actual = actual->sig;
        } while (actual != this->primero && check == false); //*mientras el nodo actual sea diferente de primero, entre al ciclo.
        if(!check) return false;
        return true;
    }else{
        return false;
    }
}


bool DoublyLinkedListCircularUser::deleteNode2(string nick){
    //*Nuevo codigo para eliminar un nodo de la lista circular doblemente enlazada
    if(this->isEmpty()) {
        return false;
    }else if(this->primero->user->getNick().compare(nick) == 0){ //Si son iguales
        this->deleteAtStart();
        return true;
    }else if(this->ultimo->user->getNick().compare(nick) == 0){
        this->deleteAtEnd();
        return true;
    }else{ //* Se realiza un recorrido hasta encontrar el nodo a eliminar
        NodoUsuario* aux = this->searchUser2(nick);
        if(aux != NULL){
            NodoUsuario* auxSiguiente = aux->sig;
            NodoUsuario* auxAnterior = aux->ant;
            aux = NULL;
            auxSiguiente->ant = auxAnterior;
            auxAnterior->sig = auxSiguiente;
            return true;
        }else{
            return false;
        } 
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
    return NULL;
}

NodoUsuario* DoublyLinkedListCircularUser::searchUser2(string nick){
    if(this->isEmpty()) return NULL; //*Retorna nulo en caso de que la lista este no contenga usuarios
    NodoUsuario* actual = this->primero;
    while (actual != NULL){
        if( (actual->user->getNick().compare(nick) == 0)) return actual; //*retorna el nodo del usuario en caso de encontrarlo
        actual = actual->sig;
        if(actual == this->primero) return NULL; //*Retorna nulo en caso de no encontrar al usuario
    }
    return NULL;
}

bool DoublyLinkedListCircularUser::searchUserForNick(string nick){
    if(this->isEmpty()) return false; //*Retorna false en caso de que la lista este no contenga usuarios
    NodoUsuario* actual = this->primero;
    while (actual != NULL){
        if( (actual->user->getNick().compare(nick) == 0)) return true; //*retorna true en caso de encontrar al user
        actual = actual->sig;
        if(actual == this->primero) return false; //*Retorna false en caso de no encontrar al usuario
    }
    return false;
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
    return; //*Llegados aqui se ordeno todo de menor a mayor
}

void DoublyLinkedListCircularUser::sortReverse(){
    NodoUsuario* aux = new NodoUsuario();
    NodoUsuario* actual = new NodoUsuario();
    NodoUsuario* temp = new NodoUsuario();

    if(!this->isEmpty()){
        actual = this->primero;
        while(actual->sig != this->primero){
            aux = actual->sig;
            while(aux != this->primero){
                if(aux->user->getAge() > actual->user->getAge()){
                    temp->user = actual->user;
                    actual->user = aux->user;
                    aux->user = temp->user;
                }
                aux = aux->sig;
            }
            actual = actual->sig;
        }
    }
    return; //*Llegados aqui se ordeno todo de menor a mayor
}

#endif