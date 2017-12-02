; Filename:     hw1.s 
; Author:       Srinidhi Emkay
; ID:			9071272901
; NetID:		emkay
; Description:  Main file creates AI_Array, loops
;				through it adding one to each iteration,
;				and waits 500ms after each right round
;				Keeps arrow displayed while right button is pressed
    export hw1
    export AI_Array
    export Button_Value
    import hw1_ai_print_pattern
    import hw1_wait_for_start
    import hw1_game_over
    import hw1_simon_clears
    import hw1_simon_says
    import hw1_ai_init_pattern
    import hw1_wait_ms
	import hw1_update_lcd
	import hw1_clear_arrow
    

    
;**********************************************
; SRAM
;**********************************************
    AREA    SRAM, READWRITE
AI_Array SPACE 1024
Button_Value SPACE 1
    align

;**********************************************
; Constant Variables (FLASH) Segment
;**********************************************
    AREA    FLASH, CODE, READONLY
    align

;**********************************************
; Code (FLASH) Segment
; main assembly program
; Registers
; R0 - AI_Array
; R1 - Total Moves Counter
; R2 - Button_Value/User Button Press
; R3 - AI_Array[R4] Correct Value
; R4 - User Loop Counter
;**********************************************
; void hw1(void)
    PRESERVE8
hw1   PROC

WAIT_START
	BL hw1_wait_for_start
	LDR R2, =(Button_Value)
	LDR R2, [R2]
	CMP R2, #0x01	
	BNE WAIT_START ; Make user only Up is pressed
    
	LDR R0, =(AI_Array)
    MOV R1, #1024 ; Moves
	MOV R2, #1	; Seed Value
	PUSH {R0}
    BL hw1_ai_init_pattern
	POP {R0}
    MOV R1, #1
    
    
TURN_START
	PUSH {R0-R2}
; Display Simon says
    BL hw1_simon_says
	POP {R0-R2}
; Display AI_Array[0] to AI_Array[R4] on LCD
    BL hw1_ai_print_pattern
	PUSH {R0-R2}
; Remove Simon says
    BL hw1_simon_clears
	POP {R0-R2}
    MOV R4, #0
	
CHECK_USER
; wait for user input
	LDR R2, =(Button_Value)
	LDR R2, [R2]
	CMP R2, #0
    BEQ CHECK_USER ; Loop Until a button is pressed
	
    LDR R3, [R0, R4]
	AND R3, R3, #0xF
    CMP R2, R3
    BNE END_GAME ; Wrong button is pressed end game
	PUSH {R0-R3}
	MOV R0, R3
	BL hw1_update_lcd
	POP {R0-R3}
	
BUTTON_PRESSED
	LDR R2, =(Button_Value)
	LDR R2, [R2]
	CMP R2, #0
    BNE BUTTON_PRESSED ; Keep Arrow showing till button is unpressed
	
	PUSH {R0-R3}
	BL hw1_clear_arrow
	POP {R0-R3}

    ADD R4, R4, #1
	CMP R1, R4
	BGT CHECK_USER ; Loop to check all user's input
	

; Entire Sequence is correct
    ADD R1, R1, #1
    PUSH {R0-R3}
    MOV R0, #500
    BL hw1_wait_ms
    POP {R0-R3}
    B TURN_START
	
END_GAME
	BL hw1_game_over
    ENDP
	
    align

    END