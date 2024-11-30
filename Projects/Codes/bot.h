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

typedef struct {
  int btnA;
  int btnB;
} ButtonPins;

#define numStates 5
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

typedef struct StackBot {
  MotorPins motorPins;
  EncoderPins encoderPins;
  ButtonPins buttonPins;
  Direction state;
  Motor motorLeft, motorRight;
  int speed;
  void (*init)(struct StackBot *);
  void (*move)(struct StackBot *, Direction, int);
  void (*stop)(struct StackBot *);
  void (*uart_control)(struct StackBot *, int);
} StackBot;

StackBot *configStackBot(MotorPins motorPins, EncoderPins encoderPins,
                         ButtonPins buttonPins);
void bot_init(StackBot *bot);
void bot_move(StackBot *bot, Direction direction, int speed);
void bot_stop(StackBot *bot);
void bot_uart_control(StackBot *bot, int speed);
void bot_radio_control(StackBot *bot, int speed);
void bot_button_control(StackBot *bot, int speed);

#endif // BOT_H
