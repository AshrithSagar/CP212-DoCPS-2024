/* Timer utilities for the SysTick timer for ARM Cortex M4
 * Two ways to implement:
 * 1. SysTick timer: Part of ARM Cortex M4 core (Implements a 24-bit timer)
 * 2. Timer peripherals: Part of nRF52833 MCU
 */

#define IOREG(addr) (*((volatile long *)(addr)))

#define SYST_CSR IOREG(0xE000E010)
#define SYST_RVR IOREG(0xE000E014)
#define SYST_CVR IOREG(0xE000E018)

#define CLOCK 64000000UL // 64 MHz clock

void timerDelay(int ms) {
  /*
   * Delay function using the SysTick timer
   * ms: delay in milliseconds
   */

  SYST_RVR = (CLOCK / 1000) * ms;
  SYST_CVR = 0; // Any write operation to CVR clears it

  SYST_CSR = 5;
  /* SYST_CSR:
  - Bit-0: ENABLE; Enable/Disable clock;
    - (1) => Enable clock
  - Bit-1: TICKINT; Enabling interrupts;
    - (0) => No interrupts
  - Bit-2: CLKSOURCE; Internal/External clock;
    - (1) => Use internal clock (the only option in nRF52833)
  */

  while ((SYST_CSR & 0x00010000) == 0)
    ; // Wait till COUNTFLAG (Bit-16) is set
};

void timerInterruptEnable(int ms){
    // TBD
};
