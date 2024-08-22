#include "printlib.h"

int main(void)
{
    myputs("Hello, World!\n");
    myputchar('A');
    myputchar('\n');
    myputd(1230);
    myputchar('\n');
    myputd(-456);
    myputchar('\n');
    myputx(0x789ABC);
    myputchar('\n');
    myputf(123.456);

    printf("%s", mybuf);
    return 0;
}
