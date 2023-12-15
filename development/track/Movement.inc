;Delete car last position and draw car in new position

MoveTrack Macro img,car_x, car_y,direction,width,height,car_speed,w_p,h_p
LOCAL up_endM,forward,backward,continueMoving
INC COUNT
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
             DrawTrack  car_x,car_y,width,height
             mov cx,width
             mov w_p,cx
             mov cx,height
             mov h_p,cx
             jmp up_endM
             up_endM:
endm MoveTrack


DRAW_TRACK_CONSTRAINT MACRO car_x,car_y,car_speed,car_width,car_height
LOCAL END,CONTINUE,UP,DOWN,LEFT,RIGHT,cmp_UP1,cmp_UP2,CMP_LEFT1,CMP_LEFT2,cmp_D2,cmp_D1,CMP_R1,CMP_R2
CMP DIR,0
JE UP
CMP DIR,1
JE DOWN
CMP DIR,2
JE LEFT
CMP DIR,3
JE RIGHT

UP:
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y 
              sub dx,car_speed
              sub dx,5
              add cx,5
              int 10H ; AL = COLOR
              cmp al, 00h
              je cmp_UP1
              JMP END
              cmp_UP1:
              add dx,10
              SUB CX,20
              int 10H ; AL = COLOR
              cmp al, 00h
               je cmp_UP2
              JMP END
              cmp_UP2:
              ADD CX,car_width
              add cx,30
              int 10H ; AL = COLOR
              cmp al, 00h
              JE CONTINUE
              JMP END

DOWN:
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y 
              add dx,car_speed
              add dx,car_height
              add dx,5
              add cx,5
              int 10H ; AL = COLOR
              cmp al, 00h
              je cmp_D1
              jmp end
              cmp_D1:
              sub dx,10
              SUB CX,20
              int 10H ; AL = COLOR
              cmp al, 00h
               je cmp_D2
              JMP END
              cmp_D2:
              ADD CX,car_width
              add cx,30
              int 10H ; AL = COLOR
              cmp al, 00h
              JE CONTINUE
              JMP END
LEFT:
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y
              sub cx,car_speed
              add dx,5
              sub cx,20
              int 10H ; AL = COLOR
              cmp al, 00h
              JE CMP_LEFT1
              JMP END
              CMP_LEFT1:
              ADD cx,25
              SUB DX,10
              int 10H ; AL = COLOR
              cmp al, 00h
              JE CMP_LEFT2
              JMP END
              CMP_LEFT2:
              ADD DX,10
              ADD DX,car_height
              int 10H ; AL = COLOR
              cmp al, 00h
JE CONTINUE
JMP END
RIGHT:
mov ah,0Dh
              mov cx,car_x
              mov dx,car_y
              add cx,car_speed
              add cx,car_width
              add dx,5
              add cx,5
              int 10H ; AL = COLOR
              cmp al, 00h
            JE CMP_R1
              JMP END
              CMP_R1:
               sub cx,5
              SUB DX,10
              int 10H ; AL = COLOR
              cmp al, 00h
              JE CMP_R2
              JMP END
              CMP_R2:
              ADD DX,10
              ADD DX,car_height
              int 10H ; AL = COLOR
              cmp al, 00h
              JE CONTINUE
JMP END
END:
MOV CX,1
CONTINUE:
ENDM DRAW_TRACK_CONSTRAINT
