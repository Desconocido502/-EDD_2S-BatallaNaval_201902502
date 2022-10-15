#include <iostream>
#include <map>
#include <string>

#include "ListaPilaMov.h"
#include "PilaMov.h"
#include "AVL.h"
#include "../lib/crow_all.h"

using namespace std;

#ifndef USER_H
#define USER_H

class User{
private:
    int id;
    string nick;
    string password;
    int money;
    int age;
public:
    ListaPilaMov* listaPilaMovimientos;
    AVL avl; //Arbol avl para los productos
    User(int id, string nick, string password, int money, int age){
        this->id = id;
        this->nick = nick;
        this->password = password;
        this->money = money;
        this->age = age;
        this->listaPilaMovimientos = new ListaPilaMov();
        
    }

    User(){ //Constructor vacio
        this->id = -1;
        this->nick = "";
        this->password = "";
        this->money = 0;
        this->age = 0;
        this->listaPilaMovimientos = new ListaPilaMov();
    }
    
    ~User(){ //Destructor

    }

    void setListaPilaMov(ListaPilaMov* listaPilaMovimientos){
        this->listaPilaMovimientos = listaPilaMovimientos;
    }

    ListaPilaMov* getListaPilaMov(){
        return this->listaPilaMovimientos;
    }

    void mostrarDatos(){
        cout<<"Nick: "<<this->nick<<", password: "<<this->password<<", money: "<<this->money<<", age: "<<this->age<<endl;
    }

    string mostrarDatos2(){
        return "Nick: " + this->nick + ",\\n password: " + this->password + ",\\n monedas: " + to_string(this->money) + ",\\n edad: " + to_string(this->age);
    }

    void setId(int id){
        this->id = id;
    }

    void setNick(string nick){
        this->nick = nick;
    }
    
    void setMoney(int money){
        this->money = money;
    }

    string getNick(){
        return this->nick;
    }

    string getPassword(){
        return this->password;
    }

    void setPassword(string password){
        this->password = password;
    }
    
    int getMoney(){
        return this->money;
    }

    int getId(){
        return this->id;
    }
    
    void setAge(int age){
        this->age = age;
    }

    int getAge(){
        return this->age;
    }
    
    void addBoat(NodoBarco* barcoComprado){
        avl.add(barcoComprado);
    }
    

    crow::json::wvalue to_map(){
        crow::json::wvalue datosUser = {{"id", this->id},{"nick", this->nick}, {"monedas", to_string(this->money)}, {"edad", to_string(this->age)}};
        return datosUser;
    }
};



#endif