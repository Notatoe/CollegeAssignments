; Noah Morris
; netID: nmorri11

; Macro for writing a string
%macro writeString 2
    mov   eax, 4
    mov   ebx, 1
    mov   ecx, %1
    mov   edx, %2
    int   80h
%endmacro

section	.text
	global _start
_start:
    ; User input message displayed
    writeString inpMsg, lenInpMsg
    
restart:
    ; Initialization for each character read
    xor eax, eax
    mov [num2], eax
    mov [num3], eax
    
read:
    ; Reads in the first character
    mov eax, 3
    mov ebx, 0
    mov ecx, num  
    mov edx, 1         
    int 80h
    
    ; Checks for the end of input marker: 'X'
    mov eax, [num]
    cmp eax, 'X'
    je endOfInput
    
    ; Checks for all whitespaces
    mov eax, [num]
    cmp eax, ' '
    je whitespace
    cmp eax, 9
    je whitespace
    cmp eax, 11
    je whitespace
    cmp eax, 10
    je whitespace
    cmp eax, 13
    je whitespace
    
    mov eax, 1
    mov [num3], eax
    
    ; Multiply the current number by 10
    mov eax, [num2]
    mov ebx, 10
    mul ebx
    mov [num2], eax
    
    ; Add the new one's place digit
    xor eax, eax
    mov eax, [num]
    sub eax, '0'
    add [num2], eax
    
    jmp read
    
    ; X was found
endOfInput:
    ; Increments so nothing else is read in and program continues
    mov eax, [num5]
    inc eax
    mov [num5], eax
    
    ; Checks if nothing was inputted before X
    mov eax, [num3]
    cmp eax, 0
    je printSorted
    
    ; Inserts remaining number
    jmp insertNode

whitespace:
    ; Checks if there is a duplicate whitespace
    mov eax, [num3]
    cmp eax, 0
    je restart
    
    ; Checks if this is the first insert
    mov eax, [num4]
    cmp eax, 0
    je beginUnsortedPrint
    
    jmp insertNode
    
beginUnsortedPrint:
    ; Prints out unsorted message and increments to make sure it dosen't print this again
    writeString unsortedMsg, lenUnsortedMsg
    mov eax, [num4]
    inc eax
    mov [num4], eax
    
    
insertNode:
    ; saves the number in num6
    mov eax, [num2]
    mov [num6], eax
    
    ; prints the number
    call print
    writeString NLMsg, lenNLMsg
    
    ; puts the number back into num2
    mov eax, [num6]
    mov [num2], eax
    
    ; Allocates node and stores the address in heap_base
    mov eax, 45
    xor ebx, ebx
    int 80h
    mov [heap_base], eax
    mov eax, 45
    mov ebx, [heap_base]
    add ebx, 8
    int 80h
    
    ; Sets the node to the inputted number
    mov [temp], eax
    mov edx, [num2]
    mov [eax], edx
    add eax, 4
    mov [eax], dword 0
    
    ; Checks if this is the first insert
    cmp dword [tail], 0
    jne listPresent
    
    ; Puts node in both head and tail if first
    mov eax, [temp]
    mov [head], eax
    mov [tail], eax
    
    ; done inserting
    jmp endOfInsert

    
listPresent:
    ; checks if the node is bigger than the head node
    mov eax, [head]
    push eax
    mov eax, [eax]
    cmp eax, [num2]
    jg newHead
    pop eax
    
traverse:
    ; checks if the current node is the tail
    mov [temp2], eax
    add eax, 4
    cmp dword [eax], 0
    je newTail
    
    ; compare two nodes within the list to see if it needs to be inserted here
    mov ebx, [eax]
    mov ebx, [ebx]
    cmp ebx, [num2]
    jg insert
    
    ; Move to the next node
    mov eax, [eax]
    jmp traverse

insert:
    ; Inserts next to the node that is greater than the current one
    mov eax, [temp]
    add eax, 4
    mov ebx, [temp2]
    add ebx, 4
    mov ebx, [ebx]
    mov [eax], ebx
    mov eax, [temp2]
    add eax, 4
    mov ebx, [temp]
    mov [eax], ebx
    
    jmp endOfInsert
    
newHead:
    ; Sets the new node to head and head to the next node
    pop eax
    mov eax, [temp]
    add eax, 4
    mov ebx, [head]
    mov [eax], ebx
    mov eax, [temp]
    mov [head], eax
    
    jmp endOfInsert
    
newTail:
    ; Sets the new node to the tail
    mov eax, [tail]
    add eax, 4
    mov ebx, [temp]
    mov [eax], ebx
    mov [tail], ebx

endOfInsert:
    ; Checks if this is the final inserted node, if so move on
    xor eax, eax
    mov eax, [num5]
    cmp eax, 0
    jne printSorted
    
    jmp restart

printSorted:
    ; Prints sorted list message
    writeString NLMsg, lenNLMsg
    writeString sortedMsg, lenSortedMsg
    
    ; Starts with the head node
    mov eax, [head]
    mov [num3], eax
    
traverse2:
    ; gets the value within the current node
    mov eax, [num3]
    push eax
    mov eax, [eax]
    mov [num2], eax
    
    ; prints the value
    call print
    writeString NLMsg, lenNLMsg
    
    ; if the tail node has been printed, exit the program
    pop eax
    add eax, 4
    cmp dword [eax], 0
    je exit
    
    ; move to the next node
    mov eax, [eax]
    mov [num3], eax
    
    ;print again
    jmp traverse2
    
exit:
	mov	eax, 1
	int	0x80
	
	
	
; Procedure for printing out multi-digit numbers
print:
    ; Puts 0 into the stack to act as a marker for the end of the stack
    mov eax, 0
    push eax
    
print2:
    ; Divides the number
    xor edx, edx
    mov eax, [num2]
    mov ecx, 10
    div ecx
    
    ; Converts to ascii and pushes it on the stack
    add edx, '0'
    push edx
    
    ; checks if that was the last digit
    cmp eax, 0
    je print3
    
    ; sets up for the next digit
    mov [num2], eax
    jmp print2

print3:
    ; pops a value and checks if its the 0 marker
    pop eax
    cmp eax, 0
    je printEnd
    
    ; prints the digit
    mov [num], eax
    writeString num, 1
    jmp print3
    
printEnd:
ret

section	.data
    ; Message for telling the user what to input
    inpMsg	db	'Please enter multiple numbers (input a "X" when finished):', 0xa, 0xD
    lenInpMsg equ $-inpMsg
    
    ; Message for displaying the unsorted list
    unsortedMsg db 'Unsorted List:', 0xa, 0xD
    lenUnsortedMsg equ $-unsortedMsg
    
    ; Message for displaying the sorted list
    sortedMsg db 'Sorted List:', 0xa, 0xD
    lenSortedMsg equ $-sortedMsg
    
    ; Newline message
    NLMsg db 0xa 
    lenNLMsg equ $-NLMsg
    
    ; Link list
    head dd 0
    tail dd 0
    temp dd 0
    heap_base dd 0
    temp2 dd 0
    
    
section .bss
    num resd 1
    num2 resd 1
    num3 resd 1
    num4 resd 1
    num5 resd 1
    num6 resd 1