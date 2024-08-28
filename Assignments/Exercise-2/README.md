# myprintf – part 1

In this exercise, we will write routines to print data in various formats.
Subsequently we will integrate these into myprintf.

At this stage, we will print the data in a character array inside memory.
Once UART is up, we will transmit these to the host and view it using a terminal.

Here are some suggestions which may be useful.
Please feel free to use these or any other resource on the internet.

## Defining functionality

We will implement a subset of many formats supported by printf.
First, let us write down which formats we want to support:

- `%c`: character
- `%s`: string
- `%d`: signed and unsigned integer in decimal format
- `%x`: unsigned integer in hexadecimal format
- `%f`: floating point number up to two decimal points

These are some basic formats that will help us in debugging; we will leave out complex ones like “`%06d`”, “`%3.2f`” etc.

## Defining interface

Next, let us define the prototypes for these functions.

- `int myputchar(int c);`

    This function prints the least significant byte of integer c as ASCII character.

    Returns the character printed or `EOF` on error.

- `int myputs(const char *s);`

    This function prints the string.

    Returns the number of characters printed or `EOF` on error.

- `int myputd(int d);`

    This function prints a signed number in decimal format.

    Returns the number of characters or `EOF` on error.

- `int myputx(int d);`

    This function prints an unsigned number in hexadecimal format.
    (For negative numbers, print 2’s complement. For example, -1 should be printed as `0xFFFFFFFF`.)

    Returns the number of characters or `EOF` on error.

- `int myputf(float f);`

    This function prints a float up to two decimal points.

    Returns the number of characters printed or `EOF` on error.

## Implementation

1. To implement `myputchar`, let us take a buffer, say 4kb in size, and write characters into the buffer using an index.
    Later, we will replace this function to transmit characters over the serial port.

    ```C
    #define BUFSIZ 4096 // also defined in stdio.h
    #define `EOF` -1 // also defined in stdio.h
    char mybuf[BUFSIZ];
    int myindex;
    int myputchar(int c) {
        int rc; // return code
        if (myindex < BUFSIZ) {
            mybuf[myindex] = (char) c;
            myindex++;
            rc = c;
        } else {
            rc = `EOF`;
        }
        return rc;
    }
    ```

2. To print a string, we can simply scan the string and print characters one-by-one using `myputchar`.

3. To print numbers, implement a common function called `myputnum` with the following interface:

    ```C
    int myputnum(unsigned int num, int base, int precision);
    Remember to send the output using myputchar.
    All the functions can use myputnum like this:
    myputd zero or positive => myputnum(num, 10, 0);
    myputd negaitive => myputchar('-'); myputnum(-num, 10, 0);
    myputx => myputnum(num, 16, 0);
    myputf => myputnum(num, 10, 2);
    ```

    You may find `myputnum`-like functions in public-domain implementation of myprintf.
    However, you may find it easier to code afresh then porting them 😊

## Deliverables

- `main.c` containing test code that tests all the functions.
- `output.txt` containing reference output that is expected when you run the main code.
- `printlib.h` containing prototypes of the interface functions.
- `printlib.c` containing implementation of all the myput* functions as mentioned above.
