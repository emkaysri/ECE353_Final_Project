; Filename:     hw1_ai_print_pattern.s 
; Author:       Srinidhi Emkay
; ID:			9071272901
; NetID:		emkay
; Description:  Takes input pattern (array) and
;				current moves (number) and calls
;				update_lcd by sending the direction
;				in R0. Waits 700ms, removes the arrow,
;				waits 700ms, and increments to next number
;				in array

    export hw1_ai_print_pattern
    import AI_Array
    import hw1_update_lcd
	import hw1_clear_arrow
    import hw1_wait_ms

;**********************************************
; SRAM
;**********************************************
    AREA    SRAM, READWRITE
    align

;**********************************************
; Constant Variables (FLASH) Segment
;**********************************************
    AREA    FLASH, CODE, READONLY
    align

;**********************************************
; Code (FLASH) Segment
; main assembly program
; R0 AI_Array (Input)
; R1 Moves (Input)
; R2 Loop Counter (Local)
;**********************************************
; void hw1_ai_print_pattern(uint8_t *pattern, uint16_t moves)
    PRESERVE8
hw1_ai_print_pattern   PROC
    MOV R2, #0
LOOP_START
    PUSH {R0-R2, LR}
    LDR R0, [R0, R2]
    BL hw1_update_lcd
	MOV R0, #700
	BL hw1_wait_ms
    BL hw1_clear_arrow
    BL hw1_wait_ms
    POP {R0-R2, LR}
	
    ADD R2, R2, #1
    CMP R1, R2
    BGT LOOP_START
    BX  LR
    ENDP
    align
        

    END            
