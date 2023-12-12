
shownum macro
    local l1     
    local l2
     lea bx, s
     mov cx,10
     mov dx,0
     l1:
       mov dx,0
       div cx     
       add dl,30h
       mov [bx],dl
       inc bx 
       cmp ax,0
     jnz l1     
     mov [bx],'$' 
     mov cx, bx
     lea dx,s
     sub cx,dx  
     dec bx
     l2:
         mov ah,2
         mov dl,[bx]
         int 21h
         dec bx
         cmp dh,0
     loop l2      
endm shownum

endl macro 
    mov ah,02h
    mov dl,10
    int 21h 
    mov ah,02h
    mov dl,13
    int 21h
endm endl 



.MODEL SMALL
.STACK 64

.DATA

   LIGHT_GREY EQU 7
   DARK_GREY EQU 8
   SEGMENT_LENGTH EQU 30
   SEGMENT_WIDTH EQU 21
   STARTING_ROW EQU 100
   STARTING_COLUMN EQU 180
   SCREEN_WIDTH EQU 320
   SCREEN_HEIGHT EQU 200
   DIR_SIZE EQU 7
   BOUNDARY_VERTICAL EQU 10
   BOUNDARY_HORIZONTAL EQU 5
   
   TRAVERSING_ROW DW 100
   TRAVERSING_COLUMN DW 180

   COLLISION DB 0
   DIRECTION DB ?
   SEED DB ?
   DELAY DW 5000
   DIRECTIONS_DEMO DB DIR_SIZE DUP(4)

   ;DIRECTIONS_DEMO DB 1,2,3,0,0
   N DB $-DIRECTIONS_DEMO
   S DB ?
   
.CODE 



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
            CALL WAIT_FOR_DELAY
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

    PRINT_ARRAY PROC
        PUSH SI
        PUSH CX
        PUSH AX
        LEA SI , DIRECTIONS_DEMO
        MOV CL , N
        MOV CH,0

        LOOP_A:
            MOV AL , [SI]
            MOV AH,0
            PUSH CX
            shownum
            ; CALL WAIT_FOR_DELAY
            endl
            POP CX
            INC SI
            LOOP LOOP_A
        POP AX
        POP CX
        POP SI
        RET
    PRINT_ARRAY ENDP

    MAIN PROC FAR
        
        MOV AX,@DATA
        MOV DS,AX
        MOV CX , 3
        LOOP_DE7K:
        CALL GENERATE_NEW_COMBINATION
        CALL PRINT_ARRAY
        LOOP LOOP_DE7K
        

        MOV AH, 4CH
        INT 21H
    MAIN ENDP 
    
    
        
    
    
    END MAIN