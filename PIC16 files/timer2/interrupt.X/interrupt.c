/*
 * File:   interrupt.c
 * Author: Sharvesh V
 *
 * Created on 27 May, 2025, 3:56 PM
 */


#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF       
#pragma config PWRTE = ON       
#pragma config MCLRE = ON       
#pragma config CP = OFF         
#pragma config CPD = OFF       
#pragma config BOREN = OFF     
#pragma config IESO = ON        
#pragma config FCMEN = ON       
#pragma config LVP = OFF       
#pragma config BOR4V = BOR40V  
#pragma config WRT = OFF

#include <xc.h>
int count=0;

void __interrupt() isr()
{
    if(TMR2IF==1)
    {
        count++;
        if(count==125)
        {
            RC0=~RC0;
            count=0;
        }
        TMR2IF=0;
    }
}

void main(void) 
{
    PORTC=TRISC=0x00;
    ANSEL=ANSELH=0;
    T2CON=0x1d;
    TMR1=6;
    PR2=255;
    GIE=PEIE=TMR2IE=1;
    while(1);
}
