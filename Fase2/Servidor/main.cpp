#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <string.h>

#include "lib/crow_all.h"
#include "lib/json.hpp"

#include "EDD/User.h"
#include "EDD/DoublyLinkedListCircularUser.h"
#include "lib/sha256.h"
#include "lib/replace.h"


using namespace std;
using json = nlohmann::json;



void to_json(json &JSON, User &user)
{
    JSON = {
            {"nickname", user.getNick()},
            {"password", user.getPassword()},
            {"monedas", user.getMoney()},
            {"edad", user.getAge()}
        };
}

void from_json(json &JSON, User &user){
    user.setNick(JSON.at("nick").get<string>());
    user.setPassword(JSON.at("password").get<string>());
    user.setMoney(JSON.at("monedas").get<int>());
    user.setAge(JSON.at("edad").get<int>());
}

void cargarDatos(DoublyLinkedListCircularUser &lts){
    ifstream json_read("json/usuarios.json", ios::in);
    json dict_json = json::parse(json_read);
    json usuarios = dict_json.at("usuarios");

    for(auto usuario: usuarios){
        if(!lts.searchUserForNick(string(usuario.at("nick")))){
            lts.insertAtEnd(usuario.at("nick"), SHA256::cifrar(usuario.at("nick")), stoi(usuario.at("monedas").get<string>()), stoi(usuario.at("edad").get<string>()));
        }
    }
    lts.sort();
    lts.displayListSE();
}

int main(int argc, char const *argv[])
{
    cout << "Inicio del proyecto fase 2" << endl;
    DoublyLinkedListCircularUser ltsUsers;
    cargarDatos(ltsUsers);

    

    crow::SimpleApp app;
    CROW_ROUTE(app, "/")
    ([]
     {
            crow::json::wvalue x({{"status", "OK!"},{"otro", 12}});
            return x; });


    CROW_ROUTE(app, "/usuarios")
	([&ltsUsers]()
	 { 
		std::vector<crow::json::wvalue> temp = ltsUsers.to_vector();
		crow::json::wvalue final = std::move(temp);
		return crow::response(std::move(final)); });

    //AQUI ABAJO NO SE TOCA, TODA RUTA SE COLOCA ENCIMA DE ESTE MENSAJE

    app.port(5000).multithreaded().run();
    return 0;
}