/*
 * File:   eeprom1.c
 * Author: Sharvesh V
 *
 * Created on 29 May, 2025, 3:18 PM
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

void lcd(int rs,char data)
{
    RE0=rs;
    PORTD=data;
    RE1=1;
    delay(100);
    RE1=0;
    delay(100);
}

void main(void) 
{
    PORTD=TRISD=0x00;
    PORTE=TRISE=0x00;
    PORTB=TRISB=0x00;
    ANSEL=ANSELH=0x00;
  
    eeprom_write(0x01,'L');
    lcd(0,0x38);
    lcd(0,0x0c);
    lcd(0,0x80);
    lcd(1,eeprom_read(0x01));
    
    
}
