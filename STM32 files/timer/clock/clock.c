#include <stm32f10x.h>
int i=0,count=0;
char time[9]="12:58:58";
void timer()
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
	delay(2500);
	GPIOC->BRR=(1<<14);
	delay(2500);
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

void hr_inc()
{
	if(time[1]=='2')
	{
		if(time[0]=='1')
		{
			time[1]='1';
			time[0]='0';
		}
		else
		{
			time[1]=time[1]+1;
		}
	}
	else
	{
		time[1]=time[1]+1;
	}
}

void min_inc()
{
	if(time[4]=='9')
	{
		time[4]='0';
		if(time[3]=='5')
		{
			time[3]='0';
			hr_inc();
		}
		else
		{
			time[3]=time[3]+1;
		}
	}
	else
	{
		time[4]=time[4]+1;
	}
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=1<<2|1<<3|1<<4;
	RCC->APB1ENR=1<<1;
	TIM3->CR1=1<<0;
	TIM3->CNT=0;
	TIM3->PSC=0XFFFF;
	TIM3->ARR=122;
	GPIOA->CRL=0x00002222;
	GPIOC->CRH=0x22000000;
	GPIOB->CRL=0X222;
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0e);
	print(0x80,time);
	while(1)
	{
		timer();
		if(count==1)
		{
			if(time[7]=='9')
			{
				time[7]='0';
				if(time[6]=='5')
				{
					time[6]='0';
					min_inc();
				}
				else
				{
					time[6]=time[6]+1;
				}
			}
			else
			{
				time[7]=time[7]+1;
			}
			print(0x80,time);
			count=0;
	 }
			
	}
}