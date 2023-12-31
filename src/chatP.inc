

StartChat PROC
       initPort
      mov rec_row, 0
      mov sender_row, 0
      mov rec_col, 39
      mov sender_col, 0

      

      ;  mov ax, 0003h
      ;   int 10h
       

C_MAIN_LOOP:
            ; Set the cursor position for sender
          
            movCur rec_row, rec_col 
          checkRecive
          JZ C_SEND

          reciveChar
          cmp al, 0dh
          jz C_NEWLINE_C

          inc rec_col

          mov ah, 02h
          mov dl, al
          int 21h

          cmp rec_col, 78
            jz C_NEWLINE_C
            BACK1:
          cmp rec_row, 25
            jz C_SCROLL_C

          jmp C_SEND

C_NEWLINE_C:
          inc rec_row
          mov rec_col, 40
          JMP BACK1
C_SCROLL_C:
          
          mov ah, 06h
          mov al, 1
          mov bh, 0
          mov ch, 0
          mov cl, 40
          mov dh, 24
          mov dl, 79
          mov bh, 07h
          int 10h

          dec rec_row
C_SEND:
        movCur sender_row, sender_col
          checkSend
          JZ C_MAIN_LOOP

          ;; Handle the key
          ChkKey
          JZ C_MAIN_LOOP
          GetKey
          ;cmp al, 0dh
          ;jmp ESCAPE
          cmp ah, 01h
          jz C_EXIT
          sendChar al
          cmp al, 0dh
          jz C_NEWLINE


            ; Print the character
            mov ah, 02h
            mov dl, al
            int 21h

            inc sender_col

            cmp sender_col, 38
            jz C_NEWLINE
C_BACK2:
            cmp sender_row, 25
            jz C_SCROLL        
         
          JMP C_MAIN_LOOP

C_NEWLINE:
          inc sender_row
          mov sender_col, 0
          JMP C_BACK2

C_SCROLL:
          ;ScrollDown 0, 0, 24, 39

          ; Color the screen red
          mov ah, 06h
          mov al, 1
          mov bh, 0
          mov ch, 0
          mov cl, 0
          mov dh, 24
          mov dl, 39
          mov bh, 07h
          int 10h
          dec sender_row
          JMP C_MAIN_LOOP
C_EXIT:
  SetVideoMode


ret 
StartChat ENDP





StartGameChat PROC
       initPort
       DrawRectangle 0,0,SCREEN_WIDTH,32,05h
       MOV rec_row, 1
       MOV sender_row, 1
      

      ;  mov ax, 0003h
      ;   int 10h
       

GC_MAIN_LOOP:
            ; Set the cursor position for sender
          
            movCur rec_row, rec_col 
          checkRecive
          JZ GC_SEND

          reciveChar
          cmp al, 0dh
          jz GC_NEWLINE_C

          inc rec_col

          mov ah, 02h
          mov dl, al
          int 21h

          cmp rec_col, 78
            jz GC_NEWLINE_C
GBACK1:
          cmp rec_row, 2
            jz GC_SCROLL_C

          jmp GC_SEND

GC_NEWLINE_C:
          inc rec_row
          mov rec_col, 40
          JMP GBACK1
GC_SCROLL_C:
          
       DrawRectangle SCREEN_WIDTH/2,0,SCREEN_WIDTH,32,05h


          dec rec_row
GC_SEND:
        movCur sender_row, sender_col
          checkSend
          JZ GC_MAIN_LOOP

          ;; Handle the key
          ChkKey
          JZ GC_MAIN_LOOP
          GetKey
          ;cmp al, 0dh
          ;jmp ESCAPE
          cmp ah, 01h
          jz GC_EXIT
          sendChar al
          cmp al, 0dh
          jz GC_NEWLINE


            ; Print the character
            mov ah, 02h
            mov dl, al
            int 21h

            inc sender_col

            cmp sender_col, 38
            jz GC_NEWLINE
GC_BACK2:
            cmp sender_row, 2
            jz GC_SCROLL        
         
          JMP GC_MAIN_LOOP

GC_NEWLINE:
          inc sender_row
          mov sender_col, 0
          JMP GC_BACK2

GC_SCROLL:
          

       DrawRectangle 0,0,SCREEN_WIDTH/2,32,05h

          
          
          dec sender_row
          JMP GC_MAIN_LOOP
GC_EXIT:
  ; SetVideoMode

       DrawRectangle 0,0,SCREEN_WIDTH,32,0

ret 
StartGameChat ENDP