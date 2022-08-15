#include <iostream>

using namespace std;

#ifndef ARTICLEB_H
#define ARTICLEB_H

class ArticleB{
private:
    int id;
    int precio;
    string nombre;
    string src;
public:
    ArticleB(int id, int precio, string nombre, string src){
        this->id = id;
        this->precio = precio;
        this->nombre = nombre;
        this->src = src;
    }

    ArticleB(){ //*Constructor vacio
        this->id = 0;
        this->precio = 0;
        this->nombre = "";
        this->src = "";
    }
    
    ~ArticleB(){ //*Destructor

    }

    void mostrarDatos(){
        cout<<"Id: "<<this->id<<", precio: "<<this->precio<<", nombre: "<<this->nombre<<", src: "<<this->src<<endl;
    }

    int getId(){
        return this->id;
    }

    int getPrecio(){
        return this->precio;
    }

    string getNombre(){
        return this->nombre;
    }

    string getSrc(){
        return this->src;
    }
};


#endif