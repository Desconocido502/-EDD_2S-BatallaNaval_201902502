#include <iostream>
#include "EDD/BTree.h"
#include "EDD/NodoUsuario.h"
#include "EDD/AVL.h"

using namespace std;

//Definicion de funciones
void hello();

void hello(){
    cout<<"Hola mundo!!!"<<endl;
}
   
int main(){
    AVL* avl = new AVL();
    avl->add(new NodoBarco("3f0e30e5-565b-48f6-b877-a4a27ab14a4f", 8817, "Colobus guerza", "/usr/libe/skins/nombre", "Granite Surfaces"));
    avl->add(new NodoBarco("b1f8da3b-c87b-46bf-80a6-2bcf8af22d35", 998, "Crax sp.", "/usr/libe/skins/nombre", "Roofing (Metal)"));
    avl->add(new NodoBarco("a989148c-65c2-4a53-a09c-05dc5288b53d", 92, "Lepus townsendii", "/usr/libe/skins/nombre", "Waterproofing & Caulking"));
    avl->add(new NodoBarco("c3d9d91b-da3e-4f03-aa93-0fbec920be75", 13211, "Lemur catta", "/usr/libe/skins/nombre", "HVAC"));
    avl->add(new NodoBarco("ef134d34-d904-47e2-8198-9a6eae0bc759", 158, "Manouria emys", "/usr/libe/skins/nombre", "Site Furnishings"));
    avl->add(new NodoBarco("6ae94616-45e2-498f-8a40-e54b678e09ce", 8, "Lycosa godeffroyi", "/usr/libe/skins/nombre", "Waterproofing & Caulking"));
    avl->add(new NodoBarco("2bae79d6-9054-42e3-96c8-135f1e546aab", 8340, "Macropus rufus", "/usr/libe/skins/nombre", "Site Furnishings"));
    avl->add(new NodoBarco("730607bb-59d5-4c7a-92ec-8e25ec213c74", 7294, "Hystrix cristata", "/usr/libe/skins/nombre", "Doors, Frames & Hardware"));
    avl->add(new NodoBarco("2f591fc3-c533-4d92-a676-29fd30633510", 95808, "Bubalus arnee", "/usr/libe/skins/nombre", "Roofing (Metal)"));
    avl->graficar();
    return 0;
}


/*

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







    AvlTree* avl = new AvlTree();
    AvlTreeNode* node = new AvlTreeNode();

    avl->root = avl->insert(avl->root, new AvlTreeNode(new NodoBarco("3f0e30e5-565b-48f6-b877-a4a27ab14a4f", 8817, "Colobus guerza", "/usr/libe/skins/nombre", "Granite Surfaces")));
    avl->root = avl->insert(avl->root, new AvlTreeNode(new NodoBarco("b1f8da3b-c87b-46bf-80a6-2bcf8af22d35", 998, "Crax sp.", "/usr/libe/skins/nombre", "Roofing (Metal)")));
    avl->root = avl->insert(avl->root, new AvlTreeNode(new NodoBarco("a989148c-65c2-4a53-a09c-05dc5288b53d", 92, "Lepus townsendii", "/usr/libe/skins/nombre", "Waterproofing & Caulking")));
    avl->root = avl->insert(avl->root, new AvlTreeNode(new NodoBarco("c3d9d91b-da3e-4f03-aa93-0fbec920be75", 13211, "Lemur catta", "/usr/libe/skins/nombre", "HVAC")));
    avl->root = avl->insert(avl->root, new AvlTreeNode(new NodoBarco("ef134d34-d904-47e2-8198-9a6eae0bc759", 158, "Manouria emys", "/usr/libe/skins/nombre", "Site Furnishings")));
    avl->root = avl->insert(avl->root, new AvlTreeNode(new NodoBarco("6ae94616-45e2-498f-8a40-e54b678e09ce", 8, "Lycosa godeffroyi", "/usr/libe/skins/nombre", "Waterproofing & Caulking")));
    avl->root = avl->insert(avl->root, new AvlTreeNode(new NodoBarco("2bae79d6-9054-42e3-96c8-135f1e546aab", 8340, "Macropus rufus", "/usr/libe/skins/nombre", "Site Furnishings")));
    avl->root = avl->insert(avl->root, new AvlTreeNode(new NodoBarco("730607bb-59d5-4c7a-92ec-8e25ec213c74", 7294, "Hystrix cristata", "/usr/libe/skins/nombre", "Doors, Frames & Hardware")));
    avl->root = avl->insert(avl->root, new AvlTreeNode(new NodoBarco("2f591fc3-c533-4d92-a676-29fd30633510", 95808, "Bubalus arnee", "/usr/libe/skins/nombre", "Roofing (Metal)")));

    avl->print2D(avl->root, 10);
    cout<<endl;
    avl->graficar();
*/