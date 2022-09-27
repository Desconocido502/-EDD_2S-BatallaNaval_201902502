#include <iostream>
#include "NodoBarco.h"


using namespace std;

class AvlTreeNode{
public:
    NodoBarco* barco;
    AvlTreeNode* left;
    AvlTreeNode* right;

    AvlTreeNode(NodoBarco* barco){
        this->barco = barco;
        left = NULL;
        right = NULL;
    }

    AvlTreeNode(){
        this->barco = NULL;
        left = right = NULL;
    }

};