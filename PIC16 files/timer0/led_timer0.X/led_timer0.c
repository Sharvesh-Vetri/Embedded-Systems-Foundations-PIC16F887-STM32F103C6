/*
 * File:   led_timer0.c
 * Author: Sharvesh V
 *
 * Created on 26 May, 2025, 10:08 AM
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

int count;

void timer()
{
    if(T0IF==1)
    {
        count++;
        T0IF=0;
    }
}
 
void main(void) 
{
    PORTC=TRISC=0x00;
    OPTION_REG=0x85;
    TMR0=131;
    while(1)
    {
        timer();
        if(count==125)
        {
            RC0=1;
        }
        if(count==250)
        {
            RC0=0;
            count=0;
        }
    }
}
