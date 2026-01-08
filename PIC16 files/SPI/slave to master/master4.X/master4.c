/*
 * File:   master4.c
 * Author: Sharvesh V
 *
 * Created on 19 June, 2025, 11:45 AM
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
char chr,ch[20]="master",data;
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

void master_in()
{
    while(SSPIF==0)
    chr=SSPBUF;
    lcd(1,chr);
    SSPIF=0;
}

void master_out(char *ptr)
{
    int i;
    for(i=0;*(ptr+i)!='\0';i++)
    {
        SSPBUF=*(ptr+i);
        while(SSPIF==0);
        SSPIF=0;
        delay(100);
    }
}

void main(void) 
{
    PORTB=0x00;
    TRISB=0x00;
    PORTC=0x00;
    TRISC=0x10;
    PORTD=0x00;
    TRISD=0x00;
    PORTE=0x00;
    TRISE=0x00;
    ANSEL=ANSELH=0x00;
    
    SSPCON=0x20;
    SSPSTAT=0x00;
    
    lcd(0,0x38);
    lcd(0,0x0E);
    lcd(0,0x80);
    
    RB0=0;RB1=0;
    //master_out("s");
    while(1)
    {
        //master_in();
        for(int j=0;j<5;j++)
        {
            SSPBUF=ch[j];
            delay(10000);
            data=SSPBUF;
            SSPIF=0;
            lcd(1,data);
        }
    }
}
