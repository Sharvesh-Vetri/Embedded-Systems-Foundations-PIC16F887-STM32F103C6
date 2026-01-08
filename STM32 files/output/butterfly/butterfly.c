#include <stm32f10x.h>

void delay(int t)
{
	while(t--);
}

int main()
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1C;
	
	GPIOA->CRL=0x22222222;
	while(1)
	{
		int i,j;
		for(i=3,j=4;i>=0;j++,i--)
		{
			GPIOA->ODR=(1<<i)+(1<<j);
			delay(200000);
			GPIOA->BRR=(1<<i)+(1<<j);
		}
		for(i=0,j=7;i<=3;j--,i++)
		{
			GPIOA->ODR=(1<<i)+(1<<j);
			delay(200000);
			GPIOA->BRR=(1<<i)+(1<<j);
		}
	}
}