import tkinter as tk
from tkinter import ttk, messagebox
from tkinter import filedialog as fd
from tkinter.font import BOLD
from Game.tabla_hash import HashTable

class CarritoCompra(ttk.Frame):
    def __init__(self, productBuy):
        self.productBuy = productBuy
        self.main_window = tk.Tk()
        # Establecer un título.
        self.main_window.title("Vista de árbol en Tkinter")
        #utl.centrar_ventana(self.main_window, (500, 500))
        self.main_window.resizable(0, 0)

        self.tablaHash = HashTable(13, 20, 80)

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

        self.eliminarSkin = tk.Button(self.main_window, text="Eliminar Skin", font=(
            'Times', 15, BOLD), bg='#666a88', bd=0, fg="#fff", pady=30, command=self.item_selected) #, command=self.orderedAst
        self.eliminarSkin.pack(fill=tk.BOTH)

        self.pagar = tk.Button(self.main_window, text="Pagar", font=(
            'Times', 15, BOLD), bg='green', bd=0, fg="#fff", pady=30) #, command=self.orderedAst
        self.pagar.pack(fill=tk.BOTH)
    
        self.cancelar = tk.Button(self.main_window, text="Cancelar", font=(
            'Times', 15, BOLD), bg='red', bd=0, fg="#fff", pady=30) #, command=self.orderedAst
        self.cancelar.pack(fill=tk.BOTH)
        self.fillTreeViewData() #Carga los datos en el arbol

        self.main_window.mainloop()
    
    def fillTreeViewData(self):
        datas = self.productBuy
        #Se cargan los datos a la hashTable
        for data in datas:
            #print(f"{str(data[5])}{data[2]}", data[2])
            self.tablaHash.agregar(f"{str(data[5])}{str(data[2])}", data[2])

        #Se cargan los datos al tree view
        for data in datas:
            self.add_row(data)
        
        self.tablaHash.printHashTable()
    
    def add_row(self, row):
        self.treeview.insert(
            "", tk.END, iid=row[1], text=row[0], values=(row[1], row[2]))

    def item_selected(self):
        print("hola")
        for item in self.treeview.selection():
            item_child = self.treeview.get_children(item)
            item = self.treeview.item(item)
            iid = self.treeview.focus()
            print("iid = ", iid, "Item = ", item, "Child iid's =", item_child)


#CarritoCompra("1")