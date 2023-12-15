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

  SEGMENT_SIZE        EQU     51
                      include track.inc
  ;---------------------------------------------------------------------------------------------------------------------------

  
  ; SCREEN INFO
  VIDEO_MODE          EQU     4F02h         ; SVGA MODE
  VIDEO_MODE_BX       EQU     0101h         ; SCREEN SIZES

  SCREEN_WIDTH        EQU     640
  SCREEN_HEIGHT       EQU     480
  SEGMENT_COUNT       EQU     40
  DIR_SIZE            EQU     200
  DIR                 DB      0

  ; DIRECTIONS
  D_UP                EQU     0
  D_DOWN              EQU     1
  D_LEFT              EQU     2
  D_RIGHT             EQU     3
  ; --------------------------------------------------------------------------------------------------------------------------------
  ; DRAW PARAMETERS
  IMAGE_OFFSET_X      dw      0
  IMAGE_OFFSET_Y      dw      0
  IMAGE_SIZE_X        dw      0
  IMAGE_SIZE_Y        dw      0
  REVERSE             DB      0
  ERASE               DB      0
  RECOLOR             DB      0
  COUNT               DB      0
  ;---------------------------------------------------------------------------------------------------------------------------------
  KeyList             db      128 dup (0)
  Where               db      0
  Prev_img            dw      0
  DIRECTIONS_DEMO     DB      DIR_SIZE (?)

  ; DIRECTIONS_DEMO DB      3,3,1,2
  spare               db      20
  DELAY               DW      10000
  
  DIRECTION           DB      ?
  SEED                DB      ?

  ; OBSTACLE CONSTS
  OBSTACLE_COLOR      EQU     2Ah
  OBSTACLE_WIDTH      EQU     13
  OBSTACLE_HEIGHT     EQU     13
  OBSTACLE_1_OFFSET_X EQU     30
  OBSTACLE_1_OFFSET_Y EQU     5
  OBSTACLE_2_OFFSET_X EQU     17
  OBSTACLE_2_OFFSET_Y EQU     17
  ;NOTE: Cur obstacl percentage is 50% to increase
  ; increase the cases in which it doesn't generate in DrawTrack Macro

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

  MAINLOOP2: 


             ClearScreen
  ; reset
             MOV             COUNT,0
             MOV             DIRECTION,0
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
 
             WaitForKeyPress
  ;if escape pressed exit
             CMP             AL,1Bh
             JE              exit
             JMP             MAINLOOP2
  exit:      
             MOV             AH,4CH
             INT             21H

CODE ENDS
END BEG
