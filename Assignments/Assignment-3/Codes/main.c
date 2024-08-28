#include "printlib.h"

// Test all the myput* functions
int main(void)
{
    // Test printing a single character
    myprintf("%c", 'A');
    myprintf("%c", '\n');

    // Test printing the number 0
    myprintf("%d", 0);
    myprintf("%c", '\n');

    // Test printing a positive decimal number
    myprintf("%d", 123);
    myprintf("%c", '\n');

    // Test printing a negative decimal number
    myprintf("%d", -456);
    myprintf("%c", '\n');

    // Test printing a positive decimal number with trailing zeros
    myprintf("%d", 7890);
    myprintf("%c", '\n');

    // Test printing a positive hexadecimal number, inputted in hexadecimal
    // myputx(0x789ABC);
    myprintf("%d", 0xFF);
    myprintf("%c", '\n');

    // Test printing a negative hexadecimal number, inputted in hexadecimal
    myprintf("%x", -0xDEF);
    myprintf("%c", '\n');

    // Test printing a positive hexadecimal number, inputted in decimal
    myprintf("%x", 127);
    myprintf("%c", '\n');

    // Test printing a negative hexadecimal number, inputted in decimal
    myprintf("%x", -1);
    myprintf("%c", '\n');

    // Test printing a positive floating point number
    myprintf("%f", 123.45);
    myprintf("%c", '\n');

    // Test printing a negative floating point number
    myprintf("%f", -67.89);
    myprintf("%c", '\n');

    // Print the buffer for now. Will be replaced later
    printf("%s", mybuf);

    return 0;
}
