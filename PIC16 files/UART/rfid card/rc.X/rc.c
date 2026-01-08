/*
 * File:   rc.c
 * Author: Sharvesh V
 *
 * Created on 17 June, 2025, 2:18 PM
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
char str,id[14];

void delay(unsigned int t)
{
    while(t--);
}
void enable()
{
    RE1=1;
    delay(10);
    RE1=0;
    delay(10);
}
void lcd(int rs,char data)
{
    RE0=rs;
    PORTD=data;
    enable();
}
void __interrupt() receive()
{
    if(RCIF==1)
    {
        str=RCREG;
        lcd(1,str);
        id[count]=str;
        count++;
        if(count==13)
        {
            int truth=strcmp(id,"5B001625BED6");
            if(truth)
            {
                //delay(10000);
                
                lcd(0,0x80);
                lcd(1,'s');
                lcd(1,'h');
                lcd(1,'a');
                lcd(1,'r');
                lcd(1,'v');
                lcd(1,'e');
                lcd(1,'s');
                lcd(1,'h');
                lcd(1,' ');
                lcd(1,' ');
                lcd(1,' ');
                lcd(1,' ');
                lcd(1,' ');
                lcd(1,' ');
                lcd(1,' ');
                lcd(1,' ');
                lcd(1,' ');
                lcd(1,' ');
                lcd(1,' ');
                //lcd(0,0x01);
            }
        }
        RCIF=0;
    }
}

void main(void) 
{
    PORTC=0x00;
    TRISC=0x80;
    PORTD=0x00;
    TRISD=0x00;
    PORTE=0x00;
    TRISE=0x00;
    ANSEL=ANSELH=0x00;
    
    SPBRG=25;
    TXSTA=0x26;
    RCSTA=0x90;
    RCIE = 1;   
    PEIE = 1;   
    GIE = 1;   
    
    lcd(0,0x38);
    lcd(0,0x0c);
    lcd(0,0x01);
    lcd(0,0x80);
    
    while(1);
}

