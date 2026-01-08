/*
 * File:   clock.c
 * Author: Sharvesh V
 *
 * Created on 26 May, 2025, 11:48 AM
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
char time[9]="01:59:55",sec1,sec0,min1,min0,hr1,hr0;

void delay(int t)
{
    while(t--);
}

void enable()
{
    RE1=1;
    delay(35);
    RE1=0;
    delay(35);
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

void __interrupt timer()
{
    if(T0IF==1)
    {
        count++;
        T0IF=0;
    }
}

void hr_inc()
{
    if(hr1=='1'&hr0=='2')
    {
        hr1='0';
        hr0='0';
    }
    else if(hr0=='9')
    {
        hr1=(int)hr1+1;
        hr0='0';
    }
    else
    {
        hr0=(int)hr0+1;
    }
}

void min_inc()
{
    if(min0=='9')
    {
        min0='0';
        if(min1=='5')
        {
            min1='0';
            hr_inc();
        }
        else
        {
            min1=(int)min1+1;
        }
    }
    else
    {
        min0=(int)min0+1;
    }
}



void main(void) 
{
    PORTD=TRISD=0x00;
    PORTE=TRISE=0x00;
    ANSEL=ANSELH=0x00;
    OPTION_REG=0x85;
    GIE=TMR0IE = 1;
    
    TMR0=131;
    RE0=0;
    PORTD=0x38;
    enable();
    PORTD=0x0C;
    enable();
    
    sec0=time[7];
    sec1=time[6];
    min0=time[4];
    min1=time[3];
    hr1=time[0];
    hr0=time[1];
    
    time[7]=sec0;
    time[6]=sec1;
    time[4]=min0;
    time[3]=min1;
    time[1]=hr0;
    time[0]=hr1;
    while(1)
    {
        timer();
        if(count==125)
        {
            time[7]=sec0;
            time[6]=sec1;
            time[4]=min0;
            time[3]=min1;
            time[1]=hr0;
            time[0]=hr1;
            print(time);    
            count=0;
            if(sec0=='9')
            {
                sec0='0';
                if(sec1=='5')
                {
                    sec1='0';
                    min_inc();
                        
                }
                else
                {
                    sec1=(int)sec1+1;
                }
            }
            else
            {
                sec0=(int)sec0+1;
            }
        }
    }
}
