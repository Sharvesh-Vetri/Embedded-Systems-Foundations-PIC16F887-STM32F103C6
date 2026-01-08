#include <stm32f10x.h>
int i=0,count=9;

void timer()
{
	if(TIM2->SR & 1<<0)
	{
		count++;
		TIM2->SR=0;
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
		lcd(1,*(str+i));
	}
}


int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=1<<11|1<<2|1<<3|1<<4;
	RCC->APB1ENR=1<<0|1<<1;
	TIM2->CR1=1<<0;
	TIM2->CNT=0;
	TIM2->PSC=0XFFFF;
	TIM2->ARR=122;
	GPIOA->CRL=0x00002222;
	GPIOC->CRH=0x22000000;
	GPIOB->CRL=0X222;
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0e);
	while(1)
	{
		timer();
		if(count==10)
		{
			lcd(0,0x01);
			GPIOB->BRR=1<<3;
			GPIOB->ODR=1;
			print("STOP");
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
			GPIOB->ODR=1<<3;
			print("GO");
			count=0;
		}
	}
}	
			