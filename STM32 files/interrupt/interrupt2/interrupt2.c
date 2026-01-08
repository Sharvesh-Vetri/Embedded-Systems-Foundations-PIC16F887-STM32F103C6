#include <stm32f10x.h>

void delay(unsigned int t)
{
	while(t--);
}

void EXTI4_IRQHandler()
{
	if(EXTI->PR & 1<<4)
	{
		GPIOB->BRR=1<<0;
		GPIOB->ODR=1<<1;
		delay(200000);
	}
	EXTI->PR=1<<4;
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=1<<0|1<<2|1<<3;
	EXTI->IMR=1<<4;
	EXTI->FTSR=1<<4;
	AFIO->EXTICR[1]=0;
	NVIC_EnableIRQ(EXTI4_IRQn);
	GPIOA->CRH=0x80000;
	GPIOB->CRL=0x22;
	while(1)
	{
		GPIOB->ODR=0X1;
	}
}
	