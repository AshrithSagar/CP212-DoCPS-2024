#include <stdarg.h>

#define BUFSIZ 1024
#define EOF (-1)

// Buffer to which the output is written to
char mybuf[BUFSIZ];
int myindex;

// Variables for unpacking formatted string
int i_val;
double f_val;

// Print a formatted string
int myprintf(const char *format, ...)
{
    int rc;
    const char *p = format;
    va_list args;
    va_start(args, format);
    while (*p != '\0')
    {
        // Check for the format specifier
        if (*p == '%')
        {
            p++;
            if (*p == '\0')
            {
                break;
            }

            // Handle the format specifiers
            switch (*p)
            {
            // char, decimal, hexadecimal, float
            case 'c':
                i_val = (char)va_arg(args, int);
                rc = myputchar(i_val);
                break;
            case 'd':
                i_val = (int)va_arg(args, int);
                rc = myputd(i_val);
                break;
            case 'x':
                i_val = (int)va_arg(args, int);
                rc = myputx(i_val);
                break;
            case 'f':
                f_val = (float)va_arg(args, double);
                rc = myputf(f_val);
                break;
            default:
                rc = EOF;
                break;
            }
        }
        else
        {
            rc = myputchar(*p); // Print the character as it is
        }
        p++;
    }
    va_end(args);
    return rc;
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
