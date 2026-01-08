#include <stm32f10x.h>

void delay(unsigned int t)
{
	while(t--);
}

int main()
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	GPIOA->CRL=GPIOA->CRH=0x22222222;
	while(1)
	{
		unsigned int i;
		for(i=1;i<=32768;)
		{
			GPIOA->ODR=i;
			delay(200000);
			GPIOA->BRR=i;
			i=i*2;
		}
	}
}
