 /*
 * File:   adc1.c
 * Author: Sharvesh V
 *
 * Created on 28 May, 2025, 10:58 AM
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
#define _XTAL_FREQ 8000000 

char display[5]="0000";

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

void adc()
{
    int res;
    GO=1;
    while(GO)
    {
       res=(ADRESL+(ADRESH*256));
    }
    
    int k=res,j=0;
    for(;k>=0;j++)
    {
        display[3-j]=(char)(48+(k%10));
        k=k/10;
    }
}

void main(void) 
{
    PORTA=0x00;
    TRISA=0x01;
    PORTD=TRISD=0x00;
    PORTE=TRISE=0x00;
    ADCON0=0x81;
    ADCON1=0x80;
    ANSEL=0x01;
    ANSELH=0x00;
    
    RE0=0;
    PORTD=0x38;
    enable();
    PORTD=0x0c;
    enable();
    print(display);
    
    while(1)
    {
        adc();
        print(display);
    }
}
