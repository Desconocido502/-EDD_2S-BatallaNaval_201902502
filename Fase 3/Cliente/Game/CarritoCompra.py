import tkinter as tk
from tkinter import ttk, messagebox
from tkinter import filedialog as fd
from tkinter.font import BOLD
from Controlador.ControlarData import buySKinsBarco, getUser
from Game.tabla_hash import HashTable

class CarritoCompra(ttk.Frame):
    def __init__(self, user, productBuy, updateData):
        self.productBuy = productBuy
        self.main_window = tk.Tk()
        # Establecer un título.
        self.main_window.title("Vista de árbol en Tkinter")
        #utl.centrar_ventana(self.main_window, (500, 500))
        self.main_window.resizable(0, 0)

        self.tablaHash = HashTable(13, 20, 80)
        self.dataUser = user
        self.updateData = updateData
        # framep
        framep = tk.Frame(self.main_window, bd=0, width=300,relief=tk.SOLID, padx=10, pady=10, bg='#3a7ff6')
        framep.pack(side="left", expand=tk.YES, fill=tk.BOTH)

        # Creación de la vista de árbol.
        self.treeview = ttk.Treeview(framep, columns=("id", "nombre"))

        # Agregamos dos scrollbars

        self.vsb = ttk.Scrollbar(framep, orient="vertical", command=self.treeview.yview)
        self.vsb.pack(side='right', fill='y')
        self.hsb = ttk.Scrollbar(framep, orient="horizontal", command=self.treeview.xview)
        self.hsb.pack(side='bottom', fill='x')

        self.treeview.configure(xscrollcommand=self.hsb.set, yscrollcommand=self.vsb.set)

        self.treeview.heading("#0", text="Categoria")
        self.treeview.heading("id", text="Id")
        self.treeview.heading("nombre", text="Nombre")

        self.treeview.pack(expand=tk.YES, fill=tk.BOTH)

        self.eliminarSkin = tk.Button(self.main_window, text="Eliminar Skin", font=('Times', 15, BOLD), bg='#666a88', bd=0, fg="#fff", pady=30, command=self.item_selected) #, command=self.orderedAst
        self.eliminarSkin.pack(fill=tk.BOTH)

        self.pagar = tk.Button(self.main_window, text="Pagar", font=('Times', 15, BOLD), bg='green', bd=0, fg="#fff", pady=30, command=self.pagarSkins) #, command=self.orderedAst
        self.pagar.pack(fill=tk.BOTH)
    
        self.cancelar = tk.Button(self.main_window, text="Cancelar", font=('Times', 15, BOLD), bg='red', bd=0, fg="#fff", pady=30, command=self.cancelarCompra) #, command=self.orderedAst
        self.cancelar.pack(fill=tk.BOTH)

        self.VisualizarHashTable = tk.Button(self.main_window, text="ver en graphviz", font=('Times', 15, BOLD), bg='#f1c40f', bd=0, fg="#fff", pady=30, command=self.crearGraficoHashTable) #, command=self.orderedAst
        self.VisualizarHashTable.pack(fill=tk.BOTH)

        self.total = tk.Label(self.main_window, text="", font=('Times', 15, BOLD), bg='#ba4a00', bd=0, fg="#fff", pady=30)
        self.total.pack(fill=tk.BOTH)
        self.changeDataForLabel()

        self.fillTreeViewData() #Carga los datos en el arbol

        self.main_window.mainloop()
    
    def fillTreeViewData(self):
        datas = self.productBuy
        #Se cargan los datos a la hashTable
        for data in datas:
            #print(f"{str(data[5])}{data[2]}", data[2])
            #print(categoryShip, idShip, nameShip, priceShip, nameUser, self.userData["id"])
            self.tablaHash.agregar(f"{str(data[5])}{str(data[2])}", data[2])

        #Se cargan los datos al tree view
        for data in datas:
            self.add_row(data)
        
        #self.tablaHash.printHashTable()

    def add_row(self, row):
        self.treeview.insert("", tk.END, iid=row[1], text=row[0], values=(row[1], row[2]))

    def item_selected(self):
            select_item = self.treeview.selection()[0]
            posicion = [indice for indice, dato in enumerate(self.productBuy) if dato[1] == select_item]
            #print(posicion[0])
            x = self.productBuy[posicion[0]]
            #print(x)
            self.tablaHash.eliminar(f"{str(x[5])}{str(x[2])}")
            self.tablaHash.printHashTable()
            self.updateData(int(x[3]), x[1])
            self.changeDataForLabel()
            # Para borrarlo en la tabla
            self.treeview.delete(select_item)
            #print(select_item)
            #print(self.productBuy)
            #del self.productBuy[posicion[0]]

    def changeDataForLabel(self):
        total = 0
        for x in self.productBuy:
            total += int(x[3])
        self.total.configure(text="Total:"+str(total))

    def cancelarCompra(self):
        total = 0
        self.total.configure(text="Total:"+str(total))
        for x in self.productBuy:
            total += int(x[3])
        self.updateData(total, 0)
        self.CleanTreeView()
        self.tablaHash.cleanHashTable()

    def CleanTreeView(self):
        for i in self.treeview.get_children():
            self.treeview.delete(i)
    
    def crearGraficoHashTable(self):
        self.tablaHash.drawHashTable(self.dataUser["nick"])
    
    def pagarSkins(self):
        credito = int(self.dataUser["monedas"])
        total = 0
        for x in self.productBuy:
            total += int(x[3])
        if(credito < total):
            texto = "Usted no cuenta con el credito necesario para comprar todas las skins!!!"
            messagebox.showwarning(message=texto, title="Credito Insuficiente")
        else:
            creditoNuevo = credito - total
            ltsSkins = []
            #newCoord = {"categoria": categoria, "id": id, "userName": userName}
            #print(categoryShip, idShip, nameShip, priceShip, nameUser, self.userData["id"])
            for x in self.productBuy:
                ltsSkins.append({"categoria": x[0], "id": x[1], "userName": x[4]})
            #print(ltsSkins, creditoNuevo)
            res = buySKinsBarco(ltsSkins, creditoNuevo)
            if(res.status_code == 200):
                self.dataUser = getUser(self.dataUser["nick"])
                self.cancelarCompra()#limpia todo
                messagebox.showinfo(message="Skins agregadas a su usuario", title="Skins agregadas")



#CarritoCompra("1")