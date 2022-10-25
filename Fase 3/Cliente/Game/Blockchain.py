import hashlib
from time import time
from Block import *

class Blockchain:
    difficulty_target = "0000"

    def __init__(self) -> None:
        self.head = None
        self.tail = None
        self.count = 0
    
    def isEmpty(self):
        return self.head == None
    
    def insertBlock(self, _from, skins, difficulty_target):
        data =  Data(_from, skins)
        #print(data.skins)
        if(self.isEmpty()):
            previoushash = '0000'
            #nonce = self.proof_of_work(previoushash)
            new_block = Block(self.count, data, difficulty_target, previoushash)
            self.head = self.tail = new_block
            #Se crea el bloque en json y se almacena en la carpeta de blockchain
            self.createJSONBlock(new_block)
        else:
            aux = self.tail
            previoushash = aux.hash
            #nonce = self.proof_of_work(aux.nonce)
            new_block = Block(self.count, data, difficulty_target, previoushash)
            self.tail = aux.next = new_block
            self.tail.back = aux
            #Se crea el bloque en json y se almacena en la carpeta de blockchain
            self.createJSONBlock(new_block)
        self.count += 1

    #queda fuera de serie
    def proof_of_work(self, last_proof):
        nonce = 0
        while (self.validate_proof(last_proof, nonce)) is False:
            nonce += 1
        return nonce

    #queda fuera de serie
    def validate_proof(self, last_proof, proof):
        guess = f'{last_proof}{proof}'.encode('utf-8')
        #guess_hash = hashlib.sha256(guess).hexdigest().find(self.difficulty_target)
        guess_hash = str(hashlib.sha256(guess).hexdigest()).find(self.difficulty_target)
        return guess_hash == 0
        #return guess_hash[:len(self.difficulty_target)] == self.difficulty_target
    

    def drawBlockchain(self):
        if(self.isEmpty()):
            return 'no se puede graficar'
        else:
            temporal:Block = self.head
            cont = 0
            cadena = ""
            cadena += "digraph G { \n"
            cadena += "rankdir=LR; \n"
            cadena += 'node[shape=box style=filled color="#ffffff" fontcolor="white" fillcolor="black"];\n'
            cadena += 'graph [fontsize=15 fontname="Verdana" compound=true];\n'
            cadena += 'bgcolor="SteelBlue";\n'

            
            while(temporal):

                cadena += "  subgraph cluster_" + str(cont) + "_block {\n"
                cadena += '  bgcolor="#283747";\n  fontcolor="white";\n'
                cadena += f'    label="Block header {cont}";\n'
                cadena += f'    "Time stamp {cont}:{temporal.timestamp}" "Nonce:{str(temporal.nonce)}";\n'
                cadena += f'    "Previoushash:{temporal.previoushash}" "Hash:{temporal.hash}";\n'
                cadena += f'    "Merkle root:{temporal.merkleroot}";\n'

                cadena += "  }\n"
                if(temporal != self.head):
                    cadena += f'   "Hash:{temporal.previoushash}"->"Hash:{temporal.hash}" [ltail=cluster_{str(cont-1)}_block lhead=cluster_{str(cont)}_block];\n'
                temporal = temporal.next
                cont += 1
            cadena += "}"
            print(cadena)
            dotX = "BlockChain_{}.dot".format("BaseX")
            file = open(dotX, "w")
            file.write(cadena)
            file.close()
            result = "BlockChain_{}.png".format("BlockChainX")
            system("dot -Tpng " + dotX + " -o " + result)
            commando = "xdg-open " + result
            system(commando)
    
    def createJSONBlock(self, bloque:Block):
        timestamp:str = bloque.timestamp.replace(":","_")
        file = open(f"./blockchain/{bloque.index}_{timestamp}.json", "w")
        file.write(bloque.blockInfo())
        file.close()
    
    def __repr__(self) -> str:
        rep = "[\n"
        if (self.isEmpty()):
            rep += "]"
        else:
            aux:Block = self.head
            while aux is not None:
                rep += '\t'
                rep += f'{aux.blockInfo()},' if aux.next != None else f'{aux.blockInfo()}'
                rep += '\n'
                aux = aux.next
            rep += "]"
        return rep