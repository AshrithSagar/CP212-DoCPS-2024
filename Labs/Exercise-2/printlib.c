#define BUFSIZ 4096
#define EOF -1

char mybuf[BUFSIZ];
int myindex;

int myputchar(int c)
{
    int rc;
    if (myindex < BUFSIZ)
    {
        mybuf[myindex] = (char)c;
        myindex++;
        rc = c;
    }
    else
    {
        rc = EOF;
    }
    return rc;
}

int myputs(const char *s)
{
    int rc;
    while (*s != '\0')
    {
        rc = myputchar(*s);
        if (rc == EOF)
        {
            break;
        }
        s++;
    }
    return rc;
};

int myputnum(unsigned int num, int base, int precision) {

};

int myputd(int d) {

};

int myputx(int d) {

};

int myputf(float f) {

};
