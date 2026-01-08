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
	ADC1->CR2|=1<<0;
	while(!(ADC1->SR & 1<<1));
	adc=ADC1->DR;
	
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
}

int conv2(char addr)
{
	ADC2->CR2|=1<<0;
	while(!(ADC2->SR & 1<<1));
	dv=ADC2->DR;
	
	a2 = dv/1000;
	b2 = (dv/100)%10;
	c2 = (dv/10)%10;
	d2 = dv%10;
	
	lcd(0,addr);
	lcd(1,(48+a2));
	lcd(1,(48+b2));
	lcd(1,(48+c2));
	lcd(1,(48+d2));
	
	lcd(1,' ');
    
	vlt2=((dv*33)/4095);
	p2 = vlt2/10;
	lcd(1,p2+48);
	lcd(1,'.');
	q2 = vlt2%10;
	lcd(1,q2+48);
	lcd(1,'V');
	
	lcd(1,' ');
	
	res2=(((float)dv)*100.0)/4095.0;
	if(res2>99)
	{
		int x2 = (res2/100);
		lcd(1,x2+48);
	}
	y2 = ((res2/10)%10);
	lcd(1,y2+48);
	z2 = res2%10;
	lcd(1,z2+48);
	lcd(1,'%');
}

int main(void)
{
	RCC->CR=0x83;
	RCC->CFGR=3<<14;
	RCC->APB2ENR=1<<10|1<<9|1<<3|1<<4|1<<2;
	
	ADC1->CR2|=1<<0|1<<2|7<<17;
	ADC1->SMPR2|=7<<12;
	ADC2->SQR1=1<<20;
	ADC1->SQR3=0x0000000004;
	
	ADC2->CR2|=1<<0|1<<2|7<<17;
	ADC2->SMPR2|=7<<12;
	ADC2->SQR3=0x00000050;

	
	GPIOA->CRL=0x00002222;
	GPIOC->CRH=0x22000000;
	lcd(0,0x02);
	lcd(0,0x28);
	lcd(0,0x0c);
	lcd(0,0x80);
	while(1)
	{
		conv1(0x80);
		conv2(0xc0);
	}
}