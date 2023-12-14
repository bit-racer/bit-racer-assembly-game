;---------------------------------------------------------------------------------------------------------------------------
; Author: Peter Safwat
; Date: 2023-12-12
; Path Drawing
;---------------------------------------------------------------------------------------------------------------------------

.386

.MODEL COMPACT
.STACK 4096

;---------------------------------------------------------------------------------------------------------------------------
; Macros

  include            drawM.inc
  include            Movement.inc
;---------------------------------------------------------------------------------------------------------------------------

DATA SEGMENT USE16

     ;---------------------------------------------------------------------------------------------------------------------------
     ; Images and their meta data

     SEGMENT_SIZE    EQU     51
                     include car1.inc
     ;---------------------------------------------------------------------------------------------------------------------------

  
     ; SCREEN INFO
     VIDEO_MODE      EQU     4F02h            ; SVGA MODE
     VIDEO_MODE_BX   EQU     0101h            ; SCREEN SIZES

     SCREEN_WIDTH    EQU     640
     SCREEN_HEIGHT   EQU     480
     SEGMENT_COUNT   EQU     40
     DIR_SIZE        EQU     200
     DIR             DB      0
     ; --------------------------------------------------------------------------------------------------------------------------------
     ; DRAW PARAMETERS
     IMAGE_OFFSET_X  dw      0
     IMAGE_OFFSET_Y  dw      0
     IMAGE_SIZE_X    dw      0
     IMAGE_SIZE_Y    dw      0
     REVERSE         DB      0
     ERASE           DB      0
     RECOLOR         DB      0
     COUNT           DB      0
     ;---------------------------------------------------------------------------------------------------------------------------------
     KeyList         db      128 dup (0)
     Where           db      0
     Prev_img        dw      0
     DIRECTIONS_DEMO DB      DIR_SIZE (?)

     ; DIRECTIONS_DEMO DB      3,3,1,2
     spare           db      20
     DELAY           DW      10000
  
     DIRECTION       DB      ?
     SEED            DB      ?

DATA ENDS
CODE SEGMENT USE16

                ASSUME          CS:CODE,DS:DATA

     ; --------------------------------------------------------------------------------------------------------------------------------
     ; DRAW Procedures

         
                include         PROCEEDS.inc
       
     ; --------------------------------------------------------------------------------------------------------------------------------
 

 
     BEG:       
                MOV             AX,DATA
                MOV             DS,AX
     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

     ; Set Video Mode
                SetVideoMode

     ; Color The Screen
                ColorScreen     0

   
     ; mov          di,offset img1F
     ; DrawCar      [car1_X_Offset],[car1_Y_Offset],car1V_Width,car1V_Height
     ; mov          di,offset img2F
     ; DrawCar      [car2_X_Offset],[car2_Y_Offset],car2V_Width,car2V_Height
     MAINLOOP2: 
                MOV             COUNT,0
                ClearScreen
                CALL            GENERATE_NEW_COMBINATION
                MOV             BX,OFFSET DIRECTIONS_DEMO
                MOV             SI,0000H
     DRAW_TRACK:
                INC             SI
                CMP             BYTE PTR [BX],0
                JE              ADDTOUP
                CMP             BYTE PTR    [BX],1
                JE              ADDTODOWN
                CMP             BYTE PTR [BX],2
                JE              ADDTOLEFT
                CMP             BYTE PTR    [BX],3
                JE              ADDTORIGHT
                             
     ADDTOUP:   
                PUSH            BX
                call            moveUp
                POP             BX
                JMP             CHECKING
     ADDTODOWN: 
                PUSH            BX
                call            moveDown
                POP             BX
                JMP             CHECKING
     ADDTOLEFT: 
                PUSH            BX
                call            moveLeft
                POP             BX
                JMP             CHECKING
     ADDTORIGHT:
                PUSH            BX
                call            moveRight
                POP             BX
                JMP             CHECKING
     CHECKING:  
                INC             BX
                CMP             SI,DIR_SIZE
                JNZ             DRAW_TRACK
                CMP             COUNT,SEGMENT_COUNT
                JB              MAINLOOP2
     ;get                the address of the existing int09h handler
     ;      mov          ax, 3509h                                                    ; Get Interrupt Vector
     ;      int          21h                                                          ; -> ES:BX
     ;      push         es bx

     ; ; replace the existing int09h handler with ours
     ;      mov          dx, offset onKeyEvent

     ;      MOV          AX,CS
     ;      MOV          DS,AX
     ;      mov          ax, 2509h
     ;      int          21h
     ;      POP          DS
     ;      call         main

     ; ; return to text mode
     ;      mov          ah, 0
     ;      mov          al, 2
     ;      int          10h

     ; ; restore the original int09h handler
     ;      pop          dx ds
     ;      mov          ax, 2509h
     ;      int          21h
                WaitForKeyPress
                JMP             MAINLOOP2
     exit:      
                MOV             AH,4CH
                INT             21H

CODE ENDS
END BEG
