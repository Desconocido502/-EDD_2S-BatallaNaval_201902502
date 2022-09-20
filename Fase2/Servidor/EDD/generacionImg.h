
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
        //*dot -Tsvg ListUsers.dot -o ListUsers.svg
        string command = "dot -Tsvg " + nombreEstructura + ".dot -o " + nombreEstructura + ".svg";
        system(command.c_str());
    }catch(const std::exception& e){
        cout<<"No se pudo crear la imagen :("<<endl;
    }
}

void moveFile(string nombreEstructura){
    string command1 = "cd .. && move Proyecto_F1\\" + nombreEstructura + ".dot " + "Proyecto_F1/Extras";
    system(command1.c_str());
    cout<<command1<<endl;
    string command2 = "cd .. && move Proyecto_F1\\" + nombreEstructura + ".svg " + "Proyecto_F1/Extras";
    cout<<command2<<endl;
    system(command2.c_str());
    //*move Proyecto_F1\ColaTutorial.png Proyecto_F1/Extras
}

void openImg(string nombreEstructura){
    //*cd Extras && ListaPilas.png
    string command = "cd Extras && " + nombreEstructura + ".svg";
    //string command = nombreEstructura + ".png";
    system(command.c_str());
}

//*string command = "cd Extras && ListaPilas.png";
//*system(command.c_str());
//*move Proyecto_F1\ColaTutorial.png Proyecto_F1/Extras

#endif