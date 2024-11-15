#include "encoder.h"

int pinM1E1, pinM1E2, pinM2E1, pinM2E2;

void encoder_init(int M1E1, int M1E2, int M2E1, int M2E2) {
  pinM1E1 = M1E1;
  pinM1E2 = M1E2;
  pinM2E1 = M2E1;
  pinM2E2 = M2E2;

  pinMode(M1E1, INPUT);
  pinMode(M1E2, INPUT);
  pinMode(M2E1, INPUT);
  pinMode(M2E2, INPUT);

  uart_init();
}

void handle_edge(int *counter, int *lastState, int currentState) {
  if (*lastState == LOW && currentState == HIGH) {
    (*counter)++; // Rising edge
    myprintf("Counter: %d\n", *counter);
  } else if (*lastState == HIGH && currentState == LOW) {
    (*counter)++; // Falling edge
    myprintf("Counter: %d\n", *counter);
  }
  *lastState = currentState;
}

void encoder_counter(void) {
  static int counter = 0;
  static int prevStateM1 = HIGH;
  static int prevStateM2 = HIGH;

  int val_M1E1 = digitalRead(pinM1E1);
  int val_M2E1 = digitalRead(pinM2E1);

  handle_edge(&counter, &prevStateM1, val_M1E1);
  handle_edge(&counter, &prevStateM2, val_M2E1);
}
