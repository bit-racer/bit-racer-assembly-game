; Activiate Power Up
ActivatePowerUp MACRO
                  LOCAL          END, CHECK_CAR_2

                  ClearPowerUp

  ; Diaplay Power Up for car 1
                  MOV            currentColumn, 68
                  MOV            currentRow, 29
                  CALL           moveCursor
                  DisplayPowerUp CAR1_POWER_UP
  
  ; Diaplay Power Up for car 2
                  MOV            currentColumn, 0
                  MOV            currentRow, 29
                  CALL           moveCursor
                  DisplayPowerUp CAR2_POWER_UP

  ; Check if car 1 presses enter to activate its powerup
                  cmp            [byte ptr KeyList+28d], 1
                  jne            CHECK_CAR_2

                  PowerUpSwitch  CAR1_POWER_UP, car1_speed, car2_speed, car1_X_Offset, car1_Y_Offset, CAR1_HAVE_SHIELD, car1_active_pu, car1_pu_count

                  MOV            CAR1_POWER_UP, 4                                                                                                      ; no power up


  CHECK_CAR_2:    
                  cmp            [byte ptr KeyList+57d], 1
                  jne            END

                  PowerUpSwitch  CAR2_POWER_UP, car2_speed, car1_speed, car2_X_Offset, car2_Y_Offset, CAR2_HAVE_SHIELD, car2_active_pu, car2_pu_count

                  MOV            CAR2_POWER_UP, 4                                                                                                      ; no power up
    
  END:            
  
ENDM

; Dispaly Power Up
DisplayPowerUp MACRO CAR_POWER_UP
                  LOCAL DisplayPowerUp1, DisplayPowerUp2, DisplayPowerUp3, DisplayPowerUp4, NoPowerUp, END


                  CMP   CAR_POWER_UP, 4
                  JE    NoPowerUp
                  CMP   CAR_POWER_UP, 3
                  JE    DisplayPowerUp4
                  CMP   CAR_POWER_UP, 2
                  JE    DisplayPowerUp3
                  CMP   CAR_POWER_UP, 1
                  JE    DisplayPowerUp2
                  CMP   CAR_POWER_UP, 0
                  JE    DisplayPowerUp1
                  JMP   END

  DisplayPowerUp1:
                  MOV   DX, offset str_pu1
                  CALL  printmsg
                  JMP   END
  
  DisplayPowerUp2:
                  MOV   DX, offset str_pu2
                  CALL  printmsg
                  JMP   END
  
  DisplayPowerUp3:
                  MOV   DX, offset str_pu3
                  CALL  printmsg
                  JMP   END
  
  DisplayPowerUp4:
                  MOV   DX, offset str_pu4
                  CALL  printmsg
                  JMP   END
  
  NoPowerUp:      
                  MOV   DX, offset str_no_pu
                  CALL  printmsg
                  JMP   END
  
  END:            
ENDM

ClearPowerUp MACRO
               MOV  currentColumn, 0
               MOV  currentRow, 29
               CALL moveCursor
               MOV  DX, offset str_clear
               CALL printmsg
               MOV  currentColumn, 68
               MOV  currentRow, 29
               CALL moveCursor
               MOV  DX, offset str_clear
               CALL printmsg
ENDM

; PowerUp switch activator
PowerUpSwitch MACRO CAR_POWER_UP, MY_CAR_SPEED, HIS_CAR_SPEED, HIS_X, HIS_Y, MY_SHIELD, O_PU, O_PUC
                LOCAL        powerup1, powerup2, powerup3, powerup4, END

  ; reset shield powerup
  ; MOV          MY_SHIELD, 0

                CMP          CAR_POWER_UP, 0
                JE           powerup1
                CMP          CAR_POWER_UP, 1
                JE           powerup2
                CMP          CAR_POWER_UP, 2
                JE           powerup3
                CMP          CAR_POWER_UP, 3
                JE           powerup4
                JMP          END

  ; Speed me up
  powerup1:     
                MOV          O_PU, 0
                MOV          O_PUC, 5
                MOV          MY_CAR_SPEED, 15
                JMP          END

  ; Slow my opponent down
  powerup2:     
                MOV          O_PU, 1
                MOV          O_PUC, 5
                MOV          HIS_CAR_SPEED, 5
                JMP          END

  ; Spawn obstacle at my opponent
  powerup3:     
                
                SUB          HIS_X, 20
                DrawObstacle HIS_X, HIS_Y, OBSTACLE_WIDTH, OBSTACLE_HEIGHT
                ADD          HIS_X, 20
                JMP          END

  ; allow me to go throgh obstacles
  powerup4:     
                MOV          O_PU, 3
                MOV          O_PUC, 5
                MOV          MY_SHIELD, 1

                JMP          END

  END:          
ENDM

DecPUCount MACRO
             LOCAL            NEXT, ENDF, REMOVE, CONT
             cmp              car1_pu_count, 0
             JE               NEXT
             DEC              car1_pu_count
             JMP              CONT
  NEXT:      
             RevPowerUpSwitch CAR1_POWER_UP, car1_speed, car2_speed, car1_X_Offset, car1_Y_Offset, CAR1_HAVE_SHIELD, car1_active_pu, car1_pu_count
  CONT:      
             cmp              car2_pu_count, 0
             je               REMOVE
             DEC              car2_pu_count
             JMP              ENDF
  REMOVE:    
             RevPowerUpSwitch CAR2_POWER_UP, car2_speed, car1_speed, car2_X_Offset, car2_Y_Offset, CAR2_HAVE_SHIELD, car2_active_pu, car2_pu_count
  ENDF:      
ENDM



; PowerUp switch activator
RevPowerUpSwitch MACRO CAR_POWER_UP, MY_CAR_SPEED, HIS_CAR_SPEED, HIS_X, HIS_Y, MY_SHIELD, O_PU, O_PUC
                   LOCAL powerup1, powerup2, powerup3, powerup4, END

  ; reset shield powerup
  ; MOV          MY_SHIELD, 0

                   CMP   O_PU, 0
                   JE    powerup1
                   CMP   O_PU, 1
                   JE    powerup2
                   CMP   O_PU, 2
                   JE    powerup3
                   CMP   O_PU, 3
                   JE    powerup4
                   JMP   END

  ; Speed me up
  powerup1:        
                   MOV   O_PU, 4
                   MOV   O_PUC, 0
                   MOV   MY_CAR_SPEED, 10
                   JMP   END

  ; Slow my opponent down
  powerup2:        
                   MOV   O_PU, 4
                   MOV   O_PUC, 0
                   MOV   HIS_CAR_SPEED, 10
                   JMP   END

  ; Spawn obstacle at my opponent
  powerup3:        
                   JMP   END

  ; allow me to go throgh obstacles
  powerup4:        
                   MOV   O_PU, 4
                   MOV   O_PUC, 0
                   MOV   MY_SHIELD, 0

                   JMP   END

  END:             
ENDM
