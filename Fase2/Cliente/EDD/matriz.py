#from pprint import pprint
import random
from nodos import Nodo,NodoEncabezado
from encabezado import ListaEncabezado
import os
import webbrowser

P = 1
S = 2
D = 3
B = 4
contador = 0
class matriz:
    def __init__(self, tamano):
        self.tamano = tamano
        self.filas = ListaEncabezado()
        self.columnas = ListaEncabezado()
    
    def insertar(self,fila,columna,estado,barco):
        nuevo = Nodo(fila,columna,estado,barco)

        eFila = self.filas.getEncabezado(fila)
        if eFila ==None:
            eFila = NodoEncabezado(fila)
            eFila.accesoNodo = nuevo
            self.filas.setEncabezado(eFila)
        
        else:
            if nuevo.columna < eFila.accesoNodo.columna:
                nuevo.right = eFila.accesoNodo
                eFila.accesoNodo.left = nuevo
                eFila.accesoNodo = nuevo
            
            else:
                actual = eFila.accesoNodo
                while actual.right != None:
                    if nuevo.columna < actual.right.columna:
                        nuevo.right = actual.right
                        actual.right.left = nuevo
                        nuevo.left = actual
                        actual.right = nuevo
                        break
                    actual = actual.right
                if actual.right == None:
                    actual.right = nuevo
                    nuevo.left = actual

        #---------------------------------------------------
        eColumna = self.columnas.getEncabezado(columna)
        if eColumna ==None:
            eColumna = NodoEncabezado(columna)
            eColumna.accesoNodo = nuevo
            self.columnas.setEncabezado(eColumna)
        
        else:
            if nuevo.fila < eColumna.accesoNodo.fila:
                nuevo.down = eColumna.accesoNodo
                eColumna.accesoNodo.up = nuevo
                eColumna.accesoNodo = nuevo
            
            else:
                actual = eColumna.accesoNodo
                while actual.down != None:
                    if nuevo.fila < actual.down.fila:
                        nuevo.down = actual.down
                        actual.down.up = nuevo
                        nuevo.up = actual
                        actual.down = nuevo
                        break
                    actual = actual.down
                if actual.down == None:
                    actual.down = nuevo
                    nuevo.up = actual

    def mostrarFilas(self):
        eFila = self.filas.primero
        print('--------FILAS---------')
        while eFila != None:
            actual = eFila.accesoNodo
            print('\n Fila ',actual.fila)
            print('Columna      Valor')
            
            while actual !=None:
                print(actual.columna,'          ',actual.estado)
                actual = actual.right

            eFila = eFila.next
        print('---------FIN----------')

    def mostrarColumnas(self):
        eColumna = self.columnas.primero

        while eColumna != None:
            actual = eColumna.accesoNodo
            print('\n Columna ',actual.columna)
            print('Fila      Valor')
            while(actual != None):
                print(actual.columna,",",actual.fila,'        ',actual.barco)
                actual = actual.down
            eColumna = eColumna.next
        print('---------FIN----------')

    def MarcarDisparo(self,x,y):
        if self.buscar(x,y)==False:
            self.insertar(y,x,"H","X")
        else:
            eColumna:NodoEncabezado = self.columnas.primero
            while eColumna != None:
                actual:Nodo = eColumna.accesoNodo
                while(actual != None):
                    if actual.columna==x and actual.fila==y:
                      actual.estado = "H"
                      print("Disparo registrado en: ("+str(x)+","+str(y)+")",actual.estado)
                    actual = actual.down
                eColumna = eColumna.next
            print('---------FIN----------')

    def Agregarbarcos(self): #dir representa la dirección del barco 0 = Vertical 1 = horizotal
        global contador,P,D,S,B
        if  contador==0:
            cantidad = int((((self.tamano-1)/10)+1))
            print(cantidad)      
            contador = contador+1   
            P = P*cantidad 
            S = S*cantidad 
            D = D*cantidad 
            B = B*cantidad 
            self.Agregarbarcos()
        else : 
            while P!=0:
                dir = random.randint(0,1)
                x = random.randint(1,self.tamano-4)
                y = random.randint(1,self.tamano-4)
                if self.Haybarco(x,y,dir,"P")==False:
                    if dir==0:
                        self.insertar(y,x,"L","P")
                        self.insertar(y+1,x,"L","P")
                        self.insertar(y+2,x,"L","P")
                        self.insertar(y+3,x,"L","P")
                        print("Agregado un portaviones")
                    else:
                        self.insertar(y,x,"L","P")
                        self.insertar(y,x+1,"L","P")
                        self.insertar(y,x+2,"L","P")
                        self.insertar(y,x+3,"L","P")
                        print("Agregado un portaviones")                        
                    P = P-1
                else: self.Agregarbarcos()
            while S!=0:
                dir = random.randint(0,1)
                x = random.randint(1,self.tamano-3)
                y = random.randint(1,self.tamano-3)
                if self.Haybarco(x,y,dir,"S")==False:
                    if dir==0:
                        self.insertar(y,x,"L","S")
                        self.insertar(y+1,x,"L","S")
                        self.insertar(y+2,x,"L","S")
                        print("Agregado un submarino")     
                    else:
                        self.insertar(y,x,"L","S")
                        self.insertar(y,x+1,"L","S")
                        self.insertar(y,x+2,"L","S")
                        print("Agregado un submarino")                       
                    S = S-1
                else: self.Agregarbarcos()
            while D!=0:
                dir = random.randint(0,1)
                x = random.randint(1,self.tamano-2)
                y = random.randint(1,self.tamano-2)
                if self.Haybarco(x,y,dir,"D")==False:
                    if dir==0:
                        self.insertar(y,x,"L","D")
                        self.insertar(y+1,x,"L","D")
                        print("Agregado un Destructor")     
                    else:
                        self.insertar(y,x,"L","D")
                        self.insertar(y,x+1,"L","D")
                        print("Agregado un Destructor")                       
                    D = D-1
                else: self.Agregarbarcos()
            while B!=0:
                dir = random.randint(0,1)
                x = random.randint(1,self.tamano)
                y = random.randint(1,self.tamano)
                if self.Haybarco(x,y,dir,"B")==False:
                    if dir==0:
                        self.insertar(y,x,"L","B")
                        print("Agregado un Buque")     
                    else:
                        self.insertar(y,x,"L","B")
                        print("Agregado un Buque")                       
                    B = B-1
                else: self.Agregarbarcos()                    

    def Haybarco(self,x,y,dir,tipo):
        i = 0

        if (tipo == "P"):
          if(dir ==0):
            while i <= 4:
                if self.buscar(x,y)==False:
                  y=y-1
                  i=i+1
                else:
                    return True
          else:
            while i <= 4:

                if self.buscar(x,y)==False:
                  x=x+1
                  i=i+1
                else:
                    return True
        elif (tipo == "S"):
          if(dir ==0):
            while i <= 3:
                if self.buscar(x,y)==False:
                  y=y-1
                  i=i+1
                else:
                    return True
          else:
            while i <= 3:

                if self.buscar(x,y)==False:
                  x=x+1
                  i=i+1
                else:
                    return True
        elif (tipo == "D"):
          if(dir ==0):
            while i <= 2:
                if self.buscar(x,y)==False:
                  y=y-1
                  i=i+1
                else:
                    return True
          else:
            while i <= 2:

                if self.buscar(x,y)==False:
                  x=x+1
                  i=i+1
                else:
                    return True
        elif (tipo == "B"):
          if(dir ==0):
            while i <= 1:
                if self.buscar(x,y)==False:
                  y=y-1
                  i=i+1
                else:
                    return True
          else:
            while i <= 1:

                if self.buscar(x,y)==False:
                  x=x+1
                  i=i+1
                else:
                    return True
        else:
            print("Esto no debería pasar")
        return False


    def buscar(self,x,y):
        eColumna:NodoEncabezado = self.columnas.primero
        if eColumna==None:
            return False
        else:
            while eColumna != None:
                actual:Nodo = eColumna.accesoNodo
                while(actual != None):
                    if actual.columna==x and actual.fila==y:
                        return True
                    actual = actual.down
                eColumna = eColumna.next    
            return False

    def printMatrixO(self):
        contenido = ""
        cadena = ""
        contenido += """digraph html {
node [fontname="Helvetica,Arial,sans-serif", fontcolor="white"]
abc [shape = none, margin = 0, label=<
<TABLE BORDER = "1" CELLBORDER = "1" CELLSPACING="0" CELLPADDING="10" style='rounded'>\n
                    """
        Cabeceras = ""
        for i in range(self.tamano):
            #Cabeceras+="C"+str(i+1)+"[label=\""+str(i+1)+"\",group = "+str(i+2)+", fillcolor=\"FireBrick\", fontcolor=\"white\"]\n"
            Cabeceras += f"<TD BGCOLOR=\"FireBrick\">{str(i+1)}</TD>\n\t"
        
        contenido += "<TR>\n\t<TD > </TD>" + "\n" + Cabeceras + "\n</TR>\n"
      
        #print(contenido)
        matrizs = []
        for i in range(1, self.tamano + 1):
            matrizs.append([])
            for j in range(1, self.tamano +1):
                matrizs[i-1].append(str(i) + "x" + str(j))
                #print(str(i) + "x" + str(j), end= " ")
            #print()
        #pprint(matrizs)


        #Para columnas
        eColumna = self.columnas.primero
        while eColumna != None:
            actual = eColumna.accesoNodo
            while(actual != None):
                #if(actual.columna > self.tamano and actual.fila > self.tamano):
                matrizs[actual.columna-1][actual.fila-1] = [actual.columna ,actual.fila, actual.barco, actual.estado]
                #print(str(actual.columna)+","+str(actual.fila)+"("+actual.barco+")")
                actual = actual.down
            eColumna = eColumna.next 

        #pprint(matrizs)
        i = 1
        for x in matrizs:
            cadena += f"<TR>\n\t<TD BGCOLOR=\"FireBrick\">{str(i)}</TD>\n\t" 
            for y in x:
                #print(type(y) == list)
                if(type(y) == list):
                    cadena += f"<TD BGCOLOR={self.colorbarco(y[2], y[3])}>{str(y[0])}X{str(y[1])}({y[2]})</TD>\n\t"
                else:
                    cadena += f"<TD BGCOLOR=\"white\">\"{y}\"</TD>\n\t"
                #print(y, end=" - ")
            cadena += "\n</TR>\n"
            i += 1
            #print("")        
        cadena += "</TABLE>>];\n}"
        contenido += cadena
        dotX = "matriz_{}_html.dot".format("Z")
        file = open(dotX, "w")
        file.write(contenido)
        file.close()
        result = "matriz_{}_html.png".format("Z")
        os.system("dot -Tpng " + dotX + " -o " + result)
        webbrowser.open(result)

    def graficarNeato(self):
        ltsColores = ['P','S','D','B']
        contenido = '''digraph G{
labelloc="t";
bgcolor="#1a1a1a";
nodesep=0.5;
fontcolor=white;
node[shape=box width=0.7 height=0.7 fontname="Arial"  style=filled fillcolor="white" fontcolor="white"]
edge[style = "bold" fontcolor=white color="#1e8449"]
node[label = "0,0" fillcolor="DarkOrange" pos = "-1,1!"]raiz;
label = "MATRIZ DISPERSA" 
fontname="Arial Black" 
fontsize="25pt" 
'''
        # --graficar nodos CABECERA-- #

        # --graficar nodos fila
        posx = 0
        for i in range(self.tamano):
            contenido += '\n\tnode[label = "F{}" fillcolor="FireBrick" pos="-1,-{}!" shape=box]x{};'.format(i+1,posx, i+1)
            posx += 1

        for i in range(1, self.tamano):
            contenido += '\n\tx{}->x{};'.format(i, i + 1)
            contenido += '\n\tx{}->x{}[dir=back];'.format(i, i + 1)
        contenido += '\n\traiz->x{};'.format(1)
            
        posy = 0
        for j in range(self.tamano):
            contenido += '\n\tnode[label = "C{}" fillcolor="FireBrick" pos = "{},1!" shape=box]y{};'.format(j+1,posy,j+1)
            posy += 1

        for j in range(1, self.tamano):
            contenido += '\n\ty{}->y{};'.format(j, j + 1)
            contenido += '\n\ty{}->y{}[dir=back];'.format(j, j + 1)
        contenido += '\n\traiz->y{};'.format(1)

        print(contenido)
        
        #* ya con las cabeceras graficadas, lo siguiente es los nodos internos, o nodosCelda
        pivote = self.filas.primero
        posx = 0

        pivote = self.filas.primero
        while pivote != None:
            pivote_celda:Nodo = pivote.accesoNodo
            while(pivote_celda != None):
                # --- buscamos posy
                pivotey:NodoEncabezado = self.columnas.primero
                posy_celda = 0
                while pivotey != None:
                    if (pivotey.id == pivote_celda.columna):
                        break
                    posy_celda += 1
                    pivotey = pivotey.next
                if(pivote_celda.barco in ltsColores):
                     contenido += f'\n\tnode[label="{(str(pivote_celda.fila))}x{str(pivote_celda.fila)}({pivote_celda.barco})"' + f'fillcolor={self.colorbarco(pivote_celda.barco, pivote_celda.estado)}'+' pos="{},-{}!" shape=box fontcolor="white"]i{}_{};'.format(  # pos="{},-{}!"
                        posy_celda, posx, pivote_celda.fila, pivote_celda.columna)
                else:
                    contenido += f'\n\tnode[label="*" fillcolor="white"' + ' pos="{},-{}!" shape=box fontcolor="black"]i{}_{};'.format(  # pos="{},-{}!"
                        posy_celda, posx, pivote_celda.fila, pivote_celda.columna)
                pivote_celda = pivote_celda.right
            
            pivote_celda = pivote.accesoNodo
            while(pivote_celda != None):
                if(pivote_celda.right != None):
                    contenido += '\n\ti{}_{}->i{}_{};'.format(pivote_celda.fila, pivote_celda.columna,pivote_celda.right.fila, pivote_celda.right.columna)
                    contenido += '\n\ti{}_{}->i{}_{}[dir=back];'.format(pivote_celda.fila, pivote_celda.columna,pivote_celda.right.fila, pivote_celda.right.columna)
                pivote_celda = pivote_celda.right

            pivote_celda = pivote.accesoNodo
            while(pivote_celda != None):
                if(pivote_celda.right != None):
                    contenido += '\n\ti{}_{}->i{}_{};'.format(pivote_celda.fila, pivote_celda.columna,pivote_celda.right.fila, pivote_celda.right.fila)
                    contenido += '\n\ti{}_{}->i{}_{}[dir=back];'.format(pivote_celda.fila, pivote_celda.columna,pivote_celda.right.fila, pivote_celda.right.columna)
                pivote_celda = pivote_celda.right
            
            contenido += '\n\tx{}->i{}_{};'.format(pivote.id, pivote.accesoNodo.fila, pivote.accesoNodo.columna)
            contenido += '\n\tx{}->i{}_{}[dir=back];'.format(pivote.id, pivote.accesoNodo.fila, pivote.accesoNodo.columna)
            pivote = pivote.next
            posx += 1

        pivote = self.columnas.primero
        while(pivote != None):
            pivote_celda:Nodo = pivote.accesoNodo
            while(pivote_celda != None):
                if(pivote_celda.down != None):
                    contenido += '\n\ti{}_{}->i{}_{};'.format(pivote_celda.fila, pivote_celda.columna,pivote_celda.down.fila, pivote_celda.down.columna)
                    contenido += '\n\ti{}_{}->i{}_{}[dir=back];'.format(pivote_celda.fila, pivote_celda.columna,pivote_celda.down.fila, pivote_celda.down.columna)
                pivote_celda = pivote_celda.down
            contenido += '\n\ty{}->i{}_{};'.format(pivote.id, pivote.accesoNodo.fila, pivote.accesoNodo.columna)
            contenido += '\n\ty{}->i{}_{}[dir=back];'.format(pivote.id, pivote.accesoNodo.fila, pivote.accesoNodo.columna)
            pivote = pivote.next
        
        contenido += '\n}' 
        print(contenido)

    def graficar(self):
        
        raiz = "raiz->F1 \nraiz->C1 "
        rCol ="{rank=same;raiz;"
        rF = ""
        Cabeceras = ""
        Uniones = ""
        for i in range(self.tamano):
            Cabeceras+="F"+str(i+1)+"[label=\""+str(i+1)+"\",group = 1]\n"
            Cabeceras+="C"+str(i+1)+"[label=\""+str(i+1)+"\",group = "+str(i+2)+"]\n"
            if (i+1==self.tamano):
                rCol +="C"+str(i+1)+"}\n"
            else: 
                rCol +="C"+str(i+1)+";"
                Uniones +="F"+str(i+1)+"->F"+str(i+2)+"\n"
                Uniones +="F"+str(i+1)+"->F"+str(i+2)+" [dir=back]\n"
                Uniones +="C"+str(i+1)+"->C"+str(i+2)+"\n"
                Uniones +="C"+str(i+1)+"->C"+str(i+2)+" [dir=back]\n"
        eColumna = self.columnas.primero
        Dir1 = ""
        Dir2 = ""
        Dir3 = ""
        Dir4 = ""
        Nodos =""

        while eColumna != None:
            actual = eColumna.accesoNodo
            cont = 0
            while(actual != None):
                while cont!=1:
                  Dir1+="F"+str(actual.columna)+"->"
                  Dir2+="F"+str(actual.columna)+"->"
                  rF+= "{rank=same;F"+str(actual.columna)+";"
                  cont = cont+1
                if (actual.down == None):
                    Nodos+=("N"+str(actual.columna)+"_"+str(actual.fila)+"[label=\""+str(actual.columna)+","+str(actual.fila)+"("+actual.barco+")\",group = "+str(actual.fila+1)+",fillcolor="+self.colorbarco(actual.barco,actual.estado)+"]\n")
                    Dir1+=("N"+str(actual.columna)+"_"+str(actual.fila)+"")
                    Dir2+=("N"+str(actual.columna)+"_"+str(actual.fila)+"[dir=back]")
                    rF+="N"+str(actual.columna)+"_"+str(actual.fila)+"}"
                else:
                    Nodos+=("N"+str(actual.columna)+"_"+str(actual.fila)+"[label=\""+str(actual.columna)+","+str(actual.fila)+"("+actual.barco+")\",group = "+str(actual.fila+1)+",fillcolor="+self.colorbarco(actual.barco,actual.estado)+"]\n")
                    Dir1+=("N"+str(actual.columna)+"_"+str(actual.fila)+"->")
                    Dir2+=("N"+str(actual.columna)+"_"+str(actual.fila)+"->")
                    rF+="N"+str(actual.columna)+"_"+str(actual.fila)+";"
                actual = actual.down
            Dir1+= "\n"    
            Dir2+= "\n"    
            rF +="\n"
            eColumna = eColumna.next 
        #print(Nodos)
        eFila = self.filas.primero

        while eFila != None:
            actual = eFila.accesoNodo
            cont = 0
            while actual !=None:
                while cont!=1:
                    cont = cont+1
                    Dir3+="C"+str(actual.fila)+"->"
                    Dir4+="C"+str(actual.fila)+"->"
                if (actual.right==None):
                    Dir3+=("N"+str(actual.columna)+"_"+str(actual.fila)+"")
                    Dir4+=("N"+str(actual.columna)+"_"+str(actual.fila)+"[dir=back]")
                else:
                    Dir3+=("N"+str(actual.columna)+"_"+str(actual.fila)+"->")
                    Dir4+=("N"+str(actual.columna)+"_"+str(actual.fila)+"->")
                actual = actual.right
            Dir3+="\n"
            Dir4+="\n"
            eFila = eFila.next
        #print(Dir3)
        #node[shape=box width=0.7 height=0.7 fontname="Arial"  style=filled fillcolor="white" fontcolor="white"]
        #edge[style = \"bold\" fontcolor=\"white\" color=\"#1e8449\"]\n
        dot = "digraph G { \n  subgraph cluster_0 { \n       node[shape=box fontname=\"Arial\" fillcolor = \"LightSteelBlue\" style = filled ] \n         label = \"Matriz dispersa\" \n         bgcolor = \"Plum\" \n         raiz[label = \"0,0\"] \n edge[style = \"bold\" color=\"#1e8449\"]\n"
        dot+= (Cabeceras+Uniones+raiz+rCol+rF+Nodos+Dir1+Dir2+"edge [dir = both]\n"+Dir3+"\n}\n}") #Dir 4 quitado
        #print(dot)
        dotX = "matriz_{}_dot.dot".format("Z")
        file = open(dotX, "w")
        file.write(dot)
        file.close()
        result = "matriz_{}.png".format("Z")
        os.system("dot -Tpng " + dotX + " -o " + result)
        webbrowser.open(result)

    def colorbarco(self,tipo,estado):
        if estado!="L":
            return "\"Red\""
        else:
            if tipo=="P":
                return "\"Maroon\""
            elif tipo=="S":
                return "\"Navy\""
            elif tipo=="D":
                return "\"Gray\"" 
            elif tipo=="B": 
                return "\"#008080\""

matrix = matriz(20)
matrix.Agregarbarcos()
matrix.MarcarDisparo(7,3)
matrix.MarcarDisparo(1,5)
matrix.graficar()
#matrix.graficarNeato()
#matrix.printMatrixO()