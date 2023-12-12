;---------------------------------------------------------------------------------------------------------------------------
; Author: Amir Anwar
; Date: 2023-12-09
; Draw Procedures
;---------------------------------------------------------------------------------------------------------------------------

.386

.MODEL COMPACT
.STACK 4096

;---------------------------------------------------------------------------------------------------------------------------
; Macros

include drawM.inc
  include            Movement.inc

;---------------------------------------------------------------------------------------------------------------------------

DATA SEGMENT USE16

    ;---------------------------------------------------------------------------------------------------------------------------
    ; Images and their meta data

                        include car1.inc
                        include car2.inc
    ;---------------------------------------------------------------------------------------------------------------------------

  
    ; SCREEN INFO
    VIDEO_MODE          EQU     4F02h          ; SVGA MODE
    VIDEO_MODE_BX       EQU     0101h          ; SCREEN SIZES

    SCREEN_WIDTH        EQU     640
    SCREEN_HEIGHT       EQU     480

    ; --------------------------------------------------------------------------------------------------------------------------------
    ; DRAW PARAMETERS
    IMAGE_OFFSET_X      dw      0
    IMAGE_OFFSET_Y      dw      0
    IMAGE_SIZE_X        dw      0
    IMAGE_SIZE_Y        dw      0
    REVERSE             DB      0
    ERASE               DB      0
    RECOLOR             DB      0
    ;---------------------------------------------------------------------------------------------------------------------------------
     KeyList             db      128 dup (0)
     Where               db         0
   Prev_img dw    0

DATA ENDS
CODE SEGMENT USE16

         ASSUME             CS:CODE,DS:DATA

    ; --------------------------------------------------------------------------------------------------------------------------------
    ; DRAW Procedures

         include            drawP.inc
         include            PROCEEDS.inc
       
    ; --------------------------------------------------------------------------------------------------------------------------------
 

 
    BEG: 
         MOV                AX,DATA
         MOV                DS,AX
    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    ; Set Video Mode
         SetVideoMode

    ; Color The Screen
         ColorScreen        0

    ; Draw The Image
         mov                cx,[carOffsetX1]
         mov                dx,[carOffsetY1]
         SetDrawImageParams cx, dx, carSizeX1, carSizeY1, 0, 0, 0
         MOV                SI, offset car1
         CALL               DrawImage

         mov                cx,[carOffsetX2]
         mov                dx,[carOffsetY2]
         SetDrawImageParams cx, dx, carSizeX2, carSizeY2, 0, 0, 0
         MOV                SI, offset car2
         CALL               DrawImage



    ; get                the address of the existing int09h handler
         mov                ax, 3509h                                     ; Get Interrupt Vector
         int                21h                                           ; -> ES:BX
         push               es bx

    ; replace the existing int09h handler with ours
        mov dx, offset onKeyEvent
PUSH DS
MOV AX,CS
MOV DS,AX
mov ax, 2509h
int 21h
POP DS
         call               main

    ; return to text mode
         mov                ah, 0
         mov                al, 2
         int                10h

    ; restore the original int09h handler
         pop                dx ds
         mov                ax, 2509h
         int                21h
    exit:
          MOV                AH,4CH
          INT                21H      

CODE ENDS
END BEG