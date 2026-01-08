#include <stm32f10x.h>
int count=0;

int main()
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1C;
	GPIOA->CRL=0x888;
	GPIOB->CRL=0x2;
	
	while(1)
	{
		if(GPIOA->IDR & (1<<2)){count++;while(GPIOA->IDR & (1<<2));}
		
		if(count%2==0)
		{
			if(GPIOA->IDR & (1<<0))
			{
				GPIOB->ODR=0X1;
			}
			
			else if(GPIOA->IDR & (1<<1))
			{
				GPIOB->BRR=0X1;
			}
		}
		
		if(count%2==1)
		{
			if(GPIOA->IDR & (1<<0))
			{
				GPIOB->BRR=0X1;
			}
			
			else if(GPIOA->IDR & (1<<1))
			{
				GPIOB->ODR=0X1;
			}
		}
	}
}	