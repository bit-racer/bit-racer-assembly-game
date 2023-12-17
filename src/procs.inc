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