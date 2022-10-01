from cmath import exp
from email.mime import image
from textwrap import fill
import tkinter as tk
from tkinter import ttk, messagebox
import util.generic as utl
from ScrollableFrame.ScrollableFrame import ScrollableFrame
from Controlador.ControlarData import getSkins
from PIL import ImageTk, Image


class User():
    def __init__(self, user): #Se traen los datos del usuario
        self.userData = user
        self.main_window = tk.Tk()
        self.main_window.title("Notebook")
        self.main_window.resizable(0, 0)
        self.main_window.geometry("1100x650")

        self.notebook = ttk.Notebook(self.main_window)
        self.notebook.pack(fill='both', expand='yes')

        # *******************************************************************
        # Tienda
        self.page1 = ttk.Frame(self.notebook)
        self.page1.grid(row=0, column=0, sticky=tk.N+tk.E+tk.S+tk.W)
        self.notebook.add(self.page1, text="Home")

        self.userName = ttk.Label(self.page1, text=self.userData["nick"])
        self.userName.config(
            foreground="blue", background="green", font=("Verdana", 14))
        self.userName.place(x=980, y=10)

        self.labelTienda = ttk.Label(self.page1, text="Tienda")
        self.labelTienda.config(font=("Verdana", 14))
        self.labelTienda.place(x=500, y=15)

        self.frameRoot = tk.Frame(self.page1)
        self.frameRoot.pack(side="left")

        self.canvas = tk.Canvas(
            self.frameRoot, borderwidth=0, background="#ff0")

        self.frameskins = tk.Frame(self.canvas, bg="lightblue")
        self.frameskins.config(width=1100, height=500)
        #self.frameskins.place(x=10, y = 50)
        self.frameskins.pack(expand=1)

        # scrollbar
        self.scrolly = tk.Scrollbar(
            self.frameRoot, orient="vertical", command=self.canvas.yview)
        self.canvas.configure(yscrollcommand=self.scrolly.set)
        self.scrolly.pack(side="right", fill="y")
        self.canvas.config(width=1100, height=500)
        self.canvas.pack(side="left", fill="both", expand=True)
        self.canvas.create_window(
            (4, 4), window=self.frameskins, anchor="sw", tags="self.frameskins")
        self.frameRoot.bind("<Configure>", self.onFrameConfigure)
        # self.populate()
        #self.scrolly.place(x=950, y=0)

        self.nuevaPartida = ttk.Button(self.page1, text="Nueva partida")
        self.nuevaPartida.place(x=10, y=580)

        self.salir = ttk.Button(self.page1, text="Salir", command=self.regresar)
        self.salir.place(x=1000, y=580)


        """
        self.frameCategoria1 = ScrollableFrame(
        self.frameskins, direction='horizontal', width=1082, height=250)
        self.frameCategoria1.grid(row=0, column=0, sticky="nsew")

        self.frameCategoria2 = ScrollableFrame(
            self.frameskins, direction='horizontal', width=1082, height=250)
        self.frameCategoria2.grid(row=1, column=0, sticky=tk.N+tk.E+tk.S+tk.W)

        self.lots_of_labels(self.frameCategoria1.frame,
                            "blue horizontal", (5, 20))
        """
        
        self.frames = []
        self.photos=[] #*Almacena las rutas de las imagenes

        self.loadSkins()

        self.page2 = ttk.Frame(self.notebook)
        self.notebook.add(self.page2, text="About")

        self.main_window.mainloop()

    def loadSkins(self):

        skins = getSkins()#Solo para ver como impreme los valores en consola
        fila = 0
        for skin in skins:
            frameAux = ScrollableFrame(self.frameskins, direction="horizontal", width=1082, height=250)
            frameAux.grid(row=fila, column=0)
            tk.Label(frameAux.frame, text=skin["categoria"], font=("Verdana", 14)).grid(row=0, column=0)
            print("categoria:" ,skin["categoria"])
            print("ltsBarcos:")
            
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
                tk.Button(frameAux.frame, text="Comprar", borderwidth="1", relief="solid", command=lambda e=barco["nombre"]:self.itemSelected(e)).grid(row=3, column=col)
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
        

    # Populates a frame with a grid of labes of given text and same bg as frame

    def lots_of_labels(self, parent, text, dim):
        for row in range(dim[0]):
            for col in range(dim[1]):
                tk.Grid.columnconfigure(parent, col, weight=1)
                tk.Grid.rowconfigure(parent, row, weight=1)
                tk.Label(parent, fg='black', text=text,
                         bg=parent.cget('bg')).grid(row=row, column=col)

    def populate(self):
        '''Put in some fake data'''
        for row in range(10):
            for column in range(9):
                s = str(row) + "x" + str(column)
                tk.Button(self.frameskins, text=s, width=3, borderwidth="1", relief="solid", command=lambda e=s: self.itemSelected(e)).grid(
                    row=row, column=column, padx=5, pady=5, ipadx=15, ipady=15)

    def itemSelected(self, button_press):
        print(button_press)

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


#User()
        """
        skins = getSkins()#Solo para ver como impreme los valores en consola
            for skin in skins:
                print("categoria:" ,skin["categoria"])
                print("ltsBarcos:")
                for barco in skin["ltsBarcos"]:
                    print("id: ", barco["id"])
                    print("nombre: " , barco["nombre"])
                    print("precio: ", barco["precio"])
                    print("src: ", barco["src"])
                    print("-----------------")
        for i, product in ltsProducts:
                self.frames[i] = ScrollableFrame(self.frameskins, direction="horizontal", width=1082, height=250).grid(row=i, column=0)
                tk.Label(self.frames[i], text=product[0], font=("Verdana", 14)).grid(row=0, column=0)










                 bg = ImageTk.PhotoImage(file = "Your_img.png")
        canvitas = tk.Canvas(self.frameskins, width=100, height=100)
        canvitas.pack(fill="both", expand=True)
        canvitas.create_image(0,0, image="efafa", anchor="nw")
        """