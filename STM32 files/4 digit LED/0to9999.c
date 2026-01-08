#include <stm32f10x.h>

int i,j,k,l,arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};

void delay(unsigned int t)
{
	while(t--);
}
int main()
{
	RCC->CR=0x83;
	RCC->CFGR=0x00;
	RCC->APB2ENR=0x1C;
	GPIOA->CRL=0x2222222;
	GPIOB->CRL=0x2222;
	
	while(1)
	{
		for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            for(k=0;k<10;k++)
            {
                for(l=0;l<10;l++)
                {
									GPIOB->ODR=1<<0;
									GPIOA->ODR=arr[l];
									delay(80000);
									
									GPIOB->ODR=1<<1;
									GPIOA->ODR=arr[k];
									delay(80000);
									
									GPIOB->ODR=1<<4;
									GPIOA->ODR=arr[j];
									delay(80000);
									
									GPIOB->ODR=1<<3;
									GPIOA->ODR=arr[i];
									delay(80000);
								}
						}
				}
		}
	}
}
