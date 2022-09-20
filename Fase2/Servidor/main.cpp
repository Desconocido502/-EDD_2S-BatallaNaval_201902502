#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>

#include "lib/crow_all.h"
#include "lib/json.hpp"

#include "EDD/User.h"
#include "EDD/DoublyLinkedListCircularUser.h"


using namespace std;
using json = nlohmann::json;

void to_json(json &JSON, const User &us){
    JSON = {{"nickname", us.getNIck()},{"password", us.getPassword()},{"monedas", to_string(us.getMoney())},{"edad", to_string(us.getAge())}};
}


void from_json(const json &JSON, User &us){
    us.setNick(JSON.at("nick").get<string>());
    us.setPassword(JSON.at("password").get<string>());
    us.setMoney(JSON.at("monedas").get<string>());
    us.setAge(JSON.at("edad").get<string>());
}

void cargar_datos(DoublyLinkedListCircularUser &ld){
    //Nos quedamos por aqui
    ifstream json_read("")
    json dict_json = json::parse(json_read);
    json usuarios = dlct_json.at("usuarios");
}


int main(int argc, char const *argv[]){
    cout<<"Inicio del proyecto fase 2"<<endl;
    
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")
    ([]
        {
            crow::json::wvalue x({{"status", "OK!"},{"otro", 12}});
            return x;
        }
    );
    
    app.port(5000).multithreaded().run();
    return 0;
}