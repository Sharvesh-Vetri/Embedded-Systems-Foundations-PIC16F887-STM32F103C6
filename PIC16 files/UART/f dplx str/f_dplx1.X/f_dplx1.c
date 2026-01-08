/*
 * File:   f_dplx1.c
 * Author: Sharvesh V
 *
 * Created on 17 June, 2025, 12:22 PM
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
char data;

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
void lcd(int rs,char chr)
{
    RE0=rs;
    PORTD=chr;
    enable();
}

void __interrupt() receive()
{
    if(RCIF==1)
    {
        data=RCREG;
        lcd(1,data);
        RCIF=0;
    }
}

void transmit(char *str)
{
    int i;
    for(i=0 ; *(str+i)!='\0' ; i++)
    {
       TXREG=*(str+i);
       while(TXIF==0);
       TXIF=0;
    }
}
void main(void) 
{
    PORTA=0x00;
    TRISA=0x01;
    PORTC=0x00;
    TRISC=0x80;
    PORTD=0x00;
    TRISD=0x00;
    PORTE=0x00;
    TRISE=0x00;
    ANSEL=ANSELH=0x00;
    RCIE = 1;   
    PEIE = 1;   
    GIE = 1;    
    
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
            transmit("FREE");
            while(RA0==1);
        }
    }
}