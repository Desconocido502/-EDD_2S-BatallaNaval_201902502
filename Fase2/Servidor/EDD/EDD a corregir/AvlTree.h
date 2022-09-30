#include <iostream>
#include <string>
#include <algorithm>

#include "AvlTreeNode.h"

using namespace std;

#define SPACE 10

#ifndef AVLTREE_H
#define AVLTREE_H

class AvlTree
{
public:
	AvlTreeNode *root;

	AvlTree();
	bool isTreeEmpty();

	//* Obtener altura
	int height(AvlTreeNode *r);

	//* Obtener el factor de equilibrio del nodo N
	int getBalanceFactor(AvlTreeNode *n);

	AvlTreeNode *rightRotate(AvlTreeNode *y);

	AvlTreeNode *leftRotate(AvlTreeNode *x);

	AvlTreeNode *insert(AvlTreeNode *r, AvlTreeNode *new_node);

	AvlTreeNode *minValueNode(AvlTreeNode *node);

	AvlTreeNode *deleteNode(AvlTreeNode *r, string v);

	void print2D(AvlTreeNode *r, int space);

	//(current node, Left, Right)
	void printPreorder(AvlTreeNode *r);

	//  (Left, current node, Right)
	void printInorder(AvlTreeNode *r);

	//(Left, Right, Root)
	void printPostorder(AvlTreeNode *r);

	/* Print nodes at a given level */
	void printGivenLevel(AvlTreeNode *r, int level);

	void printLevelOrderBFS(AvlTreeNode *r);

	AvlTreeNode *iterativeSearch(string v);

	AvlTreeNode *recursiveSearch(AvlTreeNode *r, string val);

	// graficar
	void graficar();

private:
	string graficadora(AvlTreeNode *node);
};


#endif