#include "adc.h"

#define		GPIOAEN			(1U<<0)
#define		ADC1EN			(1U<<8)
#define		CR2_CONT		(1U<<1)
#define		SEQ_LEN_1		0
#define		CH4_RANK1		(1U<<2) // 0B 0100
#define		CR2_SWSTART		(1U<<30)
#define		CR2_ADON		(1U<<0)
#define		SR_EOC			(1U<<1)

void pa4_adc1_init(void){

	/******Configure the ADC gpio pin******/
	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA4 mode to analog mode*/
	GPIOA->MODER |=(1U<<8);
	GPIOA->MODER |=(1U<<9);

	/******Configure the ADC module ******/
	/*Enable clock access to the ADC module*/
	RCC->APB2ENR |=ADC1EN;

	/*Set conversion to continuous*/
	ADC1->CR2 |=CR2_CONT;

	/*Set sequencer length to 1*/
	ADC1->SQR1 = SEQ_LEN_1;

	/*Set adc channel*/
	ADC1->SQR3 |= CH4_RANK1;

	/*Enable adc module*/
	ADC1->CR2 |=CR2_ADON;

	/*Start conversion*/
	ADC1->CR2 |= CR2_SWSTART;

}


uint32_t adc_get_data(void)
{
	/*Wait for End-of-Conversion flag*/
	while(!(ADC1->SR & SR_EOC)){}

	/*Read results*/
	return (ADC1->DR);
}
