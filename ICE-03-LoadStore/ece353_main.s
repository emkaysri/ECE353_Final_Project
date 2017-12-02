; Filename:     main.s 
; Author:       ece353 staff 
; Description:  

    export __main

;**********************************************
; Add Symbolic Constants here
;**********************************************
BYTE      EQU 1
HALF_WORD EQU 2
WORD      EQU 4

;**********************************************
; SRAM
;**********************************************
    AREA    SRAM, READWRITE	
ARRAY1 SPACE 8*HALF_WORD
ARRAY2 SPACE 8*HALF_WORD
    align
        
;**********************************************
; Constant Variables (FLASH) Segment
;**********************************************
    AREA    FLASH, CODE, READONLY
LTABLE	DCW 0
		DCW 1
		DCW 8
		DCW 27
		DCW 64
		DCW 125
		DCW 216
		DCW 343
    align

;**********************************************
; Code (FLASH) Segment
; main assembly program
;**********************************************
__main   PROC
	ADR	R0, LTABLE
	LDR	R1, =(ARRAY1)
	LDR	R2, =(ARRAY2)
	
	LDRH R10, [R0, #6]
	
	LDR    R3, [R0, #0]         ; Load  4 Bytes
    STR    R3, [R1, #0]         ; Store 4 Bytes
	
	LDR    R3, [R0, #0]         ; Load  4 Bytes
    STR    R3, [R2, #0]         ; Store 4 Bytes
    
    ; DO NOT MODIFY ANTHING BELOW THIS LINE!!!	
        
INFINITE_LOOP
    B INFINITE_LOOP
    
    ENDP
    align
        

    END            