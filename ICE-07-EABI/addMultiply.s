; Filename:	 addMultiply.s 
; Author:	   ece353 staff 
; Description:  

	export addMultiply

;**********************************************
; SRAM
;**********************************************
	AREA	SRAM, READWRITE
	align
	
;**********************************************
; Constant Variables (FLASH) Segment
;**********************************************
	AREA	FLASH, CODE, READONLY
	align


;**********************************************
; Four arrays of 8-bit signed numbers are 
; passed via the first four paramters.
; The 5th paramter indicates the length of the
; arrays. For each entry in the array, the
; following operation takes place.
;
; Array3[i] = (Array0[i] + Array1[i]) * Array2[i]
;
; Parameter 0	   Array Address 0
; Parameter 1	   Array Address 1
; Parameter 2	   Array Address 2
; Parameter 3	   Array Address 3
; Parameter 4	   Array Size 
;
; Returns
;   if ALL parameters are valid, return 0
;   else return -1.
;
;  An address is valid if it is non zero
;  The size is valid if it is greater than zero
;**********************************************
addMultiply PROC
	
	; Validate Parameters
	POP R4
	CMP R0, #0
	BEQ INVALID
	CMP R1, #0
	BEQ INVALID
	CMP R2, #0
	BEQ INVALID
	CMP R3, #0
	BEQ INVALID
	CMP R4, #0
	BEQ INVALID
	; Save required registers
	PUSH {R5, R6}
	; For each index in the arrays, compute  
	; Array3[i] = (Array0[i] + Array1[i]) * Array2[i]
	
	MOV	R5, #0          
        	
START_FOR
	CMP	R5, R4   	
	BGE	END_FOR
	ADD	R6, [R0, R5], [R1, R5]
	MUL	R6, R6, [R2, R5]
	MOV	[R3, R5], R6
	ADD	 R5, R5, #1                  
	B  	START_FOR
 
END_FOR
	; Restore registers saved to the stack
	POP {R5, R6}
	; Return from the loop
	B VAILD
INVALID
	R0, #-1
VALID
	ENDP


	
	align
	

	END		
