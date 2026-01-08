/*
 * File:   One at a time.c
 * Author: Sharvesh V
 *
 * Created on 17 May, 2025, 11:50 AM
 */


#include <xc.h>
#include <math.h>;
void delay(unsigned long int a)
{
    while(a--);
}

void main(void) 
{
    PORTA=0x00;
    TRISA=0x00;
    PORTB=0x00;
    TRISB=0x00;
    PORTC=0x00;
    TRISC=0x00;
    PORTD=0x00;
    TRISD=0x00;
    PORTE=0x00;
    TRISE=0x00;
    int i,j,k;
    while(1)
    {
        for(i=1;i<129;)
        {
            PORTA=i;
            delay(2000);
            i=i*2;
        }
        PORTA=0;
        for(j=1;j<129;)
        {
            PORTB=j;
            delay(2000);
            j=j*2;
        }
        PORTB=0;
        for(k=1;k<129;)
        {
            PORTC=k;
            delay(2000);
            k=k*2;
        }
    }
}

