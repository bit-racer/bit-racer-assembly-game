;---------------------------------------------------------------------------------
; Bit Racer Game - Assembly Language Project
; Authors:
;   - Peter Safwat
;   - Muhammad Amr
;   - George Magdy
;   - Amir Anwar
;---------------------------------------------------------------------------------
; MAIN FILE : Entry point for the program
;---------------------------------------------------------------------------------

;=================================================================================
; Module Definition

.386
.MODEL COMPACT
.STACK 8192
;=================================================================================

;=================================================================================
; MACROS INCLUDE

include     macros.inc
include     drawM.inc
;=================================================================================

;=================================================================================
; DATA SEGMENT
DATA SEGMENT USE16
    ;=================================================================================
    ; constants includes
                        include         consts.inc
    ;=================================================================================

    ; strings to print
    str_enter_usrname1  db              "User1's Name:", '$'
    str_initial_points1 db              "User1's Initial Points: ", '$'

    str_enter_usrname2  db              "User2's Name:", '$'
    str_initial_points2 db              "User2's Initial Points: ", '$'

    str_press_enter_key db              "Press Enter Key To Continue", '$'
    
    ; variables
    currentColumn       db              0
    currentRow          db              0
    currentColor        db              BLACK

    ; User 1 data
                        usernameBuffer1 label byte
    usrMaxSize1         db              16
    usrActualSize1      db              ?
    username1           db              17 DUP ('$')
    
                        pointsBuffer1   label byte
    ptsMaxSize1         db              4
    ptsActualSize1      db              ?
    pointsString1       db              5 DUP ('$')

    ; User 2 data
                        usernameBuffer2 label byte
    usrMaxSize2         db              16
    usrActualSize2      db              ?
    username2           db              17 DUP ('$')
    
                        pointsBuffer2   label byte
    ptsMaxSize2         db              4
    ptsActualSize2      db              ?
    pointsString2       db              5 DUP ('$')
DATA ENDS
;=================================================================================

;=================================================================================
; CODE SEGMENT

CODE SEGMENT USE16
                ASSUME       CS:CODE, DS:DATA

    ;=================================================================================
    ; PROCEDURES INCLUDE

                include      procs.inc
    ;=================================================================================

    BEG:        
                mov          ax, DATA
                mov          ds, ax
    
                SetVideoMode
                mov          currentColor, CYAN
                ColorScreen  currentColor
    

                mov          currentColumn, 1
                mov          currentRow, 1
                call         moveCursor
    
    ; Read username1
                readData     str_enter_usrname1, usernameBuffer1

    ; leave a space
                add          currentRow, 4
                call         moveCursor
    
    ; Read points1
                readData     str_initial_points1, pointsBuffer1
    
    ; leave a space
                add          currentRow, 4
                call         moveCursor

    ;;;;;;;;;;;;;;;;;;;;;;;;; promt and wait for enter key
                mov          dx, offset str_press_enter_key
                call         printmsg

    waiting:    
                mov          ah, 0
                int          16h                                    ; wait for keypress from user: ah = scancode
                cmp          ah, ENTER_KEY
                je           nextScreen
                jmp          waiting


    nextScreen: 
                mov          currentColor, LIGHT_GREEN
                ColorScreen  currentColor
    ;?;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;SCREEN SEPARATOR;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                mov          currentColumn, 1
                mov          currentRow, 1
                call         moveCursor

    ; Read username2
                readData     str_enter_usrname2, usernameBuffer2

    ; leave a space
                add          currentRow, 4
                call         moveCursor
    
    ; Read points1
                readData     str_initial_points2, pointsBuffer2
    
    ; leave a space
                add          currentRow, 4
                call         moveCursor

    ;;;;;;;;;;;;;;;;;;;;;;;;; promt and wait for enter key
                mov          dx, offset str_press_enter_key
                call         printmsg

    waiting2:   
                mov          ah, 0
                int          16h                                    ; wait for keypress from user: ah = scancode
                cmp          ah, ENTER_KEY
                je           nextScreen2
                jmp          waiting2


    nextScreen2:
                mov          currentColor, YELLOW
                ColorScreen  currentColor
    ;?;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;SCREEN SEPARATOR;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                mov          currentColumn, 1
                mov          currentRow, 1
                call         moveCursor

    ; print both data to make sure
                printData    username1, pointsString1
    
    ; leave a space
                add          currentRow, 4
                call         moveCursor
    
                printData    username2, pointsString2

    ;;;;;;;;;;;;;;;;;;;;;;;;; End
    byebye:     
                mov          ax ,4c00h
                int          21h

CODE ENDS
;=================================================================================
END BEG