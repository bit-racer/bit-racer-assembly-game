;Delete car last position and draw car in new position

Move Macro img,car_x, car_y,direction,width,height,car_speed,w_p,h_p
LOCAL up_endM,forward,backward,continueMoving
             mov Erase,0
             cmp Where,1
             jne backward
             jmp forward
             backward:
             mov      cx,car_speed  
             add direction,cx
             jmp continueMoving
             forward:
             mov      cx,car_speed  
             sub      direction,cx
             continueMoving:
             mov      di,offset img
             DrawCar  car_x,car_y,width,height
             mov cx,width
             mov w_p,cx
             mov cx,height
             mov h_p,cx
             jmp up_endM
             up_endM:
endm Move


;Draw car at border if the next movement will cross the border

; DrawAtBorder Macro img,car_x, car_y,width,height,w_p,h_p    
;              mov      di,offset img
;              DrawCar  car_x,car_y,width,height
;              mov cx,width
;              mov w_p,cx
;              mov cx,height
;              mov h_p,cx
; endm  DrawAtBorder

;Collision handling while moving up

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
              add cx,car_width-2
              int 10H ; AL = COLOR
              cmp al, 00h
              je continue
              jmp End
              End:
              mov cx,1
              continue:
              endm MoveUpConstraint


;Collision handling while moving down

MoveDownConstraint Macro car_x,car_y,car_speed,car_width,car_height
LOCAL End,cmp_,continue
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y 
              add dx,car_speed
              add dx,5
              add dx,5
              add dx,car_height
              int 10H ; AL = COLOR
              cmp al, 00h
              je cmp_
              jmp End
              cmp_:
              add cx,car_width-2
              int 10H ; AL = COLOR
              cmp al, 00h
              je continue
              jmp End
              End:
mov cx,1
continue:
Endm MoveDownConstraint

;Collision handling while moving right

MoveRightConstraint Macro car_x,car_y,car_speed,car_width,car_height
LOCAL End,cmp_,continue
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y
              add cx,car_speed
              add cx,car_width
              add cx,5
              int 10H ; AL = COLOR
              cmp al, 00h
              je cmp_
              jmp End
              cmp_:
              add dx,car_height-2
              int 10H ; AL = COLOR
              cmp al, 00h
              je continue
              jmp End
End:
mov cx,1
continue:
Endm MoveRightConstraint

;Collision handling while moving left

MoveLeftConstraint Macro car_x,car_y,car_speed,car_width,car_height
LOCAL End,cmp_,continue
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y
              sub cx,car_speed
              sub cx,5
              int 10H ; AL = COLOR
              cmp al, 00h
              je cmp_
              jmp End
              cmp_:
              mov ah,0Dh
              add dx,car_height-2
              int 10H ; AL = COLOR
              cmp al, 00h
              je continue
              jmp End
            End:
mov cx,1
continue:
Endm MoveLeftConstraint