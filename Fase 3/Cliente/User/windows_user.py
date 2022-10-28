from pathlib import Path
from tkinter.font import BOLD
import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
import util.generic as utl
from ScrollableFrame.ScrollableFrame import ScrollableFrame
from Controlador.ControlarData import getSkins, getTutorial, updateDataUser
from PIL import ImageTk, Image
from EDD.matriz import matriz
from Game.CarritoCompra import CarritoCompra
from Game.Game import Game

class User():

    def __init__(self, user, dataPrice=None): #Se traen los datos del usuario
        self.userData = user
        self.dataPrice = dataPrice
        self.main_window = tk.Tk()
        self.main_window.title("Notebook")
        self.main_window.resizable(0, 0)
        self.main_window.geometry("1100x650")

        self.contImg = 1
        self.limitImg = 0

        self.notebook = ttk.Notebook(self.main_window)
        self.notebook.pack(fill='both', expand='yes')

        # *******************************************************************
        # Tienda
        self.page1 = ttk.Frame(self.notebook)
        self.page1.grid(row=0, column=0, sticky=tk.N+tk.E+tk.S+tk.W)
        self.notebook.add(self.page1, text="Home")

        self.userName = ttk.Label(self.page1, text=self.userData["nick"])
        self.userName.config(foreground="blue", background="green", font=("Verdana", 14))
        self.userName.place(x=980, y=10)

        self.userMoney = tk.Label(self.page1, text=self.userData["monedas"] + " Tokens Disponibles")
        self.userMoney.config(foreground="blue", background="green", font=("Verdana", 14))
        self.userMoney.place(x=730, y=10)

        self.labelTienda = ttk.Label(self.page1, text="Tienda")
        self.labelTienda.config(font=("Verdana", 14))
        self.labelTienda.place(x=500, y=15)

        imgCarritoCompra = Image.open("./img/carritoCompra.jpg")
        imgCarritoCompra = imgCarritoCompra.resize((30, 30))
        imgCarritoCompra = ImageTk.PhotoImage(imgCarritoCompra)
        self.buttonCarritoCompra = tk.Button(self.page1, text="0", image=imgCarritoCompra, background="red", command=self.comprar)
        self.buttonCarritoCompra.place(x=15, y=10)

        self.contadorComprasL = tk.Label(self.page1, text="0", foreground="white", background="red", font=("Verdana", 15))
        self.contadorComprasL.place(x=50, y=13)

        self.contadorCompras = 0
        self.ltsDatosHashTable = []

        self.totalLabel = tk.Label(self.page1, text="Total:", foreground="white", background="red", font=("Verdana", 15))
        self.totalLabel.place(x=75, y=13)
        self.totalCompra = tk.Label(self.page1, text="0", foreground="white", background="red", font=("Verdana", 15))
        self.totalCompra.place(x=135, y=13)

        self.frameRoot = tk.Frame(self.page1)
        self.frameRoot.pack(side="left")

        self.canvas = tk.Canvas(self.frameRoot, borderwidth=0, background="#ff0")

        self.frameskins = tk.Frame(self.canvas, bg="lightblue")
        self.frameskins.config(width=1100, height=500)
        #self.frameskins.place(x=10, y = 50)
        self.frameskins.pack(expand=1)

        # scrollbar
        self.scrolly = tk.Scrollbar(self.frameRoot, orient="vertical", command=self.canvas.yview)
        self.canvas.configure(yscrollcommand=self.scrolly.set)
        self.scrolly.pack(side="right", fill="y")
        self.canvas.config(width=1100, height=500)
        self.canvas.pack(side="left", fill="both", expand=True)
        self.canvas.create_window((4, 4), window=self.frameskins, anchor="sw", tags="self.frameskins")
        self.frameRoot.bind("<Configure>", self.onFrameConfigure)
        # self.populate()
        #self.scrolly.place(x=950, y=0)

        self.nuevaPartida = ttk.Button(self.page1, text="Nueva partida", command=self.newGame)
        self.nuevaPartida.place(x=10, y=580)

        self.salir = ttk.Button(self.page1, text="Salir", command=self.regresar)
        self.salir.place(x=1000, y=580)

        self.frames = []
        self.photos=[] #*Almacena las rutas de las imagenes

        self.loadSkins()

        self.page2 = ttk.Frame(self.notebook)
        self.notebook.add(self.page2, text="Tutorial")

        self.labelTutorial = ttk.Label(self.page2, text="Tutorial")
        self.labelTutorial.config(font=("Verdana", 14))
        self.labelTutorial.place(x=15, y=15)

        logo = utl.leer_imagen("./EDDimg/matrizDispersa.png", (550, 550))
        self.labelTutorialImg = tk.Label(self.page2, text="matrizDispersa.png")
        self.labelTutorialImg.config(image=logo, font=("Verdana", 14))
        self.labelTutorialImg.place(x=275, y=70)
        
        self.iniciarTutorial = tk.Button(self.page2, text="Iniciar Tutorial", font=('Times', 15, BOLD), bg='Black', bd=0, fg="#fff", pady=5, command=self.loadTutorial) #, command=self.item_selected
        self.iniciarTutorial.place(x=900, y=15)

        self.siguienteImg = tk.Button(self.page2, text="Siguiente img", font=('Times', 15, BOLD), bg='Black', bd=0, fg="#fff", pady=5, command=self.mostrarTutorial) #, command=self.item_selected
        self.siguienteImg.place(x=900, y=60)

        self.image_folder_path = "./EDDimg"
        self.image_file_extensions = {'.jpg', '.png'}
        self.images_filenames = []
        self.images = []


        self.main_window.mainloop()

    def comprar(self):
        #self.main_window.destroy()
        CarritoCompra(self.userData, self.ltsDatosHashTable, self.updateData)
    
    def updateData(self, priceShip, idShip):
        total = 0
        for x in self.ltsDatosHashTable:
            total += int(x[3])
        #print(total, priceShip)
        if(total == priceShip):
            #print("hola")
            self.ltsDatosHashTable = []
            self.totalCompra.configure(text=str(0))
            self.contadorComprasL.configure(text=str(0))
            creditoNuevo = int(self.userData["monedas"]) - total
            self.userData = updateDataUser(self.userData["nick"], self.userData["id"], self.userData["edad"], creditoNuevo, self.userData["from"], self.userData["privatekey"])
            #self.userData = getUser(self.userData["nick"])
            #print(self.userData)
            self.userMoney.configure(text=str(self.userData["monedas"]) + " Tokens Disponibles")
        else:
            #Este es para cuando se elimina un dato de la vista del arbol y de todo
            #print("hola2")
            #Se actualiza el contador y se actualiza el total de compra
            self.totalCompra.configure(text=str(int(self.totalCompra.cget("text"))-int(priceShip)))
            self.contadorCompras -= 1
            self.contadorComprasL.configure(text=str(self.contadorCompras))
            posicion = [indice for indice, dato in enumerate(self.ltsDatosHashTable) if dato[1] == idShip]
            del self.ltsDatosHashTable[posicion[0]]
            #print(self.userData["monedas"])

    def mostrarTutorial(self):
        #matriz_tutorial39_html.png
        #print(self.labelTutorialImg["text"])
        if("matrizDispersa.png" == self.labelTutorialImg["text"]):
            messagebox.showwarning(message="No se puede avanzar, inicie el tutorial", title="Observacion")
        else:
            if(self.contImg == self.limitImg):
                messagebox.showinfo(message="Ultima imagen disponible", title="Fin tutorial")
            else:
                self.contImg += 1
                #print(self.images_filenames[0])
                image_file_path = Path(f"EDDimg/matriz_tutorial{self.contImg}_html.png")
                #print(image_file_path in self.images_filenames)
                if (image_file_path in self.images_filenames):
                    #print(image_file_path)
                    img = Image.open(image_file_path).resize((550,550))
                    img = ImageTk.PhotoImage(img)
                    #self.labelTutorialImg = tk.Label(self.page2, text=image_file_path, image=img)
                    self.labelTutorialImg.configure(image=img)
                    self.images.append(img)
    
    def loadTutorial(self):
        data = getTutorial()
        tamanyoMatriz = data.pop(0)
        matrizTutorial = matriz(int(tamanyoMatriz["AnchoX"]))
        matrizTutorial.Agregarbarcos()
        nombre = "tutorial"
        cont = 1
        self.limitImg = len(data)
        #print(self.limitImg)
        #se cargan las imagenes a mostrar
        for d in data:
            matrizTutorial.MarcarDisparo(int(d["AnchoX"]), int(d['AltoY']))
            matrizTutorial.printMatrixO(nombre+str(cont))
            #print(int(d["AnchoX"]), int(d['AltoY']), cont)
            cont += 1
        self.image2 = utl.leer_imagen("./EDDimg/matriz_tutorial{}_html.png".format(str(self.contImg)), (550, 550))
        self.labelTutorialImg["text"] = "matriz_tutorial{}_html.png".format(str(self.contImg))
        self.labelTutorialImg.configure(image=self.image2)
        self.labelTutorialImg["image"] = self.image2
        self.contImg += 1

        self.images_filenames.clear()
        for filepath in Path(self.image_folder_path).iterdir():
            if(filepath.suffix in self.image_file_extensions):
                self.images_filenames.append(filepath)

    def newGame(self):
        #ventanaPrueba()
        usuarioInvitado = simpledialog.askstring("nombre invitado", "Ingresa el nombre del usuario invitado")
        tamTabla = simpledialog.askstring("Tamaño del tablero", "Ingresa el tamañano del tablero a jugar")
        Game(int(tamTabla), self.userData, usuarioInvitado)
        

    def loadSkins(self):

        skins = getSkins()#Solo para ver como impreme los valores en consola
        fila = 0
        for skin in skins:
            frameAux = ScrollableFrame(self.frameskins, direction="horizontal", width=1082, height=250)
            frameAux.grid(row=fila, column=0)
            tk.Label(frameAux.frame, text=skin["categoria"], font=("Verdana", 14)).grid(row=0, column=0)
            #print("categoria:" ,skin["categoria"])
            #print("ltsBarcos:")
            
            """
            for barco in skin["ltsBarcos"]:
                self.photos.append(utl.leer_imagen(barco["src"], (110, 110))) #Se lee la img
            self.chargeImgInLabel(frameAux.frame, self.photos)
            self.photos = []
            """

            col = 0
            #canvitas = tk.Canvas(frameAux.frame)
            #Se crea el arreglo de label tipo img
            
            for barco in skin["ltsBarcos"]:
                self.img = utl.leer_imagen(barco["src"], (110, 110)) #Se lee la img
                #self.img = ImageTk.PhotoImage(file=barco["src"])
                labelImg = tk.Label(frameAux.frame, bg='#3a7ff6', text=barco["nombre"], image=self.img) #Se crea el label donde va la img
                #labelImg.configure(image=self.img)
                labelImg.grid(row=1, column=col)
                #canvitas.configure(width=100, height=100)
                #canvitas.grid(row=1, column=col)
                #canvitas.create_image(0,0, image=self.img, anchor="nw")
                tk.Label(frameAux.frame, text=barco["precio"], font=("Verdana", 14)).grid(row=2, column=col) #Label que muestra el precio
                tk.Button(frameAux.frame, text="Comprar", borderwidth="1", relief="solid", command=lambda e=[skin["categoria"], str(barco["id"]), self.userData["nick"], barco["nombre"], barco["precio"]]:self.itemSelected(e)).grid(row=3, column=col)
                col += 1
                #print("id: ", barco["id"])
                #print("nombre: " , barco["nombre"])
                #print("precio: ", barco["precio"])
                #print("src: ", barco["src"])
                #print("-----------------")
            fila += 1
            self.frames.append(frameAux)
            #self.frames[i] = ScrollableFrame(self.frameskins, direction="horizontal", width=1082, height=250).grid(row=i, column=0)
            #tk.Label(self.frames[i], text=skin["categoria"], font=("Verdana", 14)).grid(row=0, column=0)
            #img = utl.leer_imagen("./img/loginIcon.png", (100, 100))
    

    def chargeImgInLabel(self, parent, imgs):
        col = 0
        for img in imgs:
            print(img)
            tk.Label(parent, bg='#3a7ff6', image=img).grid(row=1, column=col)
            col += 1

    def populate(self):
        '''Put in some fake data'''
        for row in range(10):
            for column in range(9):
                s = str(row) + "x" + str(column)
                tk.Button(self.frameskins, text=s, width=3, borderwidth="1", relief="solid", command=lambda e=s: self.itemSelected(e)).grid(
                    row=row, column=column, padx=5, pady=5, ipadx=15, ipady=15)

    def itemSelected(self, button_press_data):
        #print(button_press_data)
        """Se cambia este metodo directo a usar un carrito de compras"""
        categoryShip = button_press_data[0] #Categoria del barco
        idShip = button_press_data[1] #Id del barco
        nameUser = button_press_data[2] #Nombre del usuario
        nameShip = button_press_data[3] #Nombre del barco
        priceShip = button_press_data[4] #Precio del barco
        self.totalCompra.configure(text=str(int(self.totalCompra.cget("text"))+int(priceShip)))
        self.contadorCompras += 1
        self.contadorComprasL.configure(text=str(self.contadorCompras))
        #print(categoryShip, idShip, nameShip, priceShip, nameUser, self.userData["id"])
        dataRow = (categoryShip, idShip, nameShip, priceShip, nameUser, self.userData["id"])
        self.ltsDatosHashTable.append(dataRow)

        """
                        #  "categoria"    "id"    "nick"
        res = buySKinBarco(categoryShip, idShip, nameUser)
        
        if(res.status_code == 400):
            messagebox.showerror(message="NO tiene el credito suficiente para comprar la skin!", title="Error!!!")
        elif(res.status_code == 404):
            messagebox.showerror(message="Skin repetida, imposible comprar", title="Error!!!")
        elif(res.status_code == 200):
            #En caso de que todo este bien se muestran los cambios del user en la interfaz
            user = getUser(button_press_data[2])
            if (user == None):
                messagebox.showerror(message="Sucedio un error", title="error!!!")
            else:
                print(user)
                self.userMoney.configure(text=user["monedas"] + " Tokens Disponibles")
                messagebox.showinfo(message="Compra realizada correctamente!!!", title="Compra Nice")
        """ 
        
        
        
            #print(user)

        """
        for row in range(100):
            tk.Label(self.frameskins, text="%s" % row, width=3, borderwidth="1", 
                     relief="solid").grid(row=row, column=0)
            t="this is the second column for row %s" %row
            tk.Label(self.frameskins, text=t).grid(row=row, column=1)
        """

    def onFrameConfigure(self, event):
        '''Reset the scroll region to encompass the inner frame'''
        self.canvas.configure(scrollregion=self.canvas.bbox("all"))
    
    def regresar(self):
        self.main_window.destroy()
        from Login.Login import Login
        Login()