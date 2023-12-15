            
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

moveTrackUp proc 

             mtu_up:
             mov cx,[car1_Y_Offset]
             sub cx,[car1_speed]
             cmp cx, [car1_Y_Offset]
             jb  mtu_contup
             jmp mtu_borderUp
             mtu_contup:  
             MOV DIR,0
             DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],SEGMENT_SIZE,SEGMENT_SIZE
             cmp cx,1
             jne mtu_passUP 
             jmp mtu_up_end
             mtu_passUP:
             mov Where,1
             MoveTrack TRACK_IMG,[car1_X_Offset],[car1_Y_Offset],[car1_Y_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[car1_speed],[car1_width_prev],[car1_height_prev]
             jmp mtu_up_end
             mtu_borderUp:
           mtu_up_end:    
             ret
endp


  
moveTrackDown PROC
            mtd_D:
            mov      cx,[car1_Y_Offset]
            add      cx, SEGMENT_SIZE
            add      cx, [car1_speed]
            cmp      cx,SCREEN_HEIGHT
            jb       mtd_Dcont
            jmp      mtd_borderD
            mtd_Dcont:
             MOV DIR,1
            DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],SEGMENT_SIZE,SEGMENT_SIZE
            cmp cx,1
            jne mtd_passD
            jmp mtd_D_end
            mtd_passD:
            mov Where,0
            MoveTrack TRACK_IMG,[car1_X_Offset],[car1_Y_Offset],[car1_Y_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[car1_speed],[car1_width_prev],[car1_height_prev]
            jmp mtd_D_end
            mtd_borderD:

  mtd_D_end:     
             ret
             endp
moveTrackLeft PROC 

            mtl_L:
            mov cx,[car1_X_Offset]
            sub cx,[car1_speed]
            cmp cx,[car1_X_Offset]
            jb  mtl_Lcont
            jmp mtl_borderL
            mtl_Lcont:
             MOV DIR,2
            DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],SEGMENT_SIZE,SEGMENT_SIZE
            cmp cx,1
            jne mtl_passL1
            jmp mtl_L_end
            mtl_passL1:
            mov Where,1
            MoveTrack TRACK_IMG,[car1_X_Offset],[car1_Y_Offset],[car1_X_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[car1_speed],[car1_width_prev],[car1_height_prev]
            jmp mtl_L_end
            mtl_borderL:

            mtl_L_end:     
            ret
            endp
            

moveTrackRight PROC

             mtr_R:
             mov      cx,[car1_X_Offset]
             add      cx,[car1_speed]
             add      cx,SEGMENT_SIZE
             cmp      cx,SCREEN_WIDTH
             jb       mtr_Rcont
             jmp mtr_borderR
             jmp mtr_R_end
             mtr_Rcont:
              MOV DIR,3
             DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],SEGMENT_SIZE,SEGMENT_SIZE
             cmp cx,1
             jne mtr_passR1 
             jmp mtr_R_end
             mtr_passR1:
             mov Where,0
             MoveTrack TRACK_IMG,[car1_X_Offset],[car1_Y_Offset],[car1_X_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[car1_speed],[car1_width_prev],[car1_height_prev]
             jmp mtr_R_end
             mtr_borderR:
  mtr_R_end:     
             ret
             endp


main PROC 
  
  mainLoop:  
               call     sleepSomeTime
               call     moveTrackUp
               call     moveTrackDown
               call     moveTrackLeft
               call     moveTrackRight
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