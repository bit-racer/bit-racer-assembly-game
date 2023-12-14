            
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
             DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,car1V_Height
             cmp cx,1
             jne passUP 
             jmp up_end
             passUP:
             mov Where,1
             Move img1F,[car1_X_Offset],[car1_Y_Offset],[car1_Y_Offset],car1V_Width,car1V_Height,[car1_speed],[car1_width_prev],[car1_height_prev]
             jmp up_end
             borderUp:
            ;  DrawCar [car1_X_Offset], [car1_Y_Offset],[car1_width_prev],[car1_height_prev]
            ;  mov Erase,0
            ;  mov [car1_Y_Offset],0
            ;  DrawAtBorder img1F,[car1_X_Offset],[car1_Y_Offset],car1V_Width,car1V_Height,[car1_width_prev],[car1_height_prev]
  up_end:    
             ret
             endp
moveDown PROC
  ;* check bottom border
            ; cmp      [byte ptr KeyList + 50h], 1
            ; je      D
            ; jmp D_end
            D:
            mov      cx,[car1_Y_Offset]
            add      cx, car1V_Height
            add      cx, [car1_speed]
            cmp      cx,SCREEN_HEIGHT
            jb       Dcont
            jmp      borderD
            Dcont:
             MOV DIR,1
            DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,car1V_Height
            cmp cx,1
            jne passD
            jmp D_end
            passD:
            mov Where,0
            Move img1D,[car1_X_Offset],[car1_Y_Offset],[car1_Y_Offset],car1V_Width,car1V_Height,[car1_speed],[car1_width_prev],[car1_height_prev]
            jmp D_end
            borderD:
   
            ; DrawCar [car1_X_Offset], [car1_Y_Offset],[car1_width_prev],[car1_height_prev]
            ; mov Erase,0
            ; mov [car1_Y_Offset],SCREEN_HEIGHT-car1V_Height
            ; DrawAtBorder img1D,[car1_X_Offset],[car1_Y_Offset],car1V_Width,car1V_Height,[car1_width_prev],[car1_height_prev]
              
  D_end:     
             ret
             endp
moveLeft PROC 
  ;* check left border
            ; cmp      [byte ptr KeyList + 4bh], 1
            ; je      L
            ; jmp L_end
            L:
            mov cx,[car1_X_Offset]
            sub cx,[car1_speed]
            cmp cx,[car1_X_Offset]
            jb  Lcont
            jmp borderL
            Lcont:
             MOV DIR,2
            DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height
            cmp cx,1
            jne passL1
            jmp L_end
            passL1:
            mov Where,1
            Move img1L,[car1_X_Offset],[car1_Y_Offset],[car1_X_Offset],car1H_Width,car1H_Height,[car1_speed],[car1_width_prev],[car1_height_prev]
            jmp L_end
            borderL:

            ; DrawCar [car1_X_Offset], [car1_Y_Offset],[car1_width_prev],[car1_height_prev]
            ; mov Erase,0
            ; mov [car1_X_Offset],0
            ; DrawAtborder   img1L,[car1_X_Offset],[car1_Y_Offset],car1H_Width,car1H_Height,[car1_width_prev],[car1_height_prev]
            L_end:     
            ret
            endp
            

moveRight PROC
  ;* check right border
            ;  cmp      [byte ptr KeyList + 4dh], 1
            ;  je      R
            ;  jmp R_end
             R:
             mov      cx,[car1_X_Offset]
             add      cx,[car1_speed]
             add      cx,car1H_Width
             cmp      cx,SCREEN_WIDTH
             jb       Rcont
             jmp borderR
             jmp R_end
             Rcont:
              MOV DIR,3
             DRAW_TRACK_CONSTRAINT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height
             cmp cx,1
             jne passR1 
             jmp R_end
             passR1:
             mov Where,0
             Move img1R,[car1_X_Offset],[car1_Y_Offset],[car1_X_Offset],car1H_Width,car1H_Height,[car1_speed],[car1_width_prev],[car1_height_prev]
             jmp R_end
             borderR:

            ;  DrawCar [car1_X_Offset], [car1_Y_Offset] ,[car1_width_prev],[car1_height_prev]
            ;  mov Erase,0
            ;  mov [car1_X_Offset],SCREEN_WIDTH-car1H_Width-5
            ;  DrawAtborder   img1R,[car1_X_Offset],[car1_Y_Offset],car1H_Width,car1H_Height,[car1_width_prev],[car1_height_prev]
  R_end:     
             ret
             endp
; moveUp2 PROC
;   ;* check top border
;              cmp   [byte ptr KeyList + 11h], 1
;              je    up2
;              jmp up_end2
;              up2:
;              mov cx,[car2_Y_Offset]
;              sub cx,[car2_speed]
;              cmp cx, [car2_Y_Offset]
;              jb  contup2
;              jmp borderUp2
;              contup2:  
;              MoveUpConstraint [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width
;              cmp cx,1
;              jne passUP2 
;              jmp up_end2
;              passUP2:
;              mov Where,1
;              Move img2F,[car2_X_Offset],[car2_Y_Offset],[car2_Y_Offset],car2V_Width,car2V_Height,[car2_speed],[car2_width_prev],[car2_height_prev]
;              jmp up_end2
;              borderUp2:

;              DrawCar [car2_X_Offset], [car2_Y_Offset],[car2_width_prev],[car2_height_prev]
;              mov Erase,0
;              mov [car2_Y_Offset],0
;              DrawAtBorder img2F,[car2_X_Offset],[car2_Y_Offset],car2V_Width,car2V_Height,[car2_width_prev],[car2_height_prev]
;   up_end2:    
;              ret
;              endp
  
; moveDown2 PROC
;   ;* check bottom border
;             ;  cmp        [byte ptr KeyList + 1fh], 1
;             ;  je      D2
;             ;  jmp D_end2
;              D2:
;              mov      cx,[car2_Y_Offset]
;              add      cx, car2V_Height
;              add      cx, [car2_speed]
;              cmp      cx,SCREEN_HEIGHT
;              jb       Dcont2
;              jmp      borderD2
;              Dcont2:
;              MoveDownConstraint [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,car2V_Height
;              cmp cx,1
;              jne passD2
;              jmp D_end2
;              passD2:
;              mov Where,0
;              Move img2D,[car2_X_Offset],[car2_Y_Offset],[car2_Y_Offset],car2V_Width,car2V_Height,[car2_speed],[car2_width_prev],[car2_height_prev]
;              jmp D_end2
;              borderD2:
;              mov Erase,1
;              DrawCar [car2_X_Offset], [car2_Y_Offset],[car2_width_prev],[car2_height_prev]
;              mov Erase,0
;              mov [car2_Y_Offset],SCREEN_HEIGHT-car2V_Height
;              DrawAtBorder img2D,[car2_X_Offset],[car2_Y_Offset],car2V_Width,car2V_Height,[car2_width_prev],[car2_height_prev]
              
;   D_end2:     
;              ret
;              endp
  
; moveLeft2 PROC 
;   ;* check left border
;             ; cmp      [byte ptr KeyList + 30], 1
;             ; je      L2
;             ; jmp L_end2
;             L2:
;             mov cx,[car2_X_Offset]
;             sub cx,[car2_speed]
;             cmp cx,[car2_X_Offset]
;             jb  Lcont2
;             jmp borderL2
;             Lcont2:
;             MoveLeftConstraint [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height
;             cmp cx,1
;             jne passL2
;             jmp L_end2
;             passL2:
;             mov Where,1
;             Move img2L,[car2_X_Offset],[car2_Y_Offset],[car2_X_Offset],car2H_Width,car2H_Height,[car2_speed],[car2_width_prev],[car2_height_prev]
;             jmp L_end2
;             borderL2:
;             mov Erase,1
;             DrawCar [car2_X_Offset], [car2_Y_Offset],[car2_width_prev],[car2_height_prev]
;             mov Erase,0
;             mov [car2_X_Offset],0
;             DrawAtborder   img2L,[car2_X_Offset],[car2_Y_Offset],car2H_Width,car2H_Height,[car2_width_prev],[car2_height_prev]
;             L_end2:     
;             ret
;             endp
; moveRight2 PROC 
;   ;* check right border
;             ;  cmp     [byte ptr KeyList + 32], 1
;             ;  je      R2
;             ;  jmp R_end2
;              R2:
;              mov      cx,[car2_X_Offset]
;              add      cx,[car2_speed]
;              add      cx,car2H_Width
;              cmp      cx,SCREEN_WIDTH
;              jb       Rcont2
;              jmp borderR2
;              jmp R_end2
;              Rcont2:
;              MoveRightConstraint [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height
;              cmp cx,1
;              jne passR2 
;              jmp R_end2
;              passR2:
;              mov Where,0
;              Move img2R,[car2_X_Offset],[car2_Y_Offset],[car2_X_Offset],car2H_Width,car2H_Height,[car2_speed],[car2_width_prev],[car2_height_prev]
;              jmp R_end2
;              borderR2:
;              mov Erase,1
;              DrawCar [car2_X_Offset], [car2_Y_Offset] ,[car2_width_prev],[car2_height_prev]
;              mov Erase,0
;              mov [car2_X_Offset],SCREEN_WIDTH-car2H_Width
;              DrawAtborder   img2R,[car2_X_Offset],[car2_Y_Offset],car2H_Width,car2H_Height,[car2_width_prev],[car2_height_prev]
;   R_end2:     
;              ret
;              endp

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
