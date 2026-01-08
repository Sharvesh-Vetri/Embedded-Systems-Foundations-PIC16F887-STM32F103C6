#include <stm32f10x.h>
int i=0,count=0;
char pwd[5];

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

void pwd_check()
{
	char real[5]="1234";
	lcd(0,0x01);
	for(i=0;pwd[i]!='\0';i++)
	{
		if(pwd[i]!=real[i])
		{
			print(" WRONG PWD");
			break;
		}
		else if(pwd[i+1]=='\0')
		{
			print(" PWD MATCH");
		}		
	}
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1c;
	GPIOA->CRL=0x00002222;
	GPIOA->CRH=0x00000888;
	GPIOB->CRL=0x2222;
	GPIOC->CRH=0x22000000;
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0e);
	print("ENTER THE PWD:");
	lcd(0,0xC0);
	while(1)
	{
		GPIOB->ODR=0X1;
		if(GPIOA->IDR & (1<<10)){pwd[count]='1';lcd(1,'1');count++;while(GPIOA->IDR & (1<<10));}
		if(GPIOA->IDR & (1<<9)){pwd[count]='2';lcd(1,'2');count++;while(GPIOA->IDR & (1<<9));}
		if(GPIOA->IDR & (1<<8)){pwd[count]='3';lcd(1,'3');count++;while(GPIOA->IDR & (1<<8));}
			
		GPIOB->ODR=0X2;
		if(GPIOA->IDR & (1<<10)){pwd[count]='4';lcd(1,'4');count++;while(GPIOA->IDR & (1<<10));}
		if(GPIOA->IDR & (1<<9)){pwd[count]='5';lcd(1,'5');count++;while(GPIOA->IDR & (1<<9));}
		if(GPIOA->IDR & (1<<8)){pwd[count]='6';lcd(1,'6');count++;while(GPIOA->IDR & (1<<8));}
		
		GPIOB->ODR=0X4;
		if(GPIOA->IDR & (1<<10)){pwd[count]='7';lcd(1,'7');count++;while(GPIOA->IDR & (1<<10));}
		if(GPIOA->IDR & (1<<9)){pwd[count]='8';lcd(1,'8');count++;while(GPIOA->IDR & (1<<9));}
		if(GPIOA->IDR & (1<<8)){pwd[count]='9';lcd(1,'9');count++;while(GPIOA->IDR & (1<<8));}
		
		GPIOB->ODR=0X8;
		if(GPIOA->IDR & (1<<10)){pwd_check();}
		if(GPIOA->IDR & (1<<9)){pwd[count]='0';lcd(1,'0');while(GPIOA->IDR & (1<<9));}

	}
}
