.MODEL SMALL
.STACK 64

.DATA

   LIGHT_GREY EQU 7
   DARK_GREY EQU 8
   SEGMENT_LENGTH EQU 25
   SEGMENT_WIDTH EQU 20
   SCREEN_WIDTH EQU 320
   DIRECTIONS DB 2,1,2,3,2,2,1,1,0,1,2,2,2,2,3,0,3

   
.CODE 


    
    
    COLOR_ROW PROC
        
        PUSH SI
        DRAW_ROW:
           MOV BL , LIGHT_GREY
           MOV ES:[SI] , BL
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
           MOV BL , LIGHT_GREY
           MOV ES:[SI] , BL
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
    
    
    
    FILL_GAP_UP PROC
        
        MOV CX,SEGMENT_WIDTH
        GAP_UP:
            
            CALL COLOR_ROW
            SUB SI , SCREEN_WIDTH
            SUB DI , SCREEN_WIDTH
            LOOP GAP_UP
        
        RET
    FILL_GAP_UP ENDP 
    
    FILL_GAP_DOWN PROC
        
        MOV CX,SEGMENT_WIDTH
        GAP_DOWN:
            
            CALL COLOR_ROW
            ADD SI , SCREEN_WIDTH
            ADD DI , SCREEN_WIDTH
            LOOP GAP_DOWN
        
        RET
    FILL_GAP_DOWN ENDP 
    
    FILL_GAP_RIGHT PROC
        
        MOV CX,SEGMENT_WIDTH
        GAP_RIGHT:
            
            CALL COLOR_COLUMN
            INC SI
            INC DI
            LOOP GAP_RIGHT
        
        RET
    FILL_GAP_RIGHT ENDP 
    
    FILL_GAP_LEFT PROC
        
        MOV CX,SEGMENT_WIDTH
        GAP_LEFT:
            
            CALL COLOR_COLUMN
            DEC SI
            DEC DI
            LOOP GAP_LEFT
        
        RET
    FILL_GAP_LEFT ENDP 
    
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
            CALL FILL_GAP_LEFT                   
            INC SI                               
            MOV DI,SI                            
            ADD DI , SEGMENT_WIDTH               
            CALL DRAW_SEGMENT_UP
            JMP FAR PTR FINISH_DRAW_SEGMENT
        
        FIRST_IS_LEFT_SECOND_IS_DOWN:
            CALL FILL_GAP_LEFT                  
            INC DI                              
            MOV SI,DI                           
            ADD DI , SEGMENT_WIDTH              
            CALL DRAW_SEGMENT_DOWN
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_UP_SECOND_IS_LEFT:
            CALL FILL_GAP_UP                 
            MOV DI,SI                        
            ADD SI , SCREEN_WIDTH            
            ADD DI,SEGMENT_WIDTH*SCREEN_WIDTH
            CALL DRAW_SEGMENT_LEFT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_UP_SECOND_IS_UP:
            CALL DRAW_SEGMENT_UP
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_UP_SECOND_IS_RIGHT:
            CALL FILL_GAP_UP                 
            MOV SI,DI                        
            ADD SI , SCREEN_WIDTH            
            ADD DI,SEGMENT_WIDTH*SCREEN_WIDTH
            CALL DRAW_SEGMENT_RIGHT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_RIGHT_SECOND_IS_UP:
            CALL FILL_GAP_RIGHT              
            MOV DI,SI                        
            SUB SI , SEGMENT_WIDTH           
            CALL DRAW_SEGMENT_UP
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_RIGHT_SECOND_IS_RIGHT:
            CALL DRAW_SEGMENT_RIGHT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_RIGHT_SECOND_IS_DOWN:
            CALL FILL_GAP_RIGHT              
            MOV SI,DI                        
            SUB SI , SEGMENT_WIDTH                     
            CALL DRAW_SEGMENT_DOWN
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_DOWN_SECOND_IS_LEFT:
            CALL FILL_GAP_DOWN                  
            MOV DI,SI                           
            SUB SI , SEGMENT_WIDTH*SCREEN_WIDTH 
            CALL DRAW_SEGMENT_LEFT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_DOWN_SECOND_IS_RIGHT:
            CALL FILL_GAP_DOWN                  
            MOV SI,DI                           
            SUB SI , SEGMENT_WIDTH*SCREEN_WIDTH 
            CALL DRAW_SEGMENT_RIGHT
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FIRST_IS_DOWN_SECOND_IS_DOWN:
            CALL DRAW_SEGMENT_DOWN
            JMP FAR PTR FINISH_DRAW_SEGMENT

        FINISH_DRAW_SEGMENT:
            RET
    DRAW_SEGMENT ENDP

    MAIN PROC FAR
        
        MOV AX,@DATA
        MOV DS,AX
        
        ;MOV AH,0
        ;INT 1AH
        
        MOV AX , 0A000H
        MOV ES , AX
        MOV AX, 19
        INT 10H
        
        MOV SI , 140*SCREEN_WIDTH
        MOV DI , SI
        ADD DI , SEGMENT_WIDTH*SCREEN_WIDTH

;---------------------------------------------------------------------------;        
        MOV AX,0202H
        CALL DRAW_SEGMENT

    ;   CALL DRAW_SEGMENT_RIGHT        
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        MOV AX,0201H
        CALL DRAW_SEGMENT

        ; ;WHAT TODO IF HE MOVED UP AFTER RIGHT
        ;     CALL FILL_GAP_RIGHT              ;
        ;     MOV DI,SI                        ;
        ;     SUB SI , SEGMENT_WIDTH           ;
        ; ;------------------------------------;
        
        ; CALL DRAW_SEGMENT_UP
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        MOV AX,0102H
        CALL DRAW_SEGMENT

        ; ;WHAT TODO IF HE MOVED RIGHT AFTER UP
        ;     CALL FILL_GAP_UP                 ;
        ;     MOV SI,DI                        ;
        ;     ADD SI , SCREEN_WIDTH            ;
        ;     ADD DI,SEGMENT_WIDTH*SCREEN_WIDTH;
        ; ;------------------------------------;

        ; CALL DRAW_SEGMENT_RIGHT
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        MOV AX,0203H
        CALL DRAW_SEGMENT

    ;    ;WHAT TODO IF HE MOVED DOWN AFTER RIGHT
    ;         CALL FILL_GAP_RIGHT              ;
    ;         MOV SI,DI                        ;
    ;         SUB SI , SEGMENT_WIDTH           ;           
    ;    ;-------------------------------------;

    ;    CALL DRAW_SEGMENT_DOWN
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        MOV AX , 0302H
        CALL DRAW_SEGMENT
    ;    ;  WHAT TODO IF HE MOVED RIGHT AFTER DOWN
    ;         CALL FILL_GAP_DOWN                  ;
    ;         MOV SI,DI                           ;
    ;         SUB SI , SEGMENT_WIDTH*SCREEN_WIDTH ;
    ;    ;----------------------------------------;

    ;     CALL DRAW_SEGMENT_RIGHT
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        MOV AX,0202H
        CALL DRAW_SEGMENT

    ;     CALL DRAW_SEGMENT_RIGHT
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        MOV AX , 0201H
        CALL DRAW_SEGMENT

    ;    ;WHAT TODO IF HE MOVED UP AFTER RIGHT
    ;         CALL FILL_GAP_RIGHT              ;
    ;         MOV DI,SI                        ;
    ;         SUB SI , SEGMENT_WIDTH           ;
    ;     ;------------------------------------;

    ;     CALL DRAW_SEGMENT_UP
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        MOV AX , 0101H
        CALL DRAW_SEGMENT

    ;   CALL DRAW_SEGMENT_UP
;---------------------------------------------------------------------------;


;---------------------------------------------------------------------------;

        MOV AX , 0100H
        CALL DRAW_SEGMENT

        ; ;WHAT TODO IF HE MOVED LEFT AFTER UP
        ;     CALL FILL_GAP_UP                 ;
        ;     MOV DI,SI                        ;
        ;     ADD SI , SCREEN_WIDTH            ;
        ;     ADD DI,SEGMENT_WIDTH*SCREEN_WIDTH;
        ; ;------------------------------------;
        ; CALL DRAW_SEGMENT_LEFT
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        
        MOV AX,0001H
        CALL DRAW_SEGMENT
        
        ; ;WHAT TODO IF HE MOVED UP AFTER LEFT
        ;     CALL FILL_GAP_LEFT               ;
        ;     INC SI                           ;
        ;     MOV DI,SI                        ;
        ;     ADD DI , SEGMENT_WIDTH           ;
        ; ;------------------------------------;
        
        ; CALL DRAW_SEGMENT_UP             
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;

        MOV AX , 0102H 
        CALL DRAW_SEGMENT

        ; ;WHAT TODO IF HE MOVED RIGHT AFTER UP
        ;     CALL FILL_GAP_UP                 ;
        ;     MOV SI,DI                        ;
        ;     ADD SI , SCREEN_WIDTH            ;
        ;     ADD DI,SEGMENT_WIDTH*SCREEN_WIDTH;
        ; ;------------------------------------;

        ; CALL DRAW_SEGMENT_RIGHT

;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        MOV AX,0202H
        CALL DRAW_SEGMENT
        CALL DRAW_SEGMENT
        CALL DRAW_SEGMENT

        ; CALL DRAW_SEGMENT_RIGHT
        ; CALL DRAW_SEGMENT_RIGHT
        ; CALL DRAW_SEGMENT_RIGHT
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        
        MOV AX,0203H
        CALL DRAW_SEGMENT

        ; ;WHAT TODO IF HE MOVED DOWN AFTER RIGHT
        ;     CALL FILL_GAP_RIGHT              ;
        ;     MOV SI,DI                        ;
        ;     SUB SI , SEGMENT_WIDTH           ;
        ; ;------------------------------------;

            
        ; CALL DRAW_SEGMENT_DOWN          
;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;

        MOV AX,0300H
        CALL DRAW_SEGMENT

        ; ;  WHAT TODO IF HE MOVED LEFT AFTER DOWN
        ;     CALL FILL_GAP_DOWN                  ;
        ;     MOV DI,SI                           ;
        ;     SUB SI , SEGMENT_WIDTH*SCREEN_WIDTH ;
        ; ;---------------------------------------;

        ; CALL DRAW_SEGMENT_LEFT              

;---------------------------------------------------------------------------;

;---------------------------------------------------------------------------;
        
        MOV AX,0003H
        CALL DRAW_SEGMENT

        ; ;  WHAT TODO IF HE MOVED DOWN AFTER LEFT
        ;     CALL FILL_GAP_LEFT                  ;
        ;     INC DI                              ;
        ;     MOV SI,DI                           ;
        ;     ADD DI , SEGMENT_WIDTH              ;
        ; ;---------------------------------------;

        ; CALL DRAW_SEGMENT_DOWN              

;---------------------------------------------------------------------------;

        MOV AH, 4CH
        INT 21H
    MAIN ENDP 
    
    
        
    
    
    END MAIN