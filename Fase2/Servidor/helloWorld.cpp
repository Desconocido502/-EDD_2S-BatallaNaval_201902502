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
    //t->insert("Carlos", nodo_usuario);
    t->insert("Folagor", nodo_usuario1);
    t->insert("Planton", nodo_usuario2);
    t->insert("Pikachu", nodo_usuario3);
    t->insert("Naruto", nodo_usuario4);
    t->insert("Goku", nodo_usuario5);
    t->insert("Rubius", new NodoUsuario("Rubius", "agga516r", 56, 20));
    t->insert("KingKong", new NodoUsuario("KingKong", "agga516r", 56, 20));
    t->insert("Kratos", new NodoUsuario("Kratos", "agga516r", 56, 20));
    t->insert("Homero", new NodoUsuario("Homero", "agga516r", 56, 20));
    t->insert("Mario Bros", new NodoUsuario("Mario Bros", "agga516r", 56, 20));
    t->insert("Meteoro", new NodoUsuario("Meteoro", "agga516r", 56, 20));
    t->insert("Homer el Homer", new NodoUsuario("Homer el Homer", "agga516r", 56, 20));
    t->insert("Candy", new NodoUsuario("Candy", "agga516r", 56, 20));
    t->insert("Ash", new NodoUsuario("Ash", "agga516r", 56, 20));
    t->insert("Kitty", new NodoUsuario("Kitty", "agga516r", 56, 20));
    t->traverse();
    //t->search("Pikachu");
    
    t->DrawBTree();

    return 0;
}