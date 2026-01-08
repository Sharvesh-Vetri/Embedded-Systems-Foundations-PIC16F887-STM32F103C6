#include <stm32f10x.h>
char data[7];
int i=0;

void delay(int t)
{
	while(t--);
}
void enable()
{
	GPIOC->ODR|=(1<<14);
	delay(5000);
	GPIOC->BRR=(1<<14);
	delay(5000);
}

void lcd(unsigned int rs,char data)
{
	GPIOC->ODR=(rs<<15);
	GPIOA->ODR=((data & 0xf0)>>4);
	enable();
	GPIOA->ODR=(data & 0x0f);
	enable();
}
void print(char *str)
{
	lcd(0,0x80);
	for(i=0;*(str+i)!='\0';i++)
	{
		GPIOC->ODR=1<<15;
		GPIOA->ODR=(*(str+i) & 0xf0)>>4;
		enable();
		GPIOA->ODR=*(str+i) & 0x0f;
		enable();
	}
}

void tx(char *str)
{
	int i;
	for(i=0;*(str+i)!='\0';i++)
	{
		USART1->DR=*(str+i);
		while(!(USART1->SR & 1<<7));
		delay(500);
	}
}
	
int strcheck(char *ptr1,char *ptr2)
{
    int j;
    for(j=0;*(ptr2+j)!='\0';j++)
    {
        if( *(ptr1+j)!=*(ptr2+j) )
        {
            return(0);
        }
        else if(*(ptr2+j+1)=='\0')
        {
            return(1);
        }
    }
}


void rx()
{
    while(!(USART1->SR & 1<<5));
    data[i] = USART1->DR;
    if(data[i]==13)
    {
        if(strcheck(data,"ON"))
        {
					GPIOB->ODR|=(1<<0); 
					lcd(0,0x01);
					lcd(0,0x80);
					print(" ON ");
					data[0]='\0';
					i=0;
        }
        else if(strcheck(data,"OFF"))
        {
					GPIOB->ODR&=~(1<<0);
					lcd(0,0x01);
					lcd(0,0x80);
					print(" OFF ");
					data[0]='\0';
					i=0;
        }
        else
        {
            data[0]='\0';
            i=0;
        }
    }
    else
    {
        lcd(1,data[i]);
        i++;
    }
}



int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0;
	RCC->APB2ENR=1<<0|1<<2|1<<14;
	GPIOA->CRH=0x4A0;
	GPIOB->CRL=0x2;
	USART1->CR1=1<<2|1<<3|1<<13;
	USART1->BRR=0X341;
	
	GPIOA->CRL=0x00002222;
	GPIOC->CRH=0x22000000;
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0c);
	lcd(0,0x80);
	//GPIOA->ODR |= (1 << 8); 
	while(1)
	{
		rx();
	}
}