/*
 * File:   motor_countr0.c
 * Author: Sharvesh V
 *
 * Created on 27 May, 2025, 12:02 PM
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

int prev,count=0;
char display[3]="00";

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


void count_display()
{
    int j=0,k=0;
    for(j=0;j!=(count%10);)
    {
        j++;
    }
    for(k=0;k!=(count/10);)
    {
        k++;
    }
    display[0]=(char)(48+k);
    display[1]=(char)(48+j);
}

void main(void) 
{
    PORTB=TRISB=0x00;
    PORTD=TRISD=0x00;
    PORTE=TRISE=0x00;
    PORTA=0x00;
    TRISA=0x10;
    ANSEL=ANSELH=0;
    OPTION_REG=0xa8;
    TMR0=0;
    
    RE0=0;
    PORTD=0x38;
    enable();
    PORTD=0x0c;
    enable();
    print(display);
    while(1)
    {
        count=TMR0;
        if(RA4==1)
        {
            count_display();
            print(display);
            if(count%10==0)
            {
                RB0=0;
            }
            else if(count%5==0)
            {
                RB0=1;
            }
            while(RA4==1);
        }
    }
}

