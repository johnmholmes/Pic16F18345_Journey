# Pic16F18345_Journey

I am a hobbyist programmer and have not been college or university trained in programming.

This is the start of my learning to use the Pic16F18345 20 pin chip using C it is only my way of doing this and may not be the correct way or the best way.
 
This is used for me to look back on if i need a reminder of how I did things in the future.

---------------
# I have previously covered the Pic16F676

To do the basic control of the GPIO pins but this chip is know to have issues when being programmed with the Pickit 3 and 4.

This Chip I have the 20 pin version Dip mounted on a bread board a 14 pin version is also available.

I am programming the Pic using the MPLAB X IDE version 6.00 and using the XC8 compiler as this is the software I know about.

---------------
# For this chip I will be using a Pickit 4 to do the programming and only using the Pickit 3 for older chips.

--------------
# First thoughts was how to setup the use of the interanl oscillator and this is done by.

#pragma config FEXTOSC = OFF    // FEXTOSC External Oscillator mode Selection bits (Oscillator not enabled)

#pragma config RSTOSC = HFINT32 // Power-up default value for COSC bits (HFINTOSC with 2x PLL (32MHz))

#define _XTAL_FREQ 32000000 // Define the oscillator frequency (in Hz)

-------------
# PORT Setting Or LAT setting

In the context of microcontroller programming, a LAT (Latch) bit and a PORT bit refer to two different ways of accessing a pin's output state. Here are some benefits of using LAT bit over PORT bit:

Faster response time: The response time of a LAT bit is faster compared to PORT bit because there is no read operation involved. This makes it useful in applications where fast response times are crucial, such as in real-time control applications.

Reduced power consumption: Because a LAT bit does not involve a read operation, it consumes less power compared to PORT bit, making it useful in battery-powered devices where power consumption is critical.

For my applications I feel using PORTB = 10100000 or its HEX value is easier to do as its not that time critical.
