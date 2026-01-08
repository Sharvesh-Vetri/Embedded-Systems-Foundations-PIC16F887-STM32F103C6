#include <stm32f10x.h>

unsigned int count=0,fail[4]={0x71,0x77,0x06,0x38},call[3]={0x39,0x77,0x38},arr[10]={0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67,0x3f};

void delay(unsigned int t)
{
	while(t--);
}

void dial()
{
	while(1)
	{
	if(count==10)
	{
		GPIOA->ODR=call[0]+(7<<8);
		delay(2000);
									
		GPIOA->ODR=call[1]+(11<<8);
		delay(2000);
								
		GPIOA->ODR=call[2]+(13<<8);
	  delay(2000);
									
		GPIOA->ODR=call[2]+(14<<8);
		delay(2000);
	}
	else
	{
		GPIOA->ODR=fail[0]+(7<<8);
		delay(2000);
									
		GPIOA->ODR=fail[1]+(11<<8);
		delay(2000);
								
		GPIOA->ODR=fail[2]+(13<<8);
		delay(2000);
									
		GPIOA->ODR=fail[3]+(14<<8);
		delay(2000);
	}
	}
}
int main()
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1C;
	GPIOA->CRL=0x22222222;
	GPIOA->CRH=0x88822222;
	GPIOB->CRL=0x2222;
	
	while(1)
	{
		GPIOB->ODR=0X1;
		if(GPIOA->IDR & (1<<15)){GPIOA->ODR=arr[0]+(14<<8);count++;while(GPIOA->IDR & (1<<15));}
		if(GPIOA->IDR & (1<<14)){GPIOA->ODR=arr[1]+(14<<8);count++;while(GPIOA->IDR & (1<<14));}
		if(GPIOA->IDR & (1<<13)){GPIOA->ODR=arr[2]+(14<<8);count++;while(GPIOA->IDR & (1<<13));}
			
		GPIOB->ODR=0X2;
		if(GPIOA->IDR & (1<<15)){GPIOA->ODR=arr[3]+(14<<8);count++;while(GPIOA->IDR & (1<<15));}
		if(GPIOA->IDR & (1<<14)){GPIOA->ODR=arr[4]+(14<<8);count++;while(GPIOA->IDR & (1<<14));}
		if(GPIOA->IDR & (1<<13)){GPIOA->ODR=arr[5]+(14<<8);count++;while(GPIOA->IDR & (1<<13));}
		
		GPIOB->ODR=0X4;
		if(GPIOA->IDR & (1<<15)){GPIOA->ODR=arr[6]+(14<<8);count++;while(GPIOA->IDR & (1<<15));}
		if(GPIOA->IDR & (1<<14)){GPIOA->ODR=arr[7]+(14<<8);count++;while(GPIOA->IDR & (1<<14));}
		if(GPIOA->IDR & (1<<13)){GPIOA->ODR=arr[8]+(14<<8);count++;while(GPIOA->IDR & (1<<13));}
		
		GPIOB->ODR=0X8;
		if(GPIOA->IDR & (1<<15)){dial();}
		if(GPIOA->IDR & (1<<14)){GPIOA->ODR=arr[9]+(14<<8);count++;while(GPIOA->IDR & (1<<14));}
	}
}