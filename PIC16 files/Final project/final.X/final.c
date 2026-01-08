/*
 * File:   final.c
 * Author: Sharvesh V
 *
 * Created on 4 July, 2025, 1:48 PM
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
int run_count,gen_count=0,ref_sec=0,dummy=0,count=0;
char work_time[9]="00:00:00";
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

void hr_inc()
{
    if(work_time[1]=='9')
    {
        work_time[0]=(int)work_time[0]+1;
        work_time[1]='0';
    }
    else
    {
        work_time[1]=(int)work_time[1]+1;
    }
}

void min_inc()
{
    if(work_time[4]=='9')
    {
        work_time[4]='0';
        if(work_time[3]=='5')
        {
            work_time[3]='0';
            hr_inc();
        }
        else
        {
            work_time[3]=(int)work_time[3]+1;
        }
    }
    else
    {
        work_time[4]=(int)work_time[4]+1;
    }
}

void __interrupt() timer()
{
    if(T0IF==1)
    {
        count++;
        T0IF=0;
    }
}


void work_time_inc()
{
    if(work_time[7]=='9')
    {
        work_time[7]='0';
        if(work_time[6]=='5')
        {
            work_time[6]='0';
            min_inc();
        }
        else
        {
            work_time[6]=(int)work_time[6]+1;
        }
    }
    else
    {
        work_time[7]=(int)work_time[7]+1;
    }
}

void main(void) 
{
    PORTA=0x00;
    TRISA=0x01;
    PORTB=0x00;
    TRISB=0x00;
    PORTC=0x00;
    TRISC=0x18;
    PORTD=0x00;
    TRISD=0x00;
    PORTE=0x00;
    TRISE=0x00;
    ANSEL=ANSELH=0x00;
    
    OPTION_REG=0x85;
    GIE=TMR0IE = 1;
    TMR0=131;
    
    SSPCON=0x28;
    SSPSTAT=0x80;
    SSPCON2=0x00;
    
    lcd(0,0x38);
    lcd(0,0x0c);
    lcd(0,0x01);
    lcd(0,0x80);
    start();
    address(0xd0);
    address(0x00);
    write(0x34);//sec
    write(0x09);//min
    write(0x64);//hour
    stop();
    delay(100);
    
//    int i;
//    for(i=0;i<256;i++)
//    {
//        eeprom_write(i,255);
//    }
    
//    run_count=eeprom_read(0x01);
//    if(run_count!=0x00)
//    {
//        work_time[0]=eeprom_read(0x11);
//        work_time[1]=eeprom_read(0x12);
//        work_time[3]=eeprom_read(0x13);
//        work_time[4]=eeprom_read(0x14);
//        work_time[6]=eeprom_read(0x15);
//        work_time[7]=eeprom_read(0x16);
//        eeprom_write(0x01,0x01);
//    }
    while(1)
    {
        int i=0;
        RB0=0;
        RB1=0;
        RB2=0;
        count=0;
        if(dummy==0)
        {
            lcd(0,0x01);
            dummy=1;
        }
        print(0x80,"STOP");
        while(RA0==1)
        {
            RB0=1;
            start();
            address(0xd0);
            address(0x00);
            repeated_start();
            address(0xd1);
            char sec = read(0);
            char min = read(0);
            char hour= read(1);
            stop();

            lcd(0,0x80);
            lcd(1,((hour&0x10)>>4)+48);
            lcd(1,((hour&0x0f)+48));
            lcd(1,':');
            lcd(1,((min&0xf0)>>4)+48);
            lcd(1,((min&0x0f)+48));
            lcd(1,':');
            lcd(1,((sec&0xf0)>>4)+48);
            lcd(1,((sec&0x0f)+48));
            int actual_sec=((sec&0xf0)>>4)*10+(sec&0x0f);
            
            if(gen_count==0)
            {
                ref_sec=actual_sec;
                gen_count++;
            }
            
            if(actual_sec!=ref_sec)
            {
                work_time_inc();
                ref_sec=actual_sec;
                i++;
                if(i<4)
                {
                    RB1=1;
                }
                else
                {
                    RB1=~RB1;
                }
                if(i<5)
                {
                    RB2=1;
                }
                else
                {
                    RB2=~RB2;
                }
            }
            
//            if(count==125)
//            {
//                count=0;
//                work_time_inc();
//                i++;
//                if(i<4)
//                {
//                    RB1=1;
//                }
//                else
//                {
//                    RB1=~RB1;
//                }
//                if(i<5)
//                {
//                    RB2=1;
//                }
//                else
//                {
//                    RB2=~RB2;
//                }
//            }
            
            print(0xc0,work_time);
            
            eeprom_write(0x11,work_time[0]);
            eeprom_write(0x12,work_time[1]);
            eeprom_write(0x13,work_time[3]);
            eeprom_write(0x14,work_time[4]);
            eeprom_write(0x15,work_time[6]);
            eeprom_write(0x16,work_time[7]);
            dummy=0;
        }
    }
}