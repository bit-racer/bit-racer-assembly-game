POWERUP_UP Macro car_x,car_y,car_speed,car_width,NEXT_COLOR
LOCAL End,cmp_,continue, FINISH_LINE,cmp_2
MOV COLLISION,0
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y
              sub dx,car_speed
              int 10H ; AL = COLOR
              cmp al, NEXT_COLOR
              je continue
              jmp cmp_
              cmp_:
              mov ah,0Dh
              add cx,car_width
              int 10H ; AL = COLOR
              cmp al, NEXT_COLOR
              je continue 
              cmp_2:
              mov ah,0Dh
              sub cx,8
              int 10H ; AL = COLOR
              cmp al, NEXT_COLOR
              je continue
              End:
              mov COLLISION,1
              continue:
              endm POWERUP_UP


;Collision handling while moving down

POWERUP_DOWN Macro car_x,car_y,car_speed,car_width,car_height,NEXT_COLOR
LOCAL End,cmp_,continue, FINISH_LINE,cmp_2
MOV COLLISION,0
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y 
              add dx,car_speed
              add dx,car_height
              int 10H ; AL = COLOR
              cmp al, NEXT_COLOR
              je continue
              cmp_:
              mov ah,0Dh
              add cx,car_width
              int 10H ; AL = COLOR
              cmp al, NEXT_COLOR
              je continue 
              cmp_2:
              mov ah,0Dh
              sub cx,8
              int 10H ; AL = COLOR
              cmp al, NEXT_COLOR
              je continue

              End:
mov COLLISION,1
continue:
Endm POWERUP_DOWN

;Collision handling while moving right

POWERUP_RIGHT Macro car_x,car_y,car_speed,car_width,car_height,NEXT_COLOR
LOCAL End,cmp_,continue, FINISH_LINE,cmp_2
MOV COLLISION,0
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y
              add cx,car_speed
              add cx,car_width
              int 10H ; AL = COLOR
              cmp al, NEXT_COLOR
              je continue
              cmp_:
              mov ah,0Dh
              add dx,car_height
              int 10H ; AL = COLOR
              cmp al, TRACK_COLOR
              je continue
              cmp_2:
              mov ah,0Dh
              sub dx,8
              int 10H ; AL = COLOR
              cmp al, NEXT_COLOR
              je continue
End:
mov COLLISION,1
continue:
Endm POWERUP_LEFT

;Collision handling while moving left

POWERUP_LEFT Macro car_x,car_y,car_speed,car_width,car_height,NEXT_COLOR
LOCAL End,cmp_,continue, FINISH_LINE,cmp_2
MOV COLLISION,0
              mov ah,0Dh
              mov cx,car_x
              mov dx,car_y
              sub cx,car_speed
              int 10H ; AL = COLOR
              cmp al,NEXT_COLOR
              je continue
              mov ah,0Dh
              add dx,car_height
              int 10H ; AL = COLOR
              cmp al, NEXT_COLOR
              je continue
              mov ah,0Dh
              sub dx,8
              int 10H ; AL = COLOR
              cmp al, NEXT_COLOR
              je continue
              jmp End
            End:
mov COLLISION,1
continue:
Endm POWERUP_RIGHT