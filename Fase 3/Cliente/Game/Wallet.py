import tkinter as tk
from tkinter import ttk
from tkinter import simpledialog
import json
from Game.Blockchain import Blockchain

class Wallet(ttk.Frame):
    def __init__(self, dataUser, dataSkins, total):
        self.dataUser = dataUser
        self.dataSkins = dataSkins
        self.total = total
        self.main_window = tk.Tk()
        # Establecer un título.
        self.main_window.title("Wallet")
        self.main_window.resizable(0, 0)
        self.main_window.config(bg="#707b7c")
        self.main_window.geometry("800x300")

        self.userName = tk.Label(self.main_window, text=self.dataUser["nick"])
        self.userName.config(foreground="white", background="#707b7c", font=("Verdana", 14))
        self.userName.place(x=650, y=10)

        cadena = "Dirección de cuenta: "
        self.direccionCuenta = tk.Label(self.main_window, text=cadena+self.dataUser["from"])
        self.direccionCuenta.config(foreground="white", background="#707b7c", font=("Verdana", 12))
        self.direccionCuenta.place(x=25, y=10)

        self.botonConfirmacion = tk.Button(self.main_window, text="Confirmar compra", command=self.confirmarCompra)
        self.botonConfirmacion.config(foreground="white", background="black", font=("Verdana", 12))
        self.botonConfirmacion.place(x=470, y=250)

        self.totalCompra = tk.Label(self.main_window, text="Q"+str(self.total)+".-")
        self.totalCompra.config(foreground="white", background="#707b7c", font=("Verdana", 14))
        self.totalCompra.place(x=675, y=255)

        text_frame = tk.Frame(self.main_window)
        self.textoComentario=tk.Text(text_frame, width=90, height=10)
        self.textoComentario.insert(tk.INSERT,json.dumps(self.dataSkins, indent=4))
        self.textoComentario.configure(state="disabled")
        self.textoComentario.pack(fill=tk.BOTH, expand=True, side=tk.LEFT)
        self.scrollVert=ttk.Scrollbar(text_frame, command=self.textoComentario.yview)
        self.scrollVert.pack(fill=tk.Y, side=tk.RIGHT)
        text_frame.place(x=20, y=50)

        self.main_window.mainloop()
    
    def confirmarCompra(self):
        privatekeyEntry = simpledialog.askstring("clave privada", "Ingresa la clave privada")
        _from = self.dataUser["from"]
        print(privatekeyEntry == self.dataUser["privatekey"])
        blockchain = Blockchain()
        

""" data = {
        "FROM": "0xe2E1220512c61734c650E654f63f900A4ED3bbC5",
        "SKINS": [
            {  "SKIN": "barco1", "VALUE": "123"  },
            {  "SKIN": "barco2", "VALUE": "456"  },
            {  "SKIN": "barco3", "VALUE": "789"  },
            {  "SKIN": "barco4", "VALUE": "987"  },
            {  "SKIN": "barco5", "VALUE": "654"  }
        ]
    } """
#Wallet("1",'2',data)
#0xb4d6382d0224c0ae597b63552d1d96df83bdc1135aa2dce68ccbc6973bed3d96