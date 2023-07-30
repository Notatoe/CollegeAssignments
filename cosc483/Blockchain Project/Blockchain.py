# Noah Morris
# Blockchain

from random import SystemRandom
from hashlib import sha256

# Function that inserts a quote to the block chain using the chain hash
def addToBlockChain(hash, quote, interaton):
    while True:
        # creates the nonce value of 64 random bits
        nonce = SystemRandom().getrandbits(64)

        # Creates the hash of the block
        block = sha256(int(hash, base = 16).to_bytes(32, byteorder = "big") + nonce.to_bytes(8, byteorder = "big") + quote.encode('ascii'))

        # Checks if the first 10 bits of the block hash are all 0
        # Checks the first 4 bits first, then second 4 bits, then bits 9 and 10
        if int(block.hexdigest()[0], base = 16) == 0 and int(block.hexdigest()[1], base = 16) == 0 and (int(block.hexdigest()[2], base = 16) >> 2) == 0:
            # Prints out the successful nonce value
            print(interaton, "Nonce (int): ", nonce)

            # Prints out the hash in hex form and returns that hex hash
            print(interaton, "Hash (hex): ", block.hexdigest())
            return block.hexdigest()

# First addition asks for the genesis hash and first quote and genesis hash
hash = input("Insert genesis hash: ")
quote = input("Insert quote: ")

# adds the first quote to the blockchain, prints out the sucessful nonce and prints and saves the block hash
hash = addToBlockChain(hash, quote, "Block 1")

# Second addition asks for the second quote
quote = input("Insert second quote: ")

# adds the second quote to the blockchain, prints out the sucessful nonce and prints and saves the block hash
hash = addToBlockChain(hash, quote, "Block 2")

# Third addition asks for the third quote
quote = input("Insert third quote: ")

# adds the third quote to the blockchain, prints out the sucessful nonce and block hash
hash = addToBlockChain(hash, quote, "Block 3")