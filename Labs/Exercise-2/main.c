#include "printlib.h"

int main(void)
{
    // Test all the myput* functions
    myputs("Hello, World!\n");
    myputchar('A');
    myputchar('\n');
    myputd(0);
    myputchar('\n');
    myputd(123);
    myputchar('\n');
    myputd(-456);
    myputchar('\n');
    myputx(0x789ABC);
    myputchar('\n');
    myputx(127);
    myputchar('\n');
    myputx(-1);
    myputchar('\n');
    myputf(123.45);
    myputchar('\n');

    // Print the buffer for now. Will be replaced later
    printf("%s", mybuf);
    return 0;
}
