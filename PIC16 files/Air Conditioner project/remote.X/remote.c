/*
 * File:   remote.c
 * Author: Sharvesh V
 *
 * Created on 20 June, 2025, 11:56 AM
 */

#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
int automatic=2,digit=0,speed,once=1;
char temp[3];

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
void print(char addrs,char *ptr)
{
    int j;
    for(j=0; *(ptr+j)!='\0' ;j++)
    {
        lcd(0,addrs+j);
        lcd(1,*(ptr+j));
    }
}


void transmit(char *data)
{
    int i;
    for(i=0 ; *(data+i)!='\0' ; i++)
    {
       TXREG=*(data+i);
       while(TXIF==0);
       TXIF=0;
    }
}

void main(void) 
{
    PORTA=0x00;
    TRISA=0xE3;
    PORTB=0x00;
    TRISB=0x00;
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
    
    lcd(0,0x38);
    lcd(0,0x0c);
    lcd(0,0x01);
    lcd(0,0x80);
    while(1)
    {
        if(RA0==1)
        {
            automatic=0;
            print(0x80,"MANUAL MODE");
            print(0xc0,"SPEED1");
            speed=1;
            transmit("19");
            while(RA0==1);
        }
        if(RA1==1)
        {
            automatic=1;
            lcd(0,0x01);
            while(RA1==1);
        }
        
        if(automatic==1)
        {
            if(once==1)
            {
                print(0x80,"AUTOMATIC MODE");
                lcd(0,0xc0);
                once=0;
            }
            
            RB1=RB2=RB3=0;RB0=1;
            if(RA7==1){temp[digit]='1';lcd(1,'1'); digit++;while(RA7==1);}
            if(RA6==1){temp[digit]='2';lcd(1,'2'); digit++;while(RA6==1);}
            if(RA5==1){temp[digit]='3';lcd(1,'3'); digit++;while(RA5==1);}

            RB0=RB2=RB3=0;RB1=1;
            if(RA7==1){temp[digit]='4';lcd(1,'4'); digit++;while(RA7==1);}
            if(RA6==1){temp[digit]='5';lcd(1,'5'); digit++;while(RA6==1);}
            if(RA5==1){temp[digit]='6';lcd(1,'6'); digit++;while(RA5==1);}

            RB1=RB0=RB3=0;RB2=1;
            if(RA7==1){temp[digit]='7';lcd(1,'7'); digit++;while(RA7==1);}
            if(RA6==1){temp[digit]='8';lcd(1,'8'); digit++;while(RA6==1);}
            if(RA5==1){temp[digit]='9';lcd(1,'9'); digit++;while(RA5==1);}

            RB1=RB2=RB0=0;RB3=1;
            if(RA7==1){transmit(temp);digit=0;print(0xc0,"   ");while(RA7==1);}
            if(RA6==1){temp[digit]='0';lcd(1,'0'); digit++;while(RA6==1);}
        }
        
        if(automatic==0)
        {
            if(RA0==1)
            {
                speed++;
                
                if(speed==4)
                {
                    lcd(0,0x01);
                    print(0x81,"OFF");
                    automatic=2;
                }
                if(speed==2)
                {
                    lcd(0,0xc5);
                    lcd(1,48+speed);
                    transmit("24");
                }
                if(speed==3)
                {
                    lcd(0,0xc5);
                    lcd(1,48+speed);
                    transmit("29");
                }
                while(RA0==1);
            }
        }
    }
}
