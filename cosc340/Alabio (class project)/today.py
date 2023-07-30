s1 = "(())"
s2 = "((()"
s3 = ""
s4 = "()()()()()()"
s5 = ")"
s6 = "))(("

def isBalanced(str):
    count1 = 0
    count2 = 0

    for i in str:
        if i == "(":
            count1 += 1
        else:
            count2 += 1
        
        if count2 > count1:
            return False
    
    if count1 == count2:
        return True
    return False

print(isBalanced(s1) == True)
print(isBalanced(s2) == False)
print(isBalanced(s3) == True)
print(isBalanced(s4) == True)
print(isBalanced(s5) == False)
print(isBalanced(s6) == False)

# []  () {} <>
s7 = "[<>]"
s8 = "[{(()}]"
s9 = "({)}"

def isBalanced2(str):
    paren = {"[":"]", "(":")", "{":"}", "<":">"}
    stack = []
    for i in str:
        if i in paren:
            stack.append(paren[i])
        elif i not in paren and stack.pop() != i:
            return False
    return not stack

print(isBalanced2(s7) == True)
print(isBalanced2(s8) == False)
print(isBalanced2(s9) == False)