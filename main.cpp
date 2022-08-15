#include <iostream>
#include "menu.cpp"
#include "edd/LinkedListCategoria.h"

using namespace std;

int main(int argc, char const *argv[]){
    //cout<<"Inicio del proyecto"<<endl;
    // LinkedListBarco* ltsbarcos = new LinkedListBarco();
    // ltsbarcos->insertAtEnd(47, 150,"La perla negra","sprites/barcos");
    // ltsbarcos->insertAtEnd(50, 570,"La grajilla","sprites/barcos");
    // ltsbarcos->insertAtEnd(55, 160,"La morsa","sprites/barcos");
    // ltsbarcos->insertAtEnd(80, 450,"La delicada dama","sprites/barcos");
    // ltsbarcos->displayList();
    LinkedListCategoria* ltsCategoria = new LinkedListCategoria();
    ltsCategoria->insert(47,"epico",750,"La perla negra", "sprites/barcos");
    ltsCategoria->insert(50,"epico",570,"La grajilla","sprites/barcos");
    ltsCategoria->insert(55,"normal",160,"La morsa","sprites/barcos");
    ltsCategoria->insert(80,"raro",450,"La delicada dama","sprites/barcos");
    ltsCategoria->printL();
    //menu();
    return 0;
}
