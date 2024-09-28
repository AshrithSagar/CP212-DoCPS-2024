# Matrix display

In this exercise, you will draw a picture on the 5x5 LED display.

## Learning objectives

1. What are peripheral registers?
2. How to implement peripheral APIs by programming peripheral registers?
3. How to implement a display driver using peripheral APIs?

Please note that drivers for the larger displays can be very diﬀerent and a lot more complex due to the screen size and levels of colors supported.

## Program structure

The program is structured in three layers:

1. Hardware Abstraction Layer (HAL) that abstracts the GPIO port. I   I have used an abstracKon similar to that of Arduino, but you are free to define your own APIs.
2. Device Abstraction Layer that implements the display driver.
3. Application Layer, displaying a picture using the display driver.

## GPIO driver

1. Define the function prototypes in the header file, say, `gpio.h`.
2. Define the functions in a C file, say, `gpio.c`.
   1. Define registers; refer to nrf processor document for details.
   2. Implement the API functions using these registers.

## Display driver

1. Define function prototypes in the header file, say, `display.h`.

2. Define the functions in a C file, say, `led.c`. This should have:

   1. LED row and column pin numbers

   2. An `init` function, that initializes all the row and column pins as output and sets their

      values so that the display is blank.

   3. A display function that takes 5x5 image bitmap and displays it. The logic includes:

      1. Turn on one row at a time
      2. Turn on the columns corresponding to the LEDs that need to be on
      3. Delay
      4. Turn oﬀ all the rows
      5. Turn on the row

## Main function

1. Displays a picture using the display APIs.

## References (available in Teams Files)

- Product specifications: `nRF52833_PS_v1.5.pdf`
- Board schematic diagram: `MicroBit_V2.0.0_S_schematic.pdf`

## Questions

1. How many GPIO pins does NRF52833 have?
   1. The schematic tells us that the part number is nRF52833-QIAA.
   2. Section 10.3 tells us the meaning of QIAA.
   3. Section 7.1.1 tells us pin configuration for QFN73 package.
2. What does AA mean in part number: nRF52833-QIAA.
3. Familiarize with the GPIO registers in section 6.8 of the product specifications.
   1. What is the diﬀerence between OUT, OUTSET and OUTCLR registers?
   2. What are the addresses of pin configuration register for the two push bucons?
4. What determines the period for which a row should remain on?
5. Search and find out five applications of GPIO peripheral.

## Just for fun (no marks)

1. Make a slide show of diﬀerent patterns on the display.
2. Scroll a pattern to left, right, up or down.
