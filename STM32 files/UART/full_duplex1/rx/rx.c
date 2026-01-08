#include <stm32f10x.h>

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
	int i;
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

void rx()
{	
	char data;
	if(USART1->SR & 1<<5)
	{
		data = USART1->DR;
		lcd(1,data);
	}
}

void tx(char *str)
{
	int i;
	for(i=0;*(str+i)!='\0';i++)
	{
		USART1->DR=*(str+i);
		while(!(USART1->SR & 1<<7));
		delay(80000);
		rx();
	}
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0;
	RCC->APB2ENR=1<<0|1<<2|1<<14;
	GPIOA->CRH=0x4A0;
	USART1->CR1=1<<2|1<<3|1<<13;
	USART1->BRR=0X341;
	
	GPIOA->CRL=0x00002222;
	GPIOC->CRH=0x22000000;
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0c);
	lcd(0,0x80);
	tx("uart1"); 
	while(1)
	{
		rx();
	}
}