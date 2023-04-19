#include "stm32f7xx.h"

#define 	TIM1EN		(1U<<0)
#define     CR1_CEN		(1U<<0)


void tim1_1hz_init(void)
{
	/*Enable clock access to TIM1*/
	 RCC->APB2ENR |=TIM1EN;
	/*Set the prescaler*/
	 TIM1->PSC =  16 - 1; // 16 000 000 / 1600 = 10 000
	/*Set auto-relaod value*/
	 TIM1->ARR =  1000 - 1;   //10 000 /10 000 = 1
	/*Enable timer*/
	 TIM1->CR1 |=CR1_CEN;
}
