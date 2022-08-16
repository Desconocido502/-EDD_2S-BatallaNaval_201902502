#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "lib/nlohmann/json.hpp"
#include "lib/sha256.h"
#include "edd/DoublyLinkedListCircularUser.h"
#include "edd/LinkedListCategoria.h"
#include "edd/ColaTutorial.h"

using namespace std;
using std::stoi;
using json = nlohmann::json;

//*Prototipos de funciones
void menu();
void cargaMasiva();

int opcion = 0;
DoublyLinkedListCircularUser* DoublyLinkedListU = new DoublyLinkedListCircularUser();
LinkedListCategoria* articulos = new LinkedListCategoria();
ColaTutorial* cola_tutorial = new ColaTutorial();

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
    
    //DoublyLinkedListU->drawList();

    cout<< "articulos:" << endl;
    
    for(auto articulo: data.at("articulos")){
        articulos->insert(articulo.at("id"), articulo.at("categoria"), articulo.at("precio"), articulo.at("nombre"), articulo.at("src"));
    }
    articulos->printL();
    articulos->drawList();

    cout<< "Tutorial:" << endl;
    cola_tutorial->enqueue(stoi(data.at("tutorial").at("ancho").get<string>()), stoi(data.at("tutorial").at("alto").get<string>()));

    for(auto movimiento: data.at("tutorial").at("movimientos")){
        cola_tutorial->enqueue(stoi(movimiento.at("x").get<string>()), stoi(movimiento.at("y").get<string>())); //Tremenda conversion //error 302 revisar docu  https://json.nlohmann.me/home/exceptions/#jsonexceptiontype_error301
    }

    cola_tutorial->displayQueue();
    cola_tutorial->drawQueue();
}

/*
    (actual->anterior)->siguiente = actual->siguiente;
    []<->[e]<->[]<->[]

    []->[]<->[]


    (actual->siguiente)->anterior = actual->anterior;
*/