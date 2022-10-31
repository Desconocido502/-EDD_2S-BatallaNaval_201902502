from typing import List
import hashlib
from os import system
class Node:
    def __init__(self, left, right, value: str, content)-> None:
        self.left: Node = left
        self.right: Node = right
        self.value = value
        self.content = content

    @staticmethod
    def hash(val: str)-> str:
        return hashlib.sha256(val.encode('utf-8')).hexdigest()

    @staticmethod
    def doubleHash(val: str)-> str:
        return Node.hash(Node.hash(val))

class MerkleTree:
    def __init__(self, values: List[str])-> None:
        self.__values = self.calculateLength(values)
        self.__buildTree(self.__values)

    def __buildTree(self, values: List[str])-> None:
        leaves: List[Node] = [Node(None, None, Node.doubleHash(e), e) for e in values]
        if len(leaves) % 2 == 1:

            leaves.append(leaves[-1:][0]) # duplicate last elem if odd number of elements
        self.root: Node = self.__buildTreeRec(leaves)

    def __buildTreeRec(self, nodes: List[Node])-> Node:
        half: int = len(nodes) // 2

        if len(nodes) == 2:
            return Node(nodes[0], nodes[1], Node.doubleHash(nodes[0].value + nodes[1].value), nodes[0].content + nodes[1].content)

        left: Node = self.__buildTreeRec(nodes[:half])
        right: Node = self.__buildTreeRec(nodes[half:])
        value: str = Node.doubleHash(left.value + right.value)
        content: str = left.content + right.content
        return Node(left, right, value, content)

    def printTree(self)-> None:
        self.__printTreeRec(self.root)

    def __printTreeRec(self, node:Node)-> None:
        if node != None:
            print(node.content)
            self.__printTreeRec(node.left)
            self.__printTreeRec(node.right)
    
    def graficar(self, nombre):
        #print(self.__values)
        cadena = ""
        cadena += "digraph G { \n"
        cadena += "rankdir=TB; \n"
        cadena += "label=\""
        cadena += nombre + "\"\n"
        cadena += "fontname=\"Arial Black\"\n" + "fontsize=\"25pt\"\n"
        cadena += "node[color=\"blue\",style=\"rounded,filled\",fillcolor=lightgray, shape=record, fontname=\"Arial\"];\n"
        cadena +=  self.graficadora(self.root)
        cadena += "} \n"
        dotX = "MerkleTree_{}.dot".format("Base")
        file = open(dotX, "w")
        file.write(cadena)
        file.close()
        result = "MerkleTree_{}.png".format(nombre)
        system("dot -Tpng " + dotX + " -o " + result)
        commando = "xdg-open " + result
        system(commando)
        #print(cadena)
    
    def isNumeric(self, s):
        try:
            complex(s)
            return True
        except ValueError:
            return False

    def graficadora(self, node:Node):
        cadena = ""
        
        if((node.right is None) and (node.left is None)):
            cadena = "\"nodo" + node.value + "\"" + "[label =\"" + node.value + "\"]; \n"

            if (self.isNumeric(node.content)):
                cadena += "\"nodo" + node.content + "\"" + "[label =\"" + str(-1) + "\"]; \n"
                cadena += "\"nodo" + node.value + "\"" + "->" + "\"nodo" + node.content + "\"[dir=back];\n"
            else:
                cadena += "\"nodo" + node.content + "\"" + "[label =\"" + node.content + "\"]; \n"
                cadena += "\"nodo" + node.value + "\"" + "->" + "\"nodo" + node.content + "\"[dir=back];\n"

        else:
            cadena = "\"nodo" + node.value + "\"" + "[label =\"<C0>|" + node.value + "|<C1> \"]; \n"
        
        if(node.left is not None):
            cadena += self.graficadora(node.left) +  "\"nodo" + node.value + "\":C0->\"nodo" + node.left.value + "\"[dir=back]\n"
        if(node.right is not None):
            cadena += self.graficadora(node.right) + "\"nodo" + node.value +  "\":C1->\"nodo" + node.right.value + "\"[dir=back]\n"
        
        return cadena


    def getRootHash(self)-> str:
        return self.root.value
    
    def calculateLength(self, lts:list)-> list:
        k = 0
        bin = 2
        while(len(lts) >= 2 ** k):
            k += 1 #sigue creciendo
        bin = bin ** k
        nuevoLarge = bin-len(lts)
        for x in range(0, nuevoLarge):
            lts.append(str((-1) * (x+1)))
        print(lts)
        return lts