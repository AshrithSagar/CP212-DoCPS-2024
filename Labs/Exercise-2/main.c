#include <printlib.h>

int main(void)
{
    myputs("Hello, World!\n");
    myputchar('A');
    myputchar('\n');
    myputd(123);
    myputchar('\n');
    myputx(0x123);
    myputchar('\n');
    myputf(123.456);

    return 0;
}
