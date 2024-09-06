.syntax unified
.text
.global mystrlen
.global mystrcpy
.global mystrcmp


mystrlen:
; Return length of input string

	; Read string
	MOV R1, #0				; Initialise length
	LDR R2, [R0]			; Read string head
	CMP R2, #0				; Check Null character
	BEQ _mystrlen__exit		; Exit reading loop

	; Update
	ADDS R1, R1, #1			; Increment length
	ADDS R0, R0, #1			; Increment string pointer

_mystrlen__exit:
	MOV R0, R1				; Return value in R0
	BX LR					; Return


mystrcopy:
; Copy a source string to a destination
	MOV R3, R0				; Save destination

_mystrcopy_loop:
	; Copy string head
	LDR R2, [R1]			; Read source string head
	STR R2, [R0]			; Copy to destination

	; Continue?
	CMP R2, #0				; Check Null character
	BEQ _mystrcopy__exit	; Exit reading loop

	; Increment string pointers
	ADDS R1, R1, #1
	ADDS R0, R0, #1

	B _mystrcopy_loop		; Continue string copying

_mystrcopy__exit:
	MOV R0, R3				; Return value in R0
	BX LR					; Return


mystrcmp:
/* Compare two strings.
Return 0 if strings are equal, else return the difference
in characters at their first point of difference */

	MOV R4, #0				; Result

_mystrcmp_loop:
	; Read strings
	LDR R2, [R0]			; Read string1 head
	LDR R3, [R1]			; Read string2 head

	; Compare
	CMP R2, R3
	BNE _mystrcmp__exit

	; Check Null character
	CMP R2, #0
	BEQ _mystrcmp__str1
	CMP R3, #0
	BEQ _mystrcmp__str2

	; Increment string pointers
	ADDS R0, R0, #1
	ADDS R1, R1, #1

	B _mystrcmp_loop		; Continue string parsing

_mystrcmp__str1:
	MOV R4, R3				; Copy

_mystrcmp__str2:
	MOV R4, R2				; Copy

_mystrcmp__exit:			; Exit reading loop
	BEQ _mystrcmp__return

_mystrcmp__diff:
; Compute string difference at first non-matching character
	SUBS R4, R3, R2

_mystrcmp__return:
	MOV R0, R4				; Return value in R0
	BX LR					; Return
