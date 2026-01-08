#include <stm32f10x.h>

int count=0;

int main()
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1C;
	GPIOA->CRL=0x8;
	GPIOB->CRL=0x2;
	
	while(1)
	{
		if(GPIOA->IDR & (1<<0))
		{
			GPIOB->ODR=GPIOB->ODR^(1<<0);
			while(GPIOA->IDR & (1<<0));
		}
	}
}