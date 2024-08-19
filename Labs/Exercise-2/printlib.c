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

int myputnum(unsigned int num, int base, int precision)
{
    int rc;
    char numbuf[BUFSIZ];
    char hexdigits[] = "0123456789ABCDEF";
    int numindex = 0;
    if (num == 0) {
        numbuf[numindex++] = '0';
    } else {
        while (num > 0) {
            int digit = num % base;
            char chardigit;
            if (digit < 10) {
                chardigit = digit + '0';
            } else {
                chardigit = hexdigits[digit];
            }
            numbuf[numindex++] = chardigit;
            num /= base;
        }
    }
    int left = 0;
    int right = numindex - 1;
    while (left < right)
    {
        char temp = numbuf[left];
        numbuf[left] = numbuf[right];
        numbuf[right] = temp;
        left++;
        right--;
    }
    for (int i = 0; i < numindex; i++) {
        rc = myputchar(numbuf[i]);
        if (rc == EOF) {
            return rc;
        }
    }
    if (precision > 0)
    {
        rc = myputchar('.');
        if (rc == EOF) {
            return rc;
        }
        // ...
    }
    return rc;
};

int myputd(int d)
{
    int rc;
    if (d < 0)
    {
        rc = myputchar('-');
        d = -d;
    }
    rc = myputnum(d, 10, 0);
    return rc;
};

int myputx(int x)
{
    int rc;
    rc = myputnum(x, 16, 0);
    return rc;
};

int myputf(float f)
{
    int rc;
    rc = myputnum(f, 10, 2);
    return rc;
};
