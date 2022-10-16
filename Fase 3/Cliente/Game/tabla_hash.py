from os import system
import sys

class HashTable():
    def __init__(self, m, min, max):
        self.m = m
        self.min = min
        self.max = max
        self.tabla = [None] * self.m
        self.elementos = 0
        self.contCol = 1 #Contador de colisiones
    
    def division(self, k):
        nuevaPosicion = (k % (self.m))
        return nuevaPosicion

    def dobleHash(self, k):
        nuevaPosicion = ((k % 3) + 1) * self.contCol
        return nuevaPosicion

    def agregar(self, key, value):
        #Agrega un elemento a la tabla cerrada
        posicion = self.division(self.toAscii(key))
        #print(posicion)
        if(self.tabla[posicion] is None):
            self.tabla[posicion] = (key, value)
        else:
            #Ejecutar funcion de sondeo para reubicar elemento
            posicion = self.dobleHash(self.toAscii(key))
            #print(posicion)
            while(self.tabla[posicion] is not None):
                self.contCol += 1
                posicion = self.dobleHash(self.toAscii(key))
            self.tabla[posicion] = (key, value)
        self.elementos += 1
        self.rehashing()
    
    def rehashing(self):
        #Si el factor de carga es mayor o igual a max, fijo rehashing, sino solo imprime la lista
        if(round(self.elementos*100 / self.m) >= self.max):
            temp = self.tabla
            #self.printHashTable()
            mprev = self.m
            self.m = int(self.elementos * 100 / self.min) #Se cambia el tamanio del arreglo
            #re-init
            self.elementos = 0 #Se reinicia el contador de elementos
            self.tabla = [None] * self.m #Se le da un nuevo tamanio al arreglo
            for x in range(0, mprev):
                if(temp[x] != None):
                    self.agregar(temp[x][0], temp[x][1])
        else:
            pass
            #self.printHashTable()
    
    def buscar(self, key):
        #Determine si un elemento existe en la tabla y determina su posicion
        dic = None
        for x in range(0, len(self.tabla)):
            if(self.tabla[x] != None):
                dato_a_encontrar = self.tabla[x]
                if(dato_a_encontrar[0] == key):
                    dic = f"{dato_a_encontrar[0]}: {dato_a_encontrar[1]}"
                    return dic
        return dic #No se encontro el dato a buscar dentro del hash table

    def eliminar(self, key):
        for x in range(0, len(self.tabla)):
            if(self.tabla[x] != None):
                print(self.tabla[x][0], key)
                if(self.tabla[x][0] == key):
                    #print("Eliminado")
                    self.tabla[x] = None
                    self.elementos -= 1
                    return True
        return False
    
    def cleanHashTable(self):
        for x in range(0, len(self.tabla)):
            self.tabla[x] = None
    
    def drawHashTable(self, nombre):
        contenido = ""
        cadena = ""
        contenido += """digraph html {
node [fontname="Helvetica,Arial,sans-serif", fontcolor="white"]"""
        contenido += f"\nlabel=\"{nombre}\"\n"
        contenido += """abc [shape = none, margin = 0, label=<
<TABLE BORDER = "1" CELLBORDER = "1" CELLSPACING="0" CELLPADDING="10">\n"""
        cadena += "<TR>\n\t<TD BGCOLOR=\"FireBrick\">Indice</TD>\n\t<TD BGCOLOR=\"FireBrick\">Id</TD>\n\t<TD BGCOLOR=\"FireBrick\">Nombre</TD>\n</TR>\n"
        for x in range(0, self.m):
            if(self.tabla[x] is not None):
                dato_a_encontrar = self.tabla[x]
                cadena += f"<TR>\n\t<TD BGCOLOR=\"#273746\">{x}</TD>\n\t<TD BGCOLOR=\"#273746\">{dato_a_encontrar[0]}</TD>\n\t<TD BGCOLOR=\"#273746\">{dato_a_encontrar[1]}</TD>\n</TR>\n"
        cadena += "</TABLE>>];\n}"
        contenido += cadena
        dotX = "./EDDimg/HashTable_{}_html.dot".format("Base")
        file = open(dotX, "w")
        file.write(contenido)
        file.close()
        result = "./EDDimg/HashTable_{}_html.png".format(nombre)
        system("dot -Tpng " + dotX + " -o " + result)
        commando = "xdg-open ./EDDimg/HashTable_{}_html.png".format(nombre)
        system(commando)
        #print(contenido)

    def printHashTable(self):
        print("[", end="")
        for x in range(0, len(self.tabla)):
            print(" ", self.tabla[x], end="")
        print("]", f"{round(self.elementos*100/self.m)}%")
    
    def toAscii(self, cadena):
        result = 0
        for char in cadena:
            result += ord(char)
        return result