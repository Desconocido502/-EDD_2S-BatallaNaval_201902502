#include <iostream>
#include <string>

using namespace std;

#ifndef REPLACE_H
#define REPLACE_H

//*Prototipos de funciones
string replace(string, string, string);

//*Reemplaza todas las coincidencias
/*
*s: cadena a modificar
*x: caracter a remover
*y: nuevo caracter
*/
string replace(string s, string x, string y){
    size_t pos = 0;
    while(pos += y.length()){
        pos = s.find(x, pos);
        if(pos == std::string::npos){
            break;
        }
        s.replace(pos, x.length(), y);
    }
    return s;
}

#endif