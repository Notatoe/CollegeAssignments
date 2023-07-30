# Noah Morris
# SRP

import random
import hashlib

# Fast Modular Exponentiation taken my previous lab
def FME(b, e, n):
    # sets product to 1 to start
    product = 1

    # if e's right most bit is 1, set product to b
    if e & 1:
        product = b
    
    b = (b * b) % n
    # goes through every bit in e
    while e:
        e = e >> 1
        
        # if the right most bit of e is 1, perform computation on the product
        if e & 1:
            product = (product * b) % n
        b = (b * b) % n

    return product

# Part 1

# Asks the user to input the values for g and p, generates value a
g = int(input("Insert g Value: "))
p = int(input("Insert p Value: "))
a = random.randint(1, 10000)
print ("a value: ", a)

# Generates the public key, g^a
publicKey =  FME(g, a, p)
print("Your public Key (g^a): ", publicKey)

# Part 2

# Asks the user to input the values for username, password, salt, iterations, and B
username = input("Insert username: ")
password = input("Insert password: ")
salt = input("Insert salt: ")
iterations = int(input("Insert iteration value: "))
B = int(input("Insert B value: "))

# Converts salt and password into byte form
saltBytes = bytearray.fromhex(salt)
passwordBytes = password.encode('ascii')

# Calculates x by putting it through sha256 as many times as specified by iterations
x = hashlib.sha256(saltBytes + passwordBytes).hexdigest()
for i in range(iterations - 1):
    xBytes = bytearray.fromhex(x)
    x = hashlib.sha256(xBytes).hexdigest()
x = int(x, 16)

# Prints the password
print("password hash: ", x)

# Converts values p and g to bytes
pBytes = p.to_bytes(((p.bit_length() + 7) // 8), 'big')
gBytes = g.to_bytes(((g.bit_length() + 7) // 8), 'big')

# Gets the value of k and prints it
k = int(hashlib.sha256(pBytes + gBytes).hexdigest(), 16)
print("k value: ", k)

# Calculates the server public key, g^b, and prints it
serverPublicKey = (B - k * FME(g, x, p)) % p
print("Server's public key (g^b): ", serverPublicKey)

# Converts the public key and the server public key into bytes
pkBytes = publicKey.to_bytes(((publicKey.bit_length() + 7) // 8), 'big')
spkBytes = serverPublicKey.to_bytes(((serverPublicKey.bit_length() + 7) // 8), 'big')

# Calculates and prints u
u = int(hashlib.sha256(pkBytes + spkBytes).hexdigest(), 16)
print("u value: ", u)

# Calculates and prints the shared key
sharedKey = FME(serverPublicKey, a + (u * x), p)
print("Shared key: ", sharedKey)

# Part 3

# Converts the username and shared key into bytes
usernameBytes = username.encode('ascii')
skBytes = sharedKey.to_bytes(((sharedKey.bit_length() + 7) // 8), 'big')

# Calculates and prints M1
M1 = hashlib.sha256((int(hashlib.sha256(pBytes).hexdigest(), 16) ^ int(hashlib.sha256(gBytes).hexdigest(),16)).to_bytes((((int(hashlib.sha256(pBytes).hexdigest(), 16) ^ int(hashlib.sha256(gBytes).hexdigest(),16)).bit_length() + 7) // 8), 'big') + (int(hashlib.sha256(usernameBytes).hexdigest(), 16)).to_bytes((((int(hashlib.sha256(usernameBytes).hexdigest(), 16)).bit_length() + 7) // 8), 'big') + saltBytes + pkBytes + spkBytes + skBytes).hexdigest()
print("M1: ", M1)

# Part 4

# Calulates and prints M2
M2 = hashlib.sha256(pkBytes + bytearray.fromhex(M1) + skBytes).hexdigest()
print("M2: ", M2)