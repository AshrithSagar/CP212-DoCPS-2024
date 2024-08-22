#include "printlib.h"

int myputchar(int c)
{
    int rc;
    if (myindex < BUFSIZ) // Check if the buffer is full
    {
        // Add the character to the buffer and increment the index
        mybuf[myindex++] = (char)c;

        rc = c;
    }
    else
    {
        rc = EOF; // Return EOF if the buffer is full
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
    float fractional;

    if (precision > 0)
    {
        fractional = num % 1;
        num /= 1;
    }

    // Handle the case where the number is 0 separately
    if (num == 0)
    {
        numbuf[numindex++] = '0';
    }

    while (num > 0)
    {
        int digit = num % base;
        char chardigit;
        if (digit < 10)
        {
            chardigit = digit + '0';
        }
        else
        {
            chardigit = hexdigits[digit];
        }
        numbuf[numindex++] = chardigit;
        num /= base;
    }

    // Reverse the num buffer
    int left = 0;
    int right = numindex - 1;
    while (left < right)
    {
        // Swap
        char temp = numbuf[left];
        numbuf[left] = numbuf[right];
        numbuf[right] = temp;

        left++;
        right--;
    }

    // Output
    for (int i = 0; i < numindex; i++)
    {
        rc = myputchar(numbuf[i]);
        if (rc == EOF)
        {
            return rc;
        }
    }

    if (precision > 0)
    {
        rc = myputchar('.');
        if (rc == EOF)
        {
            return rc;
        }
        char fracbuf[BUFSIZ];
        int fracindex = 0;
        while (precision > 0)
        {
            int digit = (int)(fractional * base);
            fractional -= digit;
            char chardigit;
            if (digit < 10)
            {
                chardigit = digit + '0';
            }
            else
            {
                chardigit = hexdigits[digit];
            }
            fracbuf[fracindex++] = chardigit;
            precision--;
        }
        for (int i = 0; i < fracindex; i++)
        {
            rc = myputchar(fracbuf[i]);
            if (rc == EOF)
            {
                return rc;
            }
        }
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
    rc = myputchar('0');
    if (rc == EOF)
    {
        return rc;
    }
    rc = myputchar('x');
    if (rc == EOF)
    {
        return rc;
    }
    rc = myputnum(x, 16, 0);
    return rc;
};

int myputf(float f)
{
    int rc;
    rc = myputnum(f, 10, 2);
    return rc;
};
