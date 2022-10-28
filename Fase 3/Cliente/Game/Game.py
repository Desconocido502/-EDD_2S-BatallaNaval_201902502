
import tkinter as tk
from tkinter import Image, ttk
from tkinter import messagebox
from tkinter.font import BOLD
from PIL import ImageTk, Image
from Game.matriz import matriz
from os import system


class Game(ttk.Frame):

    #--------Cargar Datos iniciales de la partida--------------------------------------------------------
    def InitializeData(self):
        self.matrizJugador1 = matriz(self.tamTabla) #Matriz para el jugador
        self.matrizJugador2 = matriz(self.tamTabla) #Matriz para la maquina
            
        #-------Se agregan los barcos aleatoriamente a cada matriz-----------
        self.matrizJugador1.Agregarbarcos()
        self.matrizJugador1.totalBarcosInicio = self.matrizJugador1.Barcos_restantes
        self.matrizJugador2.Agregarbarcos()
        self.matrizJugador2.totalBarcosInicio = self.matrizJugador2.Barcos_restantes

        self.matrizJugador1.printMatrixO("Jugador1_0")
        self.matrizJugador2.printMatrixO("Jugador2_0")
        #self.matrizJugador2.printMatrixShadow("Maquina_0")

    def atacarEnemigo1(self):
        coordX = int(self.posX.get())
        coordY = int(self.posY.get())
        state1 = self.matrizJugador2.MarcarDisparo(coordX,coordY)
        self.posX.delete(0, 'end')
        self.posY.delete(0, 'end')
        if(state1 == "ts"):
            txt = "Una de las coordinadas supera el tamaño del tablero, ingrese las coordenadas nuevas..."
            messagebox.showwarning(message=txt, title="Error tamaño tabla")
        else:
            self.namePlayer1.config(bg="#943126")
            self.namePlayer2.config(bg="#1d8348")

            self.matrizJugador2.printMatrixO("Jugador2_0")
            img2 = Image.open("./EDDimg/matriz_Jugador2_0_html.png").resize((570,570))
            img2 = ImageTk.PhotoImage(img2, master=self.main_window)
            self.labelImgSec.configure(image=img2)
            self.labelImgSec.image = img2
            if(state1):
                txt = "Juego terminado"
                totalBarcosFinal2 = (self.matrizJugador2.totalBarcosInicio - self.matrizJugador2.Barcos_restantes)
                totalBarcosFinal1 = (self.matrizJugador1.totalBarcosInicio - self.matrizJugador1.Barcos_restantes)
                print("barcos destruidos por el jugador 1: ", totalBarcosFinal2)
                tipoBarcosDestruidos2 = self.matrizJugador2.BarcosDestruidos()
                tipoBarcosDestruidos2["jugador"] = self.userData["nick"]
                print("barcos destruidos por el jugador 2: ", totalBarcosFinal1)
                tipoBarcosDestruidos1 = self.matrizJugador1.BarcosDestruidos()
                tipoBarcosDestruidos1["jugador"] = self.invitado

                if(totalBarcosFinal2 > totalBarcosFinal1): #gano el jugador 1
                    self.createTableResultGame(tipoBarcosDestruidos2, tipoBarcosDestruidos1)
                    self.matrizJugador2.ListaAdyacencia()
                    self.matrizJugador2.Grafo()
                else: #gano el jugador 2
                    self.createTableResultGame(tipoBarcosDestruidos1, tipoBarcosDestruidos2)
                    self.matrizJugador1.ListaAdyacencia()
                    self.matrizJugador1.Grafo()
                
                messagebox.showinfo(message=txt, title="Fin partida")

    
    def atacarEnemigo2(self):
        coordXE = int(self.posXE.get())
        coordYE = int(self.posYE.get())
        state2 = self.matrizJugador1.MarcarDisparo(coordXE, coordYE)
        self.posXE.delete(0, 'end')
        self.posYE.delete(0, 'end')
        if(state2 == "ts"):
            txt = "Una de las coordinadas supera el tamaño del tablero, ingrese las coordenadas nuevas..."
            messagebox.showwarning(message=txt, title="Error tamaño tabla")
        else:
            self.namePlayer1.config(bg="#1d8348")
            self.namePlayer2.config(bg="#943126")

            self.matrizJugador1.printMatrixO("Jugador1_0")
            img1 = Image.open("./EDDimg/matriz_Jugador1_0_html.png").resize((570,570))
            img1 = ImageTk.PhotoImage(img1, master=self.main_window)
            self.labelImg.configure(image=img1)
            self.labelImg.image = img1
            if(state2):
                txt = "Juego terminado"
                totalBarcosFinal2 = (self.matrizJugador2.totalBarcosInicio - self.matrizJugador2.Barcos_restantes)
                totalBarcosFinal1 = (self.matrizJugador1.totalBarcosInicio - self.matrizJugador1.Barcos_restantes)
                print("barcos destruidos por el jugador 1: ", totalBarcosFinal2)
                tipoBarcosDestruidos2 = self.matrizJugador2.BarcosDestruidos()
                tipoBarcosDestruidos2["jugador"] = self.userData["nick"]
                print("barcos destruidos por el jugador 2: ", totalBarcosFinal1)
                tipoBarcosDestruidos1 = self.matrizJugador1.BarcosDestruidos()
                tipoBarcosDestruidos1["jugador"] = self.invitado

                if(totalBarcosFinal2 > totalBarcosFinal1): #gano el jugador 1
                    self.createTableResultGame(tipoBarcosDestruidos2, tipoBarcosDestruidos1)
                    self.matrizJugador2.ListaAdyacencia()
                    self.matrizJugador2.Grafo()
                else: #gano el jugador 2
                    self.createTableResultGame(tipoBarcosDestruidos1, tipoBarcosDestruidos2)
                    self.matrizJugador1.ListaAdyacencia()
                    self.matrizJugador1.Grafo()

                messagebox.showinfo(message=txt, title="Fin partida")

    def createTableResultGame(self, ganador:dict, perdedor:dict):
        contenido = """
digraph html {
  node [fontname="Helvetica,Arial,sans-serif", fontcolor="white"]
  abc [shape = none, margin = 0, label=<
<TABLE BORDER = "1" CELLBORDER = "1" CELLSPACING="0" CELLPADDING="10" style='rounded'>
<TR>
	<TD BGCOLOR="DarkSlateGray">Jugadores</TD>
	<TD BGCOLOR="DarkSlateGray">P</TD>
	<TD BGCOLOR="DarkSlateGray">S</TD>
	<TD BGCOLOR="DarkSlateGray">D</TD>
	<TD BGCOLOR="DarkSlateGray">B</TD>
	<TD BGCOLOR="DarkSlateGray">Total</TD>
</TR>
"""
        contenido += f'''
<TR>
    <TD BGCOLOR="#008000">{ganador["jugador"]}</TD>
    <TD BGCOLOR="#008000">{ganador["P"]}</TD>
    <TD BGCOLOR="#008000">{ganador["S"]}</TD>
    <TD BGCOLOR="#008000">{ganador["D"]}</TD>
    <TD BGCOLOR="#008000">{ganador["B"]}</TD>
    <TD BGCOLOR="#008000">{ganador["total"]}</TD>
</TR>

<TR>
    <TD BGCOLOR="Crimson">{perdedor["jugador"]}</TD>
    <TD BGCOLOR="Crimson">{perdedor["P"]}</TD>
    <TD BGCOLOR="Crimson">{perdedor["S"]}</TD>
    <TD BGCOLOR="Crimson">{perdedor["D"]}</TD>
    <TD BGCOLOR="Crimson">{perdedor["B"]}</TD>
    <TD BGCOLOR="Crimson">{perdedor["total"]}</TD>
</TR>
</TABLE>>];
''' + "\n}"

        dotX = "./EDDimg/ResultGame_html.dot"
        file = open(dotX, "w")
        file.write(contenido)
        file.close()
        result = "./EDDimg/ResultGame_html.png"
        system("dot -Tpng " + dotX + " -o " + result)

    def __init__(self, tamTabla, user1, user2):  # Se traen los datos del usuario
        self.userData = user1
        self.tamTabla = tamTabla
        self.invitado = user2
        self.main_window = tk.Tk()
        self.main_window.title("BATTLE SHIP")
        self.main_window.resizable(0, 0)
        self.main_window.geometry("1250x700")
        # self.main_window.config(bg="#2c3e50")

        self.tableroPrincipal = tk.Frame(self.main_window, bg="#2c3e50", bd=0)
        self.tableroPrincipal.config(width="625", height="700")
        self.tableroPrincipal.pack(side="left",expand=tk.YES,fill=tk.BOTH)

        self.tableroSecundario = tk.Frame(self.main_window, bg="#34495e", bd=0)
        self.tableroSecundario.config(width="625", height="700")
        self.tableroSecundario.pack(side="right",expand=tk.YES,fill=tk.BOTH)

        #-------------Llamada a tableros iniciales----------------
        self.InitializeData()

        #-------------------------Widgets Tablero principal---------------------------------------------
        self.namePlayer1 = tk.Label(self.tableroPrincipal, text=self.userData["nick"])
        self.namePlayer1.config(bg="#1d8348", fg="#fff", font=("Verdana", 13, BOLD))
        self.namePlayer1.place(x=290, y=670)

        #"../EDDimg/matriz_Jugador1_0_html.png"
        #print(img)
        img = Image.open("./EDDimg/matriz_Jugador1_0_html.png").resize((570,570))
        img = ImageTk.PhotoImage(img, master=self.main_window)
        self.labelImg = tk.Label(self.tableroPrincipal, bg="#f0f3f4", text="prueba", image=img) #, image=img
        self.labelImg.image = img
        self.labelImg.place(x=10,y=15,relwidth=0.95, relheight=0.85)

        self.labelPosx = tk.Label(self.tableroPrincipal, text="Ingrese coord. X:", font=('Times', 15), bg="#5b2c6f", fg="white")
        self.labelPosx.place(x=55, y=625)

        self.posX = tk.Entry(self.tableroPrincipal, width=5,font=('Times', 15), bg="#5b2c6f", fg="white")
        self.posX.place(x=210, y=625)

        self.labelPosy = tk.Label(self.tableroPrincipal, text="Ingrese coord. Y:", font=('Times', 15), bg="#5b2c6f", fg="white")
        self.labelPosy.place(x=55, y=660)

        self.posY = tk.Entry(self.tableroPrincipal, width=5,font=('Times', 15), bg="#5b2c6f", fg="white")
        self.posY.place(x=210, y=660)

        self.ButtonAtacar = tk.Button(self.tableroPrincipal, text="ATACAR", foreground="white", background="#212f3c", font=('Times', 15,BOLD), command=self.atacarEnemigo1) #, command=self.DatosJXM
        self.ButtonAtacar.place(x=290, y=625)

        #-------------------------Fin Widgets Tablero principal---------------------------------------------


        #-------------------------Widgets Tablero Secundario---------------------------------------------
        self.namePlayer2 = tk.Label(self.tableroSecundario, text=self.invitado)
        self.namePlayer2.config(bg="#943126", fg="#fff", font=("Verdana", 13, BOLD))
        self.namePlayer2.place(x=290, y=670)

        img2 = Image.open("./EDDimg/matriz_Jugador2_0_html.png").resize((570,570))
        img2 = ImageTk.PhotoImage(img2, master=self.main_window)
        self.labelImgSec:tk.Label = tk.Label(self.tableroSecundario, bg="#f0f3f4", text="prueba2", image=img2) #, image=img2
        self.labelImgSec.image = img2
        self.labelImgSec.place(x=10,y=15,relwidth=0.95, relheight=0.85)    

        self.labelPosxE = tk.Label(self.tableroSecundario, text="Ingrese coord. X:", font=('Times', 15), bg="#5b2c6f", fg="white")
        self.labelPosxE.place(x=55, y=625)

        self.posXE = tk.Entry(self.tableroSecundario, width=5,font=('Times', 15), bg="#5b2c6f", fg="white")
        self.posXE.place(x=210, y=625)

        self.labelPosyE = tk.Label(self.tableroSecundario, text="Ingrese coord. Y:", font=('Times', 15), bg="#5b2c6f", fg="white")
        self.labelPosyE.place(x=55, y=660)

        self.posYE = tk.Entry(self.tableroSecundario, width=5,font=('Times', 15), bg="#5b2c6f", fg="white")
        self.posYE.place(x=210, y=660)

        self.ButtonAtacarE = tk.Button(self.tableroSecundario, text="ATACAR", foreground="white", background="#212f3c", font=('Times', 15,BOLD), command=self.atacarEnemigo2) #, command=self.DatosJXM
        self.ButtonAtacarE.place(x=290, y=625)

        #-------------------------Fin Widgets Tablero Secundario---------------------------------------------

        self.main_window.mainloop()


#Game(15, {"nick": "WHiteShit"}, "carlos")
#0xc43a026fdcf66930428305c6eccc6f27b8460bf3516f070e746730f0abcb35ea