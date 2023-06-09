/*
 * File:   main.c
 * Author: John Holmes
 * Target: PIC16F18345
 * Compiler: XC8 v2.36
 * IDE: MPLABX v6.00
 * See github page for details
 * https://github.com/johnmholmes/Pic16F18345_Journey
 * Created on March 23, 2023, 12:22 PM
 * 
 * A simple program to toggle an led on pin RB6 or pin 11 on the Pic
 * 
 * I have my coding style to now use more functions and just call them in the main loop.
 * 
 * This allows for easier reading of the functions
 * 
 *
 *                              PIC16F18345
 * 
 *                    +------------:_:------------+
 *           5V  ->  1 : VDD                   VSS : 20  <- GND
 *               <>  2 : RA5                   RA0 : 19  <- PGD
 *               <>  3 : RA4                   RA1 : 18  <- PGC
 *          MCLR ->  4 : RA3                   RA2 : 17  <> 
 *               <>  5 : RC5                   RC0 : 16  <> 
 *               <>  6 : RC4                   RC1 : 15  <> 
 *               <>  7 : RC3                   RC2 : 14  <> 
 *               <>  8 : RC6                   RB4 : 13  <> 
 *               <>  9 : RC7                   RB5 : 12  <> 
*                <> 10 : RB7                   RB6 : 11  <> LED1
 *                    +---------------------------:
 *                               DIP-20
 *
 */

// Define the configuration bits
#pragma config FEXTOSC = OFF    // FEXTOSC External Oscillator mode Selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINT32 // Power-up default value for COSC bits (HFINTOSC with 2x PLL (32MHz))
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; I/O or oscillator function on OSC2)
#pragma config CSWEN = OFF      // Clock Switch Enable bit (The NOSC and NDIV bits cannot be changed by user software)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config MCLRE = OFF      // Master Clear Enable bit (MCLR/VPP pin function is digital input; MCLR internally disabled; Weak pull-up under control of port pin's WPU control bit.)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config WDTE = OFF       // Watchdog Timer Enable bits (WDT disabled; SWDTEN is ignored)
#pragma config LPBOREN = OFF    // Low-power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled)
#pragma config BORV = LOW       // Brown-out Reset Voltage selection bit (Brown-out voltage (Vbor) set to 2.45V)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (The PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will not cause a Reset)
#pragma config DEBUG = OFF      // Debugger enable bit (Background debugger disabled)

// CONFIG3
#pragma config WRT = OFF        // User NVM self-write protection bits (Write protection off)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored.)

// CONFIG4
#pragma config CP = OFF         // User NVM Program Memory Code Protection bit (User NVM code protection disabled)
#pragma config CPD = OFF        // Data NVM Memory Code Protection bit (Data NVM code protection disabled)

// Include the necessary header files
#include <xc.h>

// Define the oscillator frequency (in Hz)
#define _XTAL_FREQ 32000000

void PicSetup(void){
    TRISB = 0x00;              // Set all 4 PORTB as outputs
    LATB = 0x00;               // Set all 4 pins LOW
     
}

void Led1Toggle(void){
    LATBbits.LATB6 = 1;        // Turn on the LED
    __delay_ms(500);           // Delay for a short period
    LATBbits.LATB6 = 0;        // Turn on the LED
    __delay_ms(500);           // Delay for a short period
    
}
// Main program
void main(void){
    PicSetup();
    
    // Loop forever
    while(1){
      Led1Toggle();           
    }
}
