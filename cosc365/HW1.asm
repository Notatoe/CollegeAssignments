; Noah Morris
; netID: nmorri11

section .text
    global _start
_start:
    ; Asks the user to enter two single digit numbers
    mov eax, 4
    mov ebx, 1
    mov ecx, inpMsg
    mov edx, lenInpMsg
    int 80h
    
    ; Read and stores the first number
    mov eax, 3
    mov ebx, 0
    mov ecx, num  
    mov edx, 1         
    int 80h
   
    ; Read and stores the second number
    mov eax, 3
    mov ebx, 0
    mov ecx, num2 
    mov edx, 1         
    int 80h
   
    ; Prints the input display message
    mov eax, 4
    mov ebx, 1
    mov ecx, dispMsg
    mov edx, lenDispMsg
    int 80h  
    
    ; Output the number entered
    mov eax, 4
    mov ebx, 1
    mov ecx, num
    mov edx, 1
    int 80h  

    ; Print the and message
    mov eax, 4
    mov ebx, 1
    mov ecx, andMsg
    mov edx, lenAndMsg
    int 80h
   
    ; Output the second number entered
    mov eax, 4
    mov ebx, 1
    mov ecx, num2
    mov edx, 1
    int 80h
    
    ; Prints two newlines
    mov eax, 4
    mov ebx, 1
    mov ecx, NLMsg
    mov edx, lenNLMsg
    int 80h
   
    ; Print sum message
    mov eax, 4
    mov ebx, 1
    mov ecx, sumMsg
    mov edx, lenSumMsg
    int 80h
   
    ; Add the two numbers
    mov eax, [num]
    mov ebx, [num2]
    sub ebx, '0'
    add eax, ebx
    mov [num3], eax
   
    ; If the sum is greater than or equal to 10, jump to path
    mov ebx, ':'
    cmp al, bl
    jge path
    
    ; Prints the sum
    mov eax, 4
    mov ebx, 1
    mov ecx, num3
    mov edx, 1
    int 80h
    
    ; Jumps past the double digit path
    jmp continue
    
path:
    ; Breaks the double digit number into 2 seperate numbers
    mov ah, 0
    mov al, [num3]
    sub al, '0'
    mov bl, 10
    div bl
    add al, '0'
    mov [num3], al
    add ah, '0'
    mov [num4], ah
    
    ; Print the number in the 10s place
    mov eax, 4
    mov ebx, 1
    mov ecx, num3
    mov edx, 1
    int 80h
    
    ; Print the number in the 1s place
    mov eax, 4
    mov ebx, 1
    mov ecx, num4
    mov edx, 1
    int 80h
    
continue:
    ; Prints two newlines
    mov eax, 4
    mov ebx, 1
    mov ecx, NLMsg
    mov edx, lenNLMsg
    int 80h
   
    ; Print differnce message
    mov eax, 4
    mov ebx, 1
    mov ecx, difMsg
    mov edx, lenDifMsg
    int 80h
    
    ; compares the two numbers
    ; jumps to path2 if the first number is less than the first
    mov eax, [num]
    mov ebx, [num2]
    cmp al, bl
    jl path2
    
    ; Subtract the second number from the first
    mov eax, [num]
    mov ebx, [num2]
    sub ebx, '0'
    sub eax, ebx
    mov [num3], eax
   
    ; Jump past path2
    jmp continue2

; path2 is used for when the first number is less than the second   
path2:
    ; Subtract the first number from the second
    mov eax, [num2]
    mov ebx, [num]
    sub ebx, '0'
    sub eax, ebx
    mov [num3], eax
    
continue2:
    ; Prints the difference
    mov eax, 4
    mov ebx, 1
    mov ecx, num3
    mov edx, 1
    int 80h
    
    ; Prints two newlines
    mov eax, 4
    mov ebx, 1
    mov ecx, NLMsg
    mov edx, lenNLMsg
    int 80h
   
    ; Print product message
    mov eax, 4
    mov ebx, 1
    mov ecx, proMsg
    mov edx, lenProMsg
    int 80h
    
    ; Multiplies the two numbers together
    mov al, [num]
    sub al, '0'
    mov bl, [num2]
    sub bl, '0'
    mul bl
    add al, '0'
    mov [num3], al
    
    ; Jump to path3 if the product is a double digit number
    ; Comparison had to be in binary because for some reason it would break in ascii
    mov bl, ':'
    sub al, '0'
    sub bl, '0'
    cmp al, bl
    jge path3

    ; Prints product
    mov eax, 4
    mov ebx, 1
    mov ecx, num3
    mov edx, 1
    int 80h
    
    ; Jump past path3
    jmp continue3
    
path3:
    ; Breaks the double digit number into 2 seperate numbers
    mov ah, 0
    mov al, [num3]
    sub al, '0'
    mov bl, 10
    div bl
    add al, '0'
    mov [num3], al
    add ah, '0'
    mov [num4], ah
    
    ; Prints the number in the 10s place
    mov eax, 4
    mov ebx, 1
    mov ecx, num3
    mov edx, 1
    int 80h
    
    ; Prints the number in the 1s place
    mov eax, 4
    mov ebx, 1
    mov ecx, num4
    mov edx, 1
    int 80h

continue3:    
    ; Prints two newlines
    mov eax, 4
    mov ebx, 1
    mov ecx, NLMsg
    mov edx, lenNLMsg
    int 80h
   
    ; Print division message
    mov eax, 4
    mov ebx, 1
    mov ecx, divMsg
    mov edx, lenDivMsg
    int 80h
    
    ; Checks for dividing by zero
    mov eax, [num2]
    cmp al, '0'
    jle path4
    
    ; Print quotient message
    mov eax, 4
    mov ebx, 1
    mov ecx, quoMsg
    mov edx, lenQuoMsg
    int 80h
    
    ; Performs the division
    mov ah, 0
    mov al, [num]
    sub al, '0'
    mov bl, [num2]
    sub bl, '0'
    div bl
    add al, '0'
    mov [num3], al
    add ah, '0'
    mov [num4], ah
    
    ; Prints quotient
    mov eax, 4
    mov ebx, 1
    mov ecx, num3
    mov edx, 1
    int 80h
    
    ; Prints two newlines
    mov eax, 4
    mov ebx, 1
    mov ecx, NLMsg
    mov edx, lenNLMsg
    int 80h

    ; Print remainder message
    mov eax, 4
    mov ebx, 1
    mov ecx, remMsg
    mov edx, lenRemMsg
    int 80h
    
    ; Prints remainder
    mov eax, 4
    mov ebx, 1
    mov ecx, num4
    mov edx, 1
    int 80h
    
    ; Jump past path4
    jmp exit
    
path4:
    ; Skip division and print message due to divide by zero error
    mov eax, 4
    mov ebx, 1
    mov ecx, zerMsg
    mov edx, lenZerMsg
    int 80h

exit:
    ; Exit program
    mov eax, 1
    int 80h
    
section .data

    ; Input message for telling the user to input two sigle digit numbers
    inpMsg db 'Please enter two single digit numbers: ', 0xa, 0xD
    lenInpMsg equ $-inpMsg 
    
    ; Display message for displaying the inputted numbers
    dispMsg db 'You have entered: ', 0xa, 0xD
    lenDispMsg equ $-dispMsg
   
    ; And message that seperates the two inputted number
    andMsg db ' and '
    lenAndMsg equ $-andMsg
    
    ; Prints two newline for formatting the outputs
    NLMsg db 0xa, 0xD
    lenNLMsg equ $-NLMsg
    
    ; Sum Message for displaying the sum
    sumMsg db 'The sum of the two numbers:', 0xa, 0xD
    lenSumMsg equ $-sumMsg
    
    ; Difference message for displaying the difference
    difMsg db 'The difference between the two numbers:', 0xa, 0xD
    lenDifMsg equ $-difMsg
    
    ; Product message for displaying the difference
    proMsg db 'The product of the two numbers:', 0xa, 0xD
    lenProMsg equ $-proMsg
   
    ; Division message for showing the quotient, remainder, and instructions for setup
    divMsg db 'The division of the two numbers (first number/second number):', 0xa, 0xD
    lenDivMsg equ $-divMsg
   
    ; Quotient message for displaying the quotient
    quoMsg db 'The quotient: '
    lenQuoMsg equ $-quoMsg
    
    ; Remainder message for displaying the remiander
    remMsg db 'The remainder: '
    lenRemMsg equ $-remMsg
    
    ; Divide by zero error message for when the second number is zero
    zerMsg db 'Division ERROR: cannot divide by zero'
    lenZerMsg equ $-zerMsg
   
   
section .bss
    ; num and num2 hold the the two inputs in respective order
    num resb 1
    num2 resb 1
    
    ; num3 hold values associated to the arithmetic outputs
    num3 resb 1
    num4 resb 1