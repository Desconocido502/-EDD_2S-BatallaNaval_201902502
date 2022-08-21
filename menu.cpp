#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>


#include "lib/nlohmann/json.hpp"
#include "lib/sha256.h"
#include "lib/replace.h"
#include "edd/generacionImg.h"
#include "edd/DoublyLinkedListCircularUser.h"
#include "edd/LinkedListCategoria.h"
#include "edd/ColaTutorial.h"
#include "edd/PilaMov.h"
#include "edd/ListaPilaMov.h"

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
void mostrarTutorial();
void comprarArticulos(NodoUsuario*);
void realizarMovimientos(NodoUsuario*);
void generarReportes();

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
            generarReportes();
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
        if(!DoublyLinkedListU->searchUserForNick(string(usuario.at("nick")))){ //*Se registra al usuario unicamente si no existe alguien mas con ese nick
            DoublyLinkedListU->insertAtEnd(usuario.at("nick"), SHA256::cifrar(usuario.at("password")), stoi(usuario.at("monedas").get<string>()) , stoi(usuario.at("edad").get<string>()));
        }
    }
    DoublyLinkedListU->sort();
    //DoublyLinkedListU->displayListSE();
    
    //DoublyLinkedListU->drawList();

    cout<< "articulos:" << endl;
    
    for(auto articulo: data.at("articulos")){
        articulos->insert(stoi(articulo.at("id").get<string>()), articulo.at("categoria"), stoi(articulo.at("precio").get<string>()), articulo.at("nombre"), articulo.at("src"));
    }
    //articulos->printL();
    //articulos->drawList();

    cout<< "Tutorial:" << endl;
    cola_tutorial->enqueue(stoi(data.at("tutorial").at("ancho").get<string>()), stoi(data.at("tutorial").at("alto").get<string>()));

    for(auto movimiento: data.at("tutorial").at("movimientos")){
        cola_tutorial->enqueue(stoi(movimiento.at("x").get<string>()), stoi(movimiento.at("y").get<string>())); //Tremenda conversion //error 302 revisar docu  https://json.nlohmann.me/home/exceptions/#jsonexceptiontype_error301
    }

    //cola_tutorial->displayQueue();
    //cola_tutorial->drawQueue();
}

void registrarUsuario(){
    char nick_l[250];
    char password_l[250];
    int edad = 0, monedas = 0;
    cout<<"Bienvenido al registro de usuarios, llene la siguiente informacion..."<<endl;
    cin.ignore();
    cout<<"Ingrese su nombre de jugador: ";
    cin.getline(nick_l, 250, '\n');
    if(DoublyLinkedListU->searchUserForNick(string(nick_l))){
        cout<<"El nombre de usuario ya existe, ingrese otro nick";
        return;
    }
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
    DoublyLinkedListU->sort();
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
                mostrarTutorial();
                break;
            case 4:
                comprarArticulos(nodoUser);
                break;
            case 5:
                cout<<"Se realizan los movimientos del jugador\n"<<endl;
                realizarMovimientos(nodoUser);
                break;
            case 6:
                cout<<"Regresando al menu principal...\n"<<endl;
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
    //nodoUser->mostrarDatos();
    //DoublyLinkedListU->displayListSE();
}

int eliminarUser(string nick){
    bool borrado = DoublyLinkedListU->deleteNode(nick);
    if(borrado){
        cout<<"El usuario fue eliminado con exito!!!"<<endl;
    }else{
        cout<<"El usuario No fue eliminado!!!"<<endl;
    }
    return 6;
    //DoublyLinkedListU->displayListSE();
}

void mostrarTutorial(){
    cout<<"Se vera el tutorial del juego"<<endl;
    if(cola_tutorial == NULL){
        cout<<"No hay tutorial disponible"<<endl;
    }else{
        cout<<endl;
        cola_tutorial->displayQueue();
        cout<<endl;
    }
    return;
}

void realizarMovimientos(NodoUsuario* nodoUser){
    int coordenadaX = 0, coordenadaY = 0;
    PilaMov* pila = new PilaMov();
    string nombrePila = "";
    char seguirIngresandoCoordenadas = 'y', nameStack[250];
    while (seguirIngresandoCoordenadas != 'n'){
        cin.ignore();
        cout<<"Ingrese su coordenada en X:";
        cin>>coordenadaX;
        cin.ignore();
        cout<<"Ingrese su coordenada en Y:";
        cin>>coordenadaY;
        cin.ignore();
        cout<<"Desea seguir ingresando mas coordenadas? [y/n]: ";
        cin >> seguirIngresandoCoordenadas;
        cin.ignore();
        pila->push(coordenadaX, coordenadaY);
    };
    
    cin.ignore();
    cout<<"Ingrese el nombre de la pila:";
    cin.getline(nameStack, 250, '\n');
    cout<<nameStack<<endl;
    nombrePila = string(nameStack); //parseamos de char[]  a string
    pila->setNombrePilaMov(nombrePila);
    cin.ignore();
    cout<<pila->displayStack()<<endl;
    cout<<nodoUser->user->getNick()<<endl;
    nodoUser->user->listaPilaMovimientos->insertarAlFinal(replace(nombrePila," ", "_"), pila);
    nodoUser->user->listaPilaMovimientos->desplegarLista();
    nodoUser->user->getListaPilaMov()->drawListStacks();
}

void comprarArticulos(NodoUsuario* nodoUser){
    int opcionCompra = 0;
    char seguirComprando = 'y';
    //cout<<"Se veran los articulos de la tienda"<<endl;
    if(articulos == NULL){
        cout<<"La lista de articulos esta vacia...\n"<<endl;
        return;
    }

    do{
        cout<<"Tienda\t\t\t\t  Tokens: "<<nodoUser->user->getMoney()<<endl;
        articulos->printLTienda('s'); //*por defecto se ordena en orden ascendente
        cout<<"Elija la opcion a comprar: ";
        cin.ignore();
        cin >> opcionCompra;
        //articulos->buyArticle(opcionCompra);  //*Se tiene que preguntar al aux que hacer aqui
        cout<<"\n - "<<opcionCompra<<endl;
        cout<<"Desea seguir comprando mas articulos? [y/n]: ";
        cin.ignore();
        cin >> seguirComprando;

    } while (seguirComprando != 'n');

}

void generarReportes(){
    int opcionGrafica = 0;
    char tipoOrden;
    cout<<"Bienvenido a la creacion y visualizacion de reportes\n"<<endl;
    
    do{
        cout<<"\t.:Menu graficar:.\t"<<endl;
        cout<<"1. Visualizar lista de usuarios."<<endl;
        cout<<"2. Visualizar lista de articulos."<<endl;
        cout<<"3. Visualizar cola de movimientos del tutorial."<<endl;
        cout<<"4. Visualizar una lista de pilas de algun usuario."<<endl;
        cout<<"5. Mostrar listado de usuarios ordenado."<<endl;
        cout<<"6. Mostrar listado de articulos ordenado."<<endl;
        cout<<"7. Regresar al menu principal."<<endl;
        cout<<"Elija una opcion: ";
        cin >> opcionGrafica;

        switch (opcionGrafica){
            case 1:
                /* Lista doblemente enlazada circular (Usuarios) */
                if(DoublyLinkedListU != NULL){
                    DoublyLinkedListU->drawList();
                    moveFile("ListUsers");
                    openImg("ListUsers");
                }else{
                    cout<<"No existe una lista de usuarios...\n"<<endl;
                }
                break;
            case 2:
                /* Lista de listas (Articulos) */
                if(articulos != NULL){
                    articulos->drawList();
                    moveFile("Articles");
                    openImg("Articles");
                }else{
                    cout<<"No existe una lista de articulos...\n"<<endl;
                }
                break;
            case 3:
                /* Cola de movimientos (Tutorial) */
                if(cola_tutorial != NULL){
                    cola_tutorial->drawQueue();
                    moveFile("ColaTutorial");
                    openImg("ColaTutorial");
                }else{
                    cout<<"No existe una cola del tutorial del juego...\n"<<endl;
                }
                break;
            case 4:
                /* Lista de pilas (Listado de jugadas) */
                //*Mostrarle los jugadores, y que elija al jugador para poder graficar la lista de pilas de jugador
                cout<<"Pendiente...\n"<<endl;
                break;
            case 5:
                /* Listado de usuarios ordenados por edad, de forma ascendente o descendente */
                tipoOrden = ' ';
                if(DoublyLinkedListU != NULL){
                    DoublyLinkedListU->sort();
                    cin.ignore();
                    cout<<"Ingrese si el orden tipo de orden ascendente[s]-descendente[r]: ";
                    cin>>tipoOrden;
                    if(tipoOrden == 's') {
                        DoublyLinkedListU->sort();
                        DoublyLinkedListU->displayListSE();
                    }else if(tipoOrden == 'r') {
                        DoublyLinkedListU->sortReverse();
                        DoublyLinkedListU->displayListSE();
                    }
                    else {
                        cout<<"Error!, el tipo de orden seleccionado no existe\n"<<endl;
                    }
                }else{
                    cout<<"No existe una lista de usuarios a mostrar ordenada...\n"<<endl;
                }
                break;
            case 6:
                /* Listado de artículos ordenados por precio , de forma ascendente o descendente  */
                tipoOrden = ' ';
                if(articulos != NULL){
                    cin.ignore();
                    cout<<"Ingrese si el orden tipo de orden ascendente[s]-descendente[r]: ";
                    cin>>tipoOrden;
                    if(tipoOrden == 's') articulos->printLTienda('s');
                    else if(tipoOrden == 'r') articulos->printLTienda('r');
                    else cout<<"Error!, el tipo de orden seleccionado no existe\n"<<endl;
                }else{
                    cout<<"No existe una lista de articulos a mostrar ordenada...\n"<<endl;
                }
                break;
            case 7:
                cout<<"Regresando al menu principal...\n"<<endl;
                break;
            default:
                cout<<"La opcion elegida no exista, digite correctamente!!"<<endl;
                break;
        }
    } while (opcionGrafica != 7);
    
}