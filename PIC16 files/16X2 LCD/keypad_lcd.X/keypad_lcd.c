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

void func(char addrs, char data)
{
    RE0=0;
    PORTD=addrs;
    enable();
    RE0=1;
    PORTD=data;
    enable();
}

void main(void) 
{
    PORTA=0x00;
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    PORTE=0x00;
    TRISA=0x00;
    TRISB=0x00;
    TRISC=0xff;
    TRISD=0x00;
    TRISE=0x00;
    ANSEL=ANSELH=0x00;
    int count=-1;
    RE0=0;
    PORTD=0x38;
    enable();
    PORTD=0x0C;
    enable();
    while(1)
    {
        RB1=RB2=RB3=0;RB0=1;
        if(RC0==1){count++;func(0x80+count,'1');while(RC0==1);}
        if(RC1==1){count++;func(0x80+count,'2');while(RC1==1);}
        if(RC2==1){count++;func(0x80+count,'3');while(RC2==1);}
        
        RB2=RB3=RB0=0;RB1=1;
        if(RC0==1){count++;func(0x80+count,'4');while(RC0==1);}
        if(RC1==1){count++;func(0x80+count,'5');while(RC1==1);}
        if(RC2==1){count++;func(0x80+count,'6');while(RC2==1);}
        
        RB1=RB0=RB3=0;RB2=1;
        if(RC0==1){count++;func(0x80+count,'7');while(RC0==1);}
        if(RC1==1){count++;func(0x80+count,'8');while(RC1==1);}
        if(RC2==1){count++;func(0x80+count,'9');while(RC2==1);}
        
        RB1=RB2=RB0=0;RB3=1;
        if(RC1==1){count++;func(0x80+count,'0');while(RC1==1);}

    }
}