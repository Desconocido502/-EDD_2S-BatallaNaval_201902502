// Include header file
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <sstream>
#include "NodoUsuario.h"

using namespace std;
string get_uuid();

//Se hara una clase que podra ir dentro de las llaves para no complicarse la vida
class Contenedor{
public:
    string idUnico;
    NodoUsuario* nodo_usuario;

    Contenedor(string idUnico, NodoUsuario* nodo_usuario){
        this->idUnico = idUnico;
        this->nodo_usuario = nodo_usuario;
    }

    Contenedor(){
        this->idUnico = "";
        this->nodo_usuario = nullptr;
    }

    ~Contenedor(){} //DESTRUCTOR

    string getIdUnico(){
        return this->idUnico;
    }

    NodoUsuario* getNodoUsuario(){
        return this->nodo_usuario;
    }

    void setIdUnico(string idUnico){
        this->idUnico = idUnico;
    }

    void setNodoUsuario(NodoUsuario* nodo_usuario){
        this->nodo_usuario = nodo_usuario;
    }

    //metodo de mostrar datos

};

class BTreeNode{

private:
    int count;
    string buff;
    string id = "";
public:
    std::vector<Contenedor> keys;          //llave de nodos
    int MinDeg;                        //Grado minimo del nodo B-Tree
    std::vector<BTreeNode *> children; //Nodos hijo
    int num;                           //NUmero de llaves del nodo
    bool isLeaf;                       //Verdadero cuando el nodo es una hoja

    //Constructor
    BTreeNode(int deg, bool isLeaf){
        this->MinDeg = deg;
        this->isLeaf = isLeaf;
        this->keys = std::vector<Contenedor>(2 * this->MinDeg - 1);
        this->children = std::vector<BTreeNode *>(2 * this->MinDeg);
        this->num = 0;
        this->id = get_uuid();
    }

    // Find the first location index equal to or greater than key
    int findKey(Contenedor key){
        int idx = 0;
         while (idx < num && keys[idx].getIdUnico() < key.getIdUnico())
        {
            ++idx;
        }
        return idx;
    }

    void remove(Contenedor key){
        int idx = findKey(key);
        if(idx < num && keys[idx].getIdUnico() == key.getIdUnico()){
            //Find key
            if(isLeaf){
                //key in leaf node
                removeFromLeaf(idx);
            }else{
                //key in leaf node
                removeFromNonLeaf(idx);
            }
        }else{
            if(isLeaf){
                // If the node is a leaf node, then the node is not in the B tree
                //printf("The key %d is does not exist in the tree\n", key.getIdUnico());
                cout<<"The key" + key.getIdUnico()  +"is does not exist in the tree"<<endl;
                return;
            }
            // Otherwise, the key to be deleted exists in the subtree with the node as the root
            // This flag indicates whether the key exists in the subtree whose root is the last child of the node
            // When idx is equal to num, the whole node is compared, and flag is true
            bool flag = idx == num;
            if(children[idx]->num < MinDeg){
                //WHen the child node of the node is not full, fill it first
                fill(idx);
            }
            // If the last child node has been merged, it must have been merged with the previous child node, so we recurse on the (idx-1) child node.
            // Otherwise, we recurse to the (idx) child node, which now has at least the keys of the minimum degree
            if(flag && idx > num){
                children[idx - 1]->remove(key);
            }else{
                children[idx]->remove(key);
            }
        }
    }

    void removeFromLeaf(int idx){
        //Shift from idx
        for(int i = idx + 1; i < num; i++){
            keys[i - 1] = keys[i];
        }
        num--;
    }

    void removeFromNonLeaf(int idx){
        Contenedor key = keys[idx];
        // If the subtree before key (children[idx]) has at least t keys
        // Then find the precursor 'pred' of key in the subtree with children[idx] as the root
        // Replace key with 'pred', recursively delete pred in children[idx]
        if(children[idx]->num >= MinDeg){
            Contenedor pred = getPred(idx);
            keys[idx] = pred;
            children[idx]->remove(pred);
        }else if(children[idx + 1]->num >= MinDeg){
            Contenedor succ = getSucc(idx);
            keys[idx] = succ;
            children[idx + 1]->remove(succ);
        }else{
            // If the number of keys of children[idx] and children[idx+1] is less than MinDeg
            // Then key and children[idx+1] are combined into children[idx]
            // Now children[idx] contains the 2t-1 key
            // Release children[idx+1], recursively delete the key in children[idx]
            merge(idx);
            children[idx]->remove(key);
        }
    }

    Contenedor getPred(int idx){
        // The predecessor node is the node that always finds the rightmost node from the left subtree
        // Move to the rightmost node until you reach the leaf node
        BTreeNode* cur = children[idx];
        while (!cur->isLeaf){
            cur = cur->children[cur->num];
        }
        return cur->keys[cur->num -1];
    }

    Contenedor getSucc(int idx){
        // Subsequent nodes are found from the right subtree all the way to the left
        // Continue to move the leftmost node from children[idx+1] until it reaches the leaf node
        BTreeNode* cur = children[idx + 1];
        while(!cur->isLeaf){
            cur = cur->children[0];
        }
        return cur->keys[0];
    }

    // Fill children[idx] with less than MinDeg keys
    void fill(int idx){
        // If the previous child node has multiple MinDeg-1 keys, borrow from them
        if(idx != 0 && children[idx -1]->num >= MinDeg){
            borrowFromPrev(idx);
        }else if(idx != num && children[idx + 1]->num >= MinDeg){
            borrowFromNext(idx);
        }else{
            // Merge children[idx] and its brothers
            // If children[idx] is the last child node
            // Then merge it with the previous child node or merge it with its next sibling
            if(idx != num){
                merge(idx);
            }else{
                merge(idx - 1);
            }   
        }
    }

    // Borrow a key from children[idx-1] and insert it into children[idx]
    void borrowFromPrev(int idx){
        BTreeNode* child = children[idx];
        BTreeNode* sibling = children[idx -1];
        // The last key from children[idx-1] overflows to the parent node
        // The key[idx-1] underflow from the parent node is inserted as the first key in children[idx]
        // Therefore, sibling decreases by one and children increases by one
        for(int i = child->num - 1; i >= 0; --i){
            // children[idx] move forward
            child->keys[i + 1] = child->keys[i];
        }
        if(!child->isLeaf){
            // Move children[idx] forward when they are not leaf nodes
            for(int i = child->num; i >= 0; --i){
                child->children[i+1] = child->children[i];
            }
        }

        // Set the first key of the child node to the keys of the current node [idx-1]
        child->keys[0] = keys[idx - 1];
        if(!child->isLeaf){
            // Take the last child of sibling as the first child of children[idx]
            child->children[0] = sibling->children[sibling->num];
        }
        //Move the last key of sibling up to the last key of the current node
        keys[idx - 1] = sibling->keys[sibling->num - 1];
        child->num += 1;
        sibling->num -= 1;
    }

    // Symmetric with borowfromprev
    void borrowFromNext(int idx){
        BTreeNode* child = children[idx];
        BTreeNode* sibling  = children[idx + 1];
        child->keys[child->num] = keys[idx];
        if(!child->isLeaf){
            child->children[child->num + 1] = sibling->children[0];
        }
        keys[idx] = sibling->keys[0];
        for(int i=1; i < sibling->num; ++i){
            sibling->keys[i - 1] = sibling->keys[i];
        }
        if(!sibling->isLeaf){
            for(int i = 1; i <= sibling->num; ++i){
                sibling->children[i - 1] = sibling->children[i];
            }
        }
        child->num += 1;
        sibling->num -= 1;
    }

    //Merge children[idx +1] into children[idx]
    void merge(int idx){
        BTreeNode* child = children[idx];
        BTreeNode* sibling = children[idx + 1];
        // Insert the last key of the current node into the MinDeg-1 position of the child node
        child->keys[MinDeg - 1] = keys[idx];
        // keys: children[idx+1] copy to children[idx]
        for(int i = 0; i < sibling->num; ++i){
            child->keys[i + MinDeg] = sibling->keys[i];
        }
        // children: children[idx+1] copy to children[idx]
        if(!child->isLeaf){
            for(int i = 0; i <= sibling->num; ++i){
                child->children[i + MinDeg] = sibling->children[i];
            }
        }
        // Move keys forward, not gap caused by moving keys[idx] to children[idx]
        for(int i = idx + 1; i < num ;  ++i){
            keys[i - 1 ] = keys[i];
        }
        // Move the corresponding child node forward
        for(int i = idx + 2; i <= num; ++i){
            children[i - 1] = children[i];
        }
        child->num += sibling->num + 1;
        num--;
    }

    void insertNotFull(Contenedor key){
        int i = num -1;
        // Initialize i as the rightmost index
        if(isLeaf){
            // When it is a leaf node
            // Find the location where the new key should be inserted
            while(i >= 0 && keys[i].getIdUnico() > key.getIdUnico()){
                keys[i + 1] = keys[i];
                //keys backward shift
                i--;
            }
            keys[i + 1] = key;
            num = num + 1;
        }else{
            // Find the child node location that should be inserted
            while (i >= 0 && keys[i].getIdUnico() > key.getIdUnico()){
                i--;
            }
            if(children[i + 1]->num == 2 * MinDeg - 1){
                // When the child node is full
                splitChild(i + 1, children[i + 1]);
                // After splitting, the key in the middle of the child node moves up, and the child node splits into two
                if(keys[i + 1].getIdUnico() < key.getIdUnico()){
                    i++;
                }
            }
            children[i + 1]->insertNotFull(key);
        }
    }

    void splitChild(int i, BTreeNode *&y){
        // First, create a node to hold the keys of MinDeg-1 of y
        BTreeNode *z = new BTreeNode(y->MinDeg, y->isLeaf);
        z->num = MinDeg - 1;
        //Pass te properties of y to z
        for(int j = 0; j < MinDeg - 1; j++){
            z->keys[j] = y->keys[j + MinDeg];
        }
        if(!y->isLeaf){
            for(int j = 0; j < MinDeg; j++){
                z->children[j] = y->children[j + MinDeg];
            }
        }
        y->num = MinDeg - 1;
        // Insert a new child into the child
        for(int j = num; j>= i + 1; j--){
            children[j + 1] = children[j];
        }
        children[i + 1] = z;
        // Move a key in y to this node
        for(int j = num - 1; j >= 1; j--){
            keys[j + 1] = keys[j];
        }
        keys[i] = y->keys[MinDeg - 1];
        num = num + 1;
    }

    void traverse(){
        int i;
        for(i = 0; i < num; i++){
            if(!isLeaf){
                children[i]->traverse();
            }
            std::cout<<" "+ keys[i].getIdUnico() + " "<<std::endl;
        }
        if(!isLeaf){
            children[i]->traverse();
        }
    }

    BTreeNode* search(string key){
        int i = 0;
        while(i <= num && key > keys[i].getIdUnico()){
            i++;
        }
        if(keys[i].getIdUnico() == key){
            return this;
        }
        if(isLeaf){
            return nullptr;
        }
        return children[i]->search(key);
    }
private:
    void Writer()
    {
        this->buff = "";
    }
    void Counter()
    {
        this->count = 0;
    }
    int add()
    {
        return this->count++;
    }
    void write(std::string str)
    {
        this->buff += str;
    }
    void writeln(std::string str)
    {
        this->write(str + "\n");
    }
public:
    std::string toDot()
    {
        Writer();
        Counter();
        return "digraph g {\n node [shape = record,height=.1];\n" + this->walk() + "\n" + "}";
    }
private:
    std::string getDotName(){
        return "\"Nodo" + (this->id) + "\"";
    }

    std::string walk(){
        string cadena = "";

        cadena += (getDotName());
        cadena += ("[label=\"<P0>");
        for(int i = 0; i < num; i++){
            cadena += ("|" + this->keys[i].getNodoUsuario()->getUsuario()->mostrarDatos2());
            cadena += ("|<P" + std::to_string((i + 1)) + ">");
        }
        cadena += ("\"];\n");
        for(int i = 0; i <= num; i++){
            if(children[i] != nullptr){
                cadena += (children[i]->walk());
                cadena += (getDotName() + ":P" + std::to_string(i) + " -> " + children[i]->getDotName() + ";\n");
            }
        }
        return cadena;
    }

};


//Genera un codigo casi irrepetible
string get_uuid()
{
    static random_device dev;
    static mt19937 rng(dev());

    uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};

    string res;
    for (int i = 0; i < 16; i++)
    {
        if (dash[i])
            res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
}