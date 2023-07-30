# Noah Morris
# sha1
# THIS IS A MODIFIED TO WORK WITH THE MAC ATTACK

# CONSTANTS

# K constants. Each index accounts for 20
K = [0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6]

# initial hash values
H = [0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0]

# blockSize holds 512 bits as needed by Sha-1
blockSize = 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff

# HELPER FUNCTIONS

# Rotate left operation
def rotl(x, n):
    temp = (x << n) | (x >> 32 - n)
    # returns and makes sure its 32-bit
    return temp & 0xFFFFFFFF

# f function
def f(t, x, y, z):
    if t >= 0 and t <= 19:
        return (x & y) ^ (~x & z)
    elif t >= 20 and t <= 39:
        return x ^ y ^ z
    elif t >= 40 and t <= 59:
        return (x & y) ^ (x & z) ^ (y & z)
    elif t >= 60 and t <= 79:
        return x ^ y ^ z

# this function pads the message as well as parses it into 512 bit blocks
def padMessage(input, MACsize = None):
    # create the message as a string of binary
    paddedMessage = 0
    for i in range(len(input)):
        paddedMessage = paddedMessage << 8
        paddedMessage = paddedMessage | ord(input[i])

    # adds a one directly after converting to binary
    paddedMessage = paddedMessage << 1| 1

    # adds the needed amount of zeroes to the message
    temp = 0
    while True:
        if 512 * temp - ((len(input) * 8) + 1 + 64) >= 0:
            paddedMessage = paddedMessage << (512 * temp - ((len(input) * 8) + 1 + 64))
            break
        temp += 1

    # adds the length of the input in bits 
    paddedMessage = paddedMessage << 64

    # If the MACsize is given, add the MACsize to the padding, otherwise just put the length of the original input
    if MACsize is None:
        paddedMessage = paddedMessage | len(input) * 8
    else:
        paddedMessage = paddedMessage | MACsize

    # parses the padded message
    # if the message is only 512 bits, return an array with only 1 index holding the padded message
    if (paddedMessage >> 512 == 0 ):
        return [paddedMessage]
    
    # parses the message into 512 bit blocks
    M = [paddedMessage & blockSize]
    while (paddedMessage >> 512 != 0):
        paddedMessage = paddedMessage >> 512
        M.insert(0, (paddedMessage & blockSize))

    # returns an array of the parsed message
    return M

# sha-1 function
def sha1(input, Hash = None, MACsize = None):
    # if MACsize is present pad with it, otherwise pad without
    if MACsize is None:
        M = padMessage(input)
    else:
        M = padMessage(input, MACsize)
    
    # initializes the variables that are going to be used
    W = [0] * 80
    a = 0
    b = 0
    c = 0
    d = 0
    e = 0
    
    # If the hash from the MAC Attack is present, set H to its values
    if Hash is not None:
        H[0] = Hash[0]
        H[1] = Hash[1]
        H[2] = Hash[2]
        H[3] = Hash[3]
        H[4] = Hash[4]

    # for loop from the FIPS documentation
    for i in range(1, len(M)+1):
        # part 1
        for t in range(80):
            if (t >= 0 and t <= 15):
                W[t] = (M[i-1] >> ((15 - t) * 32)) & 0xFFFFFFFF
            else:
                W[t] = rotl((W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]), 1)

        # part 2
        a = H[0]
        b = H[1]
        c = H[2]
        d = H[3]
        e = H[4]

        # part 3
        for t in range(80):
            T = (rotl(a, 5) + f(t,b,c,d) + e + K[int(t/20)] + W[t]) % (2**32)
            e = d 
            d = c
            c = rotl(b, 30)
            b = a
            a = T

        # part 4
        H[0] = a + H[0]
        H[1] = b + H[1]
        H[2] = c + H[2]
        H[3] = d + H[3]
        H[4] = e + H[4]

        for i in range(5):
            H[i] = H[i] % (2**32)

    # return statement required for the MAC Attack
    return '%08x%08x%08x%08x%08x' % (H[0], H[1], H[2], H[3], H[4])