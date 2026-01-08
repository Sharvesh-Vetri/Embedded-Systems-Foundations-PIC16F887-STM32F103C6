/*
 * File:   master1.c
 * Author: Sharvesh V
 *
 * Created on 18 June, 2025, 11:35 AM
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

void delay(unsigned int t)
{
    while(t--);
}

void master(char *ptr)
{
    int i;
    for(i=0;*(ptr+i)!='\0';i++)
    {
        SSPBUF=*(ptr+i);
        while(SSPIF==0);
        SSPIF=0;
        delay(100);
    }
}

void main(void) 
{
    PORTB=0x00;
    TRISB=0X01;
    PORTC=0x00;
    TRISC=0x00;
    ANSEL=ANSELH=0x00;
    
    SSPCON=0x20;
    SSPSTAT=0x00;
    
    while(1)
    {
        if(RB0==1)
        {
            master("string");
            while(RB0==1);  
        }
    }
}
