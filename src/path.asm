<<<<<<< Updated upstream
                                    .MODEL SMALL
=======



.MODEL SMALL
>>>>>>> Stashed changes
.STACK 64

.DATA

<<<<<<< Updated upstream
    LIGHT_GREY EQU 7
    DARK_GREY EQU 8
    SEGMENT_LENGTH EQU 60
    SEGMENT_WIDTH EQU 20
    SCREEN_WIDTH EQU 320
    STARTING_ROW EQU 170
    ;DIRECTIONS_DEMO  DB 2,2,2,1,2,2,1,0,0,0,3,0
    ;DIRECTIONS_DEMO  DB 2,1,2,3,2,1,1,0,1,2,2,2,3,0,3
    ;DIRECTIONS_DEMO  DB 2,2,2,2,2,1,1,1,0,0,0,0,0,3,2,2,2,2
    DIRECTIONS_DEMO  DB 2,1,2,3,2,1,2,3,2,1,2,3,2,1,1,1,0,3,0
    N DB $-DIRECTIONS_DEMO
=======
   LIGHT_GREY EQU 7
   DARK_GREY EQU 8
   SEGMENT_LENGTH EQU 24
   SEGMENT_WIDTH EQU 21
   STARTING_ROW EQU 60
   STARTING_COLUMN EQU 50
   SCREEN_WIDTH EQU 320
   SCREEN_HEIGHT EQU 200
   DIR_SIZE EQU 15
   BOUNDARY_VERTICAL EQU 10
   BOUNDARY_HORIZONTAL EQU 5
   
   TRAVERSING_ROW DW 60
   TRAVERSING_COLUMN DW 50

   COLLISION DB 0
   DIRECTION DB ?
   SEED DB ?
   DELAY DW 20000
   DIRECTIONS_DEMO DB DIR_SIZE DUP(4)

   ;DIRECTIONS_DEMO DB 1,2,2,2,3,3,3,0,0,3
   N DB $-DIRECTIONS_DEMO

>>>>>>> Stashed changes
   
.CODE 


<<<<<<< Updated upstream
     
=======
    SET_GRAPHICS_MODE PROC
        MOV AX , 0A000H
        MOV ES , AX
        MOV AX, 19
        INT 10H
        RET
    SET_GRAPHICS_MODE ENDP

    SRAND_SYSTEM_TIME PROC
        PUSH DX
        PUSH CX
        PUSH AX
        XOR AX,AX
        INT 1AH
        MOV SEED , DL
        POP AX
        POP CX
        POP DX
        RET
    
    SRAND_SYSTEM_TIME ENDP    
    
    WAIT_FOR_DELAY PROC
        PUSH CX
        MOV CX , DELAY
        DELAY_LOOP:
            LOOP DELAY_LOOP
        POP CX
        RET
    WAIT_FOR_DELAY ENDP
    
    UPDATE_SEED PROC
        PUSH AX
        PUSH CX
        PUSH DX
        MOV  AH, 2CH
        INT  21H
        MOV  AH, 0
        MOV  AL, DL                       ;;micro seconds
        ADD AL, SEED
        MOV CL, DH
        ROR AL, CL
        MOV SEED,AL
        POP DX
        POP CX
        POP AX
        RET
        
    UPDATE_SEED ENDP   

    RAND_FROM_0_TO_3 PROC
         
        PUSH DX
        PUSH BX
        PUSH AX

        XOR DX,DX           ; Compute randval(DX) mod 10 to get num
        MOV BX,4           ;     between 0 and 3
        MOV AL,SEED
        MOV AH,0
        DIV BX                      ; DX = modulo from division
        MOV DIRECTION , DL
        POP AX
        POP BX
        POP DX
        

        RET
    RAND_FROM_0_TO_3 ENDP 
    
>>>>>>> Stashed changes
    
    
     
        
        
        
    GENERATE_NEW_COMBINATION PROC
        PUSH CX
        PUSH BX

        MOV CX,DIR_SIZE
        LEA BX,DIRECTIONS_DEMO
        CALL WAIT_FOR_DELAY
        CALL SRAND_SYSTEM_TIME
        GENERATE_ARRAY:
            CALL WAIT_FOR_DELAY
            CALL RAND_FROM_0_TO_3
            ;CALL WAIT_FOR_DELAY
            CALL UPDATE_SEED
            PUSH CX
            MOV CL,DIRECTION
            MOV [BX] , CL
            POP CX
            INC BX
            LOOP GENERATE_ARRAY
        POP BX
        POP CX
        RET
    GENERATE_NEW_COMBINATION ENDP

   

    ; VALIDATE_COMBINATION PROC
    ;     PUSH AX
    ;     PUSH BX
    ;     PUSH CX
    ;     PUSH DX
    ;     MOV BX,OFFSET DIRECTIONS_DEMO + 1
    ;     MOV DH,N
    ;     DEC DH
    ;     MOV AH,[BX-1]
    ;     MOV AL,[BX-1]
    ;     CALL INITIALIZE_STARTING_POINT
    ;     CMP DH,0
    ;     JE FINISH_VALIDATE_COMBINATION
    ;     VALIDATE_DIRECTIONS_LOOP:
    ;         MOV AX , [BX]
    ;         MOV CX , [BX-1]
    ;         SUB AX , CX
    ;         CMP AX , 2
    ;         JE NON_VALID_COMBINATION
    ;         CMP AX , -2
    ;         JE NON_VALID_COMBINATION
    ;         INC BX
    ;         DEC DH
    ;         JNZ VALIDATE_DIRECTIONS_LOOP
    ;         CMP DH,0
    ;         JZ FINISH_VALIDATE_COMBINATION

    ;     NON_VALID_COMBINATION:
    ;         MOV COLLISION,1
    ;     FINISH_VALIDATE_COMBINATION:
    ;         POP DX
    ;         POP CX
    ;         POP BX
    ;         POP AX
    ;     RET
    ; VALIDATE_COMBINATION ENDP


    GO_UNTIL_VALID_COMBINATION PROC
        GENERATE_VALIDATE_LOOP:
            MOV COLLISION,0
            CALL GENERATE_NEW_COMBINATION
            CALL TRY_DRAW_PATH_SEGMENTS
            CMP COLLISION , 1
            JZ GENERATE_VALIDATE_LOOP
            
        RET
    GO_UNTIL_VALID_COMBINATION ENDP


;-------------------------------------------------------------------------------------------------------------;
    

    CHECK_OVERFLOW PROC
        ; SI:LEFT MOST CORNER DI : RIGHT MOST CORNER AL CURRENT DIRECTION
        PUSH TRAVERSING_ROW
        PUSH TRAVERSING_COLUMN
        PUSH CX
        CMP AL,0
        JZ CURRENT_DIRECTION_IS_LEFT
        CMP AL,1
        JZ CURRENT_DIRECTION_IS_UP
        CMP AL,2
        JZ CURRENT_DIRECTION_IS_RIGHT
        JMP CURRENT_DIRECTION_IS_DOWN
        CURRENT_DIRECTION_IS_LEFT:
            MOV CX , TRAVERSING_COLUMN
            CMP CX, SEGMENT_LENGTH+BOUNDARY_HORIZONTAL
            JL DETECTED_OVERFLOW
            MOV CX , TRAVERSING_ROW
            ADD CX , SEGMENT_WIDTH
            CMP CX , SCREEN_HEIGHT-BOUNDARY_VERTICAL
            JG DETECTED_OVERFLOW 
            JMP FINISH_CHECK_OVERFLOW

        CURRENT_DIRECTION_IS_UP:

            MOV CX,TRAVERSING_ROW
            CMP CX , SEGMENT_LENGTH+BOUNDARY_VERTICAL
            JL DETECTED_OVERFLOW
            MOV CX , TRAVERSING_COLUMN
            ADD CX , SEGMENT_WIDTH
            CMP CX , SCREEN_WIDTH-BOUNDARY_HORIZONTAL
            JG DETECTED_OVERFLOW
            JMP FINISH_CHECK_OVERFLOW

        CURRENT_DIRECTION_IS_RIGHT:
            MOV CX , TRAVERSING_COLUMN
            ADD CX , SEGMENT_LENGTH
            CMP CX , SCREEN_WIDTH-BOUNDARY_HORIZONTAL
            JG DETECTED_OVERFLOW
            MOV CX , TRAVERSING_ROW
            ADD CX , SEGMENT_WIDTH
            CMP CX , SCREEN_HEIGHT-BOUNDARY_VERTICAL
            JG DETECTED_OVERFLOW 
            JMP FINISH_CHECK_OVERFLOW

        CURRENT_DIRECTION_IS_DOWN:
            MOV CX , TRAVERSING_ROW
            ADD CX , SEGMENT_LENGTH
            CMP CX , SCREEN_HEIGHT-BOUNDARY_VERTICAL
            JG DETECTED_OVERFLOW
            MOV CX , TRAVERSING_COLUMN
            ADD CX , SEGMENT_WIDTH
            CMP CX , SCREEN_WIDTH-BOUNDARY_HORIZONTAL
            JG DETECTED_OVERFLOW
            JMP FINISH_CHECK_OVERFLOW

        DETECTED_OVERFLOW:
            MOV COLLISION,1
        FINISH_CHECK_OVERFLOW:
            POP CX
            POP TRAVERSING_COLUMN
            POP TRAVERSING_ROW
        RET
    CHECK_OVERFLOW ENDP



    
    
    
    DECREMENT_ROW PROC
        PUSH CX
        MOV CX , TRAVERSING_ROW
        DEC CX
        MOV TRAVERSING_ROW ,CX
        POP CX
        RET
    DECREMENT_ROW ENDP

    INCREMENT_ROW PROC
        PUSH CX
        MOV CX , TRAVERSING_ROW
        INC CX
        MOV TRAVERSING_ROW ,CX
        POP CX
        RET
    INCREMENT_ROW ENDP

    DECREMENT_COLUMN PROC
        PUSH CX
        MOV CX , TRAVERSING_COLUMN
        DEC CX
        MOV TRAVERSING_COLUMN ,CX
        POP CX
        RET
    DECREMENT_COLUMN ENDP

    INCREMENT_COLUMN PROC
        PUSH CX
        MOV CX , TRAVERSING_COLUMN
        INC CX
        MOV TRAVERSING_COLUMN ,CX
        POP CX
        RET
    INCREMENT_COLUMN ENDP

    COLOR_ROW PROC
        
        PUSH SI
        DRAW_ROW:
<<<<<<< Updated upstream
           MOV DL , LIGHT_GREY
=======
           MOV DL , DARK_GREY
           CMP ES:[SI] , DL
           JZ COLLIDED_DRAW_ROW
           JMP CONT_DRAW_ROW
           COLLIDED_DRAW_ROW:
           MOV COLLISION , 1
           CONT_DRAW_ROW:
>>>>>>> Stashed changes
           MOV ES:[SI] , DL
           INC SI
           CMP SI , DI
           JE FINISH_ROW
           JMP DRAW_ROW
        FINISH_ROW:
        POP SI
        RET
    COLOR_ROW ENDP 
    
    COLOR_COLUMN PROC
        
        PUSH SI
        DRAW_COLUMN:
<<<<<<< Updated upstream
           MOV DL , LIGHT_GREY
=======
           MOV DL , DARK_GREY
           CMP ES:[SI] , DL
           JZ COLLIDED_DRAW_COLUMN
           JMP CONT_DRAW_COLUMN
           COLLIDED_DRAW_COLUMN:
           MOV COLLISION , 1
           CONT_DRAW_COLUMN:
>>>>>>> Stashed changes
           MOV ES:[SI] , DL
           ADD SI , SCREEN_WIDTH
           CMP SI , DI
           JE FINISH_COLUMN
           JMP DRAW_COLUMN
            
        FINISH_COLUMN:
        POP SI 
        RET
    COLOR_COLUMN ENDP 
    
    
    DRAW_SEGMENT_UP PROC
        
        MOV CX,SEGMENT_LENGTH
        SEGMENT_UP:
            
            CALL COLOR_ROW
            SUB SI , SCREEN_WIDTH
            SUB DI , SCREEN_WIDTH
            CALL DECREMENT_ROW
            LOOP SEGMENT_UP
        
        RET
    DRAW_SEGMENT_UP ENDP 
    
    DRAW_SEGMENT_DOWN PROC
        
        MOV CX,SEGMENT_LENGTH
        SEGMENT_DOWN:
            
            CALL COLOR_ROW
            ADD SI , SCREEN_WIDTH
            ADD DI , SCREEN_WIDTH
            CALL INCREMENT_ROW
            LOOP SEGMENT_DOWN
        
        RET
    DRAW_SEGMENT_DOWN ENDP 
    
    DRAW_SEGMENT_RIGHT PROC
        
        MOV CX,SEGMENT_LENGTH
        SEGMENT_RIGHT:
            
            CALL COLOR_COLUMN
            INC SI
            INC DI
            CALL INCREMENT_COLUMN
            LOOP SEGMENT_RIGHT
        
        RET
    DRAW_SEGMENT_RIGHT ENDP 
    
    DRAW_SEGMENT_LEFT PROC
        
        MOV CX,SEGMENT_LENGTH
        SEGMENT_LEFT:
            
            CALL COLOR_COLUMN
            DEC SI
            DEC DI
            CALL DECREMENT_COLUMN
            LOOP SEGMENT_LEFT
        
        RET
    DRAW_SEGMENT_LEFT ENDP 
    
    
    
<<<<<<< Updated upstream
=======
    FILL_GAP_UP PROC
        
        MOV CX,SEGMENT_WIDTH
        GAP_UP:
            
            CALL COLOR_ROW
            SUB SI , SCREEN_WIDTH
            SUB DI , SCREEN_WIDTH
            CALL DECREMENT_ROW
            LOOP GAP_UP
        
        RET
    FILL_GAP_UP ENDP 
    
    FILL_GAP_DOWN PROC
        
        MOV CX,SEGMENT_WIDTH
        GAP_DOWN:
            
            CALL COLOR_ROW
            ADD SI , SCREEN_WIDTH
            ADD DI , SCREEN_WIDTH
            CALL INCREMENT_ROW
            LOOP GAP_DOWN
        
        RET
    FILL_GAP_DOWN ENDP 
    
    FILL_GAP_RIGHT PROC
        
        MOV CX,SEGMENT_WIDTH
        GAP_RIGHT:
            
            CALL COLOR_COLUMN
            INC SI
            INC DI
            CALL INCREMENT_COLUMN
            LOOP GAP_RIGHT
        
        RET
    FILL_GAP_RIGHT ENDP 
    
    FILL_GAP_LEFT PROC
        
        MOV CX,SEGMENT_WIDTH
        GAP_LEFT:
            
            CALL COLOR_COLUMN
            DEC SI
            DEC DI
            CALL DECREMENT_COLUMN
            LOOP GAP_LEFT
        
        RET
    FILL_GAP_LEFT ENDP 
>>>>>>> Stashed changes
    
    
    
    DRAW_SEGMENT PROC
        CMP AH , 0
        JNE FIRST_ISNT_LEFT
        JMP FAR PTR FIRST_IS_LEFT

        FIRST_ISNT_LEFT:
        CMP AH , 1
        JNE FIRST_ISNT_UP
        JMP FAR PTR FIRST_IS_UP
        
        FIRST_ISNT_UP:
        CMP AH , 2
        JNE FIRST_ISNT_RIGHT
        JMP FAR PTR FIRST_IS_RIGHT

        FIRST_ISNT_RIGHT:
        JMP FAR PTR FIRST_IS_DOWN

        FIRST_IS_LEFT:
            CMP AL , 0
            JNE FIRST_IS_LEFT_SECOND_ISNT_LEFT
            JMP FAR PTR FIRST_IS_LEFT_SECOND_IS_LEFT

            FIRST_IS_LEFT_SECOND_ISNT_LEFT:
            CMP AL , 1
            JNE FIRST_IS_LEFT_SECOND_ISNT_UP
            JMP FAR PTR FIRST_IS_LEFT_SECOND_IS_UP

            FIRST_IS_LEFT_SECOND_ISNT_UP:
            CMP AL , 2
            JNE FIRST_IS_LEFT_SECOND_ISNT_RIGHT
            JMP FAR PTR FIRST_IS_LEFT_SECOND_IS_RIGHT
            FIRST_IS_LEFT_SECOND_ISNT_RIGHT:
            JMP FAR PTR FIRST_IS_LEFT_SECOND_IS_DOWN

        FIRST_IS_UP:
            CMP AL , 0
            JNE FIRST_IS_UP_SECOND_ISNT_LEFT
            JMP FAR PTR FIRST_IS_UP_SECOND_IS_LEFT

            FIRST_IS_UP_SECOND_ISNT_LEFT:
            CMP AL , 1
            JNE FIRST_IS_UP_SECOND_ISNT_UP
            JMP FAR PTR FIRST_IS_UP_SECOND_IS_UP

            FIRST_IS_UP_SECOND_ISNT_UP:
            CMP AL , 3
            JNE FIRST_IS_UP_SECOND_ISNT_DOWN
            JMP FAR PTR FIRST_IS_UP_SECOND_IS_DOWN
            FIRST_IS_UP_SECOND_ISNT_DOWN:
            JMP FAR PTR FIRST_IS_UP_SECOND_IS_RIGHT

        FIRST_IS_RIGHT:
            CMP AL , 1
            JNE FIRST_IS_RIGHT_SECOND_ISNT_UP
            JMP FAR PTR FIRST_IS_RIGHT_SECOND_IS_UP

            FIRST_IS_RIGHT_SECOND_ISNT_UP:
            CMP AL , 2
            JNE FIRST_IS_RIGHT_SECOND_ISNT_RIGHT
            JMP FAR PTR FIRST_IS_RIGHT_SECOND_IS_RIGHT

            FIRST_IS_RIGHT_SECOND_ISNT_RIGHT:
            CMP AL , 0
            JNE FIRST_IS_RIGHT_SECOND_ISNT_LEFT
            JMP FAR PTR FIRST_IS_RIGHT_SECOND_IS_LEFT
            FIRST_IS_RIGHT_SECOND_ISNT_LEFT:
            JMP FAR PTR FIRST_IS_RIGHT_SECOND_IS_DOWN

        FIRST_IS_DOWN:
            CMP AL , 0
            JNE FIRST_IS_DOWN_SECOND_ISNT_LEFT
            JMP FAR PTR FIRST_IS_DOWN_SECOND_IS_LEFT

            FIRST_IS_DOWN_SECOND_ISNT_LEFT:
            CMP AL , 2
            JNE FIRST_IS_DOWN_SECOND_ISNT_RIGHT
            JMP FAR PTR FIRST_IS_DOWN_SECOND_IS_RIGHT
            FIRST_IS_DOWN_SECOND_ISNT_RIGHT:
            CMP AL , 1
            JNE FIRST_IS_DOWN_SECOND_ISNT_UP
            JMP FAR PTR FIRST_IS_DOWN_SECOND_IS_UP
            FIRST_IS_DOWN_SECOND_ISNT_UP:
            JMP FAR PTR FIRST_IS_DOWN_SECOND_IS_DOWN

        FIRST_IS_LEFT_SECOND_IS_LEFT:
            CALL DRAW_SEGMENT_LEFT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_LEFT_SECOND_IS_UP:             
            SUB DI , SCREEN_WIDTH                               
            MOV SI,DI                            
            ADD DI , SEGMENT_WIDTH               
            CALL DRAW_SEGMENT_UP
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_LEFT_SECOND_IS_RIGHT:
            CALL DRAW_SEGMENT_RIGHT
            JMP FAR PTR FINISH_DRAW_SEGMENT
        
        FIRST_IS_LEFT_SECOND_IS_DOWN:            
            INC SI                              
            MOV DI,SI                           
            ADD DI , SEGMENT_WIDTH              
            CALL DRAW_SEGMENT_DOWN
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_UP_SECOND_IS_LEFT:
            DEC DI               
            MOV SI,DI                        
            ;ADD SI , SCREEN_WIDTH            
            ADD DI,SEGMENT_WIDTH*SCREEN_WIDTH
            CALL DRAW_SEGMENT_LEFT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_UP_SECOND_IS_UP:
            CALL DRAW_SEGMENT_UP
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_UP_SECOND_IS_RIGHT:         
            MOV DI,SI                        
            ;ADD SI , SCREEN_WIDTH            
            ADD DI,SEGMENT_WIDTH*SCREEN_WIDTH
            CALL DRAW_SEGMENT_RIGHT
            JMP FAR PTR FINISH_DRAW_SEGMENT
        FIRST_IS_UP_SECOND_IS_DOWN:
            CALL DRAW_SEGMENT_DOWN
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_RIGHT_SECOND_IS_UP:
            SUB DI , SCREEN_WIDTH              
            MOV SI,DI                        
            SUB SI , SEGMENT_WIDTH         
            CALL DRAW_SEGMENT_UP
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_RIGHT_SECOND_IS_RIGHT:
            CALL DRAW_SEGMENT_RIGHT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_RIGHT_SECOND_IS_DOWN:        
            MOV DI,SI                        
            SUB SI , SEGMENT_WIDTH                     
            CALL DRAW_SEGMENT_DOWN
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_RIGHT_SECOND_IS_LEFT:
            CALL DRAW_SEGMENT_LEFT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_DOWN_SECOND_IS_LEFT:
<<<<<<< Updated upstream
            DEC DI                 
            MOV SI,DI                           
=======
            CALL FILL_GAP_DOWN
            DEC SI                  
            MOV DI,SI                           
>>>>>>> Stashed changes
            SUB SI , SEGMENT_WIDTH*SCREEN_WIDTH 
            CALL DRAW_SEGMENT_LEFT
            JMP FAR PTR FINISH_DRAW_SEGMENT

<<<<<<< Updated upstream
        FIRST_IS_DOWN_SECOND_IS_RIGHT:   
            MOV DI,SI                           
=======
        FIRST_IS_DOWN_SECOND_IS_UP:
            CALL DRAW_SEGMENT_UP
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_DOWN_SECOND_IS_RIGHT:
            CALL FILL_GAP_DOWN                  
            MOV SI,DI                           
>>>>>>> Stashed changes
            SUB SI , SEGMENT_WIDTH*SCREEN_WIDTH 
            CALL DRAW_SEGMENT_RIGHT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_DOWN_SECOND_IS_DOWN:
            CALL DRAW_SEGMENT_DOWN
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FINISH_DRAW_SEGMENT:
            RET
    DRAW_SEGMENT ENDP

<<<<<<< Updated upstream
    
=======
    INITIALIZE_STARTING_POINT PROC

        MOV TRAVERSING_ROW,STARTING_ROW
        MOV TRAVERSING_COLUMN,STARTING_COLUMN
        MOV SI , STARTING_ROW*SCREEN_WIDTH + STARTING_COLUMN
        MOV DI , SI
        CMP AH,0
        JZ HORIZONTAL_SETTING
        CMP AH,2
        JZ HORIZONTAL_SETTING
        JMP VERTICAL_SETTING
        HORIZONTAL_SETTING:
        ADD DI , SEGMENT_WIDTH*SCREEN_WIDTH
        JMP FINISH_INITIALIZE

        VERTICAL_SETTING:
        ADD DI , SEGMENT_WIDTH
        JMP FINISH_INITIALIZE

        FINISH_INITIALIZE:
        RET
    INITIALIZE_STARTING_POINT ENDP
    


    
    
    TRY_DRAW_PATH_SEGMENTS PROC
        MOV BX,OFFSET DIRECTIONS_DEMO + 1
        MOV DH,N
        DEC DH
        MOV AH,[BX-1]
        MOV AL,[BX-1]
        CALL INITIALIZE_STARTING_POINT
        CALL CHECK_OVERFLOW
        CMP COLLISION,1
        JZ TRY_FINISH_DRAW_PATH_SEGMENTS
        CALL DRAW_SEGMENT
        CMP DH,0
        JE TRY_FINISH_DRAW_PATH_SEGMENTS
        TRY_DIRECTIONS_LOOP:
            MOV AH,[BX-1]
            MOV AL,[BX]
            CALL CHECK_OVERFLOW
            CMP COLLISION,1
            JZ TRY_FINISH_DRAW_PATH_SEGMENTS
            CALL DRAW_SEGMENT
            INC BX
            DEC DH
            JNZ TRY_DIRECTIONS_LOOP
        TRY_FINISH_DRAW_PATH_SEGMENTS:
        CALL SET_GRAPHICS_MODE
        RET
    TRY_DRAW_PATH_SEGMENTS ENDP

>>>>>>> Stashed changes
    DRAW_PATH_SEGMENTS PROC
        MOV BX,OFFSET DIRECTIONS_DEMO + 1
        MOV DH,N
        DEC DH
<<<<<<< Updated upstream
        MOV AX,0202H
        CALL DRAW_SEGMENT
=======
        MOV AH,[BX-1]
        MOV AL,[BX-1]
        CALL INITIALIZE_STARTING_POINT
        CALL DRAW_SEGMENT
        CMP DH,0
        JE FINISH_DRAW_PATH_SEGMENTS
>>>>>>> Stashed changes
        DIRECTIONS_LOOP:
            MOV AH,[BX-1]
            MOV AL,[BX]
            CALL DRAW_SEGMENT
            INC BX
            DEC DH
<<<<<<< Updated upstream
            JNZ DIRECTIONS_LOOP  
        RET
    DRAW_PATH_SEGMENTS ENDP





=======
            JNZ DIRECTIONS_LOOP
        FINISH_DRAW_PATH_SEGMENTS:
        RET
    DRAW_PATH_SEGMENTS ENDP

>>>>>>> Stashed changes
    MAIN PROC FAR
        
        MOV AX,@DATA
        MOV DS,AX
<<<<<<< Updated upstream
        
        ;MOV AH,0
        ;INT 1AH
        
        MOV AX , 0A000H
        MOV ES , AX
        MOV AX, 19
        INT 10H
        
        MOV SI , STARTING_ROW*SCREEN_WIDTH
        MOV DI , SI
        ADD DI , SEGMENT_WIDTH*SCREEN_WIDTH
        

        CALL DRAW_PATH_SEGMENTS


=======
        MAIN_LOOP:
        CALL SET_GRAPHICS_MODE
        CALL GO_UNTIL_VALID_COMBINATION
        CALL DRAW_PATH_SEGMENTS
        MOV AH , 0
        INT 16H
        CMP AL , 01H
        JNE MAIN_LOOP
        EXIT:
>>>>>>> Stashed changes
        MOV AH, 4CH
        INT 21H
    MAIN ENDP 
    
    
        
    
    
    END MAIN