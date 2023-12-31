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

; nested empty loops
delay5s PROC
    mov cx, 0ffffh
    lbl:
        mov ax, 0b00h
        lbl1:
            dec ax
        jnz lbl1
    loop lbl

    ret
delay5s ENDP

;! require : 
;! lea si, <variable>
readUsername PROC

    ;;;;;;;;;;;;;;;;;;;;;;;;;;start
    mov cx, 0
    ; lea si, username
reading:
    ; read char
    mov ah, 0
    int 16h    ; ah = scancode, al=ascii
    cmp ah, ENTER_KEY
    je handle_enter
    cmp ah, BACKSPACE_KEY
    je handle_backspace
    cmp al, 'a'
    jl reading
    cmp al, 'z'
    jg reading
    
    ; if it is a lowercase character
    ;display char
    mov ah, 2
    mov dl, al
    int 21h
    ; move it to username ptr
    mov byte ptr [si], dl
    inc cx
    inc si
    inc currentColumn
    call moveCursor
    
    cmp cx, len_username
    jl reading
    je show_warning

    jmp done

handle_enter:
    cmp cx, 0 ; if the user have not entered anything, read again
    je reading
    jmp done_reading
    

handle_backspace:
    cmp cx, 0
    je reading
    ; move back the index
    dec si
    dec cx
    dec currentColumn
    call moveCursor
    mov byte ptr [si], '$'
    ; display null characters
    mov ah, 2
    mov dl, 0
    int 21h
    call moveCursor
    jmp reading

show_warning:
    mov bx, word ptr currentRow
    push bx
    mov bx, word ptr currentColumn
    push bx
    
    mov currentRow, row_warn
    mov currentColumn, col_warn
    call moveCursor
    mov dx, offset warning
    mov ah, 09
    int 21h
    
    pop bx
    mov currentColumn, bl
    pop bx
    mov currentRow, bl
    call moveCursor

    ; wait for backspace only
    stayHere:
        mov ah, 0
        int 16h
        cmp ah, BACKSPACE_KEY
        je clrwback
        cmp ah, ENTER_KEY
        je handle_enter
    jmp stayHere

    clrwback:
        call clear_warning
        jmp handle_backspace

    jmp reading

clear_warning:
    mov bx, word ptr currentRow
    push bx
    mov bx, word ptr currentColumn
    push bx
    push cx

    mov currentRow, row_warn
    mov currentColumn, col_warn
    call moveCursor
    
    mov cx, len_warn
    cwloop:
        mov dl, 0
        mov ah, 2
        int 21h
    loop cwloop

    ; ; try new color ;* incorrect
    ; mov ah, 09
    ; mov bh, 0
    ; mov al, 0
    ; mov cx, len_warn
    ; mov bl, 0ddh
    ; int 10h


    pop cx
    pop bx
    mov currentColumn, bl
    pop bx
    mov currentRow, bl
    call moveCursor
    ret

done_reading:

    ret
readUsername ENDP
