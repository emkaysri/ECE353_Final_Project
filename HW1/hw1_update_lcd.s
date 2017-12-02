; Filename:     hw1_ai_update_lcd.s 
; Author:       Srinidhi Emkay
; ID:			9071272901
; NetID:		emkay
; Description:  Takes input of {0x01,0x02,0x04,0x08} 
;				= {UP, DOWN, LEFT, RIGHT} and calls 
;				the respective draw function
    export hw1_update_lcd
    import hw1_draw_up_arrow
    import hw1_draw_down_arrow
    import hw1_draw_left_arrow
    import hw1_draw_right_arrow
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
; Input
; R0 Move to display
;	{0x01,0x02,0x04,0x08} = {UP, DOWN, LEFT, RIGHT}
;**********************************************
; void hw1_update_lcd(uint8_t buttons)
    PRESERVE8
hw1_update_lcd   PROC
    PUSH {LR}
    TST R0, #0x01
	PUSH {R0}
    BLNE hw1_draw_up_arrow
	POP {R0}
	
    TST R0, #0x02
	PUSH {R0}
    BLNE hw1_draw_down_arrow
	POP {R0}
	
    TST R0, #0x04
	PUSH {R0}
    BLNE hw1_draw_left_arrow
	POP {R0}
	
    TST R0, #0x08
    BLNE hw1_draw_right_arrow
END_CASE
    POP {LR}
    BX  LR
    ENDP
    align

    END            
