; General purpose macros
readData MACRO promt, buffer
    ; print prompt string
             mov  dx, offset promt
             call printmsg

             inc  currentRow
             call moveCursor
    
    ; read username
             mov  dx, offset buffer
             mov  ah, 0ah
             int  21h

             inc  currentRow
             call moveCursor
ENDM

printData MACRO usrname, ptsString
              mov  dx, offset usrname
              call printmsg

              inc  currentRow
              call moveCursor

              mov  dx, offset ptsString
              call printmsg

              inc  currentRow
              call moveCursor
ENDM

; Delay macro with counter
delayM MACRO delay
              LOCAL delayM_L1, delayM_L2
              pusha
              mov   cx, delay
    
    delayM_L1:
              mov   dx, delay
    delayM_L2:
              DEC   DX
              jnz   delayM_L2
              loop  delayM_L1
              popa
ENDM

; Random number generator
; Generates a random number between 0 and END -1 
GenerateRandomNumber MACRO END
                         pusha
                         MOV   AH, 00h
                         INT   1Ah
                         MOV   AX, DX
                         XOR   DX, DX
                         MOV   CX, END
                         DIV   CX
                         MOV   rand_value, DX

                         popa
ENDM
