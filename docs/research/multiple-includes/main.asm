;! To run this file:
    ;! the most important step is to open vscode in this folder (../bit-racer-assembly-game/docs/research/multiple-includes)
    ;! and make sure that MASM/TASM is in WORKSPACE mode
    ;otherwise the mounted folder in dosbox workspace won't contain these files
    ;* then you can directly click "Run ASM code"
    
    ;* or do the following
    ;* right click, open emulator
    ;* tasm main.asm
    ;* tlink main.obj // notice TLINK not LINK
    ;* main

; .386 ; TLINK is not happy with this

include procs.inc
include consts.inc

.model small
.stack 64
.data
    ;* Screen constants are defined in consts.inc
    ; ultility
    currentCol      db 0
    currentRow      db 0
    currentColor    db 0
    
    ; message
    msg            db "Bit racers", '$'
    msg_length     db $-msg

.code
    ;* procedures are defined in procs.inc
; draw test
main PROC
    mov ax, @data
    mov ds, ax

    ;* go to video mode (320*200)
    call enterVideoMode

    ;* fill screen color
    mov currentCol, YELLOW
    call fillScreen

    ;* write hello msg
    ; move cursor
    mov currentCol, 14
    mov currentRow, SCREEN_ROWS/2
    call moveCursor

    ; write message
    call printmsg

    ; wait for any key and exit
    mov ah, 0
    int 16h
    mov ax, 4c00h
    int 21h    
    ret
main ENDP
end main