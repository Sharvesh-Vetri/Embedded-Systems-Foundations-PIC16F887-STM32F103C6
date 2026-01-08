/*
 * File:   lm35_1.c
 * Author: Sharvesh V
 *
 * Created on 28 May, 2025, 3:49 PM
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
int dv=0;

void delay(int t)
{
    while(t--);
}

void lcd(char ra,char data)
{
    RE0 = ra;
    PORTD=data;
    RE1=1;
    delay(100);
    RE1=0;
    delay(100);
}

int adc()
{
    GO=1;
    while(GO)
    {
        dv=(ADRESL+(ADRESH*256));
    }
    lcd(0,0x80);
    int a = dv/1000;
    lcd(1,a+48);
    int b =((dv/100)%10);
    lcd(1,b+48);
    int c =((dv/10)%10);
    lcd(1,c+48);
    int d = dv%10;
    lcd(1,d+48);
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
    lcd(0,0x38);
    lcd(0,0x0c);
    while(1)
    {
        adc();
    }
}
