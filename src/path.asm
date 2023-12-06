                                    .MODEL SMALL
.STACK 64

.DATA

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
   
.CODE 


     
    
    COLOR_ROW PROC
        
        PUSH SI
        DRAW_ROW:
           MOV DL , LIGHT_GREY
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
           MOV DL , LIGHT_GREY
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
            LOOP SEGMENT_UP
        
        RET
    DRAW_SEGMENT_UP ENDP 
    
    DRAW_SEGMENT_DOWN PROC
        
        MOV CX,SEGMENT_LENGTH
        SEGMENT_DOWN:
            
            CALL COLOR_ROW
            ADD SI , SCREEN_WIDTH
            ADD DI , SCREEN_WIDTH
            LOOP SEGMENT_DOWN
        
        RET
    DRAW_SEGMENT_DOWN ENDP 
    
    DRAW_SEGMENT_RIGHT PROC
        
        MOV CX,SEGMENT_LENGTH
        SEGMENT_RIGHT:
            
            CALL COLOR_COLUMN
            INC SI
            INC DI
            LOOP SEGMENT_RIGHT
        
        RET
    DRAW_SEGMENT_RIGHT ENDP 
    
    DRAW_SEGMENT_LEFT PROC
        
        MOV CX,SEGMENT_LENGTH
        SEGMENT_LEFT:
            
            CALL COLOR_COLUMN
            DEC SI
            DEC DI
            LOOP SEGMENT_LEFT
        
        RET
    DRAW_SEGMENT_LEFT ENDP 
    
    
    
    
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

        FIRST_IS_DOWN_SECOND_IS_LEFT:
            DEC DI                 
            MOV SI,DI                           
            SUB SI , SEGMENT_WIDTH*SCREEN_WIDTH 
            CALL DRAW_SEGMENT_LEFT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_DOWN_SECOND_IS_RIGHT:   
            MOV DI,SI                           
            SUB SI , SEGMENT_WIDTH*SCREEN_WIDTH 
            CALL DRAW_SEGMENT_RIGHT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_DOWN_SECOND_IS_DOWN:
            CALL DRAW_SEGMENT_DOWN
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FINISH_DRAW_SEGMENT:
            RET
    DRAW_SEGMENT ENDP

    
    DRAW_PATH_SEGMENTS PROC
        MOV BX,OFFSET DIRECTIONS_DEMO + 1
        MOV DH,N
        DEC DH
        MOV AX,0202H
        CALL DRAW_SEGMENT
        DIRECTIONS_LOOP:
            MOV AH,[BX-1]
            MOV AL,[BX]
            CALL DRAW_SEGMENT
            INC BX
            DEC DH
            JNZ DIRECTIONS_LOOP  
        RET
    DRAW_PATH_SEGMENTS ENDP





    MAIN PROC FAR
        
        MOV AX,@DATA
        MOV DS,AX
        
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


        MOV AH, 4CH
        INT 21H
    MAIN ENDP 
    
    
        
    
    
    END MAIN