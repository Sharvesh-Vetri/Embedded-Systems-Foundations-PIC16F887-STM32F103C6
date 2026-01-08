/*
 * File:   interrupt.c
 * Author: Sharvesh V
 *
 * Created on 27 May, 2025, 3:50 PM
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
    if(TMR1IF==1)
    {
        count++;
        if(count==2)
        {
            RC0=~RC0;
            count=0;
        }
        TMR1IF=0;
    }
}

void main(void) 
{
    PORTC=TRISC=0x00;
    ANSEL=ANSELH=0;
    T1CON=0xb1;
    TMR1=3036;
    GIE=PEIE=TMR1IE=1;
    while(1);
}
