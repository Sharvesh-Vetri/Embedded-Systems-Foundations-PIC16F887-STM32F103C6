/*
 * File:   lcd_count.c
 * Author: Sharvesh V
 *
 * Created on 26 May, 2025, 11:08 AM
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
char i='1';

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

void timer()
{
    if(T0IF==1)
    {
        count++;
        T0IF=0;
    }
}

void display(char data)
{
    RE0=0;
    PORTD=0x01;
    enable();
    PORTD=0x80;
    enable();
    RE0=1;
    PORTD=data;
    enable();
}
void main(void) 
{
    PORTD=TRISD=0x00;
    PORTE=TRISE=0x00;
    ANSEL=ANSELH=0x00;
    OPTION_REG=0x85;
    TMR0=131;
    RE0=0;
    PORTD=0x38;
    enable();
    PORTD=0x0C;
    enable();
    
    while(1)
    {
        timer();
        if(count==125)
        {
            count=0;
            display(i);
            i=(int)i+1;
            
        }
    }
}
