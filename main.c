#include <stdio.h>
#include "stm32f7xx.h"
#include "uart.h"
#include "led.h"
#include "adc.h"
#include "tim.h"
#include "stm32f767xx.h"
#include "stm32f7xx.h"


float sensor_value[10000];
float y[10000]={0};


int main(void)
{
	SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2)); // set bits 20-23 for CP10 and CP11
	uart3_tx_init();
	pa4_adc1_init();
	tim1_1hz_init();

	while(1)
	{
	for(int i =0; i<1000; i++)
		{
		  sensor_value[i] =  adc_get_data();
		  while(!(TIM1->SR & SR_UIF)){}
		  TIM1->SR &=~SR_UIF;

		  for (int j = 2; j<1000; j++)
		  {
			  if (j>2)
				  {
				   //y[i] = 4096.00;
			  		 y[j] = (double)(0.9847*sensor_value[i] - 1.8731*sensor_value[i-1] + 0.9847*sensor_value[i-2] + 1.8731*y[i-1] - 0.9695*y[i-2]);
			  	   }
		  }
		  	  for (int k =0; k<1000; k++)
		  	  {
		  		  //printf("%dA\n",y[j]);
		  		printf("%fA\n",y[j]);
		  	  }

		}
	}
}
