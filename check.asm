.MODEL SMALL
.STACK 100h
.DATA
    msg db "Result: $"
    buffer db 6, ?, "00000$"  ; 
    A   db 3
    x DW ?
    y DW ?
.CODE
    MAIN PROC
        MOV AX, @DATA
        MOV DS, AX    

        
        MOV DX, OFFSET msg
        MOV AH, 09h     
        INT 21h



        ; Perform arithmetic here 


MOV AX, 92
PUSH AX
MOV AX, 2
POP BX
MOV DX, 0
XCHG AX, BX
IDIV BX
PUSH AX
MOV AX, 6
PUSH AX
MOV AX, 8
PUSH AX
MOV AX, 2
PUSH AX
MOV AX, 3
PUSH AX
MOV AX, 5
POP BX
IMUL BX
POP BX
IMUL BX
POP BX
ADD AX, BX
POP BX
IMUL BX
POP BX
ADD AX, BX



        CALL PrintNumber
        MOV AX, 4C00h  ; DOS Exit
        INT 21h

    MAIN ENDP

; ========== PROCEDURE TO PRINT A NUMBER ==========
PrintNumber PROC
    MOV BX, 10        ; Divisor for converting number to ASCII
    LEA DI, buffer+5  ; Point DI to last digit position
    MOV BYTE PTR [DI], '$' ; Null-terminate the string
    DEC DI            ; Move to digit position

ConvertLoop:
    XOR DX, DX        ; Clear DX before division
    DIV BX            ; AX / 10, remainder in DX
    ADD DL, '0'       ; Convert remainder to ASCII
    MOV [DI], DL      ; Store character
    DEC DI            ; Move left in buffer
    CMP AX, 0         ; Check if quotient is zero
    JNE ConvertLoop   ; If not, continue dividing

    INC DI            ; Adjust pointer to first valid digit
    MOV DX, DI        ; Load DX with converted string location
    MOV AH, 09h       ; DOS Print String function
    INT 21h           ; Print number

    RET
PrintNumber ENDP

END MAIN