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

int myputs(const char *s) {

};

int myputd(int d) {

};

int myputx(int d) {

};

int myputf(float f) {

};
