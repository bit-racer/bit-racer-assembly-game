;* commonly used sequences

enterVideoMode PROC
    mov ax, 0a000h
    mov es, ax
    mov ax, 0013h
    int 10h
    ret
ENDP

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

;* first set currentColor
fillScreen PROC
    mov di, 0
    mov al, currentColor
    mov cx, SCREEN_SIZE
    rep stosb
    ret
ENDP