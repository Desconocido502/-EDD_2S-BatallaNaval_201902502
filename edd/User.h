#include <iostream>

using namespace std;

class User{
private:
    string nick;
    string password;
    int money;
    int age;
public:
    User(string nick, string password, int money, int age){
        this->nick = nick;
        this->password = password;
        this->money = money;
        this->age = age;
    }

    User(){ //Constructor vacio
        this->nick = "";
        this->password = "";
        this->money = 0;
        this->age = 0;
    }
    
    ~User(){ //Destructor

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