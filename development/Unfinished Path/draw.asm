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
                  include track.inc
  ;---------------------------------------------------------------------------------------------------------------------------

  
  ; SCREEN INFO
  VIDEO_MODE      EQU     4F02h         ; SVGA MODE
  VIDEO_MODE_BX   EQU     0101h         ; SCREEN SIZES

  SCREEN_WIDTH    EQU     640
  SCREEN_HEIGHT   EQU     480
  SEGMENT_COUNT   EQU     40
  DIR_SIZE        EQU     6
  DIR             DB      0

  ; DIRECTIONS
  D_UP            EQU     0
  D_DOWN          EQU     1
  D_LEFT          EQU     2
  D_RIGHT         EQU     3
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
  track_image     Dw      0

;   DIRECTIONS_DEMO DB     3,3,3,1,1,2
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


              ClearScreen
  ; reset
              MOV             COUNT,0
              MOV             DIRECTION,0
  ; NOTE: remove following 2 lines if you want random start
            ;   MOV             car1_X_Offset,0
            ;   MOV             car1_Y_Offset,0
  ;MOV             SEED,0
              MOV             DELAY,10000

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
  ; Check next direction to put coreners

              CMP             BYTE PTR [BX+1],D_UP
              JE              UP_UP
              CMP             BYTE PTR [BX+1],D_LEFT
              JE              UP_LEFT
              CMP             BYTE PTR [BX+1],D_RIGHT
              JE              UP_RIGHT
              JMP             UP_UP
  UP_UP:      MOV             track_image, offset img_ts_ud
              JMP             UP_MOVE
  UP_LEFT:    MOV             track_image, offset img_ts_c2bl
              JMP             UP_MOVE
  UP_RIGHT:   MOV             track_image, offset img_ts_c1br
              JMP             UP_MOVE
  UP_MOVE:    
              call            moveUp
              POP             BX
              JMP             CHECKING
  ADDTODOWN:  
              PUSH            BX
  ; Check next direction to put coreners
              CMP             BYTE PTR [BX+1],D_DOWN
              JE              DOWN_DOWN
              CMP             BYTE PTR [BX+1],D_LEFT
              JE              DOWN_LEFT
              CMP             BYTE PTR [BX+1],D_RIGHT
              JE              DOWN_RIGHT
              JMP             DOWN_DOWN
  DOWN_DOWN:  MOV             track_image, offset img_ts_ud
              JMP             DOWN_MOVE
  DOWN_LEFT:  MOV             track_image, offset img_ts_c3tl
              JMP             DOWN_MOVE
  DOWN_RIGHT: MOV             track_image, offset img_ts_c4tr
              JMP             DOWN_MOVE
  DOWN_MOVE:  

              call            moveDown
              POP             BX
              JMP             CHECKING
  ADDTOLEFT:  
              PUSH            BX
  ; Check next direction to put coreners
              CMP             BYTE PTR [BX+1],D_UP
              JE              LEFT_UP
              CMP             BYTE PTR [BX+1],D_DOWN
              JE              LEFT_DOWN
              CMP             BYTE PTR [BX+1],D_LEFT
              JE              LEFT_LEFT
              JMP             LEFT_LEFT
  LEFT_UP:    MOV             track_image, offset img_ts_c4tr
              JMP             LEFT_MOVE
  LEFT_DOWN:  MOV             track_image, offset img_ts_c1br
              JMP             LEFT_MOVE
  LEFT_LEFT:  MOV             track_image, offset img_ts_lr
              JMP             LEFT_MOVE
  LEFT_MOVE:  
              call            moveLeft
              POP             BX
              JMP             CHECKING
  ADDTORIGHT: 
              PUSH            BX
  ; Check next direction to put coreners
              CMP             BYTE PTR [BX+1],D_UP
              JE              RIGHT_UP
              CMP             BYTE PTR [BX+1],D_DOWN
              JE              RIGHT_DOWN
              CMP             BYTE PTR [BX+1],D_RIGHT
              JE              RIGHT_RIGHT
              JMP             RIGHT_RIGHT
  RIGHT_UP:   MOV             track_image, offset img_ts_c3tl
              JMP             RIGHT_MOVE
  RIGHT_DOWN: MOV             track_image, offset img_ts_c1br
              JMP             RIGHT_MOVE
  RIGHT_RIGHT:MOV             track_image, offset img_ts_lr
              JMP             RIGHT_MOVE
  RIGHT_MOVE: 
              call            moveRight
              POP             BX
              JMP             CHECKING
  CHECKING:   
              INC             BX
              CMP             SI,DIR_SIZE
              JNZ             DRAW_TRACK
              CMP             COUNT,DIR_SIZE
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
