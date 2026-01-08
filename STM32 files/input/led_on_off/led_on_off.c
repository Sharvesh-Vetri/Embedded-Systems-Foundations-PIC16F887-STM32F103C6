#include <stm32f10x.h>

int main()
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1C;
	GPIOA->CRL=0x22222222;
	GPIOB->CRL=0x88888888;
	
	while(1)
	{
		if(GPIOB->IDR==0x01)
		{
			GPIOA->ODR=GPIOA->ODR^(1<<0);
			while(GPIOB->IDR==0x01);
		}
	}
}