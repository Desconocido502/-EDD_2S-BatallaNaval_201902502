
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifndef GENERACIONIMG_H
#define GENERACIONIMG_H

//*Prototipos de funciones
void generacionImg(string, string);

void generacionImg(string nombrEstructura, string cadena){
    try{
        ofstream file;
        file.open(nombrEstructura + ".dot", std::ios::out);

        if(file.fail()){
            exit(1);
        }
        file << cadena;
        file.close();
        string command = "dot -Tpng " + nombrEstructura + ".dot -o " + nombrEstructura + ".png";
        system(command.c_str());
    }catch(const std::exception& e){
        cout<<"No se pudo crear la imagen :("<<endl;
    }
}


#endif