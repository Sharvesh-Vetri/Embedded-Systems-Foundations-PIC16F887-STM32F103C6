/*
 * File:   rc3.c
 * Author: Sharvesh V
 *
 * Created on 16 June, 2025, 3:51 PM
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
char data[7];
int i=0;

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
void print(char adrs ,char *ptr)
{
    int k=0;
    for(k=0;*(ptr+k)!='\0';k++)
    {
        RE0=0;
        PORTD=adrs+k;
        enable();
        RE0=1;
        PORTD=*(ptr+k);
        enable();
    }
}

int strcheck(char *ptr1,char *ptr2)
{
    int j;
    for(j=0;*(ptr2+j)!='\0';j++)
    {
        if( *(ptr1+j)!=*(ptr2+j) )
        {
            return(0);
            break;
        }
        else if(*(ptr2+j+1)=='\0')
        {
            return(1);
            break;
        }
    }
}

void receive()
{
    while(RCIF==0);
    data[i]=RCREG;
    if(data[i]==13)
    {
        if(strcheck(data,"ON"))
        {
            RB0=1;
            lcd(0,0x01);
            print(0x80," ON ");
            data[0]='\0';
            i=0;
        }
        else if(strcheck(data,"OFF"))
        {
            RB0=0;
            lcd(0,0x01);
            print(0x80," OFF ");
            data[0]='\0';
            i=0;
        }
        else
        {
            data[0]='\0';
            i=0;
        }
    }
    else
    {
        lcd(1,data[i]);
        i++;
    }
    RCIF=0;
}

void main(void) 
{
    PORTC=0x00;
    TRISC=0x80;
    PORTB=0x00;
    TRISB=0x00;
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
        receive();
    }
}

