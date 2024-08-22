#include "printlib.h"

int main(void)
{
    myputs("Hello, World!\n");
    myputchar('A');
    myputchar('\n');
    myputd(123);
    myputchar('\n');
    myputx(0x456ABC);
    myputchar('\n');
    myputf(123.456);

    printf("%s", mybuf);
    return 0;
}
