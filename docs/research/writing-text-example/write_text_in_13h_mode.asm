;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;             Author: Amir Anwar              ;;
;;             Date:  02/12/2023               ;;
;;           Write text in video mode          ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; For more information about this solution check marwan's solution
; https://github.com/amir-kedis/Assembly-x86-helper/tree/main/writing-on-video-mode
.386
DATA SEGMENT USE16

     ; screen info Video mode 13h
     SCREEN_WIDTH  EQU 320
     SCREEN_HEIGHT EQU 200
     SCREEN_SIZE   EQU SCREEN_WIDTH*SCREEN_HEIGHT

     ; screen info text mode 03h
     SCREEN_COLS   EQU 80
     SCREEN_ROWS   EQU 25
     SCREEN_CHARS  EQU SCREEN_COLS*SCREEN_ROWS

     ; colors
     currentColor  db  1                              ; Blue

     ; text
     text          db  "Hello World",'$'
     textLength    EQU $-text


DATA ENDS
CODE SEGMENT USE16
          ASSUME CS:CODE,DS:DATA
     BEG: 
          MOV    AX,DATA
          MOV    DS,AX

     ; set video mode
          MOV    AH,0                 ; Set video mode
          MOV    AL,13h               ; 320x200 256 color mode
          INT    10H

     ; Fill the screen color
          MOV    AX,0A000h            ; Set ES to point to video memory
          MOV    ES,AX
          MOV    DI,0                 ; Set DI to point to the first pixel
          MOV    CX,SCREEN_SIZE       ; Set CX to the number of pixels on the screen
          MOV    AL,currentColor      ; Set AL to the color to fill the screen with
          REP    STOSB                ; Fill the screen with the color in AL

     ;; Write text

     ; Set cursur position to midlle of the screen
          MOV    AH,2                 ; Set cursor position
          MOV    BH,0                 ; Page number
          MOV    DH,SCREEN_ROWS/2     ; Row
          MOV    DL,14                ; Column
          INT    10H
  
     ; Write text
          MOV    AH,9                 ; Write string
          MOV    DX,OFFSET text       ; Set DX to point to the string
          INT    21H

          MOV    AH,4CH
          INT    21H                  ;back to dos
CODE ENDS
END BEG