#include "printlib.h"

// Test all the myput* functions
int main(void)
{
    // Test printing a normal string
    myprintf("s", "Hello, World!");
    myputchar('\n');

    // Test printing a single character
    myprintf("c", 'A');
    myputchar('\n');

    // Test printing the number 0
    myprintf("d", 0);
    myputchar('\n');

    // Test printing a positive decimal number
    myprintf("d", 123);
    myputchar('\n');

    // Test printing a negative decimal number
    myprintf("d", -456);
    myputchar('\n');

    // Test printing a positive decimal number with trailing zeros
    myprintf("d", 7890);
    myputchar('\n');

    // Test printing a positive hexadecimal number, inputted in hexadecimal
    // myputx(0x789ABC);
    myprintf("d", 0xFF);
    myputchar('\n');

    // Test printing a negative hexadecimal number, inputted in hexadecimal
    myprintf("x", -0xDEF);
    myputchar('\n');

    // Test printing a positive hexadecimal number, inputted in decimal
    myprintf("x", 127);
    myputchar('\n');

    // Test printing a negative hexadecimal number, inputted in decimal
    myprintf("x", -1);
    myputchar('\n');

    // Test printing a positive floating point number
    myprintf("f", 123.45);
    myputchar('\n');

    // Test printing a negative floating point number
    myprintf("f", -67.89);
    myputchar('\n');

    return 0;
}
