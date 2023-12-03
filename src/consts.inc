;* only constant values, not variables.

; sceen info video mode
SCREEN_WIDTH    equ 320
SCREEN_HEIGHT   equ 200
SCREEN_SIZE     equ SCREEN_HEIGHT * SCREEN_WIDTH

; sceen info text mode
SCREEN_COLS     equ 80
SCREEN_ROWS     equ 25
SCREEN_CHARS    equ SCREEN_COLS * SCREEN_ROWS

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

;* scan codes of pressed keys
;* scan code of released key = scan code + 80h
ESCAPE          equ 01h
ENTER           equ 1ch
F1              equ 3bh
F2              equ 3ch
UP_ARROW        equ 48h
DOWN_ARROW      equ 50h
LEFT_ARROW      equ 4bh
RIGHT_ARROW     equ 4dh
