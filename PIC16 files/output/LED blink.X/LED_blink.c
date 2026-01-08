/*
 * File:   LED_blink.c
 * Author: Sharvesh V
 *
 * Created on 17 May, 2025, 10:26 AM
 */


#include <xc.h>
#include <math.h>

void delay(unsigned long int t)
 {
    while(t!=0)
    {
        t--;
    }
 }
 void main()
 {
 PORTA=0x00;   // 0b0000 0000
 TRISA=0x00;   // 0b0000 0000
 PORTB=0x00;   // 0b0000 0000
 TRISB=0x00;   // 0b0000 0000
 PORTC=0x00;   // 0b0000 0000
 TRISC=0x00;   // 0b0000 0000
 PORTD=0x00;   // 0b0000 0000
 TRISD=0x00;   // 0b0000 0000
 PORTE=0x00;   // 0b0000 0000
 TRISE=0x00;   // 0b0000 0000
 while(1)
 {
     PORTC=0x55;
     delay(20000);
     PORTC=0xaa;
     delay(20000);
 }
 
 }

