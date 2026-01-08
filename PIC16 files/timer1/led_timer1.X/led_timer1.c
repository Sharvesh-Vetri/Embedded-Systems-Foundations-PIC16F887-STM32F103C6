/*
 * File:   led_timer1.c
 * Author: Sharvesh V
 *
 * Created on 26 May, 2025, 3:18 PM
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
    if(TMR1IF==1)
    {
        count++;
        TMR1IF=0;
    }
}
 
void main(void) 
{
    PORTC=TRISC=0x00;
    T1CON=0xb1;
    TMR1=3036;
    while(1)
    {
        timer();
        if(count==2)
        {
            RC0=1;
        }
        if(count==4)
        {
            RC0=0;
            count=0;
        }
    }
}

