# myprintf – part 2

In this exercise, we will write the `myprintf` function that processes its arguments, and depending on the arguments, calls the appropriate `myput*` function to print.

```c
int myprintf(const char *format, ...);
```

It should support `%c`, `%d`, `%f` and `%x` formats.

## Examples

```c
myprintf("Hello, world!\n");
myprintf("n = %d, x = %x\n", n, x);
myprintf("ASCII code for %c is %d\n", 'A', 'A');
myprintf("Area of the circle: r = %f, a = %f\n", r, a);
```

## varargs

`myprintf` is a variable-argument function, which accepts a format string and a number of arguments according to the format string.

Attached file ['varargs.pdf'](varargs.md) contains a note with a sample program on how to implement varargs functions, which could be a good starting point for `myprintf`.

> Please note: The objectives of this exercise are (1) to understand various data formats and (2) write our own `printf` function so that it will be helpful in debugging later.
So it’s okay if you don’t understand how varargs functions work now – until we take a deeper look at the compilation process and how argument passing works.

## Deliverables

- `main.c` containing test code that tests `printf` with different data formats.

- `printlib.c` containing implementation printf and of all the `put*` functions as mentioned above.

- `printlib.h` containing prototypes of the interface functions.

- A screenshot of the output as shown below:

    ![Memory window](TeX/figures/images/memory-window.png)

Please don’t attach all the files in the project directory – only the source code and output.

## Questions

1. Convert to hex: 100, 200, 400, 800

2. Convert to hex: -100, -200, -400, -800

3. Set a variable float x = 1.0.
   View it as an unsigned long in the memory window.
   What value do you see?
   Explain it theoretically.

4. Repeat question 3 for -1.0.

5. What does FPU do?
