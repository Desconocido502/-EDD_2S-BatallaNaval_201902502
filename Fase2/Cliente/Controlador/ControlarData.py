from email.mime import base
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