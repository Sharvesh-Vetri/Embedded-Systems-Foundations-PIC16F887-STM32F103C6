#include <stm32f10x.h>
int i;
unsigned int adc,res,x,y,z,vlt,p,q,a,b,c,d,e;
unsigned int dv,res2,x2,y2,z2,vlt2,p2,q2,a2,b2,c2,d2,e2;

void delay(unsigned int t)
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

int conv1(char addrs)
{
	a = adc/1000;
	b = (adc/100)%10;
	c = (adc/10)%10;
	d = adc%10;
	
	lcd(0,addrs);
	lcd(1,(48+a));
	lcd(1,(48+b));
	lcd(1,(48+c));
	lcd(1,(48+d));
	
	lcd(1,' ');
    
	vlt=((adc*33)/4095);
	p = vlt/10;
	lcd(1,p+48);
	lcd(1,'.');
	q = vlt%10;
	lcd(1,q+48);
	lcd(1,'V');
	
	lcd(1,' ');
	
	res=(((float)adc)*100.0)/4095.0;
	if(res>99)
	{
		int x = (res/100);
		lcd(1,x+48);
	}
	y = ((res/10)%10);
	lcd(1,y+48);
	z = res%10;
	lcd(1,z+48);
	lcd(1,'%');
	lcd(1,' ');
}

void ADC1_2_IRQHandler()
{
	if(ADC1->SR & 1<<1)
	{
		adc=ADC1->DR;
		conv1(0x80);
	}
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=3<<14;
	RCC->APB2ENR=1<<10|1<<9|1<<3|1<<2|1<<4;
	
	ADC1->CR1|=1<<5;
	ADC1->CR2|=1<<0|1<<2|7<<17;
	ADC1->SMPR2|=7<<12;
	ADC1->SQR3=0x0000000004;
	NVIC_EnableIRQ(ADC1_2_IRQn); 
	
	GPIOA->CRL=0x00002222;
	GPIOC->CRH=0x22000000;
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0c);
	lcd(0,0x80);
	while(1)
	{
		ADC1->CR2|=1<<22;
	}
}