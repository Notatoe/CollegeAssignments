; Noah Morris
; netID: nmorri11

; My macros

; Macro for writing a string
%macro writeString 2
    mov   eax, 4
    mov   ebx, 1
    mov   ecx, %1
    mov   edx, %2
    int   80h
%endmacro

; Macro for easily storing numbers
%macro storeNum 2
    mov al, [%2]
    mov [%1], al
%endmacro

; Adds 4 values together, intended to add up everything from a row
%macro addRow 5
    ; Add the value from the first column
    xor bx, bx
    add bl, [%2]
    add [%1], bx
    ; Add the value from the second column
    xor bx, bx
    mov bl, [%3]
    add [%1], bx
    ; Add the value from the third column
    xor bx, bx
    mov bl, [%4]
    add [%1], bx
    ; Add the value from the fourth column
    xor bx, bx
    mov bl, [%5]
    add [%1], bx
%endmacro

; Adds 3 values together, intended to add up everything from a column
%macro addColumn 4
    ; Add the value from the first row
    xor bx, bx
    add bl, [%2]
    add [%1], bx
    ; Add the value from the second row
    xor bx, bx
    mov bl, [%3]
    add [%1], bx
    ; Add the value from the third row
    xor bx, bx
    mov bl, [%4]
    add [%1], bx
%endmacro

section	.text
	global _start
_start:
    ; Prints message asking the user to put in 12 numbers
	writeString inpMsg, lenInpMsg
	
	; num5 is a counter for how many inputs to read in, starts at 0
	mov al, 0
	mov [num5], al
	
reset:
    ; Makes sure num2 and num3 are set to a space before reading in inputs
    mov al, ' '
    mov [num2], al
    mov [num3], al

    ; Read and stores the first digit
    mov eax, 3
    mov ebx, 0
    mov ecx, num  
    mov edx, 1         
    int 80h
    
    ; Makes sure that the first character read is not a space, jumps back to reset if so
    mov al, [num]
    cmp al, ' '
    je reset
    
    ; Read and stores the second digit
    mov eax, 3
    mov ebx, 0
    mov ecx, num2  
    mov edx, 1
    int 80h
    
    mov al, [num2]
    cmp al, 0xa
    je doneReading
    
    mov al, [num2]
    cmp al, ' '
    je doneReading
    
    ; Read and stores the third digit
    mov eax, 3
    mov ebx, 0
    mov ecx, num3  
    mov edx, 1
    int 80h
    
    mov al, [num3]
    cmp al, 0xa
    je doneReading
    
    mov al, [num3]
    cmp al, ' '
    je doneReading
    
    ; Read and stores the fourth character to make sure no >3 digit number is inputted
    mov eax, 3
    mov ebx, 0
    mov ecx, num4  
    mov edx, 1
    int 80h
    
    ; Checks for end of STDIN
    mov al, [num4]
    cmp al, 0xa
    je doneReading
    
    ; Checks for space seperating numbers
    mov al, [num4]
    cmp al, ' '
    jne inputError
    
    ; Jumps to done reading in number
    jmp doneReading
    
    ; Outputs an error message and exits the program
inputError:
    writeString inpErrMsg, lenInpErrMsg
    
    jmp exit
    
    ; Checks if the number is within the 0-250 range
doneReading:
    ; Checks if the number is a 3 digit number, if not it has to be valid
    mov al, [num3]
    cmp al, ' '
    je validNumber
    
    mov al, [num3]
    cmp al, 0xa
    je validNumber
    
    ; Checks if the 3 digit number starts with a 1, if it does it has to be valid
    mov al, [num]
    cmp al, '1'
    je validNumber
    
    ; Checks if the 3 digit number starts with a number bigger than 2, if so it is not valid
    mov al, [num]
    cmp al, '2'
    jg inputError
    
    ; Checks if the second digit is less than 5, if so it has to be valid
    mov al, [num2]
    cmp al, '5'
    jl validNumber
    
    ; Checks if the 2nd digit is greater than 5, if so it is not valid
    mov al, [num2]
    cmp al, '5'
    jg inputError
    
    ; Checks if the 3rd digit is greater than 0, if so it is not valid
    mov al, [num3]
    cmp al, '0'
    jne inputError
    
validNumber:
    ; Does an extra check specifically for newlines on the twelfth number to stop printing on the newlines
    writeString num, 1
    mov al, [num2]
    cmp al, 0xa
    je num12formating
    writeString num2, 1
    mov al, [num3]
    cmp al, 0xa
    je num12formating
    writeString num3, 1
num12formating:
    ; Double space for formatting
    writeString spcMsg, lenSpcMsg
    writeString spcMsg, lenSpcMsg
    
    ; If the second character is a space or newline, it is a one digit number
    mov al, [num2]
    cmp al, ' '
    je oneDigit
    
    mov al, [num2]
    cmp al, 0xa
    je oneDigit
    
    ; If the third character is a space or newline, it is a two digit number
    mov al, [num3]
    cmp al, ' '
    je twoDigit
    
    mov al, [num3]
    cmp al, 0xa
    je twoDigit
    
    ; Stores the number as a three digit number, multiplies and adds numbers accordingly
    mov al, [num]
    sub al, '0'
    mov bl, 100
    mul bl
    mov [num], al
    
    mov al, [num2]
    sub al, '0'
    mov bl, 10
    mul bl
    mov [num2], al
    
    mov al, [num3]
    sub al, '0'
    mov [num3], al
    
    mov al, [num]
    mov bl, [num2]
    add al, bl
    mov bl, [num3]
    add al, bl
    mov [num], al
    
    jmp storeArray
    
    ; Stores the number as a one digit number, adds the number accordingly
oneDigit:
    mov al, [num]
    sub al, '0'
    mov [num], al
    
    jmp storeArray
    
    ; Stores the number as a two digit number, multiplies and adds numbers accordingly
twoDigit:
    mov al, [num]
    sub al, '0'
    mov bl, 10
    mul bl
    mov [num], al
    
    mov al, [num2]
    sub al, '0'
    mov [num2], al
    
    mov al, [num]
    mov bl, [num2]
    add al, bl
    mov [num], al

storeArray:
    ; Checks which number was just inputted and jumps to where it should be stored
    mov al, [num5]
    cmp al, 11
    je storeNum12
    mov al, [num5]
    cmp al, 10
    je storeNum11
    mov al, [num5]
    cmp al, 9
    je storeNum10
    mov al, [num5]
    cmp al, 8
    je storeNum9
    mov al, [num5]
    cmp al, 7
    je storeNum8
    mov al, [num5]
    cmp al, 6
    je storeNum7
    mov al, [num5]
    cmp al, 5
    je storeNum6
    mov al, [num5]
    cmp al, 4
    je storeNum5
    mov al, [num5]
    cmp al, 3
    je storeNum4
    mov al, [num5]
    cmp al, 2
    je storeNum3
    mov al, [num5]
    cmp al, 1
    je storeNum2
    
    ; Stores the number in their respective array index
    storeNum array+0, num
    jmp printArray
storeNum2:
    storeNum array+1, num
    jmp printArray
storeNum3:
    storeNum array+2, num
    jmp printArray
storeNum4:
    storeNum array+3, num
    jmp printArray
storeNum5:
    storeNum array+4, num
    jmp printArray
storeNum6:
    storeNum array+5, num
    jmp printArray
storeNum7:
    storeNum array+6, num
    jmp printArray
storeNum8:
    storeNum array+7, num
    jmp printArray
storeNum9:
    storeNum array+8, num
    jmp printArray
storeNum10:
    storeNum array+9, num
    jmp printArray
storeNum11:
    storeNum array+10, num
    jmp printArray
storeNum12:
    storeNum array+11, num
    
printArray:
    ; Checks if the end of the row has been reached, if so skip to printArray2
    mov al, [num5]
    cmp al, 3
    je printArray2
    
    mov al, [num5]
    cmp al, 7
    je printArray2
    
    ; Increments the counter and resets, unless the whole array is printed out
    mov al, [num5]
    inc al
    mov [num5], al
    cmp al, 12
    jne reset
    
    jmp printed
    
printArray2:
    ; Prints a newline to seperate rows
    writeString NLMsg, lenNLMsg
    
    ; Increments the counter and resets
    mov al, [num5]
    inc al
    mov [num5], al
    jmp reset

printed:
    ; Adds each row into sum to get a sum of all numbers
    addRow sum, array+0, array+1, array+2, array+3
    addRow sum, array+4, array+5, array+6, array+7
    addRow sum, array+8, array+9, array+10, array+11
    
    ; Gets the sum of each individual row
    addRow row1, array+0, array+1, array+2, array+3
    addRow row2, array+4, array+5, array+6, array+7
    addRow row3, array+8, array+9, array+10, array+11

    ; Gets the sum of each individual column
    addColumn col1, array+0, array+4, array+8
    addColumn col2, array+1, array+5, array+9
    addColumn col3, array+2, array+6, array+10
    addColumn col4, array+3, array+7, array+11
    
    ; Resets the counter so that
    mov al, 0
    mov [num5], al
    
printSums:
    ; Checks which message should be set up for the next printed sum
    mov al, [num5]
    cmp al, 1
    je row1Sum
    mov al, [num5]
    cmp al, 2
    je row2Sum
    mov al, [num5]
    cmp al, 3
    je row3Sum
    mov al, [num5]
    cmp al, 4
    je col1Sum
    mov al, [num5]
    cmp al, 5
    je col2Sum
    mov al, [num5]
    cmp al, 6
    je col3Sum
    mov al, [num5]
    cmp al, 7
    je col4Sum
    
    ; Setup for the sum
    writeString NL2Msg, lenNL2Msg
    writeString fulSumMsg, lenFulSumMsg
    mov ax, [sum]
    mov [num6], ax
    jmp sums
    
row1Sum:
    ; Setup for row1
    writeString NL2Msg, lenNL2Msg
    writeString row1Msg, lenRow1Msg
    mov ax, [row1]
    mov [num6], ax
    jmp sums
row2Sum:
    ; Setup for row2
    writeString NL2Msg, lenNL2Msg
    writeString row2Msg, lenRow2Msg
    mov ax, [row2]
    mov [num6], ax
    jmp sums
row3Sum:
    ; Setup for row3
    writeString NL2Msg, lenNL2Msg
    writeString row3Msg, lenRow3Msg
    mov ax, [row3]
    mov [num6], ax
    jmp sums
col1Sum:
    ; Setup for col1
    writeString NL2Msg, lenNL2Msg
    writeString col1Msg, lenCol1Msg
    mov ax, [col1]
    mov [num6], ax
    jmp sums
col2Sum:
    ; Setup for col2
    writeString NL2Msg, lenNL2Msg
    writeString col2Msg, lenCol2Msg
    mov ax, [col2]
    mov [num6], ax
    jmp sums
col3Sum:
    ; Setup for col3
    writeString NL2Msg, lenNL2Msg
    writeString col3Msg, lenCol3Msg
    mov ax, [col3]
    mov [num6], ax
    jmp sums
col4Sum:
    ; Setup for col4
    writeString NL2Msg, lenNL2Msg
    writeString col4Msg, lenCol4Msg
    mov ax, [col4]
    mov [num6], ax

sums:
    ; Starts printing out the given sum
    
    ; Division for the sum, takes the remainder and puts it on the stack
    mov dx, 0
    mov ax, [num6]
    mov cx, 10
    div cx
    mov [num6], ax
    add dx, '0'
    mov [num7], dx
    push dx
    
    ; If the quotient is 0, only one digit needs to be printed
    cmp ax, 0
    je writeOneDigit

    mov dx, 0
    mov ax, [num6]
    mov cx, 10
    div cx
    mov [num6], ax
    add dx, '0'
    mov [num7], dx
    push dx
    
    ; If the quotient is 0, only two digits needs to be printed
    cmp ax, 0
    je writeTwoDigits

    mov dx, 0
    mov ax, [num6]
    mov cx, 10
    div cx
    mov [num6], ax
    add dx, '0'
    mov [num7], dx
    push dx
    
    ; If the quotient is 0, only three digits needs to be printed
    cmp ax, 0
    je writeThreeDigits

    mov dx, 0
    mov ax, [num6]
    mov cx, 10
    div cx
    mov [num6], ax
    add dx, '0'
    mov [num7], dx
    push dx
    
    ; Pops the top of the stack off to print a character of the sum
    pop dx
    mov [num7], dx
    writeString num7, 1
    
    ; Each label is for printing less and less characters as lower numbers need less
writeThreeDigits:
    pop dx
    mov [num7], dx
    writeString num7, 1

writeTwoDigits:
    pop dx
    mov [num7], dx
    writeString num7, 1

writeOneDigit:
    pop dx
    mov [num7], dx
    writeString num7, 1
    
    mov al, [num5]
    inc al
    mov [num5], al
    cmp al, 8
    jne printSums
    
exit:
	mov	eax, 1
	int	0x80

section	.data
    ; Message for telling the user what to input
    inpMsg	db	'Please enter twelve numbers (0-250) with spaces seperating them:', 0xa, 0xD
    lenInpMsg equ $-inpMsg
    
    ; Message for telling the user there was an error with their input
    inpErrMsg db 0xa, 'One inputted number was too large or had too many characters', 0xa
    lenInpErrMsg equ $-inpErrMsg
    
    ; Message for the total sum
    fulSumMsg db 'The sum of all of the numbers: '
    lenFulSumMsg equ $-fulSumMsg
    
    ; Message for the row 1 sum
    row1Msg db 'The sum of row 1: '
    lenRow1Msg equ $-row1Msg
    
    ; Message for the row 2 sum
    row2Msg db 'The sum of row 2: '
    lenRow2Msg equ $-row2Msg
    
    ; Message for the row 3 sum
    row3Msg db 'The sum of row 3: '
    lenRow3Msg equ $-row3Msg
    
    ; Message for the column 1 sum
    col1Msg db 'The sum of column 1: '
    lenCol1Msg equ $-col1Msg
    
    ; Message for the column 2 sum
    col2Msg db 'The sum of column 2: '
    lenCol2Msg equ $-col2Msg
    
    ; Message for the column 3 sum
    col3Msg db 'The sum of column 3: '
    lenCol3Msg equ $-col3Msg
    
    ; Message for the column 4 sum
    col4Msg db 'The sum of column 4: '
    lenCol4Msg equ $-col4Msg
    
    ; Message that seperates numbers as needed
    spcMsg db ' '
    lenSpcMsg equ $-spcMsg
    
    ; Newline messages
    NLMsg db 0xa 
    lenNLMsg equ $-NLMsg
    NL2Msg db 0xa, 0xD
    lenNL2Msg equ $-NL2Msg
    
    ; Array to store the inputs
    array db 0, 0, 0, 0
          db 0, 0, 0, 0
          db 0, 0, 0, 0

section .bss
    num resb 1
    num2 resb 1
    num3 resb 1
    num4 resb 1
    num5 resb 1
    num6 resb 2
    num7 resb 2
    sum resb 2
    row1 resb 2
    row2 resb 2
    row3 resb 2
    col1 resb 2
    col2 resb 2
    col3 resb 2
    col4 resb 2