import tkinter as tk
from PIL import ImageTk, Image
from tkinter import ttk, messagebox, simpledialog
from tkinter.font import BOLD

class Resultados(ttk.Frame):
    def __init__(self, tamTabla, user1, user2):
        self.tamTabla = tamTabla
        self.user1 = user1
        self.user2 = user2
        self.main_window = tk.Tk()
        self.main_window.title("Resultados")
        self.main_window.resizable(0, 0)
        self.main_window.geometry("1000x650")
        
        self.imgResult = tk.Label(self.main_window, text="Resultados de la partida")
        self.imgResult.place(x=10,y=15)

        img = Image.open("./EDDimg/ResultGame_html.png").resize((390,350))
        img = ImageTk.PhotoImage(img, master=self.main_window)
        self.labelImg = tk.Label(self.main_window, bg="#f0f3f4", text="prueba", image=img) #, image=img
        self.labelImg.place(x=10,y=55)

        self.labelImgG = tk.Label(self.main_window, bg="gray")
        self.labelImgG.place(x=400,y=55)

        self.ButtonGraficarLA = tk.Button(self.main_window, text="Graficar Lista Adyacencia", foreground="white", background="#212f3c", font=('Times', 15,BOLD), command=self.graficarLA) #, command=self.DatosJXM
        self.ButtonGraficarLA.place(x=175, y=15)

        self.ButtonGraficarG = tk.Button(self.main_window, text="Graficar Grafo", foreground="white", background="#212f3c", font=('Times', 15,BOLD), command=self.graficarG) #, command=self.DatosJXM
        self.ButtonGraficarG.place(x=430, y=15)

        self.ButtonCerrar = tk.Button(self.main_window, text="Cerrar", foreground="white", background="Crimson", font=('Times', 15,BOLD), command=self.cerrarVentana) #, command=self.DatosJXM
        self.ButtonCerrar.place(x=590, y=15)

        self.main_window.mainloop()
    
    def graficarLA(self):
        img1 = Image.open("./EDDimg/ListaAdyacencia.png").resize((570,570))
        img1 = ImageTk.PhotoImage(img1, master=self.main_window)
        self.labelImgG.configure(image=img1)
        self.labelImgG.image = img1
    
    def graficarG(self):
        img1 = Image.open("./EDDimg/Grafo.png").resize((570,570))
        img1 = ImageTk.PhotoImage(img1, master=self.main_window)
        self.labelImgG.configure(image=img1)
        self.labelImgG.image = img1
    
    def cerrarVentana(self):
        # Retorna "yes" o "no"
        response = messagebox.askquestion(message="¿Desea volver a jugar?", title="Nuevo juego")
        if(response == "yes"):
            response = messagebox.askquestion(message="¿Desea cambiar las configuraciones preestablecidas?", title="Configuraciones")
            if(response == "yes"):
                self.user2 = simpledialog.askstring("nombre invitado", "Ingresa el nombre del usuario invitado")
                self.tamTabla = simpledialog.askstring("Tamaño del tablero", "Ingresa el tamañano del tablero a jugar")
            from Game.Game import Game
            self.main_window.destroy()
            Game(int(self.tamTabla), self.user1, self.user2)
        else:
            self.main_window.destroy()


#Resultados("1","2")        