#include <stm32f10x.h>
//char *str="hello";
void delay(int t)
{
	while(t--);
}
void enable()
{
	GPIOC->ODR|=(1<<14);
	delay(500);
	GPIOC->BRR=(1<<14);
	delay(500);
}

void lcd(unsigned int rs,char data)
{
	GPIOC->ODR=(rs<<15);
	GPIOA->ODR=((data & 0xf0)>>4);
	enable();
	GPIOA->ODR=(data & 0x0f);
	enable();
}

void SPI1_IRQHandler()
{	
	if(SPI1->SR & 1<<0)
	{
		char data;
		data = SPI1->DR;
		lcd(1,data);
	}
}

void tx(char *str)
{
	int i;
	for(i=0;*(str+i)!='\0';i++)
	{
		SPI1->DR=*(str+i);
		while(!(SPI1->SR & 1<<1));
		//delay(50000);
	}
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0;
	RCC->APB2ENR=1<<0|1<<2|1<<3|1<<12|1<<4;
	SPI1->CR1=1<<2|1<<3|1<<6|1<<9;
	SPI1->CR2=1<<6;
	NVIC_EnableIRQ(SPI1_IRQn);
	
	GPIOB->CRL=0x22;
	GPIOA->CRL=0xA4AA2222;
	GPIOC->CRH=0x22000000;
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0E);
	lcd(0,0x80);
	
	GPIOB->ODR|=(3<<0);
	
	GPIOB->ODR&=~(1<<0);
	tx("slave1_");
	GPIOB->ODR|=(1<<0);
	
	lcd(0,0xc0);
	GPIOB->ODR&=~(1<<1);
	tx("slave2_");
	GPIOB->ODR|=(1<<1);
	while(1);
}