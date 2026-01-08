#include <stm32f10x.h>
#include <math.h>

void delay(unsigned int t)
{
	while(t--);
}

int main()
{
	RCC->CR=0X83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1c;
	GPIOA->CRL=0x22222222;
	while(1)
	{
		int i,j,k;
		for(i=8;i>=1;i--)
		{
			if(i==8){k=0;}
			else{k=k+pow(2,i);}
			
			for(j=0;j<i;j++)
			{				
				GPIOA->ODR=pow(2,j)+k;
				delay(200000);
				GPIOA->BRR=pow(2,j);
			}
		}
	}
}
