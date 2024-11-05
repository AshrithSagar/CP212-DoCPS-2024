# Shell

In this exercise, you will implement a command-line shell.

It should accept the following command:

`help`: list all the commands

`display bbbbb bbbbb bbbbb bbbbb bbbbb`: Display a picture with 5 rows, each row specifies the bits 0 or 1 indicating LED Off or On.

`up`:
`down`:
`left`:
`right`:
Rotate the picture (scroll 5 times) in the specified direction.

You may find the following link useful:
<https://chatgpt.com/share/6725929d-56c8-8013-88e5-dd6e7e3c636c>

## Note

The program was compiled using Segger Embedded Studio.
The video shows a plus sign displayed at the centre, that is scrolled up, down, left, and right, accordingly based on the input from the serial port.
The motion was interpreted as scrolling (in the sense of a circular shift) based on the description.
