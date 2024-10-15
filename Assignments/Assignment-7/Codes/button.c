/* Push buttons driver */
#include "button.h"

void buttonInit(void) {
  /* Initialize the button pins as INPUT */

  pinMode(BTN_A, INPUT);
  pinMode(BTN_B, INPUT);

  return;
}
