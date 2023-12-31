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
             cmp   [byte ptr KeyList + 48h], 1
             je    up
             jmp up_end
             up:
             mov cx,[car1_Y_Offset]
             sub cx,[car1_speed]
             cmp cx, [car1_Y_Offset]
             jb  contup
             jmp borderUp
             contup:  

             MoveUpConstraint [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width
             cmp COLLISION,1
             JE CHECK_P1U
             JMP passUP  
             
                                                                                                     ; THE LOGIC IS TO DETECTED IS TRACK? ELSE IS P1? ELSE IS P2? 
             CHECK_P1U:
             POWERUP_UP [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,POWERUP1_COLOR          ;P1 COLOR (POWER UP 1 COLOR)
             CMP COLLISION,1
             JE CHECK_P2U
             MOV CAR1_POWER_UP,0   
                                                                   ;MOVE THE POWER UP NUMBER TO THE BYTE THAT CARRIES CAR'S POWER UP NUMBER          
              JMP passUP


              CHECK_P2U :
               POWERUP_UP [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,POWERUP2_COLOR
                CMP COLLISION,1
                JE CHECK_P3U
              MOV CAR1_POWER_UP,1 
               JMP passUP

CHECK_P3U:
                POWERUP_UP [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,POWERUP3_COLOR
                CMP COLLISION,1
                JE CHECK_P4U
               MOV CAR1_POWER_UP,2
               JMP passUP

CHECK_P4U:
  POWERUP_UP [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,POWERUP4_COLOR
                CMP COLLISION,1
                JE U_SHIELD
              MOV CAR1_POWER_UP,3
                JMP passUP


U_SHIELD:
            CMP CAR1_HAVE_SHIELD, 0
            JE up_end
            POWERUP_UP [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,OBSTACLE_COLOR
            CMP COLLISION,1
            JE up_end
    
             passUP:
             mov Where,1
             Move img1F,[car1_X_Offset],[car1_Y_Offset],[car1_Y_Offset],car1V_Width,car1V_Height,[car1_speed],[car1_width_prev],[car1_height_prev]
             jmp up_end
             borderUp:
  up_end:    
             ret
             endp
moveDown PROC
  ;* check bottom border
            cmp      [byte ptr KeyList + 50h], 1
            je      D
            jmp D_end
            D:
            mov      cx,[car1_Y_Offset]
            add      cx, car1V_Height
            add      cx, [car1_speed]
            cmp      cx,SCREEN_HEIGHT
            jb       Dcont
            jmp      borderD
            Dcont:

            MoveDownConstraint [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,car1V_Height
            cmp COLLISION,1
             JE CHECK_P1D
             JMP passD

             CHECK_P1D:
             POWERUP_DOWN  [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,car1V_Height,POWERUP1_COLOR          ;P1 COLOR (POWER UP 1 COLOR)
             CMP COLLISION,1
             JE CHECK_P2D
        
             MOV CAR1_POWER_UP,0                                                                           ;MOVE THE POWER UP NUMBER TO THE BYTE THAT CARRIES CAR'S POWER UP NUMBER          
             JMP passD


              CHECK_P2D :
                POWERUP_DOWN  [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,car1V_Height,POWERUP2_COLOR
                CMP COLLISION,1
                JE CHECK_P3D
                MOV CAR1_POWER_UP,1  
           JMP passD

CHECK_P3D:
                POWERUP_DOWN [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,car1V_Height,POWERUP3_COLOR
                CMP COLLISION,1
                JE CHECK_P4D
                MOV CAR1_POWER_UP,2
                JMP passD

CHECK_P4D:
                POWERUP_DOWN [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,car1V_Height,POWERUP4_COLOR
                CMP COLLISION,1
                JE D_SHIELD
                MOV CAR1_POWER_UP,3
                JMP passD



D_SHIELD:
            CMP CAR1_HAVE_SHIELD, 0
            JE D_end
            POWERUP_DOWN [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1V_Width,car1V_Height,OBSTACLE_COLOR
            CMP COLLISION,1
            JE D_end


            passD:
            mov Where,0
            Move img1D,[car1_X_Offset],[car1_Y_Offset],[car1_Y_Offset],car1V_Width,car1V_Height,[car1_speed],[car1_width_prev],[car1_height_prev]
            jmp D_end
            borderD:
              
  D_end:     
             ret
             endp
moveLeft PROC 
  ;* check left border
            cmp      [byte ptr KeyList + 4bh], 1
            je      L
            jmp L_end
            L:
            mov cx,[car1_X_Offset]
            sub cx,[car1_speed]
            cmp cx,[car1_X_Offset]
            jb  Lcont
            jmp borderL
            Lcont:

            MoveLeftConstraint [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height
              cmp COLLISION,1
              JE CHECK_P1L  ; THE LOGIC IS TO DETECTED IS TRACK? ELSE IS P1? ELSE IS P2? 
              JMP passL1  
             
                                                                                                 
             CHECK_P1L:
             POWERUP_LEFT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height,POWERUP1_COLOR          ;P1 COLOR (POWER UP 1 COLOR)
             CMP COLLISION,1
             JE CHECK_P2L
      
             MOV CAR1_POWER_UP,0                                                                           ;MOVE THE POWER UP NUMBER TO THE BYTE THAT CARRIES CAR'S POWER UP NUMBER          
             JMP passL1


  CHECK_P2L :
              POWERUP_LEFT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height,POWERUP2_COLOR
                CMP COLLISION,1
                JE CHECK_P3L
                MOV CAR1_POWER_UP,1 
                JMP passL1 
  CHECK_P3L:
                 POWERUP_LEFT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height,POWERUP3_COLOR
                CMP COLLISION,1
                JE CHECK_P4L
                MOV CAR1_POWER_UP,2
                JMP passL1
 
  CHECK_P4L:
                  POWERUP_LEFT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height,POWERUP4_COLOR
                CMP COLLISION,1
                JE L_SHIELD
                MOV CAR1_POWER_UP,3
                JMP passL1


L_SHIELD:
            CMP CAR1_HAVE_SHIELD, 0
            JE L_end
            POWERUP_LEFT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height,OBSTACLE_COLOR
            CMP COLLISION,1
            JE L_end

            passL1:
            mov Where,1
            Move img1L,[car1_X_Offset],[car1_Y_Offset],[car1_X_Offset],car1H_Width,car1H_Height,[car1_speed],[car1_width_prev],[car1_height_prev]
            jmp L_end
            borderL:

            L_end:     
            ret
            endp
            

moveRight PROC
  ;* check right border
             cmp      [byte ptr KeyList + 4dh], 1
             je      R
             jmp R_end
             R:
             mov      cx,[car1_X_Offset]
             add      cx,[car1_speed]
             add      cx,car1H_Width
             cmp      cx,SCREEN_WIDTH
             jb       Rcont
             jmp borderR
             Rcont:
             MoveRightConstraint [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height
             cmp COLLISION,1
             JE CHECK_P1R
             JMP passR1
             
             
                                                                                                        ; THE LOGIC IS TO DETECTED IS TRACK? ELSE IS P1? ELSE IS P2? 
             CHECK_P1R:
             POWERUP_RIGHT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height,POWERUP1_COLOR          ;P1 COLOR (POWER UP 1 COLOR)
              CMP COLLISION,1
              JE CHECK_P2R
            
              MOV CAR1_POWER_UP,0                                                                           ;MOVE THE POWER UP NUMBER TO THE BYTE THAT CARRIES CAR'S POWER UP NUMBER          
              JMP passR1


              CHECK_P2R :
             POWERUP_RIGHT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height,POWERUP2_COLOR
              CMP COLLISION,1
              JE CHECK_P3R
              MOV CAR1_POWER_UP,1 
              JMP passR1 
     
 CHECK_P3R:
                 POWERUP_RIGHT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height,POWERUP3_COLOR
                CMP COLLISION,1
                JE CHECK_P4R
                MOV CAR1_POWER_UP,2
                JMP passR1

CHECK_P4R:
                POWERUP_RIGHT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height,POWERUP4_COLOR
                CMP COLLISION,1
                JE R_SHIELD
                MOV CAR1_POWER_UP,3
                JMP passR1


R_SHIELD:
            CMP CAR1_HAVE_SHIELD, 0
            JE R_end
            POWERUP_RIGHT [car1_X_Offset],[car1_Y_Offset],[car1_speed],car1H_Width,car1H_Height,OBSTACLE_COLOR
            CMP COLLISION,1
            JE R_end


             passR1:
             mov Where,0
             Move img1R,[car1_X_Offset],[car1_Y_Offset],[car1_X_Offset],car1H_Width,car1H_Height,[car1_speed],[car1_width_prev],[car1_height_prev]
             jmp R_end
             borderR:
  
  R_end:     
             ret
             endp
moveUp2 PROC
  ;* check top border
             cmp   [byte ptr KeyList + 11h], 1
             je    up2
             jmp up_end2
             up2:
             mov cx,[car2_Y_Offset]
             sub cx,[car2_speed]
             cmp cx, [car2_Y_Offset]
             jb  contup2
             jmp borderUp2
             contup2:  

             MoveUpConstraint [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width
             cmp COLLISION,1                                                                                              ;CX IS 1 WHEN THERE IS A COLLISION
             JE CHECK2_P1U
             JMP passUP2  
                                                                                                      ; THE LOGIC IS TO DETECTED IS TRACK? ELSE IS P1? ELSE IS P2? 
CHECK2_P1U:
             POWERUP_UP [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,POWERUP1_COLOR          ;P1 COLOR (POWER UP 1 COLOR)
             CMP COLLISION,1
             JE CHECK2_P2U
 
             MOV CAR2_POWER_UP,0                                                                           ;MOVE THE POWER UP NUMBER TO THE BYTE THAT CARRIES CAR'S POWER UP NUMBER          
              JMP passUP2

   CHECK2_P2U :
              POWERUP_UP [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,POWERUP2_COLOR
              CMP COLLISION,1
              JE CHECK2_P3U
              MOV CAR2_POWER_UP,1  
              JMP passUP2
CHECK2_P3U:
               POWERUP_UP [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,POWERUP3_COLOR
                CMP COLLISION,1
                JE CHECK2_P4U
              MOV CAR2_POWER_UP,2
               JMP passUP2

CHECK2_P4U:
                 POWERUP_UP [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,POWERUP4_COLOR
                CMP COLLISION,1
                JE U2_SHIELD
                MOV CAR2_POWER_UP,3
                JMP passUP2


U2_SHIELD:
            CMP CAR2_HAVE_SHIELD, 0
            JE up_end2
            POWERUP_UP [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,OBSTACLE_COLOR
            CMP COLLISION,1
            JE up_end2
    
             passUP2:
             mov Where,1
             Move img2F,[car2_X_Offset],[car2_Y_Offset],[car2_Y_Offset],car2V_Width,car2V_Height,[car2_speed],[car2_width_prev],[car2_height_prev]
             jmp up_end2
             borderUp2:
            
  up_end2:    
             ret
             endp
  
moveDown2 PROC
  ;* check bottom border
             cmp        [byte ptr KeyList + 1fh], 1
             je      D2
             jmp D_end2
             D2:
             mov      cx,[car2_Y_Offset]
             add      cx, car2V_Height
             add      cx, [car2_speed]
             cmp      cx,SCREEN_HEIGHT
             jb       Dcont2
             jmp      borderD2
             Dcont2:

             MoveDownConstraint [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,car2V_Height
             cmp COLLISION,1                 ;CX IS 1 WHEN THERE IS A COLLISION
             JE CHECK2_P1D
             JMP passD2 
                                                                                                       ; THE LOGIC IS TO DETECTED IS TRACK? ELSE IS P1? ELSE IS P2? 
             CHECK2_P1D:
            POWERUP_DOWN [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,car2V_Height,POWERUP1_COLOR          ;P1 COLOR (POWER UP 1 COLOR)
             CMP COLLISION,1
             JE CHECK2_P2D
             MOV CAR2_POWER_UP,0 
                                                                            ;MOVE THE POWER UP NUMBER TO THE BYTE THAT CARRIES CAR'S POWER UP NUMBER          
              JMP passD2

              CHECK2_P2D :
             POWERUP_DOWN [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,car2V_Height,POWERUP2_COLOR
              CMP COLLISION,1
              JE CHECK2_P3D
              MOV CAR2_POWER_UP,1 
             JMP passD2

CHECK2_P3D:
              POWERUP_DOWN [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,car2V_Height,POWERUP3_COLOR
                CMP COLLISION,1
                JE CHECK2_P4D
                MOV CAR2_POWER_UP,2
                JMP passD2

CHECK2_P4D:
                POWERUP_DOWN [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,car2V_Height,POWERUP4_COLOR
                CMP COLLISION,1
                JE D2_SHIELD
                MOV CAR2_POWER_UP,3
                JMP passD2



D2_SHIELD:
            CMP CAR2_HAVE_SHIELD, 0
            JE D_end2
            POWERUP_DOWN [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2V_Width,car2V_Height,OBSTACLE_COLOR
            CMP COLLISION,1
            JE D_end2

 

             passD2:
             mov Where,0
             Move img2D,[car2_X_Offset],[car2_Y_Offset],[car2_Y_Offset],car2V_Width,car2V_Height,[car2_speed],[car2_width_prev],[car2_height_prev]
             jmp D_end2
             borderD2:

              
  D_end2:     
             ret
             endp
  
moveLeft2 PROC 
  ;* check left border
            cmp      [byte ptr KeyList + 30], 1
            je      L2
            jmp L_end2
            L2:
            mov cx,[car2_X_Offset]
            sub cx,[car2_speed]
            cmp cx,[car2_X_Offset]
            jb  Lcont2
            jmp borderL2
            Lcont2:
            MoveLeftConstraint [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height
            cmp COLLISION,1
             JE CHECK2_P1L
             JMP passL2  
                                                                                                      ; THE LOGIC IS TO DETECTED IS TRACK? ELSE IS P1? ELSE IS P2? 
             CHECK2_P1L:
             POWERUP_LEFT [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height,POWERUP1_COLOR          ;P1 COLOR (POWER UP 1 COLOR)
             CMP COLLISION,1
             JE CHECK2_P2L
             MOV CAR2_POWER_UP,0 
                                                                                   ;MOVE THE POWER UP NUMBER TO THE BYTE THAT CARRIES CAR'S POWER UP NUMBER          
             JMP passL2

  CHECK2_P2L :
            POWERUP_LEFT [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height,POWERUP2_COLOR
            CMP COLLISION,1
            JE CHECK2_P3L
            MOV CAR2_POWER_UP,1  
            JMP passL2

CHECK2_P3L:
                 POWERUP_LEFT [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height,POWERUP3_COLOR
                CMP COLLISION,1
                JE CHECK2_P4L
                MOV CAR2_POWER_UP,2
                JMP passL2

CHECK2_P4L:
                  POWERUP_LEFT [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height,POWERUP4_COLOR
                CMP COLLISION,1
                JE L2_SHIELD
                MOV CAR2_POWER_UP,3
                JMP passL2



L2_SHIELD:
            CMP CAR2_HAVE_SHIELD, 0
            JE L_end2
            POWERUP_LEFT [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height,OBSTACLE_COLOR
            CMP COLLISION,1
            JE L_end2


            passL2:
            mov Where,1
            Move img2L,[car2_X_Offset],[car2_Y_Offset],[car2_X_Offset],car2H_Width,car2H_Height,[car2_speed],[car2_width_prev],[car2_height_prev]
            jmp L_end2
            borderL2:
     
            L_end2:     
            ret
            endp
moveRight2 PROC 
  ;* check right border
             cmp     [byte ptr KeyList + 32], 1
             je      R2
             jmp R_end2
             R2:
             mov      cx,[car2_X_Offset]
             add      cx,[car2_speed]
             add      cx,car2H_Width
             cmp      cx,SCREEN_WIDTH
             jb       Rcont2
             jmp borderR2
             jmp R_end2
             Rcont2:

             MoveRightConstraint [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height
             cmp COLLISION,1
             JE CHECK2_P1R
             JMP passR2   
                                                                                                     ; THE LOGIC IS TO DETECTED IS TRACK? ELSE IS P1? ELSE IS P2? 
   CHECK2_P1R:
             POWERUP_RIGHT [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height,POWERUP1_COLOR          ;P1 COLOR (POWER UP 1 COLOR)
             CMP COLLISION,1
             JE CHECK2_P2R
             MOV CAR2_POWER_UP,0   
                                                                           ;MOVE THE POWER UP NUMBER TO THE BYTE THAT CARRIES CAR'S POWER UP NUMBER          
             JMP passR2

 CHECK2_P2R :
             POWERUP_RIGHT [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height,POWERUP2_COLOR
             CMP COLLISION,1
             JE CHECK2_P3R
             MOV CAR2_POWER_UP,1  
             JMP passR2
CHECK2_P3R:
                POWERUP_RIGHT [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height,POWERUP3_COLOR
                CMP COLLISION,1
                JE CHECK2_P4R
                MOV CAR2_POWER_UP,2
                JMP passR2

CHECK2_P4R:
                POWERUP_RIGHT [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height,POWERUP4_COLOR
                CMP COLLISION,1
                JE SHIELD
                MOV CAR2_POWER_UP,3
                JMP passR2

SHIELD:
            CMP CAR2_HAVE_SHIELD, 0
            JE R_end2
            POWERUP_RIGHT [car2_X_Offset],[car2_Y_Offset],[car2_speed],car2H_Width,car2H_Height,OBSTACLE_COLOR
            CMP COLLISION,1
            JE R_end2

             passR2:
             mov Where,0
             Move img2R,[car2_X_Offset],[car2_Y_Offset],[car2_X_Offset],car2H_Width,car2H_Height,[car2_speed],[car2_width_prev],[car2_height_prev]
             jmp R_end2
             borderR2:
           
  R_end2:     
             ret
             endp
 
main PROC 
  MOV curdur, DURATION_SS
               mov CAR1_POWER_UP,4
               mov CAR2_POWER_UP,4
               MOV CAR1_HAVE_SHIELD, 0
               MOV CAR2_HAVE_SHIELD, 0
  mainLoop:  
               call     sleepSomeTime
               MOV CUR_CHECKING_CAR, 1
               call     moveUp
               call     moveDown
               call     moveLeft
               call     moveRight
               MOV CUR_CHECKING_CAR, 2
               call     moveUp2
               call     moveDown2
               call     moveLeft2
               call     moveRight2

               ; ACTIVATE POWER UP
               ActivatePowerUp

              ; Handle time
              CALL GET_TIME
              CALL PrintTimer

              call calcScore1
              call calcScore2
              call printScores

               CMP WINNER, 0
               JNE WIN

              MOV Al, PSECONDS
              CMP Al, CSECONDS
              JE DINC_TIMER

              MOV AL, curdur
              SUB AL, 1
              DAS
              MOV curdur, AL
              DecPUCount

              DINC_TIMER:
              CMP curdur, 0
              JNE CONT_MAIN
              MOV WINNER, 3
              JMP WIN
              


  CONT_MAIN:
            cmp [byte ptr KeyList+3dh], 1
            JNE CHECK_EXIT

          pop SI
          pop          dx ds
          mov          ax, 2509h
          int          21h

          mov ax, DATA
          mov ds, ax
          mov ax, EXTRA
          mov es, ax

          PUSH SI
            CALL StartGameChat
          POP SI

          mov          ax, 3509h                                                    ; Get Interrupt Vector
          int          21h                                                          ; -> ES:BX
          push         es bx

     ; replace the existing int09h handler with ours
          mov          dx, offset onKeyEvent
          PUSH         DS
          MOV          AX,CS
          MOV          DS,AX
          mov          ax, 2509h
          int          21h
          POP          DS
          PUSH SI
          MOV [byte ptr KeyList+3dh], 0

  CHECK_EXIT:
  ; if F4 is not pressed, jump back to mainLoop
                                                                           ; -> AH=1 Pressed, AH=0 Released
             cmp     [byte ptr KeyList+3eh], 1
             jne     mainLoop
            
    WIN:
             ret
             endP


PutCars PROC
        ; reset winner
        mov WINNER, 0

        ; Reset key map
        mov [byte ptr KeyList+01h],0 ; reset esc
        mov [byte ptr KeyList+3eh],0 ; reset F4
        mov [byte ptr KeyList+1ch],0 ; reset enter

        ; reset all keys
        mov [byte ptr KeyList+48h],0 ; reset up
        mov [byte ptr KeyList+50h],0 ; reset down
        mov [byte ptr KeyList+4bh],0 ; reset left
        mov [byte ptr KeyList+4dh],0 ; reset right
        mov [byte ptr KeyList+11h],0 ; reset up2
        mov [byte ptr KeyList+1fh],0 ; reset down2
        mov [byte ptr KeyList+30h],0 ; reset left2
        mov [byte ptr KeyList+32h],0 ; reset right2

        ; reset speeds
        mov [car1_speed], 10
        mov [car2_speed], 10

        

        mov where, 0
        mov Prev_img, 0

        ; reset car offsets
      
         mov [car1_X_Offset], 205
         mov [car1_Y_Offset], 180
         mov [car2_X_Offset], 205
         mov [car2_Y_Offset], 150
          mov          di,offset img1R
          DrawCar      [car1_X_Offset],[car1_Y_Offset],car1H_Width,car1H_Height
          mov          di,offset img2R
          DrawCar      [car2_X_Offset],[car2_Y_Offset],car2H_Width,car2H_Height
                                 
          ; mov bx,offset TRACK_AXIS
          ; MOV CX,WORD PTR [BX+12]
          ;  mov [car2_X_Offset],CX
          ;   MOV CX,WORD PTR [BX+14]
          ;  mov [car2_Y_Offset],CX
          ;    mov          di,offset img2R
          ; DrawCar     [car2_X_Offset],[car2_Y_Offset],car2H_Width,car2H_Height
        

DRIVE:
     ; get                the address of the existing int09h handler
          mov          ax, 3509h                                                    ; Get Interrupt Vector
          int          21h                                                          ; -> ES:BX
          push         es bx

     ; replace the existing int09h handler with ours
          mov          dx, offset onKeyEvent
          PUSH         DS
          MOV          AX,CS
          MOV          DS,AX
          mov          ax, 2509h
          int          21h
          POP          DS
          call         main

     ; return to text mode
          ;mov          ah, 0
          ;mov          al, 2
          ;int          10h
                    
          mov al, player1Score
          mov bl, player2Score

          cmp al, bl
          jg oneWins
          jl twoWins
          je tieWins

oneWins:
          mov WINNER, 1
          jmp DNOTDELAY
twoWins:  
          mov WINNER, 2
          jmp DNOTDELAY
tieWins:
          mov WINNER, 3
          jmp DNOTDELAY


          DNOTDELAY:
     ; restore the original int09h handler
          pop          dx ds
          mov          ax, 2509h
          int          21h

          

          mov ax, DATA
          mov ds, ax
          mov ax, EXTRA
          mov es, ax


          ret
PutCars ENDP
