#include <stm32f10x.h>
int count=0;

void timer()
{
	if(TIM3->SR & 1<<0)
	{
		count++;
		TIM3->SR=0;
	}
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=1<<11|1<<2;
	RCC->APB1ENR=1<<0|1<<1;
	TIM3->CR1=1<<0;
	TIM3->CNT=0;
	TIM3->PSC=0XFFFF;
	TIM3->ARR=122;
	GPIOA->CRL=0X2;
	while(1)
	{
		timer();
		if(count==2)
		{
			GPIOA->ODR^=(1<<0);
			count=0;
		}
	}
}
			
			