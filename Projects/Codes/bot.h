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

struct StackBot {
  MotorPins motorPins;
  EncoderPins encoderPins;
  void (*init)(struct StackBot *);
  void (*forward)(struct StackBot *, int);
  void (*reverse)(struct StackBot *, int);
  void (*left)(struct StackBot *, int);
  void (*right)(struct StackBot *, int);
  void (*stop)(struct StackBot *);
};
typedef struct StackBot StackBot;

StackBot *configStackBot(MotorPins motorPins, EncoderPins encoderPins);

#endif // BOT_H
