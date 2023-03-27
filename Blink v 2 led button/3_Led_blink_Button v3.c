/*
 * Author John Holmes
 * Program MPLAB X IDE version 6.00
 * XC8 version 2.36
 * Pic16F18345
 * Pickit 4 used
 * 
 * Github page https://github.com/johnmholmes/Pic16F18345_Journey
 * 
 * 27/3/2023 09:00
 * 
 * The code is used to blink 2 LEDs with 1st on while 2nd is off at a rate of 500 milliseconds.
 * Once the button is pressed the 2 LEDs will the be turned off.
 * The a 3rd LED will blink at 100 millisecond intervals while the button remains pressed
 * 
 * 
 *                              PIC16F18345
 * 
 *                    +------------:_:------------+
 *           5V  ->  1 : VDD                   VSS : 20  <- GND
 * Push button   <>  2 : RA5                   RA0 : 19  <- PGD
 *               <>  3 : RA4                   RA1 : 18  <- PGC
 *          MCLR ->  4 : RA3                   RA2 : 17  <> 
 *               <>  5 : RC5                   RC0 : 16  <> LED when button pressed
 *               <>  6 : RC4                   RC1 : 15  <> 
 *               <>  7 : RC3                   RC2 : 14  <> 
 *               <>  8 : RC6                   RB4 : 13  <> LED1
 *               <>  9 : RC7                   RB5 : 12  <> LED2
*                <> 10 : RB7                   RB6 : 11  <> 
 *                    +---------------------------:
 *                               DIP-20
 * 
 */


// Configuration settings for the PIC16F18345
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
#pragma config BOREN = ON       // Brown-out Reset Enable bits (Brown-out Reset enabled, SBOREN bit ignored)
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


#include <xc.h>                 // Library used for delays and other built in functions
#define _XTAL_FREQ 32000000     // The clock to 32MHZ

/* Setup the Pic registers */

void Init_PicSetup(void){
    TRISAbits.TRISA5 = 1;           // RA5 set as an input pin
    ANSELAbits.ANSA5 = 0;           // RA5 set as an digital pin
    WPUAbits.WPUA5 = 1;             // Weak Pull up enabled RA5
    TRISBbits.TRISB4 = 0;           // RB4 set as an output
    TRISBbits.TRISB5 = 0;           // RB5 set as an output
    TRISBbits.TRISB6 = 0;           // RB6 set as an output
    TRISBbits.TRISB7 = 0;           // RB7 set as an output
    TRISCbits.TRISC0 = 0;           // RC0 set as an output
    LATCbits.LATC0 = 0;             // Set initial state of RCO to low
    
    __delay_ms(500);      /* wait for ICD before making PGC and PGD outputs  Because the code that Microchip provides to control device programming tools like the PICkit3
                           *is kind of problematic it lets the user application run for a bit. 
                           *When this happens on a PIC16F676 and the controller sets the GPIO lines used for PGD and PGC 
                           *to outputs too soon the attempt to program the target device could fail and leave the controller bricked 
                           *in a way that can be hard to recover.*/
    
} /* End pic setup function */


/* Button has been pressed */
void Init_Button(){
    LATB = 0x00;            // sets the 4 available pins to LOW

    LATCbits.LATC0 ^= 1;    // Toggle the state of RCO
    __delay_ms(100);        // Add a delay to debounce the button
}/* End of button pressed */

/* Sequence 1 for Led flashing */
void Init_LedSeq1(){
    LATCbits.LATC0 = 0;     // Set RC0 LOW
    LATB = 0x10;            // sets pin RB4 HIGH and all 3 others LOW
    __delay_ms(500);        // Delay 500 milliseconds
    LATB = 0x20;            // sets pin RB5 HIGH and all 3 others LOW
    __delay_ms(500);        // Delay 500 milliseconds
    
}/* end of seq 1 */

void main() {
    
    Init_PicSetup();         /* Calls the function void Init_PicSetup(void) */

    /* Start the forever loop */
    while(1) {
        // Check if the button is pressed
        if(PORTAbits.RA5 == 0) {
            Init_Button();   /* Calls the button function */
        }
        else{
            Init_LedSeq1();  /* Calls the led1 sequence */
        }
    }
}
