;---------------------------------------------------------------------------------------------------------------------------
; Author: Amir Anwar
; Date: 2023-12-09
; Draw Macros
;---------------------------------------------------------------------------------------------------------------------------


; =================================================================================
; Set Video Mode To What ever the variables VIDEO_MODE and VIDEO_MODE_BX are set to
;
; Preq: VIDEO_MODE and VIDEO_MODE_BX must be set to the desired video mode
; =================================================================================
SetVideoMode MACRO
               MOV AX,VIDEO_MODE
               MOV BX,VIDEO_MODE_BX
               INT 10h               ; Set video mode
ENDM

; =================================================================================
; Clear Screen in Graphics mode
; Set BG to Black
; IS just an alyis for SetVideoMode
; =================================================================================
ClearScreen MACRO
              SetVideoMode
ENDM

; =================================================================================
; Set the color of the screen
; Draw a rectacngle of the color over the whole screen
; Preq:
;  * COLOR must be set to the desired color
;  * SCREEN_WIDTH must be set to the width of the screen
;  * SCREEN_HEIGHT must be set to the height of the screen
; =================================================================================
ColorScreen MACRO COLOR
              LOCAL DRAW_RAW, FINISH

              MOV   CX, SCREEN_WIDTH   ; X end
              MOV   DX, SCREEN_HEIGHT  ; Y end
              MOV   AH, 0Ch            ; Set pixel
              MOV   AL, COLOR          ; Color
  DRAW_RAW:   
              INT   10h                ; Set pixel
              DEC   CX                 ; Decrement X
              CMP   CX, 0              ; Check if X is 0
              JNZ   DRAW_RAW           ; If not, continue drawing
              MOV   CX, SCREEN_WIDTH   ; Reset X to draw next line
              DEC   DX                 ; Decrement Y
              CMP   DX, 0              ; Check if Y is 0
              JZ    FINISH             ; If so, finish
              JMP   DRAW_RAW           ; If not, continue drawing
  FINISH:     
ENDM

; =================================================================================
; Wait for a key press
; =================================================================================
WaitForKeyPress MACRO
                  MOV AH, 00h  ; Function 00h = Wait for key press
                  INT 16h      ; Call keyboard interrupt
ENDM

; =================================================================================
; Set Draw Image Parameters
; Sets the praameters for the DrawImage procedure
; MUST BE USER SEP FROM MOV SI, OFFSET IMAGE
; Preq:
;  * X must be set to the X offset of the image
;  * Y must be set to the Y offset of the image
;  * WIDTH must be set to the width of the image
;  * HEIGHT must be set to the height of the image
;  * ERASE_COLOR must be set to the color to erase the image with
;  * REV must be set to 1 if the image is to be drawn in reverse, 0 otherwise
;  * ERASE_IMAGE must be set to 1 if the image is to be erased, 0 otherwise
; SIDE EFFECTS:
;  * IMAGE_OFFSET_X is set to X
;  * IMAGE_OFFSET_Y is set to Y
;  * IMAGE_SIZE_X is set to WIDTH
;  * IMAGE_SIZE_Y is set to HEIGHT
;  * RECOLOR is set to ERASE_COLOR
;  * REVERSE is set to REV
;  * ERASE is set to ERASE_IMAGE
; =================================================================================
SetDrawImageParams MACRO X, Y, WIDTH, HEIGHT, ERASE_COLOR, REV, ERASE_IMAGE
                     MOV IMAGE_OFFSET_X, X
                     MOV IMAGE_OFFSET_Y, Y
                     MOV IMAGE_SIZE_X, WIDTH
                     MOV IMAGE_SIZE_Y, HEIGHT
                     MOV RECOLOR, ERASE_COLOR
                     MOV REVERSE, REV
                     MOV ERASE, ERASE_IMAGE
ENDM

; =================================================================================
; Draw Page 0 images
; Draws all images in the image that are on page 0
; =================================================================================
DrawPage0 MACRO
  ; DRAW LOGO
            SetDrawImageParams 126, 66, logo_width, logo_height, 0, 0, 0
            MOV                SI, offset img_logo
            CALL               DrawImageE
    
  ; Draw Name Prompt
            SetDrawImageParams 151, 240, name_prompt_width, name_prompt_height, 0, 0, 0
            MOV                SI, offset img_name_prompt
            CALL               DrawImageE

  ; Draw cars
            SetDrawImageParams 211, 351, red_car_large_width, red_car_large_height, 0, 0, 0
            MOV                SI, offset img_red_car_large
            CALL               DrawImageE

            SetDrawImageParams 273, 351, green_car_large_width, green_car_large_height, 0, 0, 0
            MOV                SI, offset img_green_car_large
            CALL               DrawImageE

            SetDrawImageParams 335, 351, reed_car_large_width, reed_car_large_height, 0, 0, 0
            MOV                SI, offset img_reed_car_large
            CALL               DrawImageE

            SetDrawImageParams 397, 351, pink_car_large_width, pink_car_large_height, 0, 0, 0
            MOV                SI, offset img_pink_car_large
            CALL               DrawImageE

  ; Draw Thank
            SetDrawImageParams 150, 459, thank_width, thank_height, 0, 0, 0
            MOV                SI, offset img_thank
            CALL               DrawImageE
ENDM

; =================================================================================
; Draw Page 1 images
; Draws all images in the image that are on page 1
; =================================================================================
DrawPage1 MACRO
  ; Draw logo
            SetDrawImageParams 126, 66, logo_width, logo_height, 0, 0, 0
            MOV                SI, offset img_logo
            CALL               DrawImageE
    
  ; Draw Chat btn
            SetDrawImageParams 105, 280, chat_btn_width, chat_btn_height, 0, 0, 0
            MOV                SI, offset img_chat_btn
            CALL               DrawImageE
  
  ; Draw Play btn
            SetDrawImageParams 263, 280, play_btn_width, play_btn_height, 0, 0, 0
            MOV                SI, offset img_play_btn
            CALL               DrawImageE
    
  ; Draw Exit btn
            SetDrawImageParams 421, 280, exit_btn_width, exit_btn_height, 0, 0, 0
            MOV                SI, offset img_exit_btn
            CALL               DrawImage

  ; Draw Thank
            SetDrawImageParams 150, 459, thank_width, thank_height, 0, 0, 0
            MOV                SI, offset img_thank
            CALL               DrawImageE
ENDM

; =================================================================================
; Draw car macro
; Author: Peter
; =================================================================================
DrawCar macro curr_car_x, curr_car_y ,width,height
LOCAL star,Drawit,a1,Start,ENDING ,noErase                     
    star:      
               mov    ah , 0
               MOV    CX, width                                
               MOV    DX, height                               
               jmp    Start                                    ;Avoid drawing before the calculations
  Drawit:      

               add    cx, curr_car_x
               add    dx , curr_car_y
               MOV    AH,0Ch                                   ;set the configuration to writing a pixel
               mov    al, [DI]                                 ;color of the current coordinates

               cmp Erase,1
               jne noErase

               MOV AL, RECOLOR
               MOV BH, 00h
                INT 10h
                JMP a1

               noErase:
               CMP AL, 0
               JE a1
               MOV    BH,00h                                   ;set the page number
               INT    10h                                      ;execute the configuration
  a1:          
               sub    cx , curr_car_x
               sub    dx , curr_car_y
  Start:       
               inc    DI
               DEC    Cx                                       ;  loop iteration in x direction
               JNZ    Drawit                                   ;  check if we can draw c urrent x and y and excape the y iteration
               mov    Cx, width                                ;  if loop iteration in y direction, then x should start over so that we sweep the grid
               DEC    DX                                       ;  loop iteration in y direction
               JZ     ENDING                                   ;  both x and y reached 00 so end program
               Jmp    Drawit

  ENDING:      
endm DrawCar

 
; ============================================================================================================================
; Draw a rectangle for the track 
; could use and image after some modifications
; ============================================================================================================================
DrawTrack macro curr_track_x, curr_track_y ,width,height
LOCAL star,Drawit,a1,Start,ENDING ,noErase, FINAL, DRAW_O1, DRAW_O2        
    star:      
               mov    ah , 0
               MOV    CX, width                                
               MOV    DX, height                               
               jmp    Start                                    ;Avoid drawing before the calculations
  Drawit:      

               add    cx, curr_track_x
               add    dx , curr_track_y
               MOV    AH,0Ch                                   ;set the configuration to writing a pixel
               ;mov    al, [DI]                                ;color of the current coordinates
               MOV AL, TRACK_COLOR
               cmp Erase,1
               jne noErase
               xor    al , al
               noErase:
               MOV    BH,00h                                   ;set the page number
               INT    10h                                      ;execute the configuration
  a1:          
               sub    cx , curr_track_x
               sub    dx , curr_track_y
  Start:       
               inc    DI
               DEC    Cx                                       ;  loop iteration in x direction
               JNZ    Drawit                                   ;  check if we can draw c urrent x and y and excape the y iteration
               mov    Cx, width                                ;  if loop iteration in y direction, then x should start over so that we sweep the grid
               DEC    DX                                       ;  loop iteration in y direction
               JZ     ENDING                                   ;  both x and y reached 00 so end program
               Jmp    Drawit

  ENDING:
  ; Generate the PowerUps randomly
  SpawnPowerUps curr_track_x, curr_track_y
  ; Generate the obstacles randomly
  CALL WAIT_FOR_DELAY
  CALL RAND_FROM_0_TO_3
  CALL UPDATE_SEED

  CMP DIRECTION, 0
  JE FINAL
  CMP DIRECTION, 1
  JE DRAW_O1
  CMP DIRECTION, 2
  JE DRAW_O2
  CMP DIRECTION, 3
  JE FINAL

DRAW_O1:
  DrawObstacle curr_track_x, curr_track_y , OBSTACLE_WIDTH, OBSTACLE_HEIGHT
  JMP FINAL
DRAW_O2:
  ADD curr_track_x, OBSTACLE_2_OFFSET_X
  ADD curr_track_y, OBSTACLE_2_OFFSET_Y
  DrawObstacle curr_track_x, curr_track_y , OBSTACLE_WIDTH, OBSTACLE_HEIGHT
  SUB curr_track_x, OBSTACLE_2_OFFSET_X
  SUB curr_track_y, OBSTACLE_2_OFFSET_Y
  FINAL:
endm DrawTrack

; ============================================================================================================================
; Spawn obstacles
; ============================================================================================================================
SpawnPowerUps macro curr_track_x, curr_track_y
        LOCAL CONFIG_1, CONFIG_2, CONFIG_3, CONFIG_4, END
pusha
        ; Get random number between 0, 9
        GenerateRandomNumber 10
        GeneralDelayINT 50000 ; adjusting delay affects the randomness
        ; TODO: move to random function that requires lower delay


        ;DrawRectangle curr_track_x, curr_track_y, POWERUP_SIZE, POWERUP_SIZE, POWERUP1_COLOR

        CMP rand_value, 0
        JE CONFIG_1
        CMP rand_value, 1
        JE CONFIG_2
        CMP rand_value, 2
        JE CONFIG_3
        CMP rand_value, 3
        JE CONFIG_4
        JMP END

        CONFIG_1:
        ADD curr_track_x, POWERUP1_OFFSET_X
        ADD curr_track_y, POWERUP1_OFFSET_Y
        DrawRectangle curr_track_x, curr_track_y, POWERUP_SIZE, POWERUP_SIZE, POWERUP1_COLOR
        SUB curr_track_x, POWERUP1_OFFSET_X
        SUB curr_track_y, POWERUP1_OFFSET_Y
        JMP END

        CONFIG_2:
        ADD curr_track_x, POWERUP2_OFFSET_X
        ADD curr_track_y, POWERUP2_OFFSET_Y
        DrawRectangle curr_track_x, curr_track_y, POWERUP_SIZE, POWERUP_SIZE, POWERUP2_COLOR
        SUB curr_track_x, POWERUP2_OFFSET_X
        SUB curr_track_y, POWERUP2_OFFSET_Y
        JMP END

        CONFIG_3:
        ADD curr_track_x, POWERUP3_OFFSET_X
        ADD curr_track_y, POWERUP3_OFFSET_Y
        DrawRectangle curr_track_x, curr_track_y, POWERUP_SIZE, POWERUP_SIZE, POWERUP3_COLOR
        SUB curr_track_x, POWERUP3_OFFSET_X
        SUB curr_track_y, POWERUP3_OFFSET_Y
        JMP END

        CONFIG_4:
        ADD curr_track_x, POWERUP4_OFFSET_X
        ADD curr_track_y, POWERUP4_OFFSET_Y
        DrawRectangle curr_track_x, curr_track_y, POWERUP_SIZE, POWERUP_SIZE, POWERUP4_COLOR
        SUB curr_track_x, POWERUP4_OFFSET_X
        SUB curr_track_y, POWERUP4_OFFSET_Y
        JMP END

      END:
popa
endm SpawnPowerUps

; ============================================================================================================================
; Draw Random powerup
; ============================================================================================================================
DrawRandomPowerup MACRO cur_time
LOCAL CONFIG_1, CONFIG_2, CONFIG_3, ENDMM
pusha

    ; if cur_time = 95 then draw configure 1
    CMP curdur, 10010101B
    JE CONFIG_1
    ; if cur_time = 90 then draw configure 2
    CMP curdur, 10010000B
    JE CONFIG_2
    ; if cur_time = 85 then draw configure 3
    CMP curdur, 10000101B
    JE CONFIG_3
    JMP ENDMM

   MOV SI, offset TRACK_AXIS


        ; TO KNOW HOW TO HANDLE THE CONFIGS LOOK AT THE POWERUP SPAWNER ABOVE
        ; THE DIFFERNECE IS THAT WE DON"T HAVE THE TRACK_X AND TRACK_Y we to get from the array
        CONFIG_1:
        DrawRectangle s1_x, s1_y, POWERUP_SIZE, POWERUP_SIZE, POWERUP1_COLOR

        JMP ENDMM

        CONFIG_2:
        DrawRectangle s2_x, s2_y, POWERUP_SIZE, POWERUP_SIZE, POWERUP2_COLOR
        JMP ENDMM

        CONFIG_3:
        DrawRectangle s3_x, s3_y, POWERUP_SIZE, POWERUP_SIZE, POWERUP3_COLOR
        JMP ENDMM



ENDMM:
popa
ENDM



; ============================================================================================================================
; Draw Obstacle
; ============================================================================================================================
DrawObstacle macro curr_track_x, curr_track_y ,width, height
LOCAL star,Drawit,a1,Start,ENDING ,noErase                     
    star:      
               mov    ah , 0
               MOV    CX, width                                
               MOV    DX, height                               
               jmp    Start                                    ;Avoid drawing before the calculations
  Drawit:      

               add    cx, curr_track_x
               add    dx , curr_track_y
               MOV    AH,0Ch                                   ;set the configuration to writing a pixel
               ;mov    al, [DI]                                ;color of the current coordinates
               MOV AL, OBSTACLE_COLOR
               cmp Erase,1
               jne noErase
               xor    al , al
               noErase:
               MOV    BH,00h                                   ;set the page number
               INT    10h                                      ;execute the configuration
  a1:          
               sub    cx , curr_track_x
               sub    dx , curr_track_y
  Start:       
               inc    DI
               DEC    Cx                                       ;  loop iteration in x direction
               JNZ    Drawit                                   ;  check if we can draw c urrent x and y and excape the y iteration
               mov    Cx, width                                ;  if loop iteration in y direction, then x should start over so that we sweep the grid
               DEC    DX                                       ;  loop iteration in y direction
               JZ     ENDING                                   ;  both x and y reached 00 so end program
               Jmp    Drawit

  ENDING:      
endm DrawTrack


; ============================================================================================================================
; Draw a rectangle
; ============================================================================================================================
DrawRectangle MACRO X, Y, WIDTH, HEIGHT, COLOR
               LOCAL star,Drawit,a1,Start,ENDING ,noErase

               pusha

                MOV    CX, WIDTH                                ;  loop iteration in x direction
                MOV    DX, HEIGHT                               ;  loop iteration in y direction
                jmp    Start                                    ;Avoid drawing before the calculations
  Drawit:
                add    cx, X
                add    dx , Y
                MOV    AH,0Ch                                   ;set the configuration to writing a pixel
                mov    al, COLOR                                 ;color of the current coordinates
                cmp Erase,1
                jne noErase
                xor    al , al
                noErase:
                MOV    BH,00h                                   ;set the page number
                INT    10h                                      ;execute the configuration
  a1:
                sub    cx , X
                sub    dx , Y
  Start:
                inc    DI
                DEC    Cx                                       ;  loop iteration in x direction
                JNZ    Drawit                                   ;  check if we can draw c urrent x and y and excape the y iteration
                mov    Cx, WIDTH                                ;  if loop iteration in y direction, then x should start over so that we sweep the grid
                DEC    DX                                       ;  loop iteration in y direction
                JZ     ENDING                                   ;  both x and y reached 00 so end program
                Jmp    Drawit

  ENDING:
                popa
ENDM

; ============================================================================================================================
; Erase PowerUp
ErasePowerup macro point_x, point_y, color
LOCAL GET_X, GET_y
  pusha
  ; loop till you fuond the top left corner then erase
  
  MOV CX, point_x
  MOV DX, point_y

; Get X poistion
GET_X:
  DEC CX        ; move left
  MOV AH, 0Dh   ; Get pixel
  INT 10h       ; Call video interrupt
  CMP AL, color ; Check if color is the same 
  JE GET_X

  MOV point_x, CX
  INC CX

; Get Y poistion
GET_Y:
  DEC DX        ; move up
  MOV AH, 0Dh   ; Get pixel
  INT 10h       ; Call video interrupt
  CMP AL, color ; Check if color is the same
  JE GET_Y

  MOV point_y, DX

        DrawRectangle point_x, point_y, POWERUP_SIZE+8, POWERUP_SIZE+8, TRACK_COLOR
  popa
ENDM


; ============================================================================================================================
; Draw BG tile macro
; ============================================================================================================================
DrawBGTile MACRO
  LOCAL ROW
  pusha

      MOV CX, 0
      MOV DX, 0

      ROW:

      SetDrawImageParams CX, DX, bg_tile_width, bg_tile_height, 0, 0, 0
      MOV SI, offset img_bg_tile
      pusha
      CALL DrawImage
      popa

      ADD CX, bg_tile_width
      CMP CX, 640
      JL ROW

      MOV CX, 0
      ADD DX, bg_tile_height
      CMP DX, 480
      JL ROW




  popa
ENDM 