#include <iostream>
#include <string>
#include "NodoAvl.h"
#include "generacionImg.h"

using namespace std;

#ifndef AVL_H
#define AVL_H

class AVL{
private:
    NodoAvl* addInternal(NodoBarco*, NodoAvl*); //*Metodo interno de insercion
    int getAltura(NodoAvl*);
    int max(int, int);
    NodoAvl* srl(NodoAvl*);
    NodoAvl* srr(NodoAvl*);
    NodoAvl* drl(NodoAvl*);
    NodoAvl* drr(NodoAvl*);
    bool search(NodoAvl*, string);
    void PreOrdenInterno(NodoAvl*);
    void PostOrdenInterno(NodoAvl*);
    void InOrdenInterno(NodoAvl*);
    string graficadora(NodoAvl*);
public:
    bool repetido;
    NodoAvl* root;
    AVL();
    ~AVL();
    void add(NodoBarco*);
    void PreOrden();
    void PostOrden();
    void InOrden();
    bool search(string);
    void graficar(string);
};

AVL::AVL(){
    this->root = NULL;
    this->repetido = false;
}

AVL::~AVL(){

}

void AVL::add(NodoBarco* nodoBarco){
    this->root = this->addInternal(nodoBarco, this->root);
}

int AVL::getAltura(NodoAvl* temp){
    if (temp != NULL) {
        return temp->alturaN;
    }
    return -1;
}

int AVL::max(int val1, int val2){
    if (val1 > val2) return val1;
    return val2;
}

NodoAvl* AVL::srl(NodoAvl* pivote){
    NodoAvl* aux = pivote->left;
    pivote->left = aux->right;
    aux->right = pivote;
    pivote->alturaN = this->max(this->getAltura(pivote->left), this->getAltura(pivote->right)) + 1;
    aux->alturaN = this->max(this->getAltura(aux->left), pivote->alturaN) + 1;
    return aux;
}

NodoAvl* AVL::srr(NodoAvl* pivote){
    NodoAvl* aux = pivote->right;
    pivote->right = aux->left;
    aux->left = pivote;
    pivote->alturaN = this->max(this->getAltura(pivote->right), this->getAltura(pivote->left)) + 1;
    aux->alturaN = this->max(this->getAltura(aux->right), pivote->alturaN) + 1 ;
    return aux;
}

NodoAvl* AVL::drl(NodoAvl* pivote){
    pivote->left = this->srr(pivote->left);
    return this->srl(pivote);
}

NodoAvl* AVL::drr(NodoAvl* pivote){
    pivote->right = this->srl(pivote->right);
    return this->srr(pivote);
}

NodoAvl* AVL::addInternal(NodoBarco* nodoBarco, NodoAvl* root){
    //cout<<value<<endl;
    if(root == NULL){
        //cout<<"root = null"<<endl;
        root = new NodoAvl(nodoBarco);
    }else{
        //cout<<"root = not null"<<endl;
        //(nodoBarco->getId().compare(root->nodoBarco->getId())) < 0;
        if((nodoBarco->getId().compare(root->nodoBarco->getId())) < 0){
            root->left = this->addInternal(nodoBarco, root->left);
            if(this->getAltura(root->right) - this->getAltura(root->left) == -2){
                //(nodoBarco->getId().compare(root->left->nodoBarco->getId())) < 0;
                if ((nodoBarco->getId().compare(root->left->nodoBarco->getId())) < 0){
                    root = this->srl(root);
                }else{
                    root = this->drl(root);
                }
            }
        }else if(nodoBarco->getId() == root->nodoBarco->getId()){
            this->repetido = true;
            cout<<"NO se puede ingresar valores repetidos al arbol avl"<<endl;
        }else{
            if((nodoBarco->getId().compare(root->nodoBarco->getId())) > 0){
                root->right = this->addInternal(nodoBarco, root->right);
                if(this->getAltura(root->right) - this->getAltura(root->left) == 2){
                    if((nodoBarco->getId().compare(root->right->nodoBarco->getId())) > 0){
                        root = this->srr(root);
                    }else{
                        root = this->drr(root);
                    }
                }
            }
        }
    }
    root->alturaN = this->max(this->getAltura(root->left), this->getAltura(root->right)) + 1;
    return root;
}

bool AVL::search(string indice){
    return this->search(this->root, indice);
}

void AVL::PreOrden(){
    this->PreOrdenInterno(this->root);
}

void AVL::PreOrdenInterno(NodoAvl* root){
    if(root != NULL){
        cout<<root->nodoBarco->getId()<<endl;
        this->PreOrdenInterno(root->left);
        this->PreOrdenInterno(root->right);
    }
}

void AVL::PostOrden(){
    this->PostOrdenInterno(this->root);
}

void AVL::PostOrdenInterno(NodoAvl* root){
    if(root != NULL){
        this->PostOrdenInterno(root->left);
        this->PostOrdenInterno(root->right);
        cout<<root->nodoBarco->getId()<<endl;
    }
}

void AVL::InOrden(){
    this->InOrdenInterno(this->root);
}

void AVL::InOrdenInterno(NodoAvl* root){
    if(root != NULL){
        this->InOrdenInterno(root->left);
        cout<<root->nodoBarco->getId()<<endl;
        this->InOrdenInterno(root->right);
    }
}

bool AVL::search(NodoAvl* pivote, string id){
    if(pivote != NULL){
        if(pivote->nodoBarco->getId() == id){
            return true;
        }
        if(pivote->left != NULL){
            return this->search(pivote->left, id);
        }else{
            return this->search(pivote->right, id);
        }
    }
    return false;
}

// graficar
void AVL::graficar(string nombre)
{
    string cadena = "";
    cadena += "digraph G { \n";
    cadena += "rankdir=TB; \n";
    cadena += "label=\"";
    cadena.append(nombre).append("\"\n");
    cadena.append("fontname=\"Arial Black\"\n").append("fontsize=\"25pt\"\n");
    cadena += "node[color=\"blue\",style=\"rounded,filled\",fillcolor=lightgray, shape=record, fontname=\"Arial\"];\n";
    cadena += this->graficadora(this->root);
    cadena += "} \n";
    //cout << cadena << endl;
    generacionImg(nombre + "_ArbolAVl", cadena);
        //string command = "ArbolB.png";
    string command = "xdg-open " + nombre + "_ArbolAVl.png";
    to_string(system(command.c_str()));
}

string AVL::graficadora(NodoAvl *node)
{
    string cadena = "";

    if ((node->right == NULL) && (node->left == NULL))
    {
        cadena = "\"nodo" + node->nodoBarco->getId() + "\"" + "[label =\"" + node->nodoBarco->barco->mostrarDatos2() + "\"]; \n";
    }
    else
    {
        cadena = "\"nodo" + node->nodoBarco->getId() + "\"" + "[label =\"<C0>|" + node->nodoBarco->barco->mostrarDatos2() + "|<C1> \"]; \n";
    }

    if (node->left != NULL)
    {
        cadena += this->graficadora(node->left) + "\"nodo" + node->nodoBarco->getId() + "\":C0->\"nodo" + node->left->nodoBarco->getId() + "\"\n";
    }

    if (node->right != NULL)
    {
        cadena += this->graficadora(node->right) + "\"nodo" + node->nodoBarco->getId() + "\":C1->\"nodo" + node->right->nodoBarco->getId() + "\"\n";
    }
    return cadena;
}

#endif