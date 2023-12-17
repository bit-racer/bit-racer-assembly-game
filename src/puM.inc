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

                  PowerUpSwitch  CAR1_POWER_UP, car1_speed, car2_speed

                  MOV            CAR1_POWER_UP, 4                       ; no power up


  CHECK_CAR_2:    
                  cmp            [byte ptr KeyList+57d], 1
                  jne            END

                  PowerUpSwitch  CAR2_POWER_UP, car2_speed, car1_speed

                  MOV            CAR2_POWER_UP, 4                       ; no power up
    
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
PowerUpSwitch MACRO CAR_POWER_UP, MY_CAR_SPEED, HIS_CAR_SPEED
                LOCAL powerup1, powerup2, powerup3, powerup4, END

                CMP   CAR_POWER_UP, 0
                JE    powerup1
                CMP   CAR_POWER_UP, 1
                JE    powerup2
                CMP   CAR_POWER_UP, 2
                JE    powerup3
                CMP   CAR_POWER_UP, 3
                JE    powerup4
                JMP   END

  powerup1:     
                MOV   MY_CAR_SPEED, 15
                JMP   END

  powerup2:     
                MOV   HIS_CAR_SPEED, 5
                JMP   END

  powerup3:     
                JMP   END

  powerup4:     
                JMP   END

  END:          
ENDM