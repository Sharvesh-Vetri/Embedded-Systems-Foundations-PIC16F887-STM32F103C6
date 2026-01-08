/*
 * File:   led_counter0.c
 * Author: Sharvesh V
 *
 * Created on 27 May, 2025, 11:00 AM
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

void main(void) 
{
    PORTB=TRISB=0x00;
    PORTA=TRISA=0x10;
    ANSEL=ANSELH=0;
    OPTION_REG=0xa8;
    TMR0=0;
    while(1)
    {
        count=TMR0; 
        if(count%2==1)
        {
            RB0=1;
        }
        else
        {
            RB0=0;
        }
    }
}
