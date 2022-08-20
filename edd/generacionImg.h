
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#ifndef GENERACIONIMG_H
#define GENERACIONIMG_H

//*Prototipos de funciones
void generacionImg(string, string);
void moveFile(string);
void openImg(string);

void generacionImg(string nombreEstructura, string cadena){
    try{
        ofstream file;
        file.open(nombreEstructura + ".dot", std::ios::out);

        if(file.fail()){
            exit(1);
        }
        file << cadena;
        file.close();
        string command = "dot -Tpng " + nombreEstructura + ".dot -o " + nombreEstructura + ".png";
        system(command.c_str());
        moveFile(nombreEstructura);
    }catch(const std::exception& e){
        cout<<"No se pudo crear la imagen :("<<endl;
    }
}

void moveFile(string nombreEstructura){
    string command1 = "move Proyecto_F1\\" + nombreEstructura + ".dot " + "Proyecto_F1/Extras";
    system(command1.c_str());
    string command2 = "move Proyecto_F1\\" + nombreEstructura + ".png " + "Proyecto_F1/Extras";
    system(command2.c_str());
    //*move Proyecto_F1\ColaTutorial.png Proyecto_F1/Extras
}

void openImg(string nombreEstructura){
    //*cd Extras && ListaPilas.png
    string command = "cd Extras && " + nombreEstructura + ".png";
    system(command.c_str());
}

//*string command = "cd Extras && ListaPilas.png";
//*system(command.c_str());
//*move Proyecto_F1\ColaTutorial.png Proyecto_F1/Extras

#endif