#include <iostream>
#include <string>
#include <algorithm>

#include "AvlTreeNode.h"

using namespace std;

#define SPACE 10

class AvlTree{
public:
    AvlTreeNode* root;

    AvlTree(){
        root = NULL;   
    }

	bool isTreeEmpty(){
		if (root == NULL){
			return true;
		}else{
			return false;
		}
	}

	//* Obtener altura
	int height(AvlTreeNode *r){
		if (r == NULL) return -1;
		else{
			//* calcular la altura de cada subárbol
			int lheight = height(r->left);
			int rheight = height(r->right);

			//* utilice el más grande 
			if (lheight > rheight)
				return (lheight + 1);
			else
				return (rheight + 1);
		}
	}

	//* Obtener el factor de equilibrio del nodo N
	int getBalanceFactor(AvlTreeNode *n){
		if (n == NULL)
			return -1;
		return height(n->left) - height(n->right);
	}

	AvlTreeNode *rightRotate(AvlTreeNode *y){
		AvlTreeNode *x = y->left;
		AvlTreeNode *T2 = x->right;

		//* Realizar la rotación
		x->right = y;
		y->left = T2;

		return x;
	}

	AvlTreeNode *leftRotate(AvlTreeNode *x){
		AvlTreeNode *y = x->right;
		AvlTreeNode *T2 = y->left;

		//* Realizar la rotación
		y->left = x;
		x->right = T2;

		return y;
	}

    AvlTreeNode *insert(AvlTreeNode *r, AvlTreeNode *new_node){
		if (r == NULL){
			r = new_node;
			cout << "Value inserted successfully" << endl;
			return r;
		}
        (new_node->barco->getId().compare(r->barco->getId())) < 0;
		if ((new_node->barco->getId().compare(r->barco->getId())) < 0){
			r->left = insert(r->left, new_node);
		}else if ((new_node->barco->getId().compare(r->barco->getId())) < 0){
			r->right = insert(r->right, new_node);
		}else{
			cout << "No duplicate values allowed!" << endl;
			return r;
		}

		int bf = getBalanceFactor(r);
		//* Left Left Case
        //(new_node->barco->getId().compare(r->left->barco->getId())) < 0; guia
		if (bf > 1 && (new_node->barco->getId().compare(r->left->barco->getId())) < 0)
			return rightRotate(r);

		//* Right Right Case
		if (bf < -1 && (new_node->barco->getId().compare(r->right->barco->getId())) > 0)
			return leftRotate(r);

		//* Left Right Case
		if (bf > 1 && (new_node->barco->getId().compare(r->left->barco->getId())) > 0){
			r->left = leftRotate(r->left);
			return rightRotate(r);
		}

		//* Right Left Case
		if (bf < -1 && (new_node->barco->getId().compare(r->right->barco->getId())) < 0){
			r->right = rightRotate(r->right);
			return leftRotate(r);
		}

		//* devuelve el puntero del nodo (sin cambios) 
		return r;
	}

	AvlTreeNode *minValueNode(AvlTreeNode *node){
		AvlTreeNode *current = node;
		//* bucle hacia abajo para encontrar la hoja más a la izquierda
		while (current->left != NULL){
			current = current->left;
		}
		return current;
	}

	AvlTreeNode *deleteNode(AvlTreeNode *r, string v){
		//* caso base
		if (r == NULL){
			return NULL;
		}
		//* Si la clave a eliminar es menor que la clave de la raíz,
		//* entonces se encuentra en el subárbol de la izquierda
        //(v.compare(r->barco->getId())) < 0;
		else if ((v.compare(r->barco->getId())) < 0){
			r->left = deleteNode(r->left, v);
		}
		//* Si la clave a eliminar es mayor que la clave de la raíz,
		//* entonces se encuentra en el subárbol derecho
		else if ((v.compare(r->barco->getId())) > 0){
			r->right = deleteNode(r->right, v);
		}
		//* si la clave es la misma que la clave de la raíz, 
		//* entonces Este es el nodo que se va a eliminar
		else{
			//* nodo con un solo hijo o sin hijo
			if (r->left == NULL){
				AvlTreeNode *temp = r->right;
				delete r;
				return temp;
			}else if (r->right == NULL){
				AvlTreeNode *temp = r->left;
				delete r;
				return temp;
			}else{
				//* con dos hijos: Obtener el sucesor en orden (el más pequeño
				//* en el subárbol derecho)
				AvlTreeNode *temp = minValueNode(r->right);
				//* Copiar el contenido del sucesor de la orden a este nodo
				r->barco = temp->barco;
				//* Borrar el sucesor de la orden
				r->right = deleteNode(r->right, temp->barco->getId());
				//* deleteNode(r->right, temp->value);
			}
		}

		int bf = getBalanceFactor(r);
		//* Desequilibrio de la izquierda/rotación de la caja o de la derecha
		if (bf == 2 && getBalanceFactor(r->left) >= 0)
			return rightRotate(r);
		//* Desequilibrio izquierdo-derecho/rotación de caja o LR
		else if (bf == 2 && getBalanceFactor(r->left) == -1) //*drl
		{
			r->left = leftRotate(r->left);
			return rightRotate(r);
		}
		//* Desequilibrio derecho/caso o rotación izquierda
		else if (bf == -2 && getBalanceFactor(r->right) <= 0) 
			return leftRotate(r);
		//* Desequilibrio derecha-izquierda/rotación RL
		else if (bf == -2 && getBalanceFactor(r->right) == 1) //*drr
		{
			r->right = rightRotate(r->right);
			return leftRotate(r);
		}

		return r;
	}

	void print2D(AvlTreeNode *r, int space)
	{
		if (r == NULL) // Base case  1
			return;
		space += SPACE;			  // Increase distance between levels   2
		print2D(r->right, space); // Process right child first 3
		cout << endl;
		for (int i = SPACE; i < space; i++) // 5
			cout << " ";					// 5.1
		cout << r->barco->getId()<< "\n";			// 6
		print2D(r->left, space);			// Process left child  7
	}

    void printPreorder(AvlTreeNode *r) //(current node, Left, Right)
	{
		if (r == NULL)
			return;
		/* first print data of node */
		cout << r->barco->getId() << " ";
		/* then recur on left sutree */
		printPreorder(r->left);
		/* now recur on right subtree */
		printPreorder(r->right);
	}

    void printInorder(AvlTreeNode *r) //  (Left, current node, Right)
	{
		if (r == NULL)
			return;
		/* first recur on left child */
		printInorder(r->left);
		/* then print the data of node */
		cout << r->barco->getId() << " ";
		/* now recur on right child */
		printInorder(r->right);
	}

    void printPostorder(AvlTreeNode *r) //(Left, Right, Root)
	{
		if (r == NULL)
			return;
		// first recur on left subtree
		printPostorder(r->left);
		// then recur on right subtree
		printPostorder(r->right);
		// now deal with the node
		cout << r->barco->getId() << " ";
	}

    /* Print nodes at a given level */
	void printGivenLevel(AvlTreeNode *r, int level)
	{
		if (r == NULL)
			return;
		else if (level == 0)
			cout << r->barco->getId() << " ";
		else // level > 0
		{
			printGivenLevel(r->left, level - 1);
			printGivenLevel(r->right, level - 1);
		}
	}

    void printLevelOrderBFS(AvlTreeNode *r)
	{
		int h = height(r);
		for (int i = 0; i <= h; i++)
			printGivenLevel(r, i);
	}

	AvlTreeNode *iterativeSearch(string v){
		if (root == NULL){
			return root;
		}else{
			AvlTreeNode *temp = root;
			while (temp != NULL){
				if (v == temp->barco->getId()){
					return temp;
				}else if ((v.compare(temp->barco->getId())) < 0){
					temp = temp->left;
				}else{
					temp = temp->right;
				}
			}
			return NULL;
		}
	}

    AvlTreeNode *recursiveSearch(AvlTreeNode *r, string val)
	{
		if (r == NULL || r->barco->getId() == val)
			return r;

		else if ((val.compare(r->barco->getId())) < 0)
			return recursiveSearch(r->left, val);

		else
			return recursiveSearch(r->right, val);
	}

    //NOs quedamos aqui, sigue la parte de graficar

    ~AvlTree(){

    }
};


