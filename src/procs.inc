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

DelayM MACRO counter3
           LOCAL DM_L1, DM_L2
           mov   cx, counter3
    DM_L1: 
           mov   dx, 0FFFFh
    DM_L2: 
           dec   dx
           jnz   DM_L2
           loop  DM_L1
ENDM

