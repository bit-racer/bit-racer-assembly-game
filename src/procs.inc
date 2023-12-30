;* commonly used sequences



;* first set row and column variables
moveCursor PROC
    mov ah, 02
    mov bh, 0
    mov dl, currentColumn
    mov dh, currentRow
    int 10h
    ret
ENDP

;* print the offset stored in dx
printmsg PROC
    ; call moveCursor
    mov ah, 09
    int 21h
    ret
ENDP

;* welcome screen summary
printSummary PROC

    mov dx, offset str_player1
    mov ah, 09
    int 21h
    printData          username1
    
    inc  currentRow
    call moveCursor

    mov dx, offset str_player2
    mov ah, 09
    int 21h
    printData          username2

    ret
printSummary ENDP


GET_TIME PROC
    PUSH AX
    PUSH CX
    PUSH DX

    MOV AH, CSECONDS
    MOV PSECONDS, AH

    MOV AH , 02H
    INT 1AH
    MOV CMINUTES , CL
    MOV CSECONDS , DH

    POP DX
    POP CX
    POP AX
    RET
GET_TIME ENDP


PrintTimer PROC
    pusha
    MOV AH, 02h
    INT 1Ah

    MOV BX, offset TIMER_STR
    MOV AL, curdur 
    CALL PutBCD2

    pusha
    MOV currentColumn, 0
    MOV currentRow, 0
    call moveCursor
    MOV DX, offset TIMER_STR
    MOV AH, 09h
    INT 21h
    popa

    popa
    RET
PrintTimer ENDP

PutBCD2 PROC
    PUSH ax
    SHR AX, 4

    AND AX, 0Fh
    ADD AX, '0'
    MOV [BX], AL

    INC BX
    POP AX

    AND AX, 0Fh
    ADD AX, '0'
    MOV [BX], AL

    INC BX

    ret
PutBCD2 ENDP

