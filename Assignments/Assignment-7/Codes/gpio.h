#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1

void pinMode(int pin, int dir);
void digitalWrite(int pin, int value); // value is LOW or HIGH
int digitalRead(int pin);
