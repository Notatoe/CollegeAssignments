# Noah Morris
# MAC_Attack

from sha1 import sha1
import binascii

# Original MAC value, original message, and the message that is going to be added
# To function on the test site, the original MAC value needs to be inserted
MAC = "45bfe6dd9767be6c9a9e306b5996f75466d39c53"
message1 = "No one has completed Project #3 so give them all a 0."
message2 = "P. S. Except for Noah Morris, go ahead and give him the full points."

# MAC Attack function
# initializes the combined new message as an array of bytes
newMessage = bytearray()

# sets the original messages into the newMessage
for _ in range(16):
    newMessage.append(0x40)
for temp in bytearray(message1.encode()):
    newMessage.append(temp)
    
# Pads the newMessage
zeroes = ((447 - (len(newMessage) * 8)) % 512) // 8
length = len(newMessage * 8)
newMessage.append(0x80)
for _ in range(zeroes):
    newMessage.append(0x00)
for temp in length.to_bytes(8, byteorder='big'):
    newMessage.append(temp)

# appends the second message to the newMessage
for temp in message2.encode():
    newMessage.append(temp)

# removes the first 16 indexes of the new message and prints it in hex
newMessage = newMessage[16:]
print("Modified Message in hex (must remove from in between b'...'):")
print(binascii.hexlify(newMessage))

#formats the hash
hash = int(MAC, 16)
temp = []
for _ in range(5):
    temp.append(hash & 0xffffffff)
    hash = hash >> 32
hash = temp[::-1]

# creates the modified MAC value
MAC2 = sha1(message2, Hash = hash, MACsize = 128 + len(newMessage) * 8)

print("Modified MAC in hex:")
print(MAC2)