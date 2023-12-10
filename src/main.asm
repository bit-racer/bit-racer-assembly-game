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
.STACK 4084
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
    ; includes
                        include         consts.inc
    ;include         images.inc

    ; Images
                        include         logo_img.inc                          ; logo image
                        include         np_img.inc                            ; name prompt image
                        include         car1.inc                              ; red car large
                        include         car2.inc                              ; green car large
                        include         car3.inc                              ; reed car large
                        include         car4.inc                              ; pink car large
                        include         tn_img.inc                            ; thank you image
                        include         cmr_img.inc                           ; car makrer image
    ;=================================================================================

    ; --------------------------------------------------------------------------------------------------------------------------------
    ; DRAW PARAMETERS
    IMAGE_OFFSET_X      dw              0
    IMAGE_OFFSET_Y      dw              0
    IMAGE_SIZE_X        dw              0
    IMAGE_SIZE_Y        dw              0
    REVERSE             DB              0
    ERASE               DB              0
    RECOLOR             DB              0
    ;---------------------------------------------------------------------------------------------------------------------------------


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
                ASSUME          CS:CODE, DS:DATA

    ;=================================================================================
    ; PROCEDURES INCLUDE
                include         procs.inc
                include         drawP.inc
    ;=================================================================================

    BEG:        
                mov             ax, DATA
                mov             ds, ax
    
    ;=================================================================================
    ; Code Starts Here
    
                SetVideoMode
                ColorScreen     BG_COLOR

    ; DRAW PAGE 0
                DrawPage0
    
                WaitForKeyPress

    

                mov             currentColumn, 30
                mov             currentRow, 16
                call            moveCursor
    
    ; Read username1
                readData        str_enter_usrname1, usernameBuffer1
    
    ; Read points1
                readData        str_initial_points1, pointsBuffer1
    


    ;;;;;;;;;;;;;;;;;;;;;;;;; promt and wait for enter key
                mov             dx, offset str_press_enter_key
                call            printmsg

    waiting:    
                mov             ah, 0
                int             16h                                    ; wait for keypress from user: ah = scancode
                cmp             ah, ENTER_KEY
                je              nextScreen
                jmp             waiting


    nextScreen: 
    ;?;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;SCREEN SEPARATOR;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                ColorScreen     BG_COLOR
                DrawPage0
                mov             currentColumn, 30
                mov             currentRow, 16
                call            moveCursor

    ; Read username2
                readData        str_enter_usrname2, usernameBuffer2

    ; Read points1
                readData        str_initial_points2, pointsBuffer2

    ;;;;;;;;;;;;;;;;;;;;;;;;; promt and wait for enter key
                mov             dx, offset str_press_enter_key
                call            printmsg

    waiting2:   
                mov             ah, 0
                int             16h                                    ; wait for keypress from user: ah = scancode
                cmp             ah, ENTER_KEY
                je              nextScreen2
                jmp             waiting2


    nextScreen2:
    ;?;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;SCREEN SEPARATOR;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                ColorScreen     BG_COLOR
                DrawPage0
                mov             currentColumn, 30
                mov             currentRow, 16
                call            moveCursor

    ; print both data to make sure
                printData       username1, pointsString1
                printData       username2, pointsString2

                WaitForKeyPress

    ;;;;;;;;;;;;;;;;;;;;;;;;; End
    byebye:     
                mov             ax ,4c00h
                int             21h

CODE ENDS
;=================================================================================
END BEG