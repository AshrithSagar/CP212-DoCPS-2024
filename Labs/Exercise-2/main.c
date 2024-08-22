#include "printlib.h"

// Test all the myput* functions
int main(void)
{
    // Test printing a normal string
    myputs("Hello, World!");
    myputchar('\n');

    // Test printing a single character
    myputchar('A');
    myputchar('\n');

    // Test printing the number 0
    myputd(0);
    myputchar('\n');

    // Test printing a positive decimal number
    myputd(123);
    myputchar('\n');

    // Test printing a negative decimal number
    myputd(-456);
    myputchar('\n');

    // Test printing a positive decimal number with trailing zeros
    myputd(7890);
    myputchar('\n');

    // Test printing a positive hexadecimal number, inputted in hexadecimal
    // myputx(0x789ABC);
    myputd(0xFF);
    myputchar('\n');

    // Test printing a negative hexadecimal number, inputted in hexadecimal
    myputx(-0xDEF);
    myputchar('\n');

    // Test printing a positive hexadecimal number, inputted in decimal
    myputx(127);
    myputchar('\n');

    // Test printing a negative hexadecimal number, inputted in decimal
    myputx(-1);
    myputchar('\n');

    // Test printing a positive floating point number
    myputf(123.45);
    myputchar('\n');

    // Test printing a negative floating point number
    myputf(-67.89);
    myputchar('\n');

    // Print the buffer for now. Will be replaced later
    printf("%s", mybuf);

    return 0;
}
