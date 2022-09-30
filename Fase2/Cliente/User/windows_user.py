import tkinter as tk
from tkinter import ttk, messagebox
from turtle import heading
from ScrollableFrame import ScrollableFrame
import json


class User:
    def __init__(self):
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

        self.userName = ttk.Label(self.page1, text="Carlos")
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

        self.salir = ttk.Button(self.page1, text="Salir")
        self.salir.place(x=1000, y=580)

        self.frameCategoria1 = ScrollableFrame(
            self.frameskins, direction='horizontal', width=1082, height=250)
        self.frameCategoria1.grid(row=0, column=0, sticky="nsew")

        self.frameCategoria2 = ScrollableFrame(
            self.frameskins, direction='horizontal', width=1082, height=250)
        self.frameCategoria2.grid(row=1, column=0, sticky=tk.N+tk.E+tk.S+tk.W)

        self.lots_of_labels(self.frameCategoria1.frame,
                            "blue horizontal", (5, 20))

        self.frames = []

        self.page2 = ttk.Frame(self.notebook)
        self.notebook.add(self.page2, text="About")

        self.main_window.mainloop()

    def lots_of_labels_buttons(self, ltsProducts):
        for i, product in ltsProducts:
                self.frames[i] = ScrollableFrame(self.frameskins, direction="horizontal", width=1082, height=250).grid(row=i, column=0)
                tk.Label(self.frames[i], text=product[0], font=("Verdana", 14)).grid(row=0, column=0)
                

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

    def itemSelected(self, label_press):
        print(label_press)

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


User()
