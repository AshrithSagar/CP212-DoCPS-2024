#ifndef BOT_H
#define BOT_H

typedef struct {
  int M1A;
  int M1B;
  int M2A;
  int M2B;
} MotorPins;

typedef struct {
  int M1E1;
  int M1E2;
  int M2E1;
  int M2E2;
} EncoderPins;

typedef enum { FORWARD, REVERSE, LEFT, RIGHT, STILL } Direction;

typedef enum { MOTOR_FORWARD, MOTOR_REVERSE } MotorDirection;

typedef struct {
  unsigned long current;
  unsigned long previous;
  unsigned long diff;
} Timer;

typedef struct {
  int pinE1, pinE2;
  int counter;
  Timer timer;
} Encoder;

typedef struct {
  int id;
  Encoder encoder;
  MotorDirection direction;
  int speed;
} Motor;

struct StackBot {
  MotorPins motorPins;
  EncoderPins encoderPins;
  Direction state;
  Motor motorLeft, motorRight;
  void (*init)(struct StackBot *);
  void (*move)(struct StackBot *, Direction, int);
  void (*stop)(struct StackBot *);
  void (*uart_control)(struct StackBot *, int);
};
typedef struct StackBot StackBot;

StackBot *configStackBot(MotorPins motorPins, EncoderPins encoderPins);

#endif // BOT_H
