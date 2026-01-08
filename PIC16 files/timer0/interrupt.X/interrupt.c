/*
 * File:   interrupt.c
 * Author: Sharvesh V
 *
 * Created on 27 May, 2025, 3:24 PM
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
    if(T0IF==1)
    {
        count++;
        if(count==125)
        {
            RC0=~RC0;
            count=0;
        }
        T0IF=0;
    }
}

void main(void) 
{
    PORTC=TRISC=0x00;
    ANSEL=ANSELH=0;
    OPTION_REG=0x85;
    TMR0=131;
    GIE=T0IE=1;
    while(1);
}
