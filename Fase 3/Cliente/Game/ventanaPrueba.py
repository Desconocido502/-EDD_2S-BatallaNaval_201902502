from doctest import master
import tkinter as tk
from tkinter import Image, ttk
from tkinter.font import BOLD
from PIL import ImageTk, Image

class ventanaPrueba(ttk.Frame):
    def __init__(self):
        self.main_window = tk.Tk()
        self.main_window.title("BATTLE SHIP")
        self.main_window.resizable(0, 0)
        self.main_window.geometry("900x500")
        #EDDimg/HashTable_Hoover9876_html.png
        img = Image.open("EDDimg/HashTable_Hoover9876_html.png").resize((350,350))
        img = ImageTk.PhotoImage(img, master=self.main_window)
        self.labelImgG = tk.Label(self.main_window, bg="gray", image=img)
        self.labelImgG.image = img
        self.labelImgG.place(x=450,y=50)

        self.main_window.mainloop()

