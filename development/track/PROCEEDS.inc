            
onKeyEvent  PROC                                                                                ; custom handler for int 09h
             push     ax bx
             in       al, 60h
             mov      ah, 0
             mov      bx, ax
             and      bx, 127                                                                   ; 7-bit scancode goes to BX
             shl      ax, 1                                                                     ; 1-bit pressed/released goes to AH
             xor      ah, 1                                                                     ; -> AH=1 Pressed, AH=0 Released
             mov      [byte ptr KeyList + bx], ah
             mov      al, 20h                                                                   ; The non specific EOI (End Of Interrupt)
             out      20h, al
             pop      bx ax
             iret
             endp
sleepSomeTime     PROC   
             mov      cx, 0
             mov      dx, 50000                                                                 ; 20ms
             mov      ah, 86h
             int      15h                                                                       ; param is cx:dx (in microseconds)
             ret
             endp

moveUp proc 
  ;* check top border
            ;  cmp   [byte ptr KeyList + 48h], 1
            ;  je    up
            ;  jmp up_end
             up:
             mov cx,[car1_Y_Offset]
             sub cx,[car1_speed]
             cmp cx, [car1_Y_Offset]
             jb  contup
             jmp borderUp
             contup:  
             MOV DIR,0
             DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],SEGMENT_SIZE,SEGMENT_SIZE
             cmp cx,1
             jne passUP 
             jmp up_end
             passUP:
             mov Where,1
             Move TRACK_IMG,[car1_X_Offset],[car1_Y_Offset],[car1_Y_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[car1_speed],[car1_width_prev],[car1_height_prev]
             jmp up_end
             borderUp:
           up_end:    
             ret
             endp
moveDown PROC
  ;* check bottom border

            D:
            mov      cx,[car1_Y_Offset]
            add      cx, SEGMENT_SIZE
            add      cx, [car1_speed]
            cmp      cx,SCREEN_HEIGHT
            jb       Dcont
            jmp      borderD
            Dcont:
             MOV DIR,1
            DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],SEGMENT_SIZE,SEGMENT_SIZE
            cmp cx,1
            jne passD
            jmp D_end
            passD:
            mov Where,0
            Move TRACK_IMG,[car1_X_Offset],[car1_Y_Offset],[car1_Y_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[car1_speed],[car1_width_prev],[car1_height_prev]
            jmp D_end
            borderD:

  D_end:     
             ret
             endp
moveLeft PROC 

            L:
            mov cx,[car1_X_Offset]
            sub cx,[car1_speed]
            cmp cx,[car1_X_Offset]
            jb  Lcont
            jmp borderL
            Lcont:
             MOV DIR,2
            DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],SEGMENT_SIZE,SEGMENT_SIZE
            cmp cx,1
            jne passL1
            jmp L_end
            passL1:
            mov Where,1
            Move TRACK_IMG,[car1_X_Offset],[car1_Y_Offset],[car1_X_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[car1_speed],[car1_width_prev],[car1_height_prev]
            jmp L_end
            borderL:

            L_end:     
            ret
            endp
            

moveRight PROC

             R:
             mov      cx,[car1_X_Offset]
             add      cx,[car1_speed]
             add      cx,SEGMENT_SIZE
             cmp      cx,SCREEN_WIDTH
             jb       Rcont
             jmp borderR
             jmp R_end
             Rcont:
              MOV DIR,3
             DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],SEGMENT_SIZE,SEGMENT_SIZE
             cmp cx,1
             jne passR1 
             jmp R_end
             passR1:
             mov Where,0
             Move TRACK_IMG,[car1_X_Offset],[car1_Y_Offset],[car1_X_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[car1_speed],[car1_width_prev],[car1_height_prev]
             jmp R_end
             borderR:
  R_end:     
             ret
             endp


main PROC 
  
  mainLoop:  
               call     sleepSomeTime
               call     moveUp
               call     moveDown
               call     moveLeft
               call     moveRight
              ;  call     moveUp2
              ;  call     moveDown2
              ;  call     moveLeft2
              ;  call     moveRight2
  ; if Esc is not pressed, jump back to mainLoop                                                                  ; -> AH=1 Pressed, AH=0 Released
             cmp     [byte ptr KeyList+01h], 1
             jne     mainLoop
    
             ret
             endP
             
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
