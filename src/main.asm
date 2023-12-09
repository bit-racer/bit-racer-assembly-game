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
                        include         images.inc
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
                ASSUME             CS:CODE, DS:DATA

    ;=================================================================================
    ; PROCEDURES INCLUDE
                include            procs.inc
                include            drawP.inc
    ;=================================================================================

    BEG:        
                mov                ax, DATA
                mov                ds, ax
    
    ;=================================================================================
    ; Code Starts Here
    
                SetVideoMode
                ColorScreen        BG_COLOR

    ; Draw Logo
                MOV                SI, offset ll_img                                                              ;  SI = offset of the image
                SetDrawImageParams ll_offset_x, ll_offset_y, ll_size_x, ll_size_y, 0, 0, 0
                CALl               DrawImage
    
    ; Draw design
                MOV                SI, offset design_img
                SetDrawImageParams DESIGN_offset_x, DESIGN_offset_y, DESIGN_size_x, DESIGN_size_y, 0, 0, 0
                CALl               DrawImage

    ; Draw entname
                MOV                SI, offset entname_img
                SetDrawImageParams ENTNAME_offset_x, ENTNAME_offset_y, ENTNAME_size_x, ENTNAME_size_y, 0, 0, 0
                CALl               DrawImage

    
                WaitForKeyPress

    

                mov                currentColumn, 40
                mov                currentRow, 13
                call               moveCursor
    
    ; Read username1
                readData           str_enter_usrname1, usernameBuffer1

    ; leave a space
                add                currentRow, 4
                call               moveCursor
    
    ; Read points1
                readData           str_initial_points1, pointsBuffer1
    
    ; leave a space
                add                currentRow, 4
                call               moveCursor

    ;;;;;;;;;;;;;;;;;;;;;;;;; promt and wait for enter key
                mov                dx, offset str_press_enter_key
                call               printmsg

    waiting:    
                mov                ah, 0
                int                16h                                                                            ; wait for keypress from user: ah = scancode
                cmp                ah, ENTER_KEY
                je                 nextScreen
                jmp                waiting


    nextScreen: 
    ;?;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;SCREEN SEPARATOR;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                mov                currentColumn, 1
                mov                currentRow, 1
                call               moveCursor

    ; Read username2
                readData           str_enter_usrname2, usernameBuffer2

    ; leave a space
                add                currentRow, 4
                call               moveCursor
    
    ; Read points1
                readData           str_initial_points2, pointsBuffer2
    
    ; leave a space
                add                currentRow, 4
                call               moveCursor

    ;;;;;;;;;;;;;;;;;;;;;;;;; promt and wait for enter key
                mov                dx, offset str_press_enter_key
                call               printmsg

    waiting2:   
                mov                ah, 0
                int                16h                                                                            ; wait for keypress from user: ah = scancode
                cmp                ah, ENTER_KEY
                je                 nextScreen2
                jmp                waiting2


    nextScreen2:
    ;?;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;SCREEN SEPARATOR;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                mov                currentColumn, 1
                mov                currentRow, 1
                call               moveCursor

    ; print both data to make sure
                printData          username1, pointsString1
    
    ; leave a space
                add                currentRow, 4
                call               moveCursor
    
                printData          username2, pointsString2

    ;;;;;;;;;;;;;;;;;;;;;;;;; End
    byebye:     
                mov                ax ,4c00h
                int                21h

CODE ENDS
;=================================================================================
END BEG