/*
 * File:   mltpl_emrgncy.c
 * Author: Sharvesh V
 *
 * Created on 23 May, 2025, 12:20 PM
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

void delay(int t)
{
    while(t--);
}

void enable()
{
    RE1=1;
    delay(100);
    RE1=0;
    delay(100);
}

void print(char *ptr)
{
    RE0=0;
    PORTD=0x01;
    enable();
    int i=0;
    for(i=0;*(ptr+i)!='\0';i++)
    {
        RE0=0;
        PORTD=0x80+i;
        enable();
        RE0=1;
        PORTD=*(ptr+i);
        enable();
    }
}

void __interrupt() isr()
{
    if(RBIF==1)
    {
        if(RB0==1)
        {
            print("EMR1 TRIGGERED");
            delay(10000);
            RBIF=0;
        }
        if(RB1==1)
        {
            print("EMR2 TRIGGERED");
            RBIF=0;
        }
        if(RB2==1)
        {
            print("EMR3 TRIGGERED");
            RBIF=0;
        }
    }
}
void main(void) 
{
    PORTB=0x00;
    TRISB=0xff;
    PORTD=0x00;
    TRISD=0x00;
    PORTE=0x00;
    TRISE=0x00;
    IOCB=0xff;
    
    ANSEL=ANSELH=0;
    
    RE0=0;
    PORTD=0x38;
    enable();
    PORTD=0x0C;
    enable();
    PORTD=0x01;
    enable();
    
    GIE=1;RBIE=1;
    while(1);
}
