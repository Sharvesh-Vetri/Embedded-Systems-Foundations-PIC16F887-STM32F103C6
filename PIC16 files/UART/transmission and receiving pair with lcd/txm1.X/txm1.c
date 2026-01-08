/*
 * File:   txm1.c
 * Author: Sharvesh V
 *
 * Created on 16 June, 2025, 12:38 PM
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

void transmit(char *data)
{
    int i;
    for(i=0 ; *(data+i)!='\0' ; i++)
    {
       TXREG=*(data+i);
       while(TXIF==0);
       TXIF=0;
    }
}

void main(void) 
{
    PORTC=0x00;
    TRISC=0x00;
    SPBRG=25;
    TXSTA=0x26;
    RCSTA=0x90;
    while(1)
    {
        transmit("string");
    }
}
