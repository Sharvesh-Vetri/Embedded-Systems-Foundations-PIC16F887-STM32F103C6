/*
 * File:   voltage_divider.c
 * Author: Sharvesh V
 *
 * Created on 29 May, 2025, 10:01 AM
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
int dv;

void delay(int t)
{
    while(t--);
}

void lcd(int rs,char data)
{
    RE0=rs;
    PORTD=data;
    RE1=1;
    delay(100);
    RE1=0;
    delay(100);
}

void __interrupt() adc()
{
    
if(ADIF==1)
{
    dv=ADRESL+(ADRESH*256);
    ADIF=0;

 int dvolt=(5*dv)/1023;
    int dvolt_dec=(((5*dv)%1023)*10)/1023;
    int volt=((5.0*(float)dv*4.8)/1023);
    int volt_dec=(((int)(5.0*(float)dv*4.8)%1023)*10)/1023;
    
    lcd(0,0x80);
    
    int a=dv/1000;
    lcd(1,48+a);
    int b=(dv/100)%10;
    lcd(1,48+b);
    int c=(dv/10)%10;
    lcd(1,48+c);
    int d=dv%10;
    lcd(1,48+d);

    lcd(1,' ');
    
    lcd(0,0xc0);
    lcd(1,48+dvolt);
    lcd(1,'.');
    lcd(1,48+dvolt_dec);
    lcd(1,'V');
    
    lcd(1,' ');
    
    lcd(1,48+(volt/10));
    lcd(1,48+(volt%10));
    lcd(1,'.');
    lcd(1,48+volt_dec);
    lcd(1,'V');
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
    GIE=PEIE=ADIE=1;
    
    lcd(0,0x38);
    lcd(0,0x0c);
    while(1)
    {
        GO=1;
    }
}
