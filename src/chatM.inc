
ScrollDown MACRO left_x, left_y, right_x, right_y
             mov ah,6        ; function 6
             mov al,1        ; scroll by 1 line
             mov bh,7        ; normal video attribute
             mov ch,left_y   ; upper left Y
             mov cl,left_x   ; upper left X
             mov dh,right_y  ; lower right Y
             mov dl,right_x  ; lower right X
             int 10h
ENDM

ClearScreen MACRO
              mov ah, 6
              mov al, 0
              mov bh, 0
              mov ch, 0
              mov cl, 0
              mov dh, 24
              mov dl, 79
              int 10h
ENDM

initPort MACRO
  ;Set Divisor Latch Access Bit
           mov dx,3fbh       ; Line Control Register
           mov al,10000000b  ;Set Divisor Latch Access Bit
           out dx,al         ;Out it
  ;Set LSB byte of the Baud Rate Divisor Latch register.
           mov dx,3f8h
           mov al,0ch
           out dx,al
  ;Set MSB byte of the Baud Rate Divisor Latch register.
           mov dx,3f9h
           mov al,00h
           out dx,al
  ;Set port configuration
           mov dx,3fbh
           mov al,00011011b
           out dx,al
ENDM

sendChar MACRO char
           mov dx,3f8h
           mov al,char
           out dx,al
ENDM

reciveChar MACRO
             mov dx,3f8h
             in  al,dx
ENDM

checkRecive MACRO
              mov dx , 3FDH  ; Line Status Register
              in  al , dx
              AND al , 1
ENDM

checkSend MACRO
            mov dx , 3FDH       ; Line Status Register
            in  al , dx
            AND al , 00100000B
ENDM

movCur MACRO row, column
         mov dh, row
         mov dl, column
         mov ah, 2
         MOV BH, 0
         int 10h
ENDM

printChar MACRO char
            mov ah, 9
            mov al, char  ; in ascii
            mov cx, 1
            mov bl, 0fh
            int 10h
ENDM


ChkKey MACRO 
  mov ah, 1
  int 16h
ENDM

GetKey MACRO
  mov ah, 0
  int 16h
ENDM