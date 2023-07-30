# Noah Morris
# Hash Attack

from sha1 import sha1
import random
from random import randint
import string

# function for the collision attack
def collisionAttack(num):
    # binary string of 1s in num length
    size = 0
    for _ in range(num):
        size = (size << 1) + 1
    
    # sets attempt number to 0 and creates an empty array to hold the created hashes
    attemptNum = 0
    hashes = []

    # goes through a loop until there is a collision
    while True:
        attemptNum += 1

        # creates a random string made up of the 52 ASCII letters, runs it through sha-1 and ands it with size
        randomString = ''.join(random.choices(string.ascii_letters, k = randint(1, 52)))
        newHash = sha1(randomString)
        newHash = newHash & size
        
        # if there is a collision break out of the loop, otherwise append and continue
        if newHash in hashes:
            break
        hashes.append(newHash)

    # return the amount of attempts it took for a collision
    return attemptNum

# function for the pre-image attack
def preImageAttack(num):
    # binary string of 1s in num length
    size = 0
    for _ in range(num):
        size = (size << 1) + 1

    # sets attempt number to 0 and creates specific hash which is what is going to be used to target the pre-image attack on
    attemptNum = 0
    randomString = ''.join(random.choices(string.ascii_letters, k= randint(1,52)))
    newHash = sha1(randomString)
    specificHash = newHash & size

    # goes through a loop until the specific hash is collided with
    while True:
        #increments counter
        attemptNum = attemptNum + 1

        # creates a hash to compare
        randomString = ''.join(random.choices(string.ascii_letters, k = randint(1,52)))
        newHash = sha1(randomString)
        newHash = newHash & size

        # compares the new hash against the one being targeted, if identical then break out of the loop
        if newHash == specificHash:
            break

    # returns the number of attempts it took for the collision
    return attemptNum

# attacks agaisnt bit size of 8
collision = []
preImage = []
for _ in range(50):
    collision.append(collisionAttack(8))
    preImage.append(preImageAttack(8))

print("8-bit collision attack: ", collision)
print("8-bit pre-image attack: ", preImage)

print("\n")

# attacks agaisnt bit size of 10
collision = []
preImage = []
for _ in range(50):
    collision.append(collisionAttack(10))
    preImage.append(preImageAttack(10))

print("10-bit collision attack: ", collision)
print("10-bit pre-image attack: ", preImage)

print("\n")

# attacks agaisnt bit size of 12
collision = []
preImage = []
for _ in range(50):
    collision.append(collisionAttack(12))
    preImage.append(preImageAttack(12))

print("12-bit collision attack: ", collision)
print("12-bit pre-image attack: ", preImage)

print("\n")

# attacks agaisnt bit size of 14
collision = []
preImage = []
for _ in range(50):
    collision.append(collisionAttack(14))
    preImage.append(preImageAttack(14))

print("14-bit collision attack: ", collision)
print("14-bit pre-image attack: ", preImage)

print("\n")

# attacks agaisnt bit size of 16
collision = []
preImage = []
for _ in range(50):
    collision.append(collisionAttack(16))
    preImage.append(preImageAttack(16))

print("16-bit collision attack: ", collision)
print("16-bit pre-image attack: ", preImage)

print("\n")

# attacks agaisnt bit size of 17
collision = []
preImage = []
for _ in range(50):
    collision.append(collisionAttack(17))
    preImage.append(preImageAttack(17))

print("17-bit collision attack: ", collision)
print("17-bit pre-image attack: ", preImage)

print("\n")

# attacks agaisnt bit size of 18
collision = []
preImage = []
for _ in range(50):
    collision.append(collisionAttack(18))
    preImage.append(preImageAttack(18))

print("18-bit collision attack: ", collision)
print("18-bit pre-image attack: ", preImage)

print("\n")

# attacks agaisnt bit size of 19
collision = []
preImage = []
for _ in range(50):
    collision.append(collisionAttack(19))
    preImage.append(preImageAttack(19))

print("19-bit collision attack: ", collision)
print("19-bit pre-image attack: ", preImage)