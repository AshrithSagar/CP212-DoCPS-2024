#define STACK_SIZE 32 // 32 long words => 128 bytes

long stack_memory[STACK_SIZE];
int main(void);

void Reset_Handler(void) {
  // System initialisations: Clock, Memory

  // C Run time initialisations: Initialise variables in memory

  // Execution begins here
  main();

  while (1)
    ; // ~Keep looping
}

void Default_Handler(void) {
  while (1)
    ; // ~Keep looping
}

const long __Vectors[] = {
    // Core exceptions; 0-15; Defined by ARM
    // 16 entries; ARM Architecture Reference Manual

    // Initial Stack Pointer (Reset SP)
    (long)(stack_memory + STACK_SIZE),

    // Reset_Handler: Reset Program Counter (PC)
    (long)Reset_Handler,

    // 14 exceptions: Faults, OS call implementations, System tick timer
    (long)Default_Handler, (long)Default_Handler, (long)Default_Handler,
    (long)Default_Handler, (long)Default_Handler, (long)Default_Handler,
    (long)Default_Handler, (long)Default_Handler, (long)Default_Handler,
    (long)Default_Handler, (long)Default_Handler, (long)Default_Handler,
    (long)Default_Handler, (long)Default_Handler,

    // Device interrupts; 16-31;
};
