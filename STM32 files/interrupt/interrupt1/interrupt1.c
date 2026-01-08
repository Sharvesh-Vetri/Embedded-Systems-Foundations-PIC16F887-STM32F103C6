#include <stm32f10x.h>

void delay(unsigned int t)
{
	while(t--);
}

void EXTI15_10_IRQHandler()
{
	if(EXTI->PR & 1<<15)
	{
		GPIOB->BRR=0X1;
		delay(200000);
	}
	EXTI->PR=1<<15;
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=1<<0|1<<2|1<<3;
	EXTI->IMR=1<<15;
	EXTI->FTSR=1<<15;
	AFIO->EXTICR[3]=0;
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	GPIOA->CRH=8<<28;
	GPIOB->CRL=0x2;
	while(1)
	{
		GPIOB->ODR=0X1;
	}
}
	