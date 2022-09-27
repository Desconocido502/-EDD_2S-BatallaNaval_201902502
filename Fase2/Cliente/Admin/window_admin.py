from select import select
import tkinter as tk
from tkinter import ttk, messagebox
from tkinter import filedialog as fd
from tkinter.font import BOLD
from Controlador.ControlarData import cargarUser, deleteUser, getUsers, getUsersOrderedAST, getUsersOrderedDST, deleteUser, drawTree
import json


class Admin(ttk.Frame):

    def orderedAst(self):
        self.CleanTreeView()
        users = getUsersOrderedAST()
        for user in users:
            self.add_row(user)

    def orderedDst(self):
        self.CleanTreeView()
        users = getUsersOrderedDST()
        for user in users:
            self.add_row(user)

    def cargarUsers(self):
        ruta = fd.askopenfilename(title="Seleccione archivo", filetypes=[
                                  ("Ficheros json", "*.json"), ("todos los archivos", "*.*")])
        contenido = None
        if (ruta != ""):
            with open(ruta, mode="r", encoding="utf-8") as file:
                contenido = json.load(file)

            # print(contenido['usuarios'])
            for user in contenido['usuarios']:
                cargarUser(user["nick"], user['password'],
                           user['monedas'], user["edad"])
                #print("nick:", user['nick'])

            # En este punto se tendria que haber cargado toda la informacion del user
            # ahora a insertar los datos de la API
            users = getUsers()
            for user in users:
                self.add_row(user)

    def graphTree(self):
        res = drawTree()
        if(res == 400):
             messagebox.showerror(message="NO SE PUDO CREAR LA IMAGEN DEL ARBOL", title="Error!!!")

    def add_row(self, row):
        self.treeview.insert(
            "", tk.END, iid=row["nick"], text=row["nick"], values=(row["password"], row["monedas"], row["edad"]))

    def item_selected(self):
        for item in self.treeview.selection():
            item_child = self.treeview.get_children(item)
            item = self.treeview.item(item)
            iid = self.treeview.focus()
            #print("iid = ", iid, "Item = ", item, "Child iid's =", item_child)
            if (item['text'] == "EDD"):
                messagebox.showerror(
                    message="NO SE PUEDE ELIMINAR UN ADMIN", title="Error!!!")
            else:
                res = deleteUser(item['text'])
                if (res == 200):  # Si el codigo es 200 fue eliminado correctamente el usuario de la edd
                    # se obtiene el item seleccionado
                    select_item = self.treeview.selection()[0]
                    # Pa borrarlo en la tabla
                    self.treeview.delete(select_item)
                else:
                    text = "No se encontro el usuario a eliminar"
                    messagebox.showerror(message=text, title="Error!!!")

    def CleanTreeView(self):
        for i in self.treeview.get_children():
            self.treeview.delete(i)

    def __init__(self):
        self.main_window = tk.Tk()
        # Establecer un título.
        self.main_window.title("Vista de árbol en Tkinter")
        #utl.centrar_ventana(self.main_window, (500, 500))
        self.main_window.resizable(0, 0)

        # framep
        framep = tk.Frame(self.main_window, bd=0, width=300,
                          relief=tk.SOLID, padx=10, pady=10, bg='#3a7ff6')
        framep.pack(side="left", expand=tk.YES, fill=tk.BOTH)

        # Creación de la vista de árbol.
        self.treeview = ttk.Treeview(
            framep, columns=("password", "money", "age"))

        # Agregamos dos scrollbars

        self.vsb = ttk.Scrollbar(
            framep, orient="vertical", command=self.treeview.yview)
        self.vsb.pack(side='right', fill='y')
        self.hsb = ttk.Scrollbar(
            framep, orient="horizontal", command=self.treeview.xview)
        self.hsb.pack(side='bottom', fill='x')

        self.treeview.configure(
            xscrollcommand=self.hsb.set, yscrollcommand=self.vsb.set)

        self.treeview.heading("#0", text="Nick")
        self.treeview.heading("password", text="Password")
        self.treeview.heading("money", text="Money")
        self.treeview.heading("age", text="Age")

        """ 
        self.treeview.insert(
            "",
            tk.END,
            text="Luffy",
            values=("adjgag564f56ga", "550", "22")
        )
        """
        self.treeview.pack(expand=tk.YES, fill=tk.BOTH)
        """
        self.button = ttk.Button(self.main_window, text="Mostrar información",
                                 command=self.show_info)
        self.button.pack(after=self.treeview)
        """

        self.orderedAST = tk.Button(self.main_window, text="Ordenar Ascedente", font=(
            'Times', 15, BOLD), bg='#666a88', bd=0, fg="#fff", pady=30, command=self.orderedAst)
        self.orderedAST.pack(fill=tk.BOTH)

        self.orderedDST = tk.Button(self.main_window, text="Ordenar Descedente", font=(
            'Times', 15, BOLD), bg='#666a88', bd=0, fg="#fff", pady=30, command=self.orderedDst)
        self.orderedDST.pack(fill=tk.BOTH)

        self.cargar_users = tk.Button(self.main_window, text="cargar Usuarios", font=(
            'Times', 15, BOLD), bg='#666a88', bd=0, fg="#fff", pady=30, command=self.cargarUsers)
        self.cargar_users.pack(fill=tk.BOTH)

        self.graph_tree = tk.Button(self.main_window, text="Graficar Arbol", font=(
            'Times', 15, BOLD), bg='#666a88', bd=0, fg="#fff", pady=30, command=self.graphTree)
        self.graph_tree.pack(fill=tk.BOTH)

        self.deleteUser = tk.Button(self.main_window, text="Eliminar Usuario", font=(
            'Times', 15, BOLD), bg='#666a88', bd=0, fg="#fff", pady=30, command=self.item_selected)
        self.deleteUser.pack(fill=tk.BOTH)

        self.main_window.mainloop()