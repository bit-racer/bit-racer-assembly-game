;* only constant values, not variables.

; sceen info video mode
VIDEO_MODE     EQU     4F02h         ; SVGA MODE
VIDEO_MODE_BX  EQU     0101h         ; SCREEN SIZES

SCREEN_WIDTH    equ 640
SCREEN_HEIGHT   equ 480
SCREEN_SIZE     equ SCREEN_HEIGHT * SCREEN_WIDTH

; sceen info text mode
SCREEN_COLS     equ 80
SCREEN_ROWS     equ 25
SCREEN_CHARS    equ SCREEN_COLS * SCREEN_ROWS

; Track consts
  SEGMENT_SIZE        EQU     69
  SEGMENT_COUNT       EQU     40
	DIR_SIZE            EQU     200
 
  ; DIRECTIONS
  D_UP                EQU     0
  D_DOWN              EQU     1
  D_LEFT              EQU     2
  D_RIGHT             EQU     3 

  TRACK_COLOR EQU 21d
  START_COLOR EQU 15d
  FINISH_COLOR EQU RED

  ; OBSTACLE CONSTS
  OBSTACLE_COLOR      EQU     2Ah
  OBSTACLE_WIDTH      EQU     13
  OBSTACLE_HEIGHT     EQU     13

  OBSTACLE_1_OFFSET_X EQU     5
  OBSTACLE_1_OFFSET_Y EQU     5

  OBSTACLE_2_OFFSET_X EQU     SEGMENT_SIZE - OBSTACLE_WIDTH - 5
  OBSTACLE_2_OFFSET_Y EQU     SEGMENT_SIZE - OBSTACLE_HEIGHT - 5
  ;NOTE: Cur obstacl percentage is 50% to increase
  ; increase the cases in which it doesn't generate in DrawTrack Macro

  ; POWERUPS CONSTS
  POWERUP1_COLOR       EQU     0AH ; lime  green 
  POWERUP2_COLOR       EQU     25H ; terquise
  POWERUP3_COLOR       EQU     63h ; light blue
  POWERUP4_COLOR       EQU     44h ; yellow

  POWERUP_SIZE         EQU     10 ; TODO: change later

  POWERUP1_OFFSET_X    EQU     10
  POWERUP1_OFFSET_Y    EQU     5 + POWERUP_SIZE

  POWERUP2_OFFSET_X    EQU     10
  POWERUP2_OFFSET_Y    EQU     5 + POWERUP_SIZE*2 +10

  POWERUP3_OFFSET_X    EQU     SEGMENT_SIZE - POWERUP_SIZE - 10
  POWERUP3_OFFSET_Y    EQU     SEGMENT_SIZE - POWERUP_SIZE*2 - 10

  POWERUP4_OFFSET_X    EQU     SEGMENT_SIZE - POWERUP_SIZE - 10
  POWERUP4_OFFSET_Y    EQU     SEGMENT_SIZE - POWERUP_SIZE*3 - 10
	
; colors
BLACK           equ 0
BLUE            equ 1
GREEN           equ 2
CYAN            equ 3
RED             equ 4
MAGENTA         equ 5
BROWN           equ 6
LIGHT_GRAY      equ 7
DARK_GRAY       equ 8
LIGHT_BLUE      equ 9
LIGHT_GREEN     equ 10
LIGHT_CYAN      equ 11
LIGHT_RED       equ 12
LIGHT_MAGENTA   equ 13
YELLOW          equ 14
WHITE           equ 15
BG_COLOR        equ 204

;* scan codes of pressed keys
;* scan code of released key = scan code + 80h
ESCAPE_KEY      equ 01h
ENTER_KEY       equ 1ch
BACKSPACE_KEY   EQU 0Eh
F1              equ 3bh
F2              equ 3ch
UP_ARROW        equ 48h
DOWN_ARROW      equ 50h
LEFT_ARROW      equ 4bh
RIGHT_ARROW     equ 4dh

	key_w                    equ         11h
	key_s                    equ         1FH
	key_a                    equ         1EH
	key_d                    equ         20h
	key_f                    equ         21h