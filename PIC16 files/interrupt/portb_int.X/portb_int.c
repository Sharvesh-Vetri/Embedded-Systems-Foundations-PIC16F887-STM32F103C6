/*
 * File:   portb_int.c
 * Author: Sharvesh V
 *
 * Created on 23 May, 2025, 11:39 AM
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

void __interrupt() isr()
{
    if(RBIF==1)
    {
        if(RB0==1)
        {
            RD0=~RD0;
            while(RB0==1);
            RBIF=0;
        }
        if(RB1==1)
        {
            RD1=~RD1;
            while(RB1==1);
            RBIF=0;
        }
        if(RB2==1)
        {
            RD2=~RD2;
            while(RB2==1);
            RBIF=0;
        }
        if(RB3==1)
        {
            RD3=~RD3;
            while(RB3==1);
            RBIF=0;
        }
        if(RB4==1)
        {
            RD4=~RD4;
            while(RB4==1);
            RBIF=0;
        }
         
    }
}

void main(void) 
{
    PORTB=0x00;
    TRISB=0xff;
    PORTD=0x00;
    TRISD=0x00;
    IOCB=0xff;
    
    ANSEL=ANSELH=0;
    
    GIE=1;RBIE=1;
    while(1);
}
