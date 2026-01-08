/*
 * File:   keypad1.c
 * Author: Sharvesh V
 *
 * Created on 19 May, 2025, 3:39 PM
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

void delay(int t)
{
    while(t--);
}

void enable()
{
    RE1=1;
    delay(100);
    RE1=0;
    delay(100);
}

void print(char *ptr)
{
    RE0=0;
    PORTC=0x01;
    enable();
    int i=0;
    for(i=0;*(ptr+i)!='\0';i++)
    {
        RE0=0;
        PORTC=0x80+i;
        enable();
        RE0=1;
        PORTC=*(ptr+i);
        enable();
    }
}

void __interrupt() external()
{
    if(INTF==1)
    {
        RA1=0;
        INTF=0;
        print("EMERGENCY STOP");
        while(1);
    }
}

void main(void) 
{
    PORTA=0x00;
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    PORTE=0x00;
    
    TRISA=0x00;
    TRISB=0xff;
    TRISC=0x00;
    TRISD=0xff;
    TRISE=0x00;
    
    GIE=1;INTE=1;
    
    ANSEL=ANSELH=0x00;
    
    RE0=0;
    PORTC=0x38;
    enable();
    PORTC=0x0C;
    enable();
    PORTC=0x01;
    enable();
    print("INITIALIZED");
    
    label:
    print("INITIALIZED");
    RA1=0;
    
    while(1)
    {
        if(RD0==1)
        {
            print("RUNNING");
            RA1=1;
            while(RD0==1);
        }
        
        if(RD1==1)
        {
            print("STOPPED");
            RA1=0;
            while(RD1==1);
        }
        
        if(RD2==1)
        {
            print("RESETING");
            RD2=0;
            delay(10000);
            goto label;
        }
        
    }
}
