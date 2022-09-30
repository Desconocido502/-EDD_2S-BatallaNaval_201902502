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
#include "EDD/NodoUsuario.h"
#include "EDD/DoublyLinkedListCircularUser.h"
#include "EDD/BTree.h"
#include "EDD/LinkedListCategoria.h"
#include "lib/sha256.h"
#include "lib/replace.h"


using namespace std;
using json = nlohmann::json;

json to_json(User &user)
{
    json JSON;
    JSON = {
        {"nickname", user.getNick()},
        {"password", user.getPassword()},
        {"monedas", user.getMoney()},
        {"edad", user.getAge()}};
    return JSON;
}

void from_json(json &JSON, User &user)
{
    user.setNick(JSON.at("nick").get<string>());
    user.setPassword(JSON.at("password").get<string>());
    user.setMoney(JSON.at("monedas").get<int>());
    user.setAge(JSON.at("edad").get<int>());
}

void cargarDatos(DoublyLinkedListCircularUser &lts)
{
    ifstream json_read("json/usuarios.json", ios::in);
    json dict_json = json::parse(json_read);
    json usuarios = dict_json.at("usuarios");

    for (auto usuario : usuarios)
    {
        if (!lts.searchUserForNick(string(usuario.at("nick"))))
        {
            lts.insertAtEnd(usuario.at("nick"), SHA256::cifrar(usuario.at("password")), stoi(usuario.at("monedas").get<string>()), stoi(usuario.at("edad").get<string>()));
        }
    }
    lts.sort();
    // lts.displayListSE();
}



int main(int argc, char const *argv[])
{
    cout << "Inicio del proyecto fase 2" << endl;
    DoublyLinkedListCircularUser ltsUsers;
    
    //-------------Arbol de usuarios-------------
    BTree arbolUsers;
    arbolUsers.root = nullptr;
    arbolUsers.MinDeg = 2;

    arbolUsers.insert("EDD", ltsUsers.insertAtEnd("EDD", SHA256::cifrar("edd123"), 50, 25));

    //---------------Lista de listas de barcos------------------
    LinkedListCategoria ltsBarcos;
    
    //cargarDatos(ltsUsers);



    crow::SimpleApp app;
    CROW_ROUTE(app, "/")
    ([]
    {
        crow::json::wvalue x({{"status", "OK!"},{"otro", 12}});
        return x; 
    });


    CROW_ROUTE(app, "/usuarios")
    ([&ltsUsers]()
     { 
		std::vector<crow::json::wvalue> temp = ltsUsers.to_vector();
		crow::json::wvalue final = std::move(temp);
		return crow::response(std::move(final)); });

    CROW_ROUTE(app, "/login")
    ([&ltsUsers](const crow::request &req)
     {
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);
		string nick=x["nick"].s();
        string pass= SHA256::cifrar(x["password"].s());
        //string pass=x["password"].s();

		//Usuario *usuario=ls.buscar(nick);
        NodoUsuario* aux = ltsUsers.searchUser2(nick);
		
		if(aux != NULL){
            //Si aux es diferente de null quiere decir que el user si existe
            if(aux->getUsuario()->getPassword()==pass){
                //crow::json::wvalue cuerpo({{"nick", usuario.getNick()},{"password", usuario.getPassword()}, {"money", usuario.getMoney()}, {"age", usuario.getAge()}});
                crow::json::wvalue cuerpo(crow::json::wvalue::list({false, aux->getUsuario()->to_map()}));
                crow::response send(std::move(cuerpo));
                return send;
            }

        }else{
            //{"error", "usuario no encontrado"}
            //crow::json::wvalue c({{"error", "usuario no encontrado"}});
            crow::json::wvalue cuerpo(crow::json::wvalue::list({true, {{"error", "usuario no encontrado"}}}));
            crow::response send(std::move(cuerpo));
            send.code=404;
            return send;
        }
        crow::json::wvalue response(crow::json::wvalue::list({true, {{"error", "Contraseña incorrecta"}}}));
        return crow::response(std::move(response)); });

    CROW_ROUTE(app, "/guardar_usuario")
        .methods("POST"_method)([&ltsUsers, &arbolUsers](const crow::request &req)
        {
            auto x = crow::json::load(req.body);
			if (!x) return crow::response(400);

			string nick=x["nick"].s();
			string pass=x["password"].s();
			int monedas=x["monedas"].i();
			int edad=x["edad"].i();
            if (!ltsUsers.searchUserForNick(nick)){
                arbolUsers.insert(nick, ltsUsers.insertAtEnd(nick,SHA256::cifrar(pass),monedas,edad));
            }
			return crow::response(200);
        });

    CROW_ROUTE(app, "/eliminar_usuario")
		.methods("DELETE"_method)([&ltsUsers, &arbolUsers](const crow::request &req)
		{
          auto x = crow::json::load(req.body);
			if (!x)
				return crow::response(400);
			string nick=x["nick"].s();
	
            bool nodoAELiminar = ltsUsers.deleteNode2(nick);
            if(nodoAELiminar) {
                arbolUsers.remove(nick);
                return crow::response(200);
            } //Todo nice, se borro el user
			return crow::response(404);  //Error no se encontro usuario a borrar
        });
        
    CROW_ROUTE(app, "/usuarios/oast")
    ([&ltsUsers]()
     { 
        ltsUsers.sort(); //Se ordena la lista ascendentemente
		std::vector<crow::json::wvalue> temp = ltsUsers.to_vector();
		crow::json::wvalue final = std::move(temp);
		return crow::response(std::move(final)); });

    CROW_ROUTE(app, "/usuarios/odst")
    ([&ltsUsers]()
     { 
        ltsUsers.sortReverse(); //Se ordena la lista descendentemente
        //ltsUsers.displayListSE();
		std::vector<crow::json::wvalue> temp = ltsUsers.to_vector();
		crow::json::wvalue final = std::move(temp);
		return crow::response(std::move(final)); });
    

    CROW_ROUTE(app, "/usuarios/graficarArbol")
    ([&arbolUsers]()
    { 
        //arbolUsers.traverse();
        
		string drawSucces = arbolUsers.DrawBTree(); 
        //cout<<arbolUsers.DrawBTree()<<endl;
        if(stoi(drawSucces) == 0){
            return crow::response(200);
        }
        return crow::response(400);
    });
    /*
    CROW_ROUTE(app, "/skins")
    ([&ltsBarcos]()
     { 

		std::vector<crow::json::wvalue> temp = ltsUsers.to_vector();
		crow::json::wvalue final = std::move(temp);
		return crow::response(std::move(final)); });
    */

    CROW_ROUTE(app, "/skins/guardar_skin_barco")
        .methods("POST"_method)([&ltsBarcos](const crow::request &req)
        {
            auto x = crow::json::load(req.body);
			if (!x) return crow::response(400);

			string id=x["id"].s();
			string categoria =x["categoria"].s();
			int precio=x["precio"].i();
			string nombre =x["nombre"].s();
            string src =x["src"].s();
            ltsBarcos.insert(id, categoria, precio, nombre, src);
			return crow::response(200);
        });        

    // AQUI ABAJO NO SE TOCA, TODA RUTA SE COLOCA ENCIMA DE ESTE MENSAJE

    app.port(5000).multithreaded().run();
    return 0;
}