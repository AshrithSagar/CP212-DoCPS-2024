.syntax unified
.text
.global mystrlen


; Return length of input string
mystrlen:

	; Read string
	MOV R1, #0				; Initialise length
	LDR R2, [R0]			; Read string head
	CMP R2, #0				; Check Null character
	BEQ _mystrlen__exit		; Exit reading loop

	; Update
	ADDS R1, #1				; Increment length
	ADDS R0, #1				; Increment string pointer

_mystrlen__exit:
	MOV R0, R1				; Return value in R0
	BX LR					; Return
