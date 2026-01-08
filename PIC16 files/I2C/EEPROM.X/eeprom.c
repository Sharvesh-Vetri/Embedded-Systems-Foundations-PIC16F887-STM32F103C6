/*
 * File:   eeprom.c
 * Author: Sharvesh V
 *
 * Created on 24 June, 2025, 11:58 AM
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


void start()
{
    SEN=1;
    while(SSPIF==0);
    SSPIF=0;
}
void address(char addrs)
{
    SSPBUF=addrs;
    while(BF==1);
    while(ACKSTAT==1);
    SSPIF=0;
}
void repeated_start()
{
    RSEN=1;
    while(SSPIF==0);
    SSPIF=0;
}
void write(char data)
{
    ACKSTAT=1;
    SSPBUF=data;
    while(SSPIF==0);
    SSPIF=0;
}
char read(unsigned char ack)
{
    char d;
    RCEN=1;
    ACKDT=ack;
    while(BF==0);
    d=SSPBUF;
    ACKEN=1;
    while(SSPIF==0);
    SSPIF=1;
    return d;
}
void stop()
{
    PEN=1;
    while(SSPIF==0);
    SSPIF=0;
}
void main(void) 
{
    PORTC=0x00;
    TRISC=0x18;
    PORTD=0x00;
    TRISD=0x00;
    PORTE=0x00;
    TRISE=0x00;
    ANSEL=ANSELH=0x00;
    
    SSPCON=0x28;
    SSPSTAT=0x80;
    SSPCON2=0x00;
    
    start();
    address(0xa0);
    address(0x00);
    //address(0x00);
    write('1');
    write('2');
    write('3');
    stop();
    delay(100);
    
    
    lcd(0,0x38);
    lcd(0,0x0e);
    lcd(0,0x01);
    lcd(0,0x80);
    while(1)
    {
        start();
        address(0xa0);
        address(0x00);
        address(0x00);
        repeated_start();
        address(0xa1);
        char val1=read(0);
        char val2=read(0);
        char val3=read(1);
        stop();
        lcd(0,0x80);
        lcd(1,val1);
        lcd(1,val2);
        lcd(1,val3);
        delay(100);
    }
}
