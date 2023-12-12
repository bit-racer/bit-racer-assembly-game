;---------------------------------------------------------------------------------------------------------------------------
; Author: Amir Anwar
; Date: 2023-12-09
; Draw Procedures
;---------------------------------------------------------------------------------------------------------------------------

; ============================================================================================================================
;  DrawImage procedure
;  Draws an image to the screen
;
; Pre-condition:  SI points to the image to draw
;                  MOV SI, offest image
;                  CALL DrawImage
; INPUT PARAMETERS:
;  *  IMAGE_OFFSET_X - X offset to draw the image
;  * IMAGE_OFFSET_Y - Y offset to draw the image
;  * IMAGE_SIZE_X - X size of the image
;  * IMAGE_SIZE_Y - Y size of the image
;  * REVERSE - 0 = normal, 1 = reverse
;  * ERASE - 0 = normal, 1 = erase
;  * RECCOLOR - color to draw the image (Erase Color)
;
; To set this parameters, use SetDrawImageParams MACRO 
;  SetDrawImageParams IMAGE_OFFSET_X, IMAGE_OFFSET_Y, IMAGE_SIZE_X, IMAGE_SIZE_Y, ERASE_COLOR, REVERSE, ERASE
; NOTE: MAY be turned into a prcedure with parameters
; ============================================================================================================================
DrawImage PROC
     ; initialize the parameters
                           MOV     CX, IMAGE_SIZE_X          ; X size of the image
                           CMP     REVERSE, 0                ; 0 = normal, 1 = reverse
                           JZ      DI_NO_REVERSE

     ; reverse the X size of the image
                           MOV     CX, 0
     DI_NO_REVERSE:        
                           PUSH    CX                        ; save the X size of the image
                           MOV     DX, IMAGE_SIZE_Y          ; Y size of the image
                           MOV     AH, 0ch                   ; Draw Pixel Command
    
     DI_DRAW:              
                           MOV     BL, [SI]                  ; use color from array color for testing
                           AND     BL, BL                    ; check if the color is 0
                           JZ      DI_CONTINUE                   ; if the color is 0, then skip the drawing
                           ADD     CX, IMAGE_OFFSET_X        ; add the X offset
                           ADD     DX, IMAGE_OFFSET_Y        ; add the Y offset
                           MOV     AL, [SI]                  ; use color from array color for testing

                           CMP     ERASE, 0                  ; 0 = normal, 1 = erase
                           JZ      DI_DRAW_PX                ; if the color is not 0, then draw the pixel

                           MOV     AL, RECOLOR               ; use color from array color for testing
     DI_DRAW_PX:                                             ; draw the pixel
                           INT     10h                       ; draw the pixel
                           SUB     CX, IMAGE_OFFSET_X        ; subtract the X offset
                           SUB     DX, IMAGE_OFFSET_Y        ; subtract the Y offset
     DI_CONTINUE:                                            ; continue the drawing
                           INC     SI                        ; increment the image pointer
                           CMP     REVERSE, 1                ; 0 = normal, 1 = reverse
                           JZ      DI_REV_DRAW
                           DEC     CX                        ; decrement the X offset
                           JMP     DI_CONTINUE_DRAW_LOOP
     DI_REV_DRAW:                                            ; reverse the X offset
                           INC     CX
                           CMP     CX, IMAGE_SIZE_X          ; check if we can draw current X and Y and escape the Y iteration
     DI_CONTINUE_DRAW_LOOP:                                  ; continue the drawing loop
                           JNZ     DI_DRAW                   ; if loop iteration in Y direction, then X should start over so that we sweep the grid
                           POP     CX                        ; restore the X size of the image
                           PUSH    CX                        ; if loop iteration in Y direction, then X should start over so that we sweep the grid
                           DEC     DX                        ; decrement the Y offset
                           JZ      DI_FINISH                 ; both X and Y reached 0 so finish drawing
                           JMP     DI_DRAW
     DI_FINISH:                                              ; finish drawing
                           POP     CX                        ; restore the X size of the image
                           RET

DrawImage ENDP


;============================================================================================================================
; DrawImageE procedure
; Same as DrawImage but draws from the extra segment
; ============================================================================================================================
DrawImageE PROC
     ; initialize the parameters
                           MOV     CX, IMAGE_SIZE_X          ; X size of the image
                           CMP     REVERSE, 0                ; 0 = normal, 1 = reverse
                           JZ      DIE_NO_REVERSE

     ; reverse the X size of the image
                           MOV     CX, 0
     DIE_NO_REVERSE:        
                           PUSH    CX                        ; save the X size of the image
                           MOV     DX, IMAGE_SIZE_Y          ; Y size of the image
                           MOV     AH, 0ch                   ; Draw Pixel Command
    
     DIE_DRAW:              
                           MOV     BL, ES:[SI]                  ; use color from array color for testing
                           AND     BL, BL                    ; check if the color is 0
                           JZ      DIE_CONTINUE                   ; if the color is 0, then skip the drawing
                           ADD     CX, IMAGE_OFFSET_X        ; add the X offset
                           ADD     DX, IMAGE_OFFSET_Y        ; add the Y offset
                           MOV     AL, ES:[SI]                  ; use color from array color for testing

                           CMP     ERASE, 0                  ; 0 = normal, 1 = erase
                           JZ      DIE_DRAW_PX                ; if the color is not 0, then draw the pixel

                           MOV     AL, RECOLOR               ; use color from array color for testing
     DIE_DRAW_PX:                                             ; draw the pixel
                           INT     10h                       ; draw the pixel
                           SUB     CX, IMAGE_OFFSET_X        ; subtract the X offset
                           SUB     DX, IMAGE_OFFSET_Y        ; subtract the Y offset
     DIE_CONTINUE:                                            ; continue the drawing
                           INC     SI                        ; increment the image pointer
                           CMP     REVERSE, 1                ; 0 = normal, 1 = reverse
                           JZ      DIE_REV_DRAW
                           DEC     CX                        ; decrement the X offset
                           JMP     DIE_CONTINUE_DRAW_LOOP
     DIE_REV_DRAW:                                            ; reverse the X offset
                           INC     CX
                           CMP     CX, IMAGE_SIZE_X          ; check if we can draw current X and Y and escape the Y iteration
     DIE_CONTINUE_DRAW_LOOP:                                  ; continue the drawing loop
                           JNZ     DIE_DRAW                   ; if loop iteration in Y direction, then X should start over so that we sweep the grid
                           POP     CX                        ; restore the X size of the image
                           PUSH    CX                        ; if loop iteration in Y direction, then X should start over so that we sweep the grid
                           DEC     DX                        ; decrement the Y offset
                           JZ      DIE_FINISH                 ; both X and Y reached 0 so finish drawing
                           JMP     DIE_DRAW
     DIE_FINISH:                                              ; finish drawing
                           POP     CX                        ; restore the X size of the image
                           RET

DrawImageE ENDP

; ============================================================================================================================
; Draw Makrer
; Draws a marker to the screen at the correct position by index
; actulay erase first then draw
; INPUT PARAMETERS:
;  * curCar
; ============================================================================================================================
DrawMarker PROC FAR
               ;; Erase Prev Markers
               SetDrawImageParams 205, 345, car_marker_width, car_marker_height, BG_COLOR, 0, 1
               MOV                SI, offset img_car_marker
               CALL              DrawImageE
               SetDrawImageParams 268, 345, car_marker_width, car_marker_height, BG_COLOR, 0, 1
               MOV                SI, offset img_car_marker
               CALL              DrawImageE
               SetDrawImageParams 330, 345, car_marker_width, car_marker_height, BG_COLOR, 0, 1
               MOV                SI, offset img_car_marker
               CALL              DrawImageE
               SetDrawImageParams 390, 345, car_marker_width, car_marker_height, BG_COLOR, 0, 1
               MOV                SI, offset img_car_marker
               CALL              DrawImageE

               CMP curCar, 0
               JZ  DrawMarker1
               CMP curCar, 1
               JZ  DrawMarker2
               CMP curCar, 2
               JZ  DrawMarker3
               CMP curCar, 3
               JZ  DrawMarker4
               JMP DONE

               DrawMarker1:
                    SetDrawImageParams 205, 345, car_marker_width, car_marker_height, 0, 0, 0
                    MOV                SI, offset img_car_marker
                    CALL              DrawImageE

               JMP DONE

               DrawMarker2:
                    SetDrawImageParams 268, 345, car_marker_width, car_marker_height, 0, 0, 0
                    MOV                SI, offset img_car_marker
                    CALL              DrawImageE
               JMP DONE

               DrawMarker3:
                    SetDrawImageParams 330, 345, car_marker_width, car_marker_height, 0, 0, 0
                    MOV                SI, offset img_car_marker
                    CALL              DrawImageE
               JMP DONE


               DrawMarker4:
                    SetDrawImageParams 390, 345, car_marker_width, car_marker_height, 0, 0, 0
                    MOV                SI, offset img_car_marker
                    CALL              DrawImageE
               JMP DONE

               DONE:

               RET 
DrawMarker ENDP