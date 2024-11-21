#include "gpio.h"
#include "motor.h"
#include "printlib.h"
#include "timer32.h"
#include "uart.h"

int M1A = 3;
int M1B = 2;
int M2A = 4;
int M2B = 31;
int M1E1 = 28;
int M1E2 = 14;
int M2E1 = 37;
int M2E2 = 11;

void setup() {
  uart_init();

  pinMode(M1A, OUTPUT, PULL_NONE);
  pinMode(M1B, OUTPUT, PULL_NONE);
  pinMode(M2A, OUTPUT, PULL_NONE);
  pinMode(M2B, OUTPUT, PULL_NONE);
  motor_init(M1A, M1B, M2A, M2B);

  pinMode(M1E1, INPUT, PULLDOWN);
  pinMode(M1E2, INPUT, PULLDOWN);
  digitalInterruptEnable(M1E1, GPIO_RISINGEDGE, 0);
  digitalInterruptEnable(M2E1, GPIO_RISINGEDGE, 1);

  timer32_init();

  myprintf("Bot initialized\n");
}

void loop() {
  while (1)
    ;
}
