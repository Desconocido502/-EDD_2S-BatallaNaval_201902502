#include <iostream>
#include "EDD/BTree.h"
#include "EDD/NodoUsuario.h"


using namespace std;

//Definicion de funciones
void hello();

void hello(){
    cout<<"Hola mundo!!!"<<endl;
}

int main(){
    //hello();
    BTree* t = new BTree(2);
    NodoUsuario* nodo_usuario = new NodoUsuario("Carlos", "edd123", 550, 22);
    NodoUsuario* nodo_usuario1 = new NodoUsuario("Folagor", "alfal475", 700, 29);
    NodoUsuario* nodo_usuario2 = new NodoUsuario("Planton", "cam78dad", 50, 20);
    NodoUsuario* nodo_usuario3 = new NodoUsuario("Pikachu", "beliz5a4", 59, 18);
    NodoUsuario* nodo_usuario4 = new NodoUsuario("Naruto", "jfagaga16a", 80, 19);
    NodoUsuario* nodo_usuario5 = new NodoUsuario("Goku", "agga516r", 56, 20);
    NodoUsuario* nodo_usuario6 = new NodoUsuario("Homero", "agfa84aafg8", 86, 45);
    t->insert("Carlos", nodo_usuario);
    t->insert("Folagor", nodo_usuario1);
    t->insert("Planton", nodo_usuario2);
    t->insert("Pikachu", nodo_usuario3);
    t->insert("Naruto", nodo_usuario4);
    t->insert("Goku", nodo_usuario5);
    t->insert("HOmero", nodo_usuario6);
    t->remove("Naruto");
    t->traverse();
    t->DrawBTree();

    return 0;
}