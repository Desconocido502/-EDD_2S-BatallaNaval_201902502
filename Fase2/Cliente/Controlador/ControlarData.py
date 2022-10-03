
from pickle import NONE
import requests
import json

base_url = "http://localhost:5000"


def verificarLogueo(name, password):
    dataUser = {"nick": name, "password": password}
    x = requests.get(f"{base_url}/login", json=dataUser)
    res = x.json()  # Se convierte la respuesta en diccionario
    return res


def RegisterUser(name, password, age):
    userRegister = {"nick": name, "password": password, "age": age}
    x = requests.post(f"{base_url}/guardar_usuario", json=userRegister)
    pass

# *Obtengo todos los usuarios del lado del backend
def getUsers():
    res = requests.get(f"{base_url}/usuarios")

    if (res.status_code == 503):
        print("Server not found!!!")
    else:
        data = res.json()  # Convertimos la respuesta en dict
        return data

def getUser(nick):
    userName = {"nick": nick}
    res = requests.get(f"{base_url}/usuarios/get_user", json=userName)
    if (res.status_code == 400):
        print("Error en la data!!!")
        return None
    else:
        data = res.json()  # Convertimos la respuesta en dict
        return data

#*Carga un user
def cargarUser(nick, password, money, age):
    newUser = {"nick": nick, "password": password, "monedas": money ,"edad": age}
    res = requests.post(f"{base_url}/guardar_usuario", json=newUser)


#Obtienela lista ordenadamente en orden ascendente
def getUsersOrderedAST():
    res = requests.get(f"{base_url}/usuarios/oast")
    data = res.json()  # Convertimos la respuesta en dict
    return data

#Obtienela lista ordenadamente en orden descendente
def getUsersOrderedDST():
    res = requests.get(f"{base_url}/usuarios/odst")
    data = res.json()  # Convertimos la respuesta en dict
    return data

#
def deleteUser(nick):
    name = {"nick": nick}
    res = requests.delete(f"{base_url}/eliminar_usuario", json=name)
    return res.status_code

def drawTree():
    res = requests.get(f"{base_url}/usuarios/graficarArbol")
    return res.status_code

#*Carga un sink barco
def cargarSkinBarco(id, categoria, precio, nombre, src):
    newSKinBoat = {"id": id, "categoria": categoria, "precio": precio ,"nombre": nombre, "src": src}
    res = requests.post(f"{base_url}/skins/guardar_skin_barco", json=newSKinBoat)

def getSkins():
    res = requests.get(f"{base_url}/skins")
    data = res.json()  # Convertimos la respuesta en dict
    return data

#*Carga una coordenada o tamaño del tutorial;
def cargarCoorTutorial(x, y):
    newCoord = {"x": x, "y": y}
    res = requests.post(f"{base_url}/tutorial/guardar_coordenada", json=newCoord)

def getTutorial():
    res = requests.get(f"{base_url}/tutorial")
    data = res.json()  # Convertimos la respuesta en dict
    print(data)
    #return data

def buySKinBarco(categoria, id, userName):
    newCoord = {"categoria": categoria, "id": id, "userName": userName}
    #print(newCoord)
    res = requests.put(f"{base_url}/skins/buy_boat", json=newCoord)
    return res

    #res = requests.put(f"{base_url}/skins/comprar_skin_barco", json=newCoord)



"""
            auto x = crow::json::load(req.body);
			if (!x) return crow::response(400);

			string id=x["id"].s();
			string categoria =x["categoria"].s();
			string userName =x["userName"].s();
            cout<<id<<", "<<categoria<<", "<<userName<<endl;
            /*
            NodoBarco* barco_a_comprar = ltsBarcos.buyArticle2(categoria, id);
            NodoUsuario* usuario = ltsUsers.searchUser2(userName);
            if(barco_a_comprar != NULL &&  usuario != NULL){
                int credito = usuario->getUsuario()->getMoney();
                int precioBarco = barco_a_comprar->getPrecio();
                if(credito < precioBarco){
                    //no se puede comprar el barco por falta de credito
                    return crow::response(400);
                }else{
                    //Se tienen dos opciones, que se pueda comprar:
                    //   1.Se compra y se almacena sin problemas
                    //    2.El barco ya se tenga y no se puede repetir
                    usuario->user->addBoat(barco_a_comprar);
                    bool isBoatRepeat = usuario->user->avl->repetido;
                    //Si el valor de isBoatRepeat es true no se puede comprar por que ya se ha comprado antes
                    if(isBoatRepeat){
                        usuario->user->avl->repetido = false;
                        return crow::response(404);
                    }else{
                        credito = credito - precioBarco;
                        usuario->user->setMoney(credito);
                    }
                }
            }else{
                return crow::response(400);
            }
            */
			return crow::response(200);
"""