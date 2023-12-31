
; ====================================================================================================
; Check if the car is colliding with the powerup
; ====================================================================================================
CheckColisionForPowerup MACRO point_x, point_y, color 
LOCAL ENDL, POWERUP1, POWERUP2, POWERUP3, POWERUP4, PU1C2, PU2C2, PU3C2, PU4C2
pusha
CMP COLLISION,1
JE ENDL 
              MOV PU_X,point_x
              MOV PU_Y,point_y
              ErasePowerup PU_X,PU_Y,color
              MOV COLLISION,1

              ; Give powerup
              MOV AX, color
              CMP AX, POWERUP1_COLOR
              JE POWERUP1
              CMP AX, POWERUP2_COLOR
              JE POWERUP2
              CMP AX, POWERUP3_COLOR
              JE POWERUP3
              CMP AX, POWERUP4_COLOR
              JE POWERUP4

POWERUP1:
        CMP CUR_CHECKING_CAR, 2
        JNE PU1C2
        MOV CAR1_POWER_UP,0
        JMP ENDL
PU1C2:
        MOV CAR2_POWER_UP,0
        JMP ENDL
POWERUP2:
        CMP CUR_CHECKING_CAR, 2
        JNE PU2C2
        MOV CAR1_POWER_UP,1
        JMP ENDL
PU2C2:
        MOV CAR2_POWER_UP,1
        JMP ENDL
POWERUP3:
        CMP CUR_CHECKING_CAR, 2
        JNE PU3C2
        MOV CAR1_POWER_UP,2
        JMP ENDL
PU3C2:
        MOV CAR2_POWER_UP,2
        JMP ENDL
POWERUP4:
        CMP CUR_CHECKING_CAR, 2
        JNE PU4C2
        MOV CAR1_POWER_UP,3
        JMP ENDL
PU4C2:
        MOV CAR2_POWER_UP,3
        JMP ENDL
ENDL:
popa
ENDM CheckColisionForPowerup

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
              CheckColisionForPowerup cx, dx, NEXT_COLOR
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
              CheckColisionForPowerup cx, dx, NEXT_COLOR
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
              cmp al, NEXT_COLOR
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

            CheckColisionForPowerup cx, dx, NEXT_COLOR

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

            CheckColisionForPowerup cx, dx, NEXT_COLOR
Endm POWERUP_RIGHT

