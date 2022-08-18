#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>

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
void registrarUsuario();
void login();
void subMenuUser(NodoUsuario*);
void editarInfoUser(NodoUsuario*);
int eliminarUser(string);

//*EDD y variables a usar
int opcion = 0, edad = 0, monedas = 0;
string nick = "", password = "";
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
            registrarUsuario();
            break;
        case 3:
            cout<<"Se esta logueando un user"<<endl;
            login();
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

void registrarUsuario(){
    char nick_l[250];
    char password_l[250];
    int edad = 0, monedas = 0;
    cout<<"Bienvenido al registro de usuarios, llene la siguiente informacion..."<<endl;
    cin.ignore();
    cout<<"Ingrese su nombre de jugador: ";
    cin.getline(nick_l, 250, '\n');
    cin.ignore();
    cout<<"Ingrese su password: ";
    cin.getline(password_l, 250, '\n');
    cin.ignore();
    cout<<"Ingrese su edad: ";
    cin >> edad;
    //cout<<nick_l<<", "<<password_l<<", "<<edad<<endl;
    DoublyLinkedListU->insertAtEnd(std::string(nick_l), SHA256::cifrar(std::string(password_l)), monedas, edad);
    //cout<<nick_l<<", "<<password_l<<endl;
    //DoublyLinkedListU->displayListSE();
    cout<<"Datos ingresados correctamente..."<<endl;
}

void login(){
    char nick_l[250];
    char password_l[250];
    NodoUsuario* user = NULL;
    
    cin.ignore();
    cout<<"Ingrese su nombre de jugador: ";
    cin.getline(nick_l, 250, '\n');
    //cin >> nick;
    cin.ignore();
    cout<<"Ingrese su password: ";
    cin.getline(password_l, 250, '\n');
    //cin >> password;
    //cout<<std::string(nick_l)<<", "<<std::string(password_l)<<endl;
    user = DoublyLinkedListU->searchUser(std::string(nick_l), SHA256::cifrar(std::string(password_l)));
    if(user == NULL){
        cout<<"El nombre de jugador no existe, ingrese correctamente su nombre de jugador"<<endl;
        return;
    }
    // //*Sale de do-while en caso de que si exista un usuario

    subMenuUser(user);
}

void subMenuUser(NodoUsuario* nodoUser){
    int opcion2 = 0;
    do{
        cout<<"\t.:SubMenu:.\t"<<endl;
        cout<<"1. Editar datos."<<endl;
        cout<<"2. Eliminar cuenta."<<endl;
        cout<<"3. Ver el tutorial."<<endl;
        cout<<"4. Ver articulos de la tienda."<<endl;
        cout<<"5. Realizar movimientos."<<endl;
        cout<<"6. Regresar al menu principal"<<endl;
        cout<<"Elija una opcion: ";
        cin >> opcion2;

        switch (opcion2){
            case 1:
                //cout<<"Editando informacion del usuario..."<<endl;
                editarInfoUser(nodoUser);
                break;
            case 2:
                //cout<<"Se va a eliminar la cuenta"<<endl;
                opcion2 = eliminarUser(nodoUser->user->getNick());
                break;
            case 3:
                cout<<"Se vera el tutorial del juego"<<endl;
                if(cola_tutorial == NULL){
                    cout<<"No hay tutorial disponible"<<endl;
                }else{
                    cola_tutorial->displayQueue();
                }
                break;
            case 4:
                cout<<"Se veran los articulos de la tienda"<<endl;
                if(articulos != NULL){
                    cout<<"\t\t\tTotal: Tokens: "<<nodoUser->user->getMoney()<<endl;
                    cout<<"Tienda"<<endl;
                    articulos->printL();
                    cout<<"Elija la opcion a comprar:"<<endl;
                }else{
                    cout<<"No hay articulos que mostrar"<<endl;
                }
                break;
            case 5:
                cout<<"Se realizan los movimientos del jugador"<<endl;
                break;
            case 6:
                cout<<"Gracias por jugar, vuelva pronto!!!"<<endl;
                break;
            default:
                cout<<"La opcion elegida no exista, digite correctamente!!"<<endl;
                break;
            }
    } while (opcion2 != 6);
}

void editarInfoUser(NodoUsuario* nodoUser){
    char nick_l[250];
    char password_l[250];
    cin.ignore();
    cout<<"Ingrese su nuevo nick: ";
    cin.getline(nick_l, 250, '\n');
    nodoUser->user->setNick(std::string(nick_l));
    cin.ignore();
    cout<<"Ingrese su nuevo password: ";
    cin.getline(password_l, 250, '\n');
    nodoUser->user->setPassword(SHA256::cifrar(std::string(password_l)));
    nodoUser->mostrarDatos();
    DoublyLinkedListU->displayListSE();
}

int eliminarUser(string nick){
    bool borrado = DoublyLinkedListU->deleteNode(nick);
    if(borrado){
        cout<<"El usuario fue eliminado con exito!!!"<<endl;
    }else{
        cout<<"El usuario No fue eliminado!!!"<<endl;
    }
    return 6;
    DoublyLinkedListU->displayListSE();
}