readData MACRO promt, buffer
    ; print prompt string
    mov dx, offset promt
    call printmsg

    inc currentRow
    call moveCursor
    
    ; read username
    mov dx, offset buffer
    mov ah, 0ah
    int 21h

    inc currentRow
    call moveCursor
ENDM

printData MACRO usrname, ptsString
    mov dx, offset usrname
    call printmsg

    inc currentRow
    call moveCursor

    mov dx, offset ptsString
    call printmsg

    inc currentRow
    call moveCursor
ENDM