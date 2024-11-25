// From BSP
#define INPUT 0
#define OUTPUT 1
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);

#define LOW 0
#define HIGH 1

#define LED_PIN 8

#define CLOCK 64000000UL // 64 MHz clock

#define IOREG(addr) (*((volatile long *)(addr)))

#define SYST_CSR IOREG(0xE000E010)
#define SYST_RVR IOREG(0xE000E014)
#define SYST_CVR IOREG(0xE000E018)

void timerDelay(int ms) {
  /*
   * Delay function using the SysTick timer
   * ms: delay in milliseconds
   * Uses the internal timer to implement a naive delay
   */

  while (ms > 0) {
    ms--;

    SYST_RVR = (CLOCK / 1000);
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

    SYST_CSR = 0; // Turn OFF
  }
};

int main() {
  // Set the brightness level to a value between 0 and 10
  int brightnessLevel = 5;

  // Calculate the ON time and OFF time based on brightness level
  // Using percentage values
  int onTime = (brightnessLevel * 100) / 10;
  int offTime = 100 - onTime;

  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);

  while (1) {
    // Turn ON the LED
    digitalWrite(LED_PIN, HIGH);

    // Delay for the ON time
    timerDelay(onTime);

    // Turn OFF the LED
    digitalWrite(LED_PIN, LOW);

    // Delay for the OFF time
    timerDelay(offTime);
  }
}
