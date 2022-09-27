// Include header file
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "BTreeNode.h"
#include "generacionImg.h"

using namespace std;

class BTree{
public:
    BTreeNode *root;
    int MinDeg;
    // Constructor
    BTree(int deg){
        this->root = nullptr;
        this->MinDeg = deg;
    }

    BTree(){
        this->root = nullptr;
        this->MinDeg = 0;
    }

    void traverse(){
        if(root != nullptr){
            root->traverse();
        }   
    }

    string DrawBTree(){
        //std::cout << "\n" + root->toDot() << std::endl;
        generacionImg("ArbolB", root->toDot());
        string command = "xdg-open ArbolB.png";
        //string command = "ArbolB.png";
        string x = to_string(system(command.c_str()));
        cout<<"x:"<<x<<endl;
        return x;
    }


    // Function to find key
    BTreeNode *search(string key){
       
        return ((root == nullptr) ? nullptr : root->search(key));
    }

    void insert(string idUnico, NodoUsuario *nodo_usuario){
        Contenedor key;
        key.setIdUnico(idUnico);
        key.setNodoUsuario(nodo_usuario);
        if (root == nullptr){
            root = new BTreeNode(MinDeg, true);
            root->keys[0] = key;
            root->num = 1;
        }else{
            // When the root node is full, the tree will grow high
            if (root->num == 2 * MinDeg - 1){
                BTreeNode *s = new BTreeNode(MinDeg, false);
                // The old root node becomes a child of the new root node
                s->children[0] = root;
                // Separate the old root node and give a key to the new node
                s->splitChild(0, root);
                // The new root node has 2 child nodes. Move the old one over there
                int i = 0;
                if ((s->keys[0].getIdUnico().compare(key.getIdUnico())) < 0){
                    i++;
                }
                s->children[i]->insertNotFull(key);
                root = s;
            }else{
                root->insertNotFull(key);
            }
        }
    }

    void remove(string key){
        if (root == nullptr)
        {
            std::cout << "The tree is empty" << std::endl;
            return;
        }
        Contenedor aux;
        aux.setIdUnico(key);
        aux.setNodoUsuario(new NodoUsuario("","",0,0));

        root->remove(aux);
        if (root->num == 0){
            // If the root node has 0 keys
            // If it has a child, its first child is taken as the new root,
            // Otherwise, set the root node to null
            if (root->isLeaf){
                root = nullptr;
            }else{
                root = root->children[0];
                cout<<root<<endl;
            }
        }
    }

    //Sirve como complemento del metodo search
    Contenedor valueFound(BTreeNode* aux, string valueToBeSearch){
        Contenedor auxContenedor;
        auxContenedor.setIdUnico("NULL");
        if (aux == nullptr) return auxContenedor;
        for(int i =0; i < aux->num; i++){
            if(aux->keys[i].getIdUnico() == valueToBeSearch){
                return aux->keys[i];
            }
        }
        return auxContenedor;
    } 


    ~BTree(){

    }
};
