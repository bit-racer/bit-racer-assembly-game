.model small    ;! important
.code           ;! important
;? I am not exactly sure why these 2 lines work

enterVideoMode PROC
    mov ax, 0a000h
    mov es, ax
    mov ax, 0013h
    int 10h
    ret
ENDP

;first set row and column variables
moveCursor PROC
    mov ah, 02
    mov bh, 0
    mov dl, currentCol
    mov dh, currentRow
    int 10h
    ret
ENDP

; first set msg
printmsg PROC
    mov dx, offset msg
    mov ah, 09
    int 21h
    ret
ENDP

; first set currentColor
fillScreen PROC
    mov di, 0
    mov al, currentCol
    mov cx, SCREEN_SIZE
    rep stosb
    ret
ENDP

