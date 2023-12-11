            onKeyEvent  PROC                                                                     ; custom handler for int 09h
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
             mov cx,[carOffsetY1]
             sub cx,[car_one_speed]
             cmp cx, [carOffsetY1]
             jb  contup
             jmp borderUp
             contup:  
            mov                 cx,[carOffsetX1]
             mov                 dx,[carOffsetY1] 
             mov                 bx ,car_one_width_prev
             mov                 ax,car_one_height_prev
             SetDrawImageParams cx, dx, bx,ax, 0, 0, 1
             MOV                SI, offset Prev_img
             CALL               DrawImage
             MoveUpConstraint [carOffsetX1],[carOffsetY1],[car_one_speed], carSizeX1
             cmp cx,1
             jne passUP 
             jmp up_end
             passUP:
             mov Where,1
             Move car1,[carOffsetX1],[carOffsetY1],[carOffsetY1],carSizeX1,carSizeY1,[car_one_speed],[car_one_width_prev],[car_one_height_prev]
             mov Prev_img,offset car1
             jmp up_end
             borderUp:
             mov                 cx,[carOffsetX1]
             mov                 dx,[carOffsetY1] 
             mov                 bx ,car_one_width_prev
             mov                 ax,car_one_height_prev
             SetDrawImageParams cx, dx, bx,ax, 0, 0, 1
             MOV                SI, offset Prev_img
             CALL               DrawImage
             DrawAtBorder car1,[carOffsetX1],[carOffsetY1],carSizeX1,carSizeY1,[car_one_width_prev],[car_one_height_prev]
             mov Prev_img,offset car1
  up_end:    
             ret
             endp
 moveDown PROC
  ;* check bottom border
             cmp      [byte ptr KeyList + 50h], 1
             je      D
             jmp D_end
             D:
             mov      cx,[carOffsetY1]
             add      cx, carSizeY1
             add      cx, [car_one_speed]
             cmp      cx,480
             jb       Dcont
             jmp      borderD
             Dcont:
             MoveDownConstraint [carOffsetX1],[carOffsetY1],[car_one_speed],carSizeX1,carSizeY1
             cmp cx,1
            jne passD
            jmp D_end
            passD:
            mov Where,0
            Move car1D,[carOffsetX1],[carOffsetY1],[carOffsetY1],carSizeX1,carSizeY1,[car_one_speed],[car_one_width_prev],[car_one_height_prev]
            mov Prev_img,offset car1D
            jmp D_end
            borderD:
             mov                 cx,[carOffsetX1]
             mov                 dx,[carOffsetY1] 
             mov                 bx ,car_one_width_prev
             mov                 ax,car_one_height_prev
             SetDrawImageParams  cx, dx, bx,ax, 0, 0, 1
             MOV                 SI, offset Prev_img
             CALL                DrawImage
            mov [carOffsetY1],457
            DrawAtBorder car1D,[carOffsetX1],[carOffsetY1],carSizeX1,carSizeY1,[car_one_width_prev],[car_one_height_prev]
              mov Prev_img,offset car1D
  D_end:     
             ret
             endp
moveLeft PROC 
  ;* check left border
            cmp      [byte ptr KeyList + 4bh], 1
            je      L
            jmp L_end
            L:
            mov cx,[carOffsetX1]
            sub cx,carSizeX1_horz
            sub cx,[car_one_speed]
            cmp cx,[carOffsetX1]
            jb  Lcont
            jmp borderL
            Lcont:
            MoveLeftConstraint [carOffsetX1],[carOffsetY1],[car_one_speed],carSizeX1_horz,carSizeY1_horz

            cmp cx,1
            jne passL1
            jmp L_end
            passL1:
            mov Where,1
            Move car1L,[carOffsetX1],[carOffsetY1],[carOffsetX1],carSizeX1_horz,carSizeY1_horz,[car_one_speed],[car_one_width_prev],[car_one_height_prev]
            mov Prev_img,offset car1L
            jmp L_end
            borderL:
             mov                 cx,[carOffsetX1]
             mov                 dx,[carOffsetY1] 
             mov                 bx ,car_one_width_prev
             mov                 ax,car_one_height_prev
             SetDrawImageParams  cx, dx, bx,ax, 0, 0, 1
             MOV                 SI, offset car1L
             CALL                DrawImage
            mov [carOffsetX1],0
            DrawAtborder   car1L,[carOffsetX1],[carOffsetY1],carSizeX1_horz,carSizeY1_horz,[car_one_width_prev],[car_one_height_prev]
            mov Prev_img,offset car1L
            L_end:     
            ret
            endp
            



moveRight PROC
  ;* check right border
             cmp      [byte ptr KeyList + 4dh], 1
             je      R
             jmp R_end
             R:
             mov      cx,[carOffsetX1]
             add      cx,[car_one_speed]
             add      cx,carSizeX1_horz
             cmp      cx,640
             jb       Rcont
             jmp borderR
             jmp R_end
             Rcont:
            MoveRightConstraint [carOffsetX1],[carOffsetY1],[car_one_speed],carSizeX1_horz,carSizeY1_horz
            
             cmp cx,1
            jne passR1 
            jmp R_end
            passR1:
            mov Where,0
            Move car1R,[carOffsetX1],[carOffsetY1],[carOffsetX1],carSizeX1_horz,carSizeY1_horz,[car_one_speed],[car_one_width_prev],[car_one_height_prev]
mov Prev_img,offset car1R
            jmp R_end
            borderR:
             mov                 cx,[carOffsetX1]
             mov                 dx,[carOffsetY1] 
             mov                 bx ,car_one_width_prev
             mov                 ax,car_one_height_prev
             SetDrawImageParams  cx, dx, bx,ax, 0, 0, 1
             MOV                 SI, offset Prev_img
             CALL                DrawImage
            mov [carOffsetX1],640-carSizeX1_horz
            DrawAtborder   car1R,[carOffsetX1],[carOffsetY1],carSizeX1_horz,carSizeY1_horz,[car_one_width_prev],[car_one_height_prev]
            mov Prev_img,offset car1R
  R_end:     
             ret
             endp
; PROC moveUp2
;   ;* check top border
;           cmp   [byte KeyList + 11h], 1
;              je    up2
;              jmp up_end2
;              up2:
;              mov cx,[curr_car_two_y]
;              sub cx,[car_two_speed]
;              cmp cx, [curr_car_two_y]
;              jb  contup2
;              jmp borderUp2
;              contup2:  
;             MoveUpConstraint [curr_car_two_x],[curr_car_two_y],[car_two_speed],car_two_width_F
;             cmp cx,1
;             jne passUP2 
;             jmp up_end2
;              passUP2:
;              mov bx,5
;              Move img1F,[curr_car_two_x],[curr_car_two_y],[curr_car_two_y],car_two_width_F,car_two_height_F,[car_two_speed],[car_two_width_prev],[car_two_height_prev]
;              jmp up_end2
;              borderUp2:
;               DrawCarB 0Ah,[curr_car_two_x], [curr_car_two_y],[car_two_width_prev],[car_two_height_prev]
;              mov [curr_car_two_y],0
;              DrawAtBorder img1F,[curr_car_two_x],[curr_car_two_y],car_two_width_F,car_two_height_F,[car_two_width_prev],[car_two_height_prev]
;   up_end2:    
;              ret
;              endp
  
; PROC moveDown2
;   ;* check bottom border
;            cmp        [byte KeyList + 1fh], 1
;              je      D2
;              jmp D_end2
;              D2:
;              mov      cx,[curr_car_two_y]
;              add      cx, car_two_height_D
;              add      cx, [car_two_speed]
;              cmp      cx,200
;              jb       Dcont2
;              jmp      borderD2
;              Dcont2:
;              MoveDownConstraint [curr_car_two_x],[curr_car_two_y],[car_two_speed],car_two_width_D,car_two_height_D
;              cmp cx,1
;             jne passD2
;             jmp D_end2
;             passD2:
;             mov bx,0
;             Move img1D,[curr_car_two_x],[curr_car_two_y],[curr_car_two_y],car_two_width_D,car_two_height_D,[car_two_speed],[car_two_width_prev],[car_two_height_prev]
;             jmp D_end2
;             borderD2:
;               DrawCarB 0Ah,[curr_car_two_x], [curr_car_two_y],[car_two_width_prev],[car_two_height_prev]
;             mov [curr_car_two_y],175
;             DrawAtBorder img1D,[curr_car_two_x],[curr_car_two_y],car_two_width_D,car_two_height_D,[car_two_width_prev],[car_two_height_prev]
              
;   D_end2:     
;              ret
;              endp
  
; PROC moveLeft2
;   ;* check left border
;                cmp      [byte KeyList + 30], 1
;             je      L2
;             jmp L_end2
;             L2:
;             mov cx,[curr_car_two_x]
;             sub cx,car_two_width_L
;             sub cx,[car_two_speed]
;             cmp cx,[curr_car_two_x]
;             jb  Lcont2
;             jmp borderL2
;             Lcont2:
;             MoveLeftConstraint [curr_car_two_x],[curr_car_two_y],[car_two_speed],car_two_width_L,car_two_height_L
;             cmp cx,1
;             jne passL2
;             jmp L_end2
;             passL2:
;             mov bx,5
;             Move img1L,[curr_car_two_x],[curr_car_two_y],[curr_car_two_x],car_two_width_L,car_two_height_L,[car_two_speed],[car_two_width_prev],[car_two_height_prev]
;             jmp L_end2
;             borderL2:
;              DrawCarB 0Ah,[curr_car_two_x], [curr_car_two_y],[car_two_width_prev],[car_two_height_prev]
;             mov [curr_car_two_x],0
;             DrawAtborder   img1L,[curr_car_two_x],[curr_car_two_y],car_two_width_L,car_two_height_L,[car_two_width_prev],[car_two_height_prev]
;             L_end2:     
;             ret
;             endp
; PROC moveRight2
;   ;* check right border
;            cmp     [byte KeyList + 32], 1
;              je      R2
;              jmp R_end2
;              R2:
;              mov      cx,[curr_car_two_x]
;              add      cx,[car_two_speed]
;              add      cx,car_two_width_R
;              cmp      cx,320
;              jb       Rcont2
;              jmp borderR2
;              jmp R_end2
;              Rcont2:
;             MoveRightConstraint [curr_car_two_x],[curr_car_two_y],[car_two_speed],car_two_width_R,car_two_height_R
;              cmp cx,1
;             jne passR2 
;             jmp R_end2
;             passR2:
;             mov bx,0
;             Move img1R,[curr_car_two_x],[curr_car_two_y],[curr_car_two_x],car_two_width_R,car_two_height_R,[car_two_speed],[car_two_width_prev],[car_two_height_prev]
;             jmp R_end2
;             borderR2:
;             DrawCarB 0Ah,[curr_car_two_x], [curr_car_two_y] ,[car_two_width_prev],[car_two_height_prev]
;             mov [curr_car_two_x],SCREEN_WIDTH-car_two_width_R-2
;      DrawAtborder   img1R,[curr_car_two_x],[curr_car_two_y],car_two_width_R,car_two_height_R,[car_two_width_prev],[car_two_height_prev]
;   R_end2:     
;              ret
;              endp

main PROC 
  
  mainLoop:  
               call     sleepSomeTime
                mov Prev_img,offset car1
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
