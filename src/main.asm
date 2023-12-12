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
.MODEL HUGE
.STACK 4084
;=================================================================================

;=================================================================================
; MACROS INCLUDE

include     macros.inc
include     drawM.inc
;=================================================================================


;!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
; TODO: BIG TODO: MIGRATE TO Binary files and remove EXTRA SEGMENT
    ; AND DraeImageE PROC
;!!!!!!!!
EXTRA SEGMENT USE16
    ;=================================================================================
    ; More image includes page 0 and most of page 1
          include chat_img.inc    ; chat btn image
          include play_img.inc    ; play btn image
          include np_img.inc      ; name prompt image
          include car1.inc        ; red car large
          include car2.inc        ; green car large
          include car3.inc        ; reed car large
          include car4.inc        ; pink car large
          include tn_img.inc      ; thank you image
          include cmr_img.inc     ; car makrer image
          include logo_img.inc    ; logo image
EXTRA ENDS

    ;=================================================================================
    ; DATA SEGMENT
DATA SEGMENT USE16
    ;=================================================================================
    ; includes
                        include         consts.inc
    ; Images
                        include         exit_img.inc                          ; exit btn image
                        include         arr_up.inc                            ; arrow up image

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
    curCar              db              0                                     ; 0: red, 1: green, 2: reed, 3: pink

    ; User 1 data
                        usernameBuffer1 label byte
    usrMaxSize1         db              16
    usrActualSize1      db              ?
    username1           db              17 DUP ('$')
    
                        pointsBuffer1   label byte
    ptsMaxSize1         db              4
    ptsActualSize1      db              ?
    pointsString1       db              5 DUP ('$')

    usrCar1             db              0                                     ; 0: red, 1: green, 2: reed, 3: pink


    ; User 2 data
                        usernameBuffer2 label byte
    usrMaxSize2         db              16
    usrActualSize2      db              ?
    username2           db              17 DUP ('$')
    
                        pointsBuffer2   label byte
    ptsMaxSize2         db              4
    ptsActualSize2      db              ?
    pointsString2       db              5 DUP ('$')

    usrCar2             db              0                                     ; 0: red, 1: green, 2: reed, 3: pink

    
DATA ENDS
;=================================================================================

;=================================================================================
; CODE SEGMENT

CODE SEGMENT USE16
                    ASSUME          CS:CODE, DS:DATA, ES:EXTRA

    ;=================================================================================
    ; PROCEDURES INCLUDE
                    include         procs.inc
                    include         drawP.inc
    ;=================================================================================

    BEG:            
                    mov             ax, DATA
                    mov             ds, ax
                    mov             AX, EXTRA
                    mov             ES, AX
    
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
    
    ; Read usr car by moving by the arrow keys <- and -> to choose press enter
                    MOV             curCar, 0
                    CALL            DrawMarker
    ChooseCar1:     
                    MOV             AH, 0                                  ; wait for keypress from user: ah = scancode
                    INT             16h
                    CMP             AH, LEFT_ARROW                         ; left arrow
                    JE              ChooseCar1Left
                    CMP             AH, RIGHT_ARROW                        ; right arrow
                    JE              ChooseCar1Right
                    CMP             AH, ENTER_KEY
                    JE              ChooseCar1Done
                    JMP             ChooseCar1
    ChooseCar1Left: 
                    CMP             curCar, 0
                    JE              ChooseCar1
                    DEC             curCar
                    CALL            DrawMarker
                    JMP             ChooseCar1
    ChooseCar1Right:
                    CMP             curCar, 3
                    JE              ChooseCar1
                    INC             curCar
                    CALL            DrawMarker
                    JMP             ChooseCar1
    ChooseCar1Done: 
                    MOV             AL, curCar
                    MOV             usrCar1, AL
                


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
    
    ; Read usr car by moving by the arrow keys <- and -> to choose press enter
                    MOV             curCar, 0
                    CALL            DrawMarker
    ChooseCar2:     
                    MOV             AH, 0                                  ; wait for keypress from user: ah = scancode
                    INT             16h
                    CMP             AH, LEFT_ARROW                         ; left arrow
                    JE              ChooseCar2Left
                    CMP             AH, RIGHT_ARROW                        ; right arrow
                    JE              ChooseCar2Right
                    CMP             AH, ENTER_KEY
                    JE              ChooseCar2Done
                    JMP             ChooseCar2
    ChooseCar2Left: 
                    CMP             curCar, 0
                    JE              ChooseCar2
                    DEC             curCar
                    CALL            DrawMarker
                    JMP             ChooseCar2
    ChooseCar2Right:
                    CMP             curCar, 3
                    JE              ChooseCar2
                    INC             curCar
                    CALL            DrawMarker
                    JMP             ChooseCar2
    ChooseCar2Done: 
                    MOV             AL, curCar
                    MOV             usrCar2, AL

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
    
    ;=================================================================================
    ; Start of Program loop
    ;=================================================================================
    PROGRAM_LOOP:   
    ;---------------------------------------------------------------------------------------------------------------------------------
    ; Page 1
                    ColorScreen     BG_COLOR
                    DrawPage1

    ;;;;;;;;;;;;;;;;;;;;;;;;; End
    EXIT:           
                    mov             ax ,4c00h
                    int             21h

CODE ENDS
;=================================================================================
END BEG