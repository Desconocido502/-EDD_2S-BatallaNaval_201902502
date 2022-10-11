
import tkinter as tk
from tkinter import ttk
from tkinter.simpledialog import askinteger
from tkinter.font import BOLD

class MenuGame(ttk.Frame):
        def __init__(self, user): #Se traen los datos del usuario
            self.userData = user
            self.main_window = tk.Tk()
            self.main_window.title("Menu del juego")
            self.main_window.resizable(0, 0)
            self.main_window.geometry("450x200")
            self.main_window.config(bg="#2c3e50")

            self.jugadorXmaquina = tk.Button(self.main_window, text="JUGADOR vs MAQUINA", foreground="white", background="#212f3c", font=('Times', 15,BOLD), command=self.DatosJXM)
            self.jugadorXmaquina.place(x=100, y=50)

            self.jugadorXjugador = tk.Button(self.main_window, text="JUGADOR vs JUGADOR", foreground="white", background="#212f3c", font=('Times', 15,BOLD))
            self.jugadorXjugador.place(x=100, y=120)

            self.main_window.mainloop()
        

        def DatosJXM(self):
            tamTabla = askinteger("Tamaño", "Ingrese el tamaño de la tabla:")
            print(tamTabla)
        
        

       

MenuGame("1")