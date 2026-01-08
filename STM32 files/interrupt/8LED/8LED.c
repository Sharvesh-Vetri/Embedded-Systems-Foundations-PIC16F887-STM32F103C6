#include <stm32f10x.h>

void delay(unsigned int t)
{
	while(t--);
}

void EXTI0_IRQHandler()
{
	if(EXTI->PR & 1<<0)
	{
		GPIOB->ODR^=1<<0;
	}
	EXTI->PR=1<<0;
}
void EXTI1_IRQHandler()
{
	if(EXTI->PR & 1<<1)
	{
		GPIOB->ODR^=1<<1;
	}
	EXTI->PR=1<<1;
}
void EXTI2_IRQHandler()
{
	if(EXTI->PR & 1<<2)
	{
		GPIOB->ODR^=1<<2;
	}
	EXTI->PR=1<<2;
}
void EXTI3_IRQHandler()
{
	if(EXTI->PR & 1<<3)
	{
		GPIOB->ODR^=1<<3;
	}
	EXTI->PR=1<<3;
}
void EXTI4_IRQHandler()
{
	if(EXTI->PR & 1<<4)
	{
		GPIOB->ODR^=1<<4;
	}
	EXTI->PR=1<<4;
}
void EXTI9_5_IRQHandler()
{
	int i=5;
	for(;i<=9;i++)
	{
		if(EXTI->PR & 1<<i)
		{
			GPIOB->ODR^=1<<i;
			EXTI->PR=1<<i;
		}
	}
}
int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=1<<0|1<<2|1<<3;
	EXTI->IMR=255;
	EXTI->FTSR=255;
	
	AFIO->EXTICR[0]=0;
	AFIO->EXTICR[1]=0;
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	
	GPIOA->CRL=0x88888888;
	GPIOB->CRL=0x22222222;
	GPIOB->ODR=0;
	while(1)
	{
	}
}
	