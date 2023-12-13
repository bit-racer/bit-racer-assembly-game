;---------------------------------------------------------------------------------------------------------------------------
; Author: Peter Safwat
; Date: 2023-12-11
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
; ============================================================================================================================
 
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
               mov    al, 0Ah                                ;color of the current coordinates
               cmp Erase,1
               jne noErase
               xor    al , al
               noErase:
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

