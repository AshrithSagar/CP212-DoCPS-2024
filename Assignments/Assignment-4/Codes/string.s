.syntax unified
.text
.global mystrlen
.global mystrcpy


mystrlen:
; Return length of input string

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


mystrcopy:
; Copy a source string to a destination
	MOV R3, R0				; Save destination

	; Copy string head
	LDR R2, [R1]			; Read source string head
	STR R2, [R0]			; Copy to destination

	; Continue?
	CMP R2, #0				; Check Null character
	BEQ _mystrcopy__exit	; Exit reading loop

	; Increment string pointers
	ADDS R1, #1
	ADDS R0, #1

_mystrcopy__exit:
	MOV R0, R3				; Return value in R0
	BX LR					; Return
