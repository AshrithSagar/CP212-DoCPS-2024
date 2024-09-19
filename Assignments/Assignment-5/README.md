# Minimal system

In this exercise, you will implement a standalone system with your own startup code.

1. Create project without CMSIS Core and Device.

2. Create a `start.c` file as discussed in the lab session.

3. Add two files supplied with this assignment:
   - `linear.c` : Implements integer $y = mx + c$, where $m$ and $c$ are 32-bit constants.
   - `main.c`: Calls `linear()` with diﬀerent values of $x$.

4. Fill in the following table.
   Specify the type to be one of:
   function, read-only data, initialized data, uninitialized data, local data.

    | symbol           | type      | section | address |
    |------------------|-----------|---------|---------|
    | main             | function  | .text   | ???     |
    | i                |           |         |         |
    | linear           |           |         |         |
    | x_array          |           |         |         |
    | y_array          |           |         |         |
    | m                |           |         |         |
    | c                |           |         |         |
    | (vector table)   |           |         |         |
    | (reset handler)  |           |         |         |
    | (default handler)|           |         |         |
