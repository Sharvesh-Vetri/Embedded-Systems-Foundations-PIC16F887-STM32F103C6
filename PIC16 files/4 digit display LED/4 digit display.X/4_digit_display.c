/*
 * File:   4_digit_display.c
 * Author: Sharvesh V
 *
 * Created on 20 May, 2025, 10:22 AM
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

void main(void) 
{
    PORTB=0x00;
    TRISB=0x00;
    PORTA=0x00;
    TRISA=0x00;
    ANSEL=ANSELH=0;
    int i,j,k,l,arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};
    while(1)
    {
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            for(k=0;k<10;k++)
            {
                for(l=0;l<10;l++)
                {
                    RA0=1;RA1=RA2=RA3=0;
                    PORTB=arr[i];
                    delay(900);
                    RA1=1;RA0=RA2=RA3=0;
                    PORTB=arr[j];
                    delay(900);
                    RA2=1;RA1=RA0=RA3=0;
                    PORTB=arr[k];
                    delay(900);
                    RA3=1;RA1=RA2=RA0=0;
                    PORTB=arr[l];
                    delay(900);
                    
                }
            }
        }
    }
    }
}
