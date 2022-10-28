from Nodo_Barcos import nodo_barco

class doble():
    def __init__(self):
        self.primero = None
        self.ultimo = None


    def vacia(self):
        return self.primero == None

    def agregar(self,tipo,estado,posx1,posx2,posx3,posx4,posy1,posy2,posy3,posy4,dir,vida):
        
        if self.vacia():
            
            self.primero = self.ultimo = nodo_barco(tipo,estado,posx1,posx2,posx3,posx4,posy1,posy2,posy3,posy4,dir,vida)
        else:
            aux = self.ultimo
            self.ultimo = aux.siguiente = nodo_barco(tipo,estado,posx1,posx2,posx3,posx4,posy1,posy2,posy3,posy4,dir,vida)
            #self.ultimo = aux.siguiente
    
    def revisar(self,x,y):
        aux = self.primero
        i = 0
        while aux is not None:
            i = i+1

            if x == aux.posx1 and y == aux.posy1:
                aux.vida = aux.vida-1
                print(aux.vida)
                if aux.vida == 0:
                    return 1
                else:
                    return 0
            elif x == aux.posx1 and y == aux.posy2:
                aux.vida = aux.vida-1
                print(aux.vida)
                if aux.vida == 0:
                    return 1
                else:
                    return 0
            elif x == aux.posx1 and y == aux.posy3:
                aux.vida = aux.vida-1
                print(aux.vida)
                if aux.vida == 0:
                    return 1
                else:
                    return 0
            elif x == aux.posx1 and y == aux.posy4:
                aux.vida = aux.vida-1
                print(aux.vida)
                if aux.vida == 0:
                    return 1
                else:
                    return 0
            elif x == aux.posx1 and y == aux.posy1:
                aux.vida = aux.vida-1
                print(aux.vida)
                if aux.vida == 0:
                    return 1
                else:
                    return 0
            elif x == aux.posx2 and y == aux.posy1:
                aux.vida = aux.vida-1
                print(aux.vida)
                if aux.vida == 0:
                    return 1
                else:
                    return 0
            elif x == aux.posx3 and y == aux.posy1:
                aux.vida = aux.vida-1
                print(aux.vida)
                if aux.vida == 0:
                    return 1
                else:
                    return 0
            elif x == aux.posx4 and y == aux.posy1:
                aux.vida = aux.vida-1
                print(aux.vida)
                if aux.vida == 0:
                    return 1
                else:
                    return 0
            else:
                pass

            aux = aux.siguiente
    def Destruidos(self):
        aux = self.primero
        while aux is not None:
            if aux.vida == 0:
                print("Destruido barco de tipo: " + aux.tipo)
            aux = aux.siguiente
    def getin(self,x,y):
        tmp = self.primero
        while tmp is not None:
            if tmp.x == x and tmp.y == y:
                return tmp
            tmp = tmp.siguiente
        return None