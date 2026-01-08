#include <stm32f10x.h>

void delay(unsigned int t)
{
	while(t--);
}

void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & 1<<13)
	{
		GPIOA->BRR=1<<0;
		GPIOA->ODR=1<<1;
		delay(200000);
	}
	EXTI->PR=1<<13;
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=1<<0|1<<2|1<<3;
	EXTI->IMR=1<<13;
	EXTI->FTSR=1<<13;
	AFIO->EXTICR[3]=1<<4;
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	GPIOB->CRH=8<<20;
	GPIOA->CRL=0x22;
	while(1)
	{
		GPIOA->ODR=0X1;
	}
}
