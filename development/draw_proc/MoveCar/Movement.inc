Move Macro img,car_x, car_y,direction,width,height,car_speed,w_p,h_p
LOCAL up_endM,forward,backward,continueMoving

             mov                cx,car_x
             mov                dx,car_y
             mov                bx ,w_p
             mov                ax,h_p
             
             SetDrawImageParams cx, dx, bx,ax, 0, 0, 1
             lea                SI,Prev_img
             CALL               DrawImage
             cmp Where,1
             jne backward
             jmp forward
             backward:
             mov cx,car_speed
             add direction,cx
             jmp continueMoving
             forward:  
             mov cx,car_speed
             sub      direction,cx
             continueMoving:

             mov                cx,car_x
             mov                dx,car_y
             SetDrawImageParams cx, dx, width,height, 0, 0, 0
              lea                SI,img
             CALL               DrawImage
             
             mov cx,width
             mov w_p,cx
             mov cx,height
             mov h_p,cx
             jmp up_endM
             up_endM:
endm Move
DrawAtBorder Macro img,car_x, car_y,width,height,w_p,h_p

             mov                cx,car_x
             mov                dx,car_y
             mov                bx ,w_p
             mov                ax,h_p
             SetDrawImageParams cx, dx, bx,ax, 0, 0, 0
             MOV                SI, di
             CALL               DrawImage
             mov                cx,width
             mov                w_p,cx
             mov                cx,height
             mov                h_p,cx
endm  DrawAtBorder

MoveUpConstraint Macro car_x,car_y,car_speed,car_width
LOCAL End,cmp_,continue
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y 
              sub dx,car_speed
              int 10H ; AL = COLOR
              cmp al, 00h
              je cmp_
              jmp End
              cmp_:
              add cx,car_width
              int 10H ; AL = COLOR
              cmp al, 00h
              je continue
              jmp End
              End:
              mov cx,1
              continue:
              endm MoveUpConstraint


MoveDownConstraint Macro car_x,car_y,car_speed,car_width,car_height
LOCAL End,cmp_,continue
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y 
              add dx,car_speed
              add dx,car_height
              int 10H ; AL = COLOR
              cmp al, 00h
              je cmp_
              jmp End
              cmp_:
              add cx,car_width
              int 10H ; AL = COLOR
              cmp al, 00h
              je continue
              jmp End
              End:
mov cx,1
continue:
Endm MoveDownConstraint

MoveRightConstraint Macro car_x,car_y,car_speed,car_width,car_height
LOCAL End,cmp_,continue
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y
              add cx,car_speed
              add cx,car_width
              int 10H ; AL = COLOR
              cmp al, 00h
              je cmp_
              jmp End
              cmp_:
              add dx,car_height
              int 10H ; AL = COLOR
              cmp al, 00h
              je continue
              jmp End
End:
mov cx,1
continue:
Endm MoveRightConstraint

MoveLeftConstraint Macro car_x,car_y,car_speed,car_width,car_height
LOCAL End,cmp_,continue
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y
              sub cx,car_speed
              int 10H ; AL = COLOR
              cmp al, 00h
              je cmp_
              jmp End
              cmp_:
              mov ah,0Dh
              add dx,car_height
              int 10H ; AL = COLOR
              cmp al, 00h
              je continue
              jmp End
            End:
mov cx,1
continue:
Endm MoveLeftConstraint
