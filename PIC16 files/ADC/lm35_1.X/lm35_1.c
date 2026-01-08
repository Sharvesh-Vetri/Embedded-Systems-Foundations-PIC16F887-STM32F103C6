/*
 * File:   lm35_1.c
 * Author: Sharvesh V
 *
 * Created on 28 May, 2025, 3:57 PM
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
    
    
    int rem = dv%1023;
    lcd(0,0x80);
    int x = dv/1000;
    lcd(1,x+48);
    int y =((dv/100)%10);
    lcd(1,y+48);
    int z =((dv/10)%10);
    lcd(1,z+48);
    int w = dv%10;
    lcd(1,w+48);
    lcd(1,'.');
    int v = (rem*10)/1023;
    lcd(1,v+48);
    
    lcd(1,' ');
    
    int temp=(((float)dv*150.0)/1023);
    int p = temp/100;
    lcd(1,p+48);
    int q = (temp/10)%10;
    lcd(1,q+48);
    int r = temp%10;
    lcd(1,r+48);
    lcd(1,'*');
    lcd(1,'C');
    
    lcd(1,' ');
    
    lcd(0,0xc0);
    int res=(((float)dv)*100.0)/1023.0;
    if(res>99)
    {
        int b = (res/100);
        lcd(1,b+48);
    }
    int c = ((res/10)%10);
    lcd(1,c+48);
    int d = res%10;
    lcd(1,d+48);
    lcd(1,'%');
}

void main(void) 
{
    PORTA=0x00;
    TRISA=0xff;
    PORTD=TRISD=0x00;
    PORTE=TRISE=0x00;
    ADCON0=0x81;
    ADCON1=0xb0;
    ANSEL=0x01;
    ANSELH=0x00;
    lcd(0,0x38);
    lcd(0,0x0c);
    while(1)
    {
        adc();
    }
}


