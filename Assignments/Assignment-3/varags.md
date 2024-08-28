# Using variable arguments (varargs) in C

C compiler provides a set of macros for using variable number of arguments.
These are defined in the header file `<stdarg.h>`.

## Steps to use varargs

1. Include the `<stdarg.h>` header.

2. Use `...` (three dots) in the function definition / declaration to indicate variable arguments.

3. Within the calling function:

   - Define a va_list type variable.
   - Initalize it using va_start.
    va_start takes two arguments: the va_list type variable defined in the previous step, and the last named argument, in our case, type_string.
   - Retrieve each argument using va_arg according to its type specified in the format string.
   - Clean up with va_end.

## Example

```c
#include <stdarg.h>
void printNumbers(char *type_string, ...);
int main() {
printNumbers("fcfd", 3.14, '@', 77.0, 99); return 0;
}
char c_val;
int i_val;
float f_val;
char *p_val;
void printNumbers(char *type_string, ...) { char *p = type_string;
va_list args;
va_start(args, type_string); while (*p != '\0')
{
switch (*p) {
// float, char, float, int
case 'c': c_val = (char) va_arg(args, int); break; case 'd': i_val = (int) va_arg(args, int); break;
case 'f': f_val = (float) va_arg(args, double); break; default: break;
}
p++; }
    va_end(args);
}
```

Please note that while passing variable arguments, `char` is promoted to `int`, and `float` is promoted to `double`.
So, when you extract the variables, you only need to extract `int`s and `double`s.
