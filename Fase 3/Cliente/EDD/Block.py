from datetime import datetime
import hashlib
from EDD.merkle import MerkleTree
import json

class Data:
    _from: str
    skins: list

    def __init__(self, _from=None, skins=None) -> None:
        self._from = _from
        self.skins = skins

class Block:
    difficulty_target = "0000"
    index: int
    timestamp: str
    data: Data
    nonce: int
    previoushash: str
    rootmerkle: str
    hash: str

    def __init__(self, index, data, difficulty_target, previoushash=''):
        self.index = index
        self.difficulty_target = difficulty_target
        self.timestamp = datetime.now().strftime("%d-%m-%Y::%H:%M:%S")
        self.data: Data = data
        self.nonce = 0
        self.previoushash = previoushash
        self.merkleroot = self.calcMerkleRoot()
        self.hash = self.calcBlockhash()
        self.mtEDD = None #Se toma la referencia en memoria del arbol merkle

        self.next = None
        self.back = None

    def calcMerkleRoot(self)-> str:
        elems = []
        for x in self.data.skins['data']:
            #print(x)
            elems.append(x["SKIN"]+str(x["VALUE"]))
        self.mtEDD = MerkleTree(elems)
        #mt.graficar(mt.getRootHash())
        return self.mtEDD.getRootHash()

    def calcBlockhash(self):
        # Verificar el orden de concatenacion
        nonce = 0
        while(True):
            h:str = str(self.index) + str(self.timestamp) + self.previoushash + self.merkleroot + str(nonce)
            nonce += 1
            if(str(hashlib.sha256(h.encode('utf-8')).hexdigest()).find(self.difficulty_target) == 0):
                self.nonce = nonce
                return hashlib.sha256(h.encode('utf-8')).hexdigest()
        #return hashlib.sha256(h.encode('utf-8')).hexdigest()

    def rawblockInfo(self):
        return {'index': str(self.index), 'timestamp': self.timestamp, 'nonce': str(self.nonce), "data": {"FROM": self.data._from, "SKINS": self.data.skins} ,'hash': self.hash, 'previoushash': self.previoushash, 'merkle_root': self.merkleroot}

    def blockInfo(self):
        return json.dumps(self.rawblockInfo(), indent=4)