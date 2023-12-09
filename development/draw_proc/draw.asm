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

;---------------------------------------------------------------------------------------------------------------------------

DATA SEGMENT USE16

     ;---------------------------------------------------------------------------------------------------------------------------
     ; Images and their meta data

                    include image.inc

     ;---------------------------------------------------------------------------------------------------------------------------

  
     ; SCREEN INFO
     VIDEO_MODE     EQU     4F02h         ; SVGA MODE
     VIDEO_MODE_BX  EQU     0101h         ; SCREEN SIZES

     SCREEN_WIDTH   EQU     640
     SCREEN_HEIGHT  EQU     480

     ; --------------------------------------------------------------------------------------------------------------------------------
     ; DRAW PARAMETERS
     IMAGE_OFFSET_X dw      0
     IMAGE_OFFSET_Y dw      0
     IMAGE_SIZE_X   dw      0
     IMAGE_SIZE_Y   dw      0
     REVERSE        DB      0
     ERASE          DB      0
     RECOLOR        DB      0
     ;---------------------------------------------------------------------------------------------------------------------------------



DATA ENDS
CODE SEGMENT USE16
          ASSUME             CS:CODE,DS:DATA

     ; --------------------------------------------------------------------------------------------------------------------------------
     ; DRAW Procedures

          include            drawP.inc
     ; --------------------------------------------------------------------------------------------------------------------------------

     BEG: 
          MOV                AX,DATA
          MOV                DS,AX
     ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

     ; Set Video Mode
          SetVideoMode

     ; Color The Screen
          ColorScreen        1

     ; Draw The Image
      
          SetDrawImageParams shipOffsetX1, shipOffsetY1, shipSizeX, shipSizeY, 0, 0, 0
          MOV                SI, offset Mikasa_Plane
          CALL               DrawImage

          SetDrawImageParams shipOffsetX1+100, shipOffsetY1+50, shipSizeX, shipSizeY, 0, 0, 0
          MOV                SI, offset Mikasa_Plane
          CALL               DrawImage

          SetDrawImageParams shipOffsetX1+200, shipOffsetY1+75, shipSizeX, shipSizeY, 0, 1, 0
          MOV                SI, offset Mikasa_Plane
          CALL               DrawImage

          SetDrawImageParams shipOffsetX1+300, shipOffsetY1+120, shipSizeX, shipSizeY, 1, 0, 1
          MOV                SI, offset Mikasa_Plane
          CALL               DrawImage

          SetDrawImageParams shipOffsetX1+350, shipOffsetY1+170, shipSizeX, shipSizeY, 3, 0, 1
          MOV                SI, offset Mikasa_Plane
          CALL               DrawImage
     


     ; Wait for a key press
          WaitForKeyPress

     ; Clear the screen
          ClearScreen

     ; Wait for a key press
          WaitForKeyPress

          MOV                AH,4CH
          INT                21H                                                                   ;back to dos
CODE ENDS
END BEG