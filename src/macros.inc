; General purpose macros
readData MACRO promt, buffer
    ; print prompt string
             mov  dx, offset promt
             call printmsg

             inc  currentRow
             call moveCursor
    
    ; read username
             mov  dx, offset buffer
             mov  ah, 0ah
             int  21h

             inc  currentRow
             call moveCursor
ENDM

printData MACRO usrname
              mov  dx, offset usrname
              call printmsg

              inc  currentRow
              call moveCursor

ENDM

; Delay macro with counter
delayM MACRO delay
              LOCAL delayM_L1, delayM_L2
              pusha
              mov   cx, delay
    
    delayM_L1:
              mov   dx, delay
    delayM_L2:
              DEC   DX
              jnz   delayM_L2
              loop  delayM_L1
              popa
ENDM

; Random number generator
; Generates a random number between 0 and END -1 
GenerateRandomNumber MACRO END
                         pusha
                         MOV   AH, 00h
                         INT   1Ah
                         MOV   AX, DX
                         XOR   DX, DX
                         MOV   CX, END
                         DIV   CX
                         MOV   rand_value, DX

                         popa
ENDM

GeneralDelayINT MACRO delay
                    pusha
                    mov   cx, 0
                    mov   dx, delay
                    mov   ah, 86h
                    int   15h
                    popa
ENDM

; to print scores
print2DigitNum MACRO num
    pusha
    mov al, num
    cbw
    mov bl, 10
    div bl
    ; print what is in al => quotient (tens)
    ; print what is in ah => remainder (ones)
    ; store them
    mov bh, ah
    mov bl, al
    ; convert to ascii
    add bh, 30h
    add bl, 30h
    
    mov ah, 02
    mov dl, bl
    int 21h

    mov ah, 02
    mov dl, bh
    int 21h
    popa
ENDM

; all are 16 bits 
insideSeg MACRO seg_x, seg_y, car_x, car_y
    LOCAL notInside, Inside
    pusha

    mov ax, car_x
    mov bx, car_y
    mov cx, seg_x
    mov dx, seg_y

    cmp ax, cx
    jl notInside
    sub ax, SEGMENT_SIZE
    cmp ax, cx
    jg notInside
    cmp bx, dx
    jl notInside
    sub bx, SEGMENT_SIZE
    cmp bx, dx
    jg notInside
    mov foundHere, 1
    jmp Inside
    
    notInside:
    mov foundHere, 0

    Inside: 
    popa
ENDM
