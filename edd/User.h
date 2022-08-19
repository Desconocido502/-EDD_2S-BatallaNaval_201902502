#include <iostream>

#include "ListaPilaMov.h"
#include "PilaMov.h"

using namespace std;

#ifndef USER_H
#define USER_H

class User{
private:
    string nick;
    string password;
    int money;
    int age;
public:
    ListaPilaMov* listaPilaMovimientos;
    User(string nick, string password, int money, int age){
        this->nick = nick;
        this->password = password;
        this->money = money;
        this->age = age;
        this->listaPilaMovimientos = new ListaPilaMov();
    }

    User(){ //Constructor vacio
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

    void setNick(string nick){
        this->nick = nick;
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

    int getAge(){
        return this->age;
    }
};



#endif