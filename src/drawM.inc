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
