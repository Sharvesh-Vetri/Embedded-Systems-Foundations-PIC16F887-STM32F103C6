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

void main(void) 
{
    PORTA=0x00;
    PORTC=0x00;
    PORTD=0x00;
    TRISA=0x00;
    TRISC=0xff;
    TRISD=0x00;
    int count,arr[10]={0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67,0x3f};
    while(1)
    {
        RD0=1;RD1=RD2=RD3=0;
        if(RC0==1){PORTA=arr[0];count++;while(RC0=1);}
        if(RC1==1){PORTA=arr[1];count++;while(RC1=1);}
        if(RC2==1){PORTA=arr[2];count++;while(RC2=1);}
        
        RD1=1;RD2=RD3=RD0=0;
        if(RC0==1){PORTA=arr[3];count++;while(RC0=1);}
        if(RC1==1){PORTA=arr[4];count++;while(RC1=1);}
        if(RC2==1){PORTA=arr[5];count++;while(RC2=1);}
        
        RD2=1;RD1=RD0=RD3=0;
        if(RC0==1){PORTA=arr[6];count++;while(RC0=1);}
        if(RC1==1){PORTA=arr[7];count++;while(RC1=1);}
        if(RC2==1){PORTA=arr[8];count++;while(RC2=1);}
        
        RD3=1;RD1=RD2=RD0=0;
        if(RC1==1){PORTA=arr[9];count++;while(RC1=1);}

    }
}
