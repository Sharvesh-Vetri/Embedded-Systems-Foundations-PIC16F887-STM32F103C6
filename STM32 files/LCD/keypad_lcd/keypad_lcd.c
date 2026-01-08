#include <stm32f10x.h>

unsigned int i=0,count=0;

void delay(unsigned int t)
{
	while(t--);
}

void enable()
{
	GPIOA->ODR|=(1<<8);
	delay(200);
	GPIOA->BRR=(1<<8);
	delay(200);
}

void lcd(int rs,char data)
{
	GPIOA->ODR = rs<<9;
	GPIOA->ODR|=data;
	enable();
}

void dial(void)
{
	if(count==10)
	{
		lcd(0,0xc0);
		lcd(1,'C');
		lcd(1,'A');
		lcd(1,'L');
		lcd(1,'L');
	}
	else
	{
		lcd(0,0xc0);
		lcd(1,'F');
		lcd(1,'A');
		lcd(1,'I');
		lcd(1,'L');
	}
	while(1);
}
int main()
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1C;
	GPIOA->CRL=0x22222222;
	GPIOA->CRH=0x88800022;
	GPIOB->CRL=0x2222;
	
	lcd(0,0x38);
	lcd(0,0x0E);
	lcd(0,0x80);
	while(1)
	{
		GPIOB->ODR=0X1;
		if(GPIOA->IDR & (1<<15)){lcd(1,49);count++;while(GPIOA->IDR & (1<<15));}
		if(GPIOA->IDR & (1<<14)){lcd(1,50);count++;while(GPIOA->IDR & (1<<14));}
		if(GPIOA->IDR & (1<<13)){lcd(1,51);count++;while(GPIOA->IDR & (1<<13));}
			
		GPIOB->ODR=0X2;
		if(GPIOA->IDR & (1<<15)){lcd(1,52);count++;while(GPIOA->IDR & (1<<15));}
		if(GPIOA->IDR & (1<<14)){lcd(1,53);count++;while(GPIOA->IDR & (1<<14));}
		if(GPIOA->IDR & (1<<13)){lcd(1,54);count++;while(GPIOA->IDR & (1<<13));}
		
		GPIOB->ODR=0X4;
		if(GPIOA->IDR & (1<<15)){lcd(1,55);count++;while(GPIOA->IDR & (1<<15));}
		if(GPIOA->IDR & (1<<14)){lcd(1,56);count++;while(GPIOA->IDR & (1<<14));}
		if(GPIOA->IDR & (1<<13)){lcd(1,57);count++;while(GPIOA->IDR & (1<<13));}
		
		GPIOB->ODR=0X8;
		if(GPIOA->IDR & (1<<15)){dial();}
		if(GPIOA->IDR & (1<<14)){lcd(1,48);count++;while(GPIOA->IDR & (1<<14));}
	}
}