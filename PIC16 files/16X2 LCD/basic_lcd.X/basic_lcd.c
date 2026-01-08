/*
 * File:   basic_lcd.c
 * Author: Sharvesh V
 *
 * Created on 20 May, 2025, 3:31 PM
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

void delay(int t)
{
    while(t--);
}

void lcd(char rs , char data)
{
    RE0 = rs;
    PORTD = data;
    RE1=1;
    delay(100);
    RE1=0;
    delay(100);
}

void string(char *ptr)
{
    while(*ptr)
    {
        lcd(1,*ptr++);
    }
}
void main(void) 
{
    PORTD=0x00;
    PORTE=0x00;
    TRISD=0x00;
    TRISE=0x00;
    ANSEL=ANSELH=0;
    lcd(0,0x38);
    lcd(0,0x0c);    
    while(1)
    {
        lcd(0,0x80);
        string("manfree");
    }
}
