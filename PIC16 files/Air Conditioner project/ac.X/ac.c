/*
 * File:   ac.c
 * Author: Sharvesh V
 *
 * Created on 20 June, 2025, 12:30 PM
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
int count=0,dv,dv_temp,i=1,int_set_temp;
char room_temp[5], set_temp[5];

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

int adc()
{
    GO=1;
    while(GO)
    {
        dv=(ADRESL+(ADRESH*256));
    }
        
    dv_temp=(((float)dv*150.0)/1023);
    int p = dv_temp/100;
    int q = (dv_temp/10)%10;
    int r = dv_temp%10;
    
    room_temp[0]=p+48;
    room_temp[1]=q+48;
    room_temp[2]=r+48;
    room_temp[3]='C';
}

void temp_compare()
{
    int_set_temp=(((int)set_temp[1] - 48) * 10) + ((int)set_temp[2] - 48);
    
    if( (int_set_temp<18) || (int_set_temp>35) )
    {
        lcd(0,0x01);
        print(0x80,"ERROR");
        RB0=0;
    }
    else if(dv_temp>int_set_temp)
    {
        for(;dv_temp>int_set_temp;)
        {
            dv_temp--;
            room_temp[1]=(dv_temp/10)+48;
            room_temp[2]=(dv_temp%10)+48;
            print(0x8b,room_temp);
            delay(20000);
        }
        RB0=0;
    }
    else if(dv_temp<int_set_temp)
    {
        for(;dv_temp<int_set_temp;)
        {
            dv_temp++;
            room_temp[1]=(dv_temp/10)+48;
            room_temp[2]=(dv_temp%10)+48;
            print(0x8b,room_temp);
            delay(20000);
        }
        RB0=0;
    }
    else
    {
        RB0=0;
    }
}

void receive()
{
    if(RCIF==1)
    {
        set_temp[i]=RCREG;
        i++;
        if(i==3)
        {
            count++;
            set_temp[i]='C';
            i=1;
            RB0=1;
            print(0xc0,"SET TEMP :");
            print(0xcb,set_temp);
            temp_compare();
        }
        RCIF=0;
    }
}

void main(void) 
{
    PORTA=0x00;
    TRISA=0x0D;
    PORTB=0x00;
    TRISB=0x00;
    PORTC=0x00;
    TRISC=0x80;
    PORTD=0x00;
    TRISD=0x00;
    PORTE=0x00;
    TRISE=0x00;
    
    ADCON0=0x81;
    ADCON1=0xb0;
    ANSEL=0x01;
    ANSELH=0x00;
    
    SPBRG=25;
    TXSTA=0x26;
    RCSTA=0x90;
    
    lcd(0,0x38);
    lcd(0,0x0c);
    lcd(0,0x01);
    lcd(0,0x80);
    
    set_temp[0]='0';
    while(1)
    {
        if(count==0)
        {
            adc();
            print(0x80,"ROOM TEMP:");
            print(0x8b,room_temp);
        }
        receive();
    }
    
}
