#ifndef ENCODER_H
#define ENCODER_H

void encoder_init(int M1E1, int M1E2, int M2E1, int M2E2);
float encoder_speed(int pin);
void encoder_update(int event);

#endif // ENCODER_H
