CIRCLE_AREA:
; Compute the area of a circle with radius r
; Using the formula A = pi * r^2
; pi is approximated as 22/7

; Since the calling function already saves registers R0 and R1
; Here we only need to save the other registers

; Save all the other registers into the stack frame
PUSH R2, R3, R5, R6, R7

; The radius is available in R0
; R1 is free here to use, but we will avoid touching it

; Compute the square of the radius first and store in R0
MUL R0, R0

; Compute the value of pi into R2
MOV R2, #22
MOV R3, #7
DIV R2, R3

; Compute the area of the circle which is stored in R0
MUL R0, R2
; Return value is in the register R0

; Restore the registers from the stack frame
POP R2, R3, R5, R6, R7
