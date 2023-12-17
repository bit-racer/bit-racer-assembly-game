.386
DATA SEGMENT USE16

DATA ENDS
CODE SEGMENT USE16
            ASSUME CS:CODE,DS:DATA
  BEG:      
            MOV    AX,DATA
            MOV    DS,AX

            MOV    BX, 100
  RANDSTART:
            MOV    AH, 00h          ; interrupts to get system time
            INT    1AH              ; CX:DX now hold number of clock ticks since midnight

            mov    ax, dx
            xor    dx, dx
            mov    cx, 10
            div    cx               ; here dx contains the remainder of the division - from 0 to 9

            add    dl, '0'          ; to ascii from '0' to '9'
            mov    ah, 2h           ; call interrupt to display a value in DL
            int    21h

  ; wait for delay
            pusha
            mov    cx, 1
            mov    dx, 0
            mov    ah, 86h
            int    15h
            popa

            DEC    BX
            CMP    BX, 0
            JNZ    RANDSTART

            MOV    AH,4CH
            INT    21H              ;back to dos
CODE ENDS
END BEG