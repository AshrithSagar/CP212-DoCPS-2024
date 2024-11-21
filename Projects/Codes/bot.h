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

struct StackBot {
  MotorPins motorPins;
  EncoderPins encoderPins;
  Direction state;
  void (*init)(struct StackBot *);
  void (*move)(struct StackBot *, Direction, int);
  void (*stop)(struct StackBot *);
};
typedef struct StackBot StackBot;

StackBot *configStackBot(MotorPins motorPins, EncoderPins encoderPins);

#endif // BOT_H
