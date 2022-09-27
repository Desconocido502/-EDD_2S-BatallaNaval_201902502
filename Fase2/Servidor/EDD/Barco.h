#include <iostream>

using namespace std;

#ifndef ARTICLEB_H
#define ARTICLEB_H

class Barco{
private:
    string id;
    int precio;
    string nombre;
    string src;
public:
    Barco(string id, int precio, string nombre, string src){
        this->id = id;
        this->precio = precio;
        this->nombre = nombre;
        this->src = src;
    }

    Barco(){ //*Constructor vacio
        this->id = "";
        this->precio = 0;
        this->nombre = "";
        this->src = "";
    }
    
    ~Barco(){ //*Destructor

    }

    void mostrarDatos(){
        cout<<"Id: "<<this->id<<", precio: "<<this->precio<<", nombre: "<<this->nombre<<", src: "<<this->src<<endl;
    }

    string mostrarDatos2(){
        return "Id: " + id +  ",\n nombre: " + nombre + ",\n precio: " + to_string(precio);
    }

    void setId(string id){
        this->id = id;
    }

    string getId(){
        return this->id;
    }

    void setPrecio(int precio){
        this->precio = precio;
    }

    int getPrecio(){
        return this->precio;
    }

    void setNombre(string nombre){
        this->nombre = nombre;
    }

    string getNombre(){
        return this->nombre;
    }

    void setSrc(string src){
        this->src = src;
    }

    string getSrc(){
        return this->src;
    }
};


#endif