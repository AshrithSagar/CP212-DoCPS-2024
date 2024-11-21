#ifndef MOTOR_H
#define MOTOR_H

typedef enum { MOTOR_FORWARD, MOTOR_REVERSE } MotorDirection;

void motor_init(int M1A, int M1B, int M2A, int M2B);
void motor_on(MotorDirection dirA, int dutyA, MotorDirection dirB, int dutyB);
void motor_off(void);

#endif /* MOTOR_H */
