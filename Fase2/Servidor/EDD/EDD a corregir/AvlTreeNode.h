#include <iostream>
#include "NodoBarco.h"

using namespace std;

#ifndef AVLTREENODE_H
#define AVLTREENODE_H

class AvlTreeNode{
public:
    NodoBarco* nodoBarco;
    AvlTreeNode* left;
    AvlTreeNode* right;

    AvlTreeNode(NodoBarco* nodoBarco){
        this->nodoBarco = nodoBarco;
        left = NULL;
        right = NULL;
    }

    AvlTreeNode(){
        this->nodoBarco = NULL;
        left = right = NULL;
    }

};

#endif