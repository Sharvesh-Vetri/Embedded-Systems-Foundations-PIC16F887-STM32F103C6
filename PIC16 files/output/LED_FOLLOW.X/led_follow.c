/*
 * File:   newmain.c
 * Author: Sharvesh V
 *
 * Created on 17 May, 2025, 4:25 PM
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

int power(int bas,int exp)
{
    int i,res=1;
    if(exp==0)
    {
        return(1);
    }
    else
    {
        for(i=1;i<=exp;i++)
        {
            res=res*bas;
        }
        return(res);
    }
}

void delay(int t)
{
    while(t--);
}

void main(void) 
{
    PORTA=0x00;
    TRISA=0x00;
    int i,j,k,l;
    while(1)
    {
    for(i=8;i>=1;i--)
    {
        if(i==8)
        {
            k=0;
        }
        else
        {
            k=0;
            for(l=7;l>=i;l--)
            {
                k=k+power(2,l);
            }
        }
        for(j=0;j<i;j++)
        {
            PORTA=(power(2,j))+k;
            delay(20000);
        }
    }
    }
}