moveTrackUp proc 

             mtu_up:
             mov cx,[track_Y_Offset]
             sub cx,[track_speed]
             cmp cx, [track_Y_Offset]
             jb  mtu_contup
             jmp mtu_borderUp
             mtu_contup:  
             MOV DIR,0
             DRAW_TRACK_CONSTRAINT [track_X_Offset],[track_Y_Offset],[track_speed],SEGMENT_SIZE,SEGMENT_SIZE
             cmp cx,1
             jne mtu_passUP 
             jmp mtu_up_end
             mtu_passUP:
             mov Where,1
             MoveTrack TRACK_IMG,[track_X_Offset],[track_Y_Offset],[track_Y_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[track_speed],[track_width_prev],[track_height_prev]
             jmp mtu_up_end
             mtu_borderUp:
           mtu_up_end:    
             ret
endp


  
moveTrackDown PROC
            mtd_D:
            mov      cx,[track_Y_Offset]
            add      cx, SEGMENT_SIZE
            add      cx, [track_speed]
            cmp      cx,SCREEN_HEIGHT
            jb       mtd_Dcont
            jmp      mtd_borderD
            mtd_Dcont:
             MOV DIR,1
            DRAW_TRACK_CONSTRAINT [track_X_Offset],[track_Y_Offset],[track_speed],SEGMENT_SIZE,SEGMENT_SIZE
            cmp cx,1
            jne mtd_passD
            jmp mtd_D_end
            mtd_passD:
            mov Where,0
            MoveTrack TRACK_IMG,[track_X_Offset],[track_Y_Offset],[track_Y_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[track_speed],[track_width_prev],[track_height_prev]
            jmp mtd_D_end
            mtd_borderD:

  mtd_D_end:     
             ret
             endp
moveTrackLeft PROC 

            mtl_L:
            mov cx,[track_X_Offset]
            sub cx,[track_speed]
            cmp cx,[track_X_Offset]
            jb  mtl_Lcont
            jmp mtl_borderL
            mtl_Lcont:
             MOV DIR,2
            DRAW_TRACK_CONSTRAINT [track_X_Offset],[track_Y_Offset],[track_speed],SEGMENT_SIZE,SEGMENT_SIZE
            cmp cx,1
            jne mtl_passL1
            jmp mtl_L_end
            mtl_passL1:
            mov Where,1
            MoveTrack TRACK_IMG,[track_X_Offset],[track_Y_Offset],[track_X_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[track_speed],[track_width_prev],[track_height_prev]
            jmp mtl_L_end
            mtl_borderL:

            mtl_L_end:     
            ret
            endp
            

moveTrackRight PROC

             mtr_R:
             mov      cx,[track_X_Offset]
             add      cx,[track_speed]
             add      cx,SEGMENT_SIZE
             cmp      cx,SCREEN_WIDTH
             jb       mtr_Rcont
             jmp mtr_borderR
             jmp mtr_R_end
             mtr_Rcont:
              MOV DIR,3
             DRAW_TRACK_CONSTRAINT [track_X_Offset],[track_Y_Offset],[track_speed],SEGMENT_SIZE,SEGMENT_SIZE
             cmp cx,1
             jne mtr_passR1 
             jmp mtr_R_end
             mtr_passR1:
             mov Where,0
             MoveTrack TRACK_IMG,[track_X_Offset],[track_Y_Offset],[track_X_Offset],SEGMENT_SIZE,SEGMENT_SIZE,[track_speed],[track_width_prev],[track_height_prev]
             jmp mtr_R_end
             mtr_borderR:
  mtr_R_end:     
             ret
             endp
