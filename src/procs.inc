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



GET_STARTING_TIME PROC
    PUSH AX
    PUSH CX
    PUSH DX

    MOV AH , 2CH
    INT 21H
    MOV SMINUTES , CL
    MOV SSECONDS , DH
    MOV CMINUTES , CL
    MOV CSECONDS , DH
    POP DX
    POP CX
    POP AX
    RET
GET_STARTING_TIME ENDP

GET_TIME PROC
    PUSH AX
    PUSH CX
    PUSH DX

    MOV AH , 2CH
    INT 21H
    MOV CMINUTES , CL
    MOV CSECONDS , DH

    POP DX
    POP CX
    POP AX
    RET
GET_TIME ENDP




CALC_FINISH PROC
    PUSH AX
    MOV AL , SMINUTES
    ADD AL , 1
    MOV FMINUTES , 60
    MOV AH,0
    DIV FMINUTES
    MOV FMINUTES , AH
    MOV AH , SSECONDS
    MOV FSECONDS,AH
    POP AX
    RET
CALC_FINISH ENDP


