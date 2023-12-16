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

include     macros.inc      ; general macros
include     drawM.inc       ; drawing macros
include     moveM.inc       ; car movement macros 
include     trackMM.inc     ; Move track random walker function
include     chatM.inc       ; chat macros
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
                              include         car1s.inc                             ; red car small
                              include         car2s.inc                             ; green car small
                              include         track.inc                             ; track

    ;=================================================================================

    ; --------------------------------------------------------------------------------------------------------------------------------
    ; DRAW PARAMETERS
    IMAGE_OFFSET_X            dw              0
    IMAGE_OFFSET_Y            dw              0
    IMAGE_SIZE_X              dw              0
    IMAGE_SIZE_Y              dw              0
    REVERSE                   DB              0
    ERASE                     DB              0
    RECOLOR                   DB              0
    ;---------------------------------------------------------------------------------------------------------------------------------


    ; strings to print
    str_enter_usrname1        db              "User1's Name:", '$'
    str_initial_points1       db              "User1's Initial Points: ", '$'

    str_enter_usrname2        db              "User2's Name:", '$'
    str_initial_points2       db              "User2's Initial Points: ", '$'

    str_press_enter_key       db              "Press Enter Key To Continue", '$'

    str_user1_won             db              "User1 Won!", '$'
    str_user2_won             db              "User2 Won!", '$'
    str_tie                   db              "Tie!", '$'
    
    ; variables
    currentColumn             db              0
    currentRow                db              0
    currentColor              db              BLACK
    curCar                    db              0                                     ; 0: red, 1: green, 2: reed, 3: pink

    ; User 1 data
                              usernameBuffer1 label byte
    usrMaxSize1               db              16
    usrActualSize1            db              ?
    username1                 db              17 DUP ('$')
    
                              pointsBuffer1   label byte
    ptsMaxSize1               db              4
    ptsActualSize1            db              ?
    pointsString1             db              5 DUP ('$')

    usrCar1                   db              0                                     ; 0: red, 1: green, 2: reed, 3: pink


    ; User 2 data
                              usernameBuffer2 label byte
    usrMaxSize2               db              16
    usrActualSize2            db              ?
    username2                 db              17 DUP ('$')
    
                              pointsBuffer2   label byte
    ptsMaxSize2               db              4
    ptsActualSize2            db              ?
    pointsString2             db              5 DUP ('$')

    usrCar2                   db              0                                     ; 0: red, 1: green, 2: reed, 3: pink

    ; Main Menu Buttons variables
    curBtn                    db              1                                     ; 0: chat, 1: play, 2: exit

    ; Car Movement Variables and keyboard input handling
    KeyList                   db              128 dup (0)
    Where                     db              0
    Prev_img                  dw              0

    ; Chat Variables

    ; User 1 cursor position
    sender_row                db              0
    sender_col                db              0

    ; User 2 cursor position
    rec_row                   db              0
    rec_col                   db              40

    ; Track Params
    DIR                       DB              0
    COUNT                     DB              0
                              label           INITIAL_TRACK_DIRECTION
    DIRECTIONS_DEMO           DB              DIR_SIZE (?)
    spare                     db              20
    DELAY                     DW              10000
  
    DIRECTION                 DB              ?
    SEED                      DB              ?



    INITIAL_TRACK_X           DW              0
    INITIAL_TRACK_Y           DW              0
    ; FINAL_TRACK_X           DW              0
    ; FINAL_TRACK_Y           DW              0
    ; INITIAL_TRACK_DIRECTION DW              0

    ; Winning Variables
    WINNER                    DB              0                                     ; 0: idle, 1: user1, 2: user2, 3: tie
    START_TRACK               DB              0

    DURATION                  DB              5
    FMINUTES                  DB              ?
    FSECONDS                  DB              ?
    CMINUTES                  DB              ?
    CSECONDS                  DB              ?
    SMINUTES                  DB              ?
    SSECONDS                  DB              ?
    CURRENT_MOMENT_IN_SECONDS DB              ?
    
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
                      include         moveP.inc
                      include         chatP.inc
                      include         randomP.inc                            ; random walker functions (randomization)
                      include         trackMP.inc                            ; Move track random walker functions
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
    ; Get user action
                      MOV             curBtn, 1
                      CALL            DrawBtnMarker
    ChooseAction:     
                      MOV             AH, 0                                  ; wait for keypress from user: ah = scancode
                      INT             16h
                      CMP             AH, LEFT_ARROW                         ; left arrow
                      JE              ChooseActionLeft
                      CMP             AH, RIGHT_ARROW                        ; right arrow
                      JE              ChooseActionRight
                      CMP             AH, ENTER_KEY
                      JE              ChooseActionDone
                      JMP             ChooseAction
    ChooseActionLeft: 
                      CMP             curBtn, 0
                      JE              ChooseAction
                      DEC             curBtn
                      CALL            DrawBtnMarker
                      JMP             ChooseAction
    ChooseActionRight:
                      CMP             curBtn, 2
                      JE              ChooseAction
                      INC             curBtn
                      CALL            DrawBtnMarker
                      JMP             ChooseAction
    ChooseActionDone: 
                      CMP             curBtn, 0
                      JE              Chat
                      CMP             curBtn, 1
                      JE              Play
                      CMP             curBtn, 2
                      JE              Exit
                      JMP             ChooseAction
    
    Chat:             
                      CALL            StartChat
                      JMP             PROGRAM_LOOP
    Play:             
                      MOV             COUNT, 0
                      CALL            GET_STARTING_TIME
                      CALL            CALC_FINISH
                      CALL            GenerateTrack
                      WaitForKeyPress
                      CMP             AH, ENTER_KEY
                      JNE             Play
                      CALL            PutCars
                      CMP             WINNER, 1
                      JE              User1Wins
                      CMP             WINNER, 2
                      JE              User2Wins
                      CMP             WINNER, 3
                      JE              Tie

    User1Wins:        
                      ColorScreen     1
    ; Set curser to the middle of the screen
                      mov             currentColumn, 30
                      mov             currentRow, 16
                      call            moveCursor
                      MOV             DX, offset str_user1_won
                      call            printmsg
                      CALL            WAIT_FOR_DELAY
                      WaitForKeyPress
                      JMP             PROGRAM_LOOP
    User2Wins:        
                      ColorScreen     2
                      mov             currentColumn, 30
                      mov             currentRow, 16
                      call            moveCursor
                      MOV             DX, offset str_user1_won
                      call            printmsg
                      CALL            WAIT_FOR_DELAY
                      WaitForKeyPress
                      JMP             PROGRAM_LOOP
    Tie:              
                      ColorScreen     3
                      mov             currentColumn, 30
                      mov             currentRow, 16
                      call            moveCursor
                      MOV             DX, offset str_user1_won
                      call            printmsg
                      CALL            WAIT_FOR_DELAY
                      WaitForKeyPress
                      JMP             PROGRAM_LOOP



    ;;;;;;;;;;;;;;;;;;;;;;;;; End
    EXIT:             
                      ClearScreen
                      mov             ax ,4c00h
                      int             21h

CODE ENDS
;=================================================================================
END BEG
