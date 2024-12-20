.syntax unified
.text
.global mystrlen
.global mystrcpy
.global mystrcmp


mystrlen:
// Return length of input string
	MOV R1, #0				// Initialise length

_mystrlen__loop:
	// Read string
	LDRB R2, [R0]			// Read string head
	CMP R2, #0				// Check Null character
	BEQ _mystrlen__exit		// Exit reading loop

	// Update
	ADD R1, R1, #1			// Increment length
	ADD R0, R0, #1			// Increment string pointer

	B _mystrlen__loop		// Continue string parsing

_mystrlen__exit:
	MOV R0, R1				// Return value in R0
	BX LR					// Return


mystrcpy:
// Copy a source string to a destination
	MOV R3, R0				// Save destination

_mystrcpy_loop:
	// Copy string head
	LDRB R2, [R1]			// Read source string head
	STRB R2, [R0]			// Copy to destination

	// Continue?
	CMP R2, #0				// Check Null character
	BEQ _mystrcpy__exit	// Exit reading loop

	// Increment string pointers
	ADD R1, R1, #1
	ADD R0, R0, #1

	B _mystrcpy_loop		// Continue string copying

_mystrcpy__exit:
	MOV R0, R3				// Return value in R0
	BX LR					// Return


mystrcmp:
/* Compare two strings.
Return 0 if strings are equal, else return the difference
in characters at their first point of difference */
	// Read strings
	LDRB R2, [R0]			// Read string1 head
	LDRB R3, [R1]			// Read string2 head

	// Compare
	CMP R2, R3
	BNE _mystrcmp__neq

	// Check Null character
	CMP R2, #0
	BEQ _mystrcmp__eq

	// Increment string pointers
	ADD R0, R0, #1
	ADD R1, R1, #1

	B mystrcmp		// Continue string parsing

_mystrcmp__eq:				// Identical strings
	MOV R0, #0				// Return 0
	BX LR					// Return

_mystrcmp__neq:
// Compute string difference at first non-matching character
	SUBS R0, R2, R3
	BX LR					// Return
