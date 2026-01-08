#include <stm32f10x.h>

void delay(unsigned int t)
{
	while(t--);
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1C;
	GPIOA->CRL=0X22222222;
	while(1)
	{
		GPIOA->ODR=0xff;
		delay(200000);
		GPIOA->BRR=0xff;
		delay(200000);
	}	
}