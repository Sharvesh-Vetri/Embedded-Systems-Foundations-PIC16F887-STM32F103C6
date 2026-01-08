#include <stm32f10x.h>
int i=0,count=0;
char pwd[5];

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
	GPIOA->ODR=(rs<<9);
	GPIOA->ODR|=(data);
	enable();
}

void print(char *str)
{
	for(i=0;*(str+i)!='\0';i++)
	{
		lcd(0,0x80+i);
		GPIOA->ODR=(1<<9);
		GPIOA->ODR|=*(str+i);
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
			print("WRONG PWD");
		}
		else if(pwd[i+1]!='\0')
		{
			print("PWD MATCH");
		}		
	}
	while(1);
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1c;
	GPIOA->CRL=0x22222222;
	GPIOA->CRH=0x88800022;
	GPIOB->CRL=0x2222;
	
	lcd(0,0x38);
	lcd(0,0x0c);
	print("ENTER THE PWD:");
	lcd(0,0xC0);
	while(1)
	{
		GPIOB->ODR=0X1;
		if(GPIOA->IDR & (1<<15)){pwd[count]='1';lcd(1,'1');count++;while(GPIOA->IDR & (1<<15));}
		if(GPIOA->IDR & (1<<14)){pwd[count]='2';lcd(1,'2');count++;while(GPIOA->IDR & (1<<14));}
		if(GPIOA->IDR & (1<<13)){pwd[count]='3';lcd(1,'3');count++;while(GPIOA->IDR & (1<<13));}
			
		GPIOB->ODR=0X2;
		if(GPIOA->IDR & (1<<15)){pwd[count]='4';lcd(1,'4');count++;while(GPIOA->IDR & (1<<15));}
		if(GPIOA->IDR & (1<<14)){pwd[count]='5';lcd(1,'5');count++;while(GPIOA->IDR & (1<<14));}
		if(GPIOA->IDR & (1<<13)){pwd[count]='6';lcd(1,'6');count++;while(GPIOA->IDR & (1<<13));}
		
		GPIOB->ODR=0X4;
		if(GPIOA->IDR & (1<<15)){pwd[count]='7';lcd(1,'7');count++;while(GPIOA->IDR & (1<<15));}
		if(GPIOA->IDR & (1<<14)){pwd[count]='8';lcd(1,'8');count++;while(GPIOA->IDR & (1<<14));}
		if(GPIOA->IDR & (1<<13)){pwd[count]='9';lcd(1,'9');count++;while(GPIOA->IDR & (1<<13));}
		
		GPIOB->ODR=0X8;
		if(GPIOA->IDR & (1<<15)){pwd_check();}
		if(GPIOA->IDR & (1<<14)){pwd[count]='0';lcd(1,'0');while(GPIOA->IDR & (1<<14));}

	}
}