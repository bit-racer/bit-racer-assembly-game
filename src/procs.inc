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

    MOV AH , 02h
    INT 1Ah
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




CALC_FINISH PROC
    pusha

    ; MOV AL , SMINUTES
    ; ADD AL , 1
    ; MOV FMINUTES , 60

    ; MOV AH,0

    ; DIV FMINUTES
    ; MOV FMINUTES , AH

    ; MOV AH , SSECONDS
    ; MOV FSECONDS,AH

    ; Divide duration by 60
    ; them put in fminutes the result + starting minutes
    ; put the remainder in fseconds + starting seconds

    ; MOV BL, 60
    ; MOV AX, DURATION
    ; DIV BL
    ; AAD

    ; ADD AL, SMINUTES
    ; MOV FMINUTES, AL

    ; ADD AH, SSECONDS
    ; MOV FSECONDS, AH

    MOV AL, CSECONDS
    ;ADD AL, DURATION_S
    DAA
    MOV FSECONDS, AL

    MOV AL, CMINUTES
    ADD AL, DURATION_M
    DAA
    MOV FMINUTES, AL

    popa
    RET
CALC_FINISH ENDP

PrintTimer PROC
    pusha
    MOV AH, 02h
    INT 1Ah

    MOV BX, offset TIMER_STR
    MOV AL, curdur 
    ; SUB AL, CMINUTES
    ; DAS
    CALL PutBCD2

    INC BX ; for :

    MOV AL, 10d
    ; SUB AL, CSECONDS
    ; DAS
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

