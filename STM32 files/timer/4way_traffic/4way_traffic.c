#include <stm32f10x.h>
int i=0,count=9;

void TIM3_IRQHandler()
{
	if(TIM3->SR & 1<<0)
	{
		count++;
		TIM3->SR=0;
	}
}

void delay(unsigned int t)
{
	while(t--);
}

void enable()
{
	GPIOC->ODR|=(1<<14);
	delay(20000);
	GPIOC->BRR=(1<<14);
	delay(20000);
}

void lcd(unsigned int rs,char data)
{
	GPIOC->ODR=(rs<<15);
	GPIOA->ODR=((data & 0xf0)>>4);
	enable();
	GPIOA->ODR=(data & 0x0f);
	enable();
}

void print(char *str)
{
	lcd(0,0x80);
	for(i=0;*(str+i)!='\0';i++)
	{
		GPIOC->ODR=1<<15;
		GPIOA->ODR=(*(str+i) & 0xf0)>>4;
		enable();
		GPIOA->ODR=*(str+i) & 0x0f;
		enable();
	}
}


int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=1<<2;
	RCC->APB1ENR=1<<1;
	TIM3->CR1=1<<0;
	TIM3->CNT=0;
	TIM3->PSC=0XFFFF;
	TIM3->ARR=122;
	TIM3->DIER=1;
	GPIOA->CRL=0x00002222;
	GPIOC->CRH=0x22000000;
	GPIOB->CRL=0X222;
	NVIC_EnableIRQ(TIM3_IRQn);
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0e);
	while(1)
	{
		if(count==10)
		{
			lcd(0,0x01);
			GPIOB->BRR=1<<2;
			GPIOB->ODR=1;
			print("1:STOP 2:G0");
		}
		if(count==15)
		{
			lcd(0,0x01);
			GPIOB->BRR=1;
			GPIOB->ODR=1<<1;
			print("WAIT");
		}
		if(count==25)
		{
			lcd(0,0x01);
			GPIOB->BRR=1<<1;
			GPIOB->ODR=1<<2;
			print("1:GO 2:STOP");
			count=0;
		}
	}
}
			
			