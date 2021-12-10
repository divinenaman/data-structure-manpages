# Bloom Filters

A bloom filter is a probabilistic data structure that is based on hashing. It is extremely space efficient and is typically used to add elements to a set and test if an element is in a set. Though, the elements themselves are not added to a set. Instead a hash of the elements is added to the set.

When testing if an element is in the bloom filter, false positives are possible. It will either say that an element is definitely not in the set or that it is possible the element is in the set.

A bloom filter is very much like a hash table in that it will use a hash function to map a key to a bucket. However, it will not store that key in that bucket, it will simply mark it as filled. So, many keys might map to same filled bucket, creating false positives.

## Properties

- An empty bloom filter is a bit array of mm bits, all of which are initially set to zero. A bit array is an extremely space-efficient data structure that has each position in the array set to either 0 or 1.

- A bloom filter also includes a set of k hash functions with which we hash incoming values. These hash functions must all have a range of 0 to m - 1m−1. If these hash functions match an incoming value with an index in the bit array, the bloom filter will make sure the bit at that position in the array is 1. Take a look at this gif showing the insertion of the strings "Hello" and "Bloom" into a bloom filter of 3 bits and 2 hash functions.

- When a query happens in a bloom filter, we once again hash the key with all kk of our hash functions. We then check all of the output bits to make sure they are all 1. If any of them is a 0, we know for sure that the key we are searching for is not in our list. If they are all 1, we know that it might be.

- False Positives: A search query might return that queried element might be present in bloom filter but it can false since the bits generated by the element might collide with other element or elements already present in bloom filter. 

## Implementation

```

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

```

## Uses of Bloom Filter In Blockchain Transaction: 

This method allows lightweight clients to limit the amount of transaction data they receive from full nodes to only those transactions that affect their wallet.
herefore, light nodes can use them to ask their peers for transactions, without revealing exactly what information the light node is interested in. 

Light nodes/wallet software will create a Bloom filter and insert into it the addresses that its wallets contain. When a light client connects to a full node, it sends this Bloom filter. In turn, whenever the full node receives a transaction, it checks if its input or output addresses match the filter. Peers will only send transactions that match the filter.
