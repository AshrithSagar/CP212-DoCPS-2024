#ifndef BOT_H
#define BOT_H

typedef struct StackBot {
  int motorPins[4];
  int encoderPins[4];
  void (*init)(struct StackBot *);
  void (*forward)(struct StackBot *, int);
  void (*reverse)(struct StackBot *, int);
  void (*left)(struct StackBot *, int);
  void (*right)(struct StackBot *, int);
  void (*stop)(struct StackBot *);
} StackBot;
void bot_create(StackBot *bot);

#endif // BOT_H
