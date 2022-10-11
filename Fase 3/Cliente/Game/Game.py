
import tkinter as tk
from tkinter import Image, ttk
from tkinter.font import BOLD
from PIL import ImageTk, Image
from matriz import matriz


class Game(ttk.Frame):

    #--------Cargar Datos iniciales de la partida--------------------------------------------------------
    def InitializeData(self):
        matrizJugador = matriz(self.tamTabla) #Matriz para el jugador
        matrizMaquina = matriz(self.tamTabla) #Matriz para la maquina
            
        #-------Se agregan los barcos aleatoriamente a cada matriz-----------
        matrizJugador.Agregarbarcos()
        matrizMaquina.Agregarbarcos()

        matrizJugador.printMatrixO("Jugador_0")
        matrizMaquina.printMatrixShadow("Maquina_0")

        #img = Image.open("./EDDimg/matriz_Jugador_0_html.png").resize((675,590))
        #img = ImageTk.PhotoImage(img)
        #self.labelImg = tk.Label(self.tableroPrincipal, bg="#f0f3f4", text="prueba", image=img)
        #self.labelImg.configure(image=img)
        #self.labelImg.place(x=55,y=15,relwidth=0.85, relheight=0.85)

        #img2 = Image.open("./EDDimg/matriz_Maquina_0_html.png").resize((420,350))
        #img2 = ImageTk.PhotoImage(img2)
        #self.labelImgSec = tk.Label(self.tableroSecundario, bg="#f0f3f4", text="prueba2", image=img2)
        #self.labelImgSec.configure(image=img2)
        #self.labelImgSec.place(x=10,y=10,relwidth=0.95, relheight=0.50)


    def __init__(self, tamTabla, user):  # Se traen los datos del usuario
        self.userData = user
        self.tamTabla = tamTabla
        self.main_window = tk.Tk()
        self.main_window.title("BATTLE SHIP")
        self.main_window.resizable(0, 0)
        self.main_window.geometry("1250x700")
        # self.main_window.config(bg="#2c3e50")

        self.tableroPrincipal = tk.Frame(self.main_window, bg="#2c3e50", bd=0)
        self.tableroPrincipal.config(width="800", height="700")
        self.tableroPrincipal.pack(side="left",expand=tk.YES,fill=tk.BOTH)

        self.tableroSecundario = tk.Frame(self.main_window, bg="#34495e", bd=0)
        self.tableroSecundario.config(width="450", height="700")
        self.tableroSecundario.pack(side="right",expand=tk.YES,fill=tk.BOTH)

        #-------------Llamada a tableros iniciales----------------
        self.InitializeData()

        #-------------------------Widgets Tablero principal---------------------------------------------

        img = Image.open("./EDDimg/matriz_Jugador_0_html.png").resize((675,590))
        img = ImageTk.PhotoImage(img)
        self.labelImg = tk.Label(self.tableroPrincipal, bg="#f0f3f4", text="prueba", image=img) #, image=img
        self.labelImg.place(x=55,y=15,relwidth=0.85, relheight=0.85)

        self.labelPosx = tk.Label(self.tableroPrincipal, text="Ingrese coord. X:", font=('Times', 15), bg="#5b2c6f", fg="white")
        self.labelPosx.place(x=55, y=625)

        self.posX = tk.Entry(self.tableroPrincipal, width=5,font=('Times', 15), bg="#5b2c6f", fg="white")
        self.posX.place(x=210, y=625)

        self.labelPosy = tk.Label(self.tableroPrincipal, text="Ingrese coord. Y:", font=('Times', 15), bg="#5b2c6f", fg="white")
        self.labelPosy.place(x=55, y=660)

        self.posY = tk.Entry(self.tableroPrincipal, width=5,font=('Times', 15), bg="#5b2c6f", fg="white")
        self.posY.place(x=210, y=660)

        self.ButtonAtacar = tk.Button(self.tableroPrincipal, text="ATACAR", foreground="white", background="#212f3c", font=('Times', 15,BOLD)) #, command=self.DatosJXM
        self.ButtonAtacar.place(x=290, y=625)

        #-------------------------Fin Widgets Tablero principal---------------------------------------------


        #-------------------------Widgets Tablero Secundario---------------------------------------------

        img2 = Image.open("./EDDimg/matriz_Maquina_0_html.png").resize((420,350))
        img2 = ImageTk.PhotoImage(img2)
        self.labelImgSec = tk.Label(self.tableroSecundario, bg="#f0f3f4", text="prueba2", image=img2) #, image=img2
        self.labelImgSec.place(x=10,y=10,relwidth=0.95, relheight=0.50)    

        #-------------------------Fin Widgets Tablero Secundario---------------------------------------------

        self.main_window.mainloop()


Game(20, "15")
