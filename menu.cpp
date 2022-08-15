#include <iostream>
#include <fstream>
#include "edd/DoublyLinkedListCircularUser.h"
#include "lib/nlohmann/json.hpp"
#include "lib/sha256.h"

using namespace std;
using json = nlohmann::json;

//*Prototipos de funciones
void menu();
void cargaMasiva();

int opcion = 0;
DoublyLinkedListCircularUser* DoublyLinkedListU = new DoublyLinkedListCircularUser();

void menu(){
    
    do{
        cout<<"\t.:Menu:."<<endl;
        cout<<"1. Carga Masiva"<<endl;
        cout<<"2. Registrar Usuario"<<endl;
        cout<<"3. Login"<<endl;
        cout<<"4. Reportes"<<endl;
        cout<<"5. Salir del juego"<<endl;
        cout<<"Eliga una opcion: ";
        cin>>opcion;

        switch (opcion){
        case 1:
            cout<<"Vamos a realizar una carga masiva..."<<endl;
            cargaMasiva();
            break;
        case 2:
            cout<<"Se esta registrando un usuario"<<endl;
            break;
        case 3:
            cout<<"Se esta logueando un user"<<endl;
            break;
        case 4:
            cout<<"Se generan los reportes aqui"<<endl;
            break;
        case 5:
            cout<<"Gracias por jugar, vuelva pronto!!!"<<endl;
            break;
        default:
            cout<<"La opcion elegida no exista, digite correctamente!!"<<endl;
            break;
        }

    }while(opcion != 5);

}


void cargaMasiva(){
    
    ifstream file("./json/data.json", ios::in);

    if(!file){
        cout<<"Hubo un problema al leer el archivo"<<endl;
    }
    json data;
    file >> data;
    file.close();

    cout<< "Usuarios:" << endl;

    for(auto usuario: data.at("usuarios")){
        DoublyLinkedListU->insertAtEnd(usuario.at("nick"), SHA256::cifrar(usuario.at("password")), usuario.at("monedas") , usuario.at("edad"));
    }
    DoublyLinkedListU->displayListSE();
    DoublyLinkedListU->drawList();

    //cout<< "articulos:" << endl;

    // VariadicTable<int, std::string, int, std::string, std::string> articulos({"id","categoria","precio","nombre","src"});
    // for(auto articulo: data.at("articulos")){
    //     articulos.addRow(articulo.at("id"), articulo.at("categoria"), articulo.at("precio"), articulo.at("nombre"), articulo.at("src"));
    //     // cout<<"id: "<<articulo.at("id")<<", ";
    //     // cout<<"categoria: "<<articulo.at("categoria")<<", ";
    //     // cout<<"precio: "<<articulo.at("precio")<<", ";
    //     // cout<<"nombre: "<<articulo.at("nombre")<<", ";
    //     // cout<<"src: "<<articulo.at("src")<<endl;
    // }
    // articulos.print(cout);
}