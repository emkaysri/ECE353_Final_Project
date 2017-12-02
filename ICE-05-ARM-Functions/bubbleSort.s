export bubbleSort
        
    AREA    FLASH, CODE, READONLY
    ALIGN
        

;******************************************************************************
; Description
;     Given the address in R7, it will read the unsigned byte at R7 and R7 + 1.
;     If [R7] > [R7 + 1], swap the values
;
;     Modify only registers R8 or greater.
;
; Parameters
;   R7 - Array Address
;
; Returns
;   Nothing
;******************************************************************************
swap_values PROC
     ;---------------------------------------
     ; START ADD CODE
     ;---------------------------------------
     
     CMP R7, [R7+1]
     MOVGT R8, R7
	 MOVGT R7, [R7+1]
     MOVGT [R7+1] , R8
	 
	 BX LR
     
     ;---------------------------------------
     ; END ADD CODE
     ;---------------------------------------
    ENDP


    
;******************************************************************************
; Description
;   Uses Bubble Sort to sort an array of unsigned 8-bit numbers.
;
;   Modify only registers R0-R7
;
; Parameters
;   R0 - Array Address
;   R1 - Array Size
;
; Returns
;   Nothing
;******************************************************************************
bubble_sort PROC

    ; Save registers
     PUSH   {R0-R12, LR}
     
     ;---------------------------------------
     ; START ADD CODE
     ;---------------------------------------
	 MOV R2, R1
	 SUB R2, R2, 1
	 
     START_FOR
		CMP R2, #0
		BLE END_FOR
		
		MOV R3, #0
		START_FOR2
			CMP R3, R2
			BGE END_FOR2
			
			LDR R7, [R3]
			
			BL swap_values
		
			ADD R3, R3, #1
			B START_FOR2	 
		END_FOR2
		
		SUB R2, R2, #1
		B START_FOR	 
     END_FOR
     
     ; NOTE: The return from the function is already
     ; provided below
     
     ;---------------------------------------
     ; END ADD CODE
     ;---------------------------------------
     
    
    ; Restore Registers
    POP     {R0-R12, LR}
    
    ; Return from the function
    BX      LR
    
    ENDP
         
    END     

