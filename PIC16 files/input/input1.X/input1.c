/*
 * File:   input1.c
 * Author: Sharvesh V
 *
 * Created on 17 May, 2025, 4:59 PM
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
#include <xc.h>
#define _XTAL_FREQ 4000000
void main(void) 
{
    PORTA=0x00;
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    TRISA=0x01;
    TRISB=0x01;
    TRISC=0x00;
    TRISD=0x00;
    ANSEL=ANSELH=0x00;
    while(1)
    {
        if(RA0==1)
        {
            RC0=~RC0;
            while(RA0==1);
        }
        if(RA1==1)
        {
            RC1=~RC1;
            while(RA2==1);
        }
        if(RA2==1)
        {
            RC2=~RC2;
            while(RA2==1);
        }
        
        if(RA3==1)
        {
            RC3=~RC3;
            while(RA3==1);
        }
        if(RA4==1)
        {
            RC4=~RC4;
            while(RA4==1);
        }
        if(RA5==1)
        {
            RC5=~RC5;
            while(RA5==1);
        }
        if(RA6==1)
        {
            RC6=~RC6;
            while(RA6==1);
        }
        if(RA7==1)
        {
            RC7=~RC7;
            while(RA7==1);
        }
    }
}
