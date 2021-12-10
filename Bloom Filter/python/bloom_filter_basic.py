import hashlib

class BloomFilter:
    def __init__(self, m, k):
        self.m = m
        self.k = k
        self.data = [0]*m
        self.n = 0
    def insert(self, element):
        if self.k == 1:
            hash1 = h1(element) % self.m
            self.data[hash1] = 1
        elif self.k == 2:
            hash1 = h1(element) % self.m
            hash2 = h2(element) % self.m
            self.data[hash1] = 1
            self.data[hash2] = 1
        self.n += 1
    def search(self, element):
        if self.k == 1:
            hash1 = h1(element) % self.m
            if self.data[hash1] == 0:
                return "Not in Bloom Filter"
        elif self.k == 2:
            hash1 = h1(element) % self.m
            hash2 = h2(element) % self.m
            if self.data[hash1] == 0 or self.data[hash2] == 0:
                return "Not in Bloom Filter"
        prob = (1.0 - ((1.0 - 1.0/self.m)**(self.k*self.n))) ** self.k
        return "Might be in Bloom Filter with false positive probability "+str(prob)

def h1(w):
    h = hashlib.md5(w.encode('utf-8'))
    return hash(h.digest()[:6])%10

def h2(w):
    h = hashlib.sha256(w.encode('utf-8'))
    return hash(h.digest()[:6])%10

bf = BloomFilter(10, 2)
bf.insert("hello")

print(bf.data)

bf.insert("hi")
print(bf.data)

print(bf.search("hola"))

print(bf.search("hi"))