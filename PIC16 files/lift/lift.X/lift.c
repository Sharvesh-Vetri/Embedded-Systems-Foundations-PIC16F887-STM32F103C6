/*
 * File:   lift.c
 * Author: Sharvesh V
 *
 * Created on 9 June, 2025, 3:21 PM
 */


#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF       
#pragma config PWRTE = ON       
#pragma config MCLRE = ON       
#pragma config CP = OFF         
#pragma config CPD = OFF       
#pragma config BOREN = OFF     
#pragma config IESO = ON        
#pragma config FCMEN = ON       
#pragma config LVP = OFF       
#pragma config BOR4V = BOR40V  
#pragma config WRT = OFF

#include <xc.h>
int pow=0;
int current_floor,direction=1;
int log(int num)
{
    
    if(num==1)
    {
        pow=0;
    }
    while(num>1)
    {
        num=num/2;
        pow = pow++;
    }
    return pow;
}
void delay(unsigned int t)
{
    while(t--);
}
void enable()
{
    RE1=1;
    delay(1000);
    RE1=0;
    delay(1000);
}
void lcd(int rs,char data)
{
    RE0=rs;
    PORTD=data;
    enable();
}
void print(char adrs ,char *ptr)
{
    int i=0;
    for(i=0;*(ptr+i)!='\0';i++)
    {
        RE0=0;
        PORTD=adrs+i;
        enable();
        RE0=1;
        PORTD=*(ptr+i);
        enable();
    }
}

void motor_fwd()
{
    RC0=0;
    RC1=1;
}
void motor_rev()
{
    RC0=1;
    RC1=0;
}
void motor_stop()
{
    RC0=1;
    RC1=1;
}

void motor(int pressed_floor)
{
    if(pressed_floor > current_floor)
    {
        motor_fwd();
        for(;current_floor<pressed_floor;)
        {     
            if( ~(PORTA) & 1<<(current_floor+1)  )                
            {
                current_floor++;
                lcd(0,0x8E);
                lcd(1,current_floor+48);
                if(current_floor==pressed_floor)
                {
                    motor_stop();
                    print(0xC0,"PRESSED FLOOR:");
                    break;
                }
            }
        }
    }
    
    if(pressed_floor < current_floor)
    {
        motor_rev();
        for(;current_floor>pressed_floor;)
        {     
            if( ~(PORTA) & (1<<current_floor-1)  )                
            {
                current_floor--;
                lcd(0,0x8E);
                lcd(1,current_floor+48);
                if(current_floor==pressed_floor)
                {
                    motor_stop();
                    print(0xC0,"PRESSED FLOOR:");
                    break;
                }
            }
        }
    }
} 

void main(void) 
{
    PORTA=0x00;
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    PORTE=0x00;
    TRISA=0xff;
    TRISB=0xff;
    TRISC=0x00;
    TRISD=0x00;
    TRISE=0x00;
    ANSEL=ANSELH=0;
    int val = 0x0f & (~PORTA);
    current_floor=log(val);
    
    lcd(0,0x38);
    lcd(0,0x0c);
    lcd(0,0x01);
    print(0x80,"CURRENT FLOOR:");
    lcd(1,48+current_floor);
    while(1)
    {
        int j;
        
        if(direction==1)
        {
            for(j=current_floor;j<=4;j++)
            {
                delay(20000);
                if(PORTB & 1<<j)
                {
                    print(0xC0,"PRESSED FLOOR:");
                    lcd(1,48+j);
                    
                    motor(j);
                    if(j==4)
                    {
                        direction=0;
                    }
                }
            }
            direction=0;
        }
        
        if(direction==0)
        {
            for(j=current_floor;j>=0;j--)
            {
                delay(20000);
                if(PORTB & 1<<j)
                {
                    print(0xC0,"PRESSED FLOOR:");
                    lcd(1,48+j);
                    
                    motor(j);
                    if(j==0)
                    {
                        direction=1;
                    }
                }
            }
            direction=1;
        }
    }
}
