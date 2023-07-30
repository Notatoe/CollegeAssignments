# Noah Morris
# Public-Key Cryptography

from random import randint, getrandbits
import Crypto.Util.Padding
from Crypto.Cipher import AES
from hashlib import sha256

# Part 1: Fast Modular Exponentiation
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

# Part 2: primality testing

def millerRabin(p, k = 40):
    # calculates the value of S
    S = 0
    temp = p - 1
    while temp % 2 == 0:
        temp = temp // 2
        S += 1

    # calculates the value of d
    d = (p - 1) // (2 ** S)

    # loops through k times
    for _ in range(k):
        # value that is used so that we know if the outer for loop needs to be continued or if we should return false
        primeCheck = 0

        # gets a random value between 1 and p - 1 for a
        a = randint(1, p - 1)

        # sets x for x = a^d (mod p)
        x = FME(a, d, p)

        # continues if the value of x is 1 or p - 1
        if x == 1 or x == p - 1:
            continue

        # loops through s - 1 times
        for _ in range(S - 1):
            # sets x for x = x^2 (mod p)
            x = FME(x, 2, p)

            # if x is equal to -1 mod p continue
            if x == p - 1:
                primeCheck = 1
                break

        # failed the last loop and returns false for p not being prime
        if primeCheck == 0:  
            return False
        # returns true for it most likely being prime
    return True

# Part 3: Diffie-Hellman

# takes in a generator and user number in order to create a public key and DH modulus using a randomly generated safe prime
def DH_publicKeyGenerator(g, a):
    # sets the first iteration of trying to find a safe prime
    safePrime = getrandbits(1023)
    safePrime = (1 << 1024) | safePrime
    safePrime = safePrime | 1

    # iterates indefinetley until a safe prime is found
    while True:
        # tests safePrime twice to see if it is a safe prime, if so break out of the loop
        if millerRabin(safePrime):
            safePrime2 = (safePrime - 1) // 2
            if millerRabin(safePrime2):
                break

        # update safePrime to be a new number
        safePrime = getrandbits(1023)
        safePrime = (1 << 1024) | safePrime
        safePrime = safePrime | 1

    # creates the public key using fast modular exponentiation
    print("Public key: ", FME(g, a, safePrime))
    
    # prints out the safe prime or DH modulus
    print("p: ", safePrime)

# takes in multiple values inorder to create the Shared Diffie-Hellman key and decrypts the cipher text
def DH_decryptor(a, SPK, cipherText, CBCIV, p):
    # creates the shared diffie-hellman key or g^(a*b)
    sharedKey = FME(SPK, a, p)
    print("Shared Diffie-Hellman Key: ", sharedKey)

    # gets the sha256 hash of the shared key
    sharedKey = sha256(sharedKey.to_bytes(128, byteorder = 'big')).hexdigest()
    sharedKey = sharedKey[:32]

    # convert the shared key and CBC IV into bytes
    sharedKey = bytearray.fromhex(sharedKey)
    IV = bytes.fromhex(CBCIV)
    
    # creates a AES cipher and decrypts the cipher text into the decrypted message
    cipher = AES.new(sharedKey, AES.MODE_CBC, IV)
    decryptedMessage = Crypto.Util.Padding.unpad(cipher.decrypt(bytes.fromhex(cipherText)), AES.block_size)
    print("Decrpyted Message: ", decryptedMessage)

# Part 4: RSA
def rsaValues():
    # generates primes p and q
    while True:
        # generates p
        while True:
            # sets p as a 1024 bit odd number
            p = getrandbits(1023)
            p = (1 << 1024) | p
            p = p | 1

            # if p is prime, break from the loop
            if (millerRabin(p)):
                break

        # generates q
        while True:
            # sets q as a 1024 bit odd number
            q = getrandbits(1023)
            q = (1 << 1024) | q
            q = q | 1

            # if q is prime, break from the loop
            if (millerRabin(q)):
                break

        # sets the values of n, pn, and e
        n = p * q
        pn = (p - 1) * (q - 1)
        e = 65537

        # gets the greatest common denominator in temp1 between pn and e using euclidean algorithm
        temp1 = e
        temp2 = pn
        while temp2 != 0:
            temp1, temp2 = temp2, temp1 % temp2

        # if the gcd is 1 break from the loop, otherwise restart
        if temp1 == 1:
            break
    
    # prints out the values gained
    print("First prime number (p): ", p)
    print("Second prime number (q): ", q)
    print("RSA modulus (n): ", n)
    print("φ(n): ", pn)    

    # modifiable values of e and pn
    temp1 = e
    temp2 = pn

    # initializes values of s
    s = 0
    s2 = 1
    
    # performs euclidean agorithm to obtain the value to compute d
    while temp2 > 0:
        divide = temp1 // temp2
        r = temp1 - temp2 * divide
        s3 = s2 - divide * s
      
        temp1 = temp2
        temp2 = r
        s2 = s
        s = s3
    d = s2 % pn

    # prints out the RSA private exponent
    print("RSA private exponent (d): ", d)

# encrypts the inputted message
def encryptMessage(e, n, message):
    encryptedMessage = FME(int.from_bytes(message.encode('ascii'), "big"), e, n)
    print("Encrypted value: ", encryptedMessage)

# decrypts given messages
def decryptMessage(d, n, encryptedMessage):
    decryptedMessage = FME(encryptedMessage, d, n)
    decryptedMessage = decryptedMessage.to_bytes(20, 'big')
    print("Decrypted message: ", decryptedMessage)

#*****************************
#*****************************
# SECTION FOR RUNNING THE CODE
#*****************************
#*****************************

# Part 3.1

# g or DH generator value
g = 5

# user chosen a value
a = 5001

# generates a public key and DH modulus / p
# this on fastest took 5 minutes, slowest around 30 minutes
# uncomment to run
#DH_publicKeyGenerator(g, a)

# Part 3.2

# change the values of g and a from 3.1 if needed

# server's public key or g^b value
SPK = 87710481954279462283297491068257022837400910927220516792891370873880289386224227691565205531067762872380448497354106482940813350022123565106648280125329539260514914176813358283146221297232974030351238898438169209847161810195738043704310585757206561682053270270986473361112994457089522974756710269077035542783

# Ciphertext (hex) value
cipherText = "5d187941428a43b6e1353c6a921c79ea2f5cfc8d585fa261b2e5c420138d42f7854e567da9dd590d34cc07721c813860e972b44bb4f2e8b1b40e4faa9b5d499e"

# CBC IV (hex) value
CBCIV = "9229c53ecad61a196ee7c607fc1886ae"

# DH modulus (p) value / p from 3.1
p = 208303832995046294834393562012125483515705497303370613955761303417441908760494719925130004878866493013422490791546082856879625304795653042655749004569993467391910014205297250284212545997710172857437029134220573034994771621113367164539614142120421246306814176730962389468498555193351180298255838298244991796719

# generates the shared Diffie-Hellman key and decrypts the inserted message
# uncomment to run
#DH_decryptor(a, SPK, cipherText, CBCIV, p)

# Part 4

# function that prints out all of the values needed in the first part of rsa passoff
# uncomment to run
#rsaValues()

# message needed to be encrypted
message = "brouhahas"

# RSA public exponent value
e = 65537

# RSA private exponent value
d = 18172174150864071120898946493832911193368020687163690577832055939178561304388588951756874018482252745971160208428994025030140534999741577726703572092096886088856632961686483483184724015044249703006969531252253764990212794352969152520014588766366967923093783953665889898107004771685135490979303560098307663047047844347634740898247052783587651990307138403116907714369355609165671276895530816024256408809723767397307214377448284639522196177904625410053481642893769336718546267518229205725406449883044229712191441612818516572464650883365665883593256211191344886204104869285115869545334906888716154165293852083222991247225

# RSA modulus value
n = 43818748935765798191631563205648754585516758224167437705558683177671929511965670338544105837200463527455459236168033460333357380414219205249456271540518548276441265477392364253190965737295522012802816960509178225694969494959731386316795912431708009006063406268494110388617637577612448017672122499656454958354824072892803127991073367780507319901017182634572986481353459380426045585715994774864754156119822578111309320647442227821853658266922280796592820181280104822689318952324206169439647142939396115654769964778834769105118573552649332641310918266852381686390615604789568102861197492024058965006410334205719316275367

# function that encypts a given message
# uncomment to run
#encryptMessage(e, n, message)

# message needed to be decrypted
encryptedMessage = 18998742269506959400894960667781480647932067364644589401885188712245032728668739189607052718242307460840478903884676228453608044803914270473241645406252352016446196597619059939246037309099114928534662816410763544585960943707327718067327186760233328743780927857926535628355022333979196854582429563183428353075797970678248745409573550743882147372242940857469845037244877255448042680238587871598773351250521517519085505537921989990826486405485191547595411039704331140644249382553060389168011164026260016366559756695677534542713498404651732515583827716009858071977579397462813113298483022652982712960730392528437443546819

# function that decrypts a given message
# uncomment to run
#decryptMessage(d, n, encryptedMessage)