class Nodo:
    def __init__(self,fila, columna, estado,barco):
        self.fila = fila
        self.columna = columna
        self.estado = estado
        self.barco = barco
        self.right = None
        self.left = None
        self.up = None
        self.down = None

class NodoEncabezado:
    def __init__(self,id):
        self.id = id
        self.next = None
        self.prev = None
        self.accesoNodo = None