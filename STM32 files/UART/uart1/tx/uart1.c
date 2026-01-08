#include <stm32f10x.h>

void delay(unsigned int t)
{
	while(t--);
}

void tx(char *str)
{
	int i;
	for(i=0;*(str+i)!='\0';i++)
	{
		USART1->DR=*(str+i);
		while(!(USART1->SR & 1<<7));
		//delay(80000);
	}
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0;
	RCC->APB2ENR=1<<0|1<<2|1<<3|1<<14;
	GPIOA->CRH=0x4A0;
	GPIOB->CRL=0x8;
	USART1->CR1=1<<2|1<<3|1<<13;
	USART1->BRR=0X341;
	
	while(1)
	{
		//if(GPIOB->IDR&(1<<0))
		//{
		tx("sharvesh");
		//while(GPIOB->IDR&(1<<0));
		//}
	}
}