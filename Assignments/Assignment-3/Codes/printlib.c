#include <stdarg.h>
#include "printlib.h"

// Variables for unpacking formatted string
char c_val;
int i_val;
float f_val;
char *p_val;

// Print a formatted string
int myprintf(const char *format, ...)
{
    char *p = format;
    va_list args;
    va_start(args, format);
    while (*p != '\0')
    {
        switch (*p)
        {
        // char, string, decimal, hexadecimal, float
        case 'c':
            c_val = (char)va_arg(args, int);
            myputchar(c_val);
            break;
        case 's': // char array
            c_val = (char *)va_arg(args, int *);
            myputs(c_val);
            break;
        case 'd':
            i_val = (int)va_arg(args, int);
            myputd(i_val);
            break;
        case 'x':
            i_val = (int)va_arg(args, int);
            myputx(i_val);
            break;
        case 'f':
            f_val = (float)va_arg(args, double);
            myputf(f_val);
            break;
        default:
            break;
        }
        p++;
    }
    va_end(args);
}

// Print a character
int myputchar(int c)
{
    int rc;
    if (myindex < BUFSIZ) // Check if the buffer is full
    {
        // Add the character to the buffer and increment the index
        mybuf[myindex++] = (char)c;

        rc = c; // Return the character printed
    }
    else
    {
        rc = EOF; // Return EOF if the buffer is full
    }
    return rc;
}

// Print a string (character array)
int myputs(const char *s)
{
    int rc;
    int length = 0;
    while (*s != '\0')
    {
        rc = myputchar(*s);
        if (rc == EOF)
            break;
        s++;
        length++;
    }
    return length; // Return the number of characters printed
};

int myputnum(unsigned int num, int base, int precision)
{
    int rc;
    char numbuf[BUFSIZ]; // Buffer to store the number
    int numindex = 0;    // Index to the buffer `numbuf`
    float fractional;

    if (precision > 0)
    {
        // Revert back to float
        float f = *(float *)&num;

        // Handle negative floats
        if (f < 0)
        {
            rc = myputchar('-');
            if (rc == EOF)
                return rc;
            f = -f;
        }

        // Extract the fractional part
        fractional = f - (unsigned int)f;
        float shift = 0.5; // Rounding off
        for (unsigned int i = 0; i < precision; i++)
        {
            shift /= base;
            fractional *= base;
        }
        fractional += shift;
        num = (unsigned int)f;
    }

    // Handle the case where the number is 0 separately
    if (num == 0)
        numbuf[numindex++] = '0';

    // Base conversion
    while (num > 0)
    {
        int offset;
        int digit = num % base;
        offset = (digit < 10) ? '0' : 'A' - 10; // Handle char digit
        digit = digit + offset;
        numbuf[numindex++] = (char)digit;
        num /= base;
    }

    // Output
    while (numindex > 0)
    {
        rc = myputchar(numbuf[--numindex]);
        if (rc == EOF)
            return rc;
    }

    // Handle floating point precision
    if (precision > 0)
    {
        rc = myputchar('.');
        if (rc == EOF)
            return rc;

        // Call `myputnum` for the converted fractional part with precision 0
        myputnum((unsigned int)fractional, base, 0);
    }
    return rc;
};

// Print a signed integer
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

// Print a hexadecimal number.
// Input number is converted to hexadecimal and printed, if necessary.
// If number is negative, internally it represented in it's 2's complement form,
// which can be accessed by type casting to unsigned int.
int myputx(int x)
{
    int rc;
    rc = myputchar('0');
    if (rc == EOF)
        return rc;
    rc = myputchar('x');
    if (rc == EOF)
        return rc;
    rc = myputnum(x, 16, 0);
    return rc;
};

// Print a floating-point number up to 2 decimal places
int myputf(float f)
{
    int rc;
    unsigned int uint_f = *(unsigned int *)&f;
    rc = myputnum(uint_f, 10, 2);
    return rc;
}
