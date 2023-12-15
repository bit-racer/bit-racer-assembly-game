  
SRAND_SYSTEM_TIME PROC
                             PUSH                DX
                             PUSH                CX
                             PUSH                AX
                             XOR                 AX,AX
                             INT                 1AH
                             MOV                 SEED , DL
                             POP                 AX
                             POP                 CX
                             POP                 DX
                             RET
    
SRAND_SYSTEM_TIME ENDP
WAIT_FOR_DELAY PROC
                             PUSH                CX
                             MOV                 CX , DELAY
    DELAY_LOOP:              
                             LOOP                DELAY_LOOP
                             POP                 CX
                             RET
WAIT_FOR_DELAY ENDP
    
UPDATE_SEED PROC
                             PUSH                AX
                             PUSH                CX
                             PUSH                DX
                             MOV                 AH, 2CH
                             INT                 21H
                             MOV                 AH, 0
                             MOV                 AL, DL                            ;;micro seconds
                             ADD                 AL, SEED
                             MOV                 CL, DH
                             ROR                 AL, CL
                             MOV                 SEED,AL
                             POP                 DX
                             POP                 CX
                             POP                 AX
                             RET
        
UPDATE_SEED ENDP
RAND_FROM_0_TO_3 PROC
         
                             PUSH                DX
                             PUSH                BX
                             PUSH                AX

                             XOR                 DX,DX                             ; Compute randval(DX) mod 10 to get num
                             MOV                 BX,4                              ;     between 0 and 3
                             MOV                 AL,SEED
                             MOV                 AH,0
                             DIV                 BX                                ; DX = modulo from division
                             MOV                 DIRECTION , DL
                             POP                 AX
                             POP                 BX
                             POP                 DX
        

                             RET
RAND_FROM_0_TO_3 ENDP
    
GENERATE_NEW_COMBINATION PROC
                             PUSH                CX
                             PUSH                BX

                             MOV                 CX,DIR_SIZE
                             LEA                 BX,DIRECTIONS_DEMO
                             CALL                WAIT_FOR_DELAY
                             CALL                SRAND_SYSTEM_TIME
    GENERATE_ARRAY:          

                             CALL                WAIT_FOR_DELAY
                             CALL                RAND_FROM_0_TO_3
                             CALL                WAIT_FOR_DELAY
                             CALL                UPDATE_SEED

                              ; if prev is ^ and cur is v generate new
                              CMP [BX], D_UP
                              JNZ P_next
                              CMP DIRECTION, D_DOWN
                              JZ GENERATE_ARRAY
                              P_next:
                              ; if prev is v and cur is ^ generate new
                              CMP [BX], D_DOWN
                              JNZ P_next2
                              CMP DIRECTION, D_UP
                              JZ GENERATE_ARRAY
                              P_next2:
                              ;if prev is -> and cur is <- generate new
                              CMP [BX], D_RIGHT
                              JNZ P_next3
                              CMP DIRECTION, D_LEFT
                              JZ GENERATE_ARRAY
                              P_next3:
                              ;if prev is <- and cur is -> generate new
                              CMP [BX], D_LEFT
                              JNZ P_next4
                              CMP DIRECTION, D_RIGHT
                              JZ GENERATE_ARRAY
                              P_next4:
                            




                             PUSH                CX
                             MOV                 CL,DIRECTION


                             MOV                 [BX] , CL
                             POP                 CX
                             INC                 BX
                             LOOP                GENERATE_ARRAY
                             POP                 BX
                             POP                 CX
                             RET
GENERATE_NEW_COMBINATION ENDP

    ; REMOVE_OL_VALUES: 
    ; if prv <- and cur -> or prv -> and cur <-
    ; or prv ^ and cur v or prv v and cur ^
    ; then generate new value


; Generate random number between 0 and 1
RAND_FROM_0_TO_1 PROC
                             PUSH                DX
                             PUSH                BX
                             PUSH                AX

                             XOR                 DX,DX                             ; Compute randval(DX) mod 10 to get num
                             MOV                 BX,2                              ;     between 0 and 1
                             MOV                 AL,SEED
                             MOV                 AH,0
                             DIV                 BX                                ; DX = modulo from division
                             MOV                 DIRECTION , DL
                             POP                 AX
                             POP                 BX
                             POP                 DX
        

                             RET
RAND_FROM_0_TO_1 ENDP