/*
 * File:   led_timer2.c
 * Author: Sharvesh V
 *
 * Created on 26 May, 2025, 4:30 PM
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
    if(TMR2IF==1)
    {
        count++;
        TMR2IF=0;
    }
}
 
void main(void) 
{
    PORTC=TRISC=0x00;
    T2CON=0x05;
    TMR2=6;
    PR2=255;
    while(1)
    {
        timer();
        if(count==4000)
        {
            RC0=1;
        }
        if(count==8000)
        {
            RC0=0;
            count=0;
        }
    }
}

