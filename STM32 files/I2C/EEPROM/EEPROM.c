#include <stm32f10x.h>
char val1,val2,val3;

void delay(int t)
{
	while(t--);
}
void enable()
{
	GPIOC->ODR|=(1<<14);
	delay(5000);
	GPIOC->BRR=(1<<14);
	delay(5000);
}

void lcd(unsigned int rs,char data)
{
	GPIOC->ODR=(rs<<15);
	GPIOA->ODR=((data & 0xf0)>>4);
	enable();
	GPIOA->ODR=(data & 0x0f);
	enable();
}
void print(char addrs,char *str)
{
	int i;
	lcd(0,addrs);
	for(i=0;*(str+i)!='\0';i++)
	{
		GPIOC->ODR=1<<15;
		GPIOA->ODR=(*(str+i) & 0xf0)>>4;
		enable();
		GPIOA->ODR=*(str+i) & 0x0f;
		enable();
	}
}

void start()
{
	I2C1->CR1|=1<<8;
	while(!(I2C1->SR2&1<<0));
	while(!(I2C1->SR2&1<<1));
	while(!(I2C1->SR1&1<<0));
}

void address(char adrs)
{
	I2C1->DR=adrs;
	while(!(I2C1->SR1&1<<1));
	while(!(I2C1->SR2&1<<2));
	while(!(I2C1->SR1&1<<7));
}

void write(char data)
{
	I2C1->DR=data;
	while(!(I2C1->SR1&1<<2));
	while(!(I2C1->SR1&1<<7));
}

void stop()
{
	I2C1->CR1|=1<<9;
	while(!(I2C1->SR2&1<<0));
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB1ENR=1<<21;
	RCC->APB2ENR=1<<0|1<<2|1<<3|1<<4;
	GPIOA->CRL=0x00002222;
	GPIOB->CRL=0xEE000000;
	GPIOC->CRH=0x22000000;
	I2C1->CR1=1<<0;
	I2C1->CR2=8;
	I2C1->CCR=40;
	I2C1->TRISE=9;

	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0e);
	lcd(0,0x80);
	start();
	address(0xA0);
	address(0x00);
	write('1');
	write('2');
	write('3');
	stop();
	delay(500);
	
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0e);
	lcd(0,0x80);
	while(1)
	{
		start();
		address(0xA0);
		write(0x00);
		start();
		I2C1->DR=0xA1;
		while(!(I2C1->SR1&1<<1));
		(void)I2C1->SR2;
		I2C1->CR1|=1<<10;
		while(!(I2C1->SR1&1<<6));
    val1 = I2C1->DR;
		while(!(I2C1->SR1&1<<6));
		val2 = I2C1->DR;
		while(!(I2C1->SR1&1<<6));
		val3 = I2C1->DR;
		I2C1->CR1|=(~(1<<10));
		stop();
		
		lcd(0,0x80);
		lcd(1,val1);
		lcd(1,val2);
		lcd(1,val3);
	}
}
	