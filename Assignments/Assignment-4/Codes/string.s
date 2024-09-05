.syntax unified
.text

.global mystrlen
.global mystrcpy
.global mystrcmp

// int mystrlen(char *s)
mystrlen:
    push {r4, lr}          // Save link register and r4
    mov r1, r0             // r1 = s
    mov r0, #0             // Initialize length to 0
strlen_loop:
    ldrb r2, [r1], #1      // Load byte from s and increment pointer
    cmp r2, #0             // Compare byte with 0 (null terminator)
    beq strlen_done        // If equal, we are done
    add r0, r0, #1         // Increment length
    b strlen_loop          // Repeat loop
strlen_done:
    pop {r4, lr}           // Restore link register and r4
    bx lr                  // Return

// char *mystrcpy(char*dest, char *src)
mystrcpy:
    push {r4, lr}          // Save link register and r4
    mov r2, r0             // r2 = dest
    mov r1, r1             // r1 = src
strcpy_loop:
    ldrb r3, [r1], #1      // Load byte from src and increment src pointer
    strb r3, [r2], #1      // Store byte to dest and increment dest pointer
    cmp r3, #0             // Compare byte with 0 (null terminator)
    bne strcpy_loop        // If not equal, continue loop
    pop {r4, lr}           // Restore link register and r4
    bx lr                  // Return

// int mystrcmp(char *s1, char *s2)
mystrcmp:
    push {r4, lr}          // Save link register and r4
    mov r3, r0             // r3 = s1
    mov r2, r1             // r2 = s2
strcmp_loop:
    ldrb r4, [r3], #1      // Load byte from s1 and increment pointer
    ldrb r5, [r2], #1      // Load byte from s2 and increment pointer
    cmp r4, r5             // Compare bytes
    bne strcmp_done        // If not equal, we are done
    cmp r4, #0             // Compare byte with 0 (null terminator)
    beq strcmp_equal       // If equal and at end, strings are equal
    b strcmp_loop          // Repeat loop
strcmp_done:
    sub r0, r4, r5         // Return difference of differing bytes
    pop {r4, lr}           // Restore link register and r4
    bx lr                  // Return
strcmp_equal:
    mov r0, #0             // Return 0 if strings are equal
    pop {r4, lr}           // Restore link register and r4
    bx lr                  // Return
