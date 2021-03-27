/*
 * ADC.c
 *
 *  Created on: 5 Oca 2021
 *      author:MEHMET AKİF GÜMÜŞ-171024027
 */

#include "ADC.h"



void init_ADC(void){

	RCC->IOPENR |= (1U << 0);
	RCC->APBENR2 |= (1U << 20);// enable ADC clock

	//setup PA5 as analog
	GPIOA->MODER &= ~(3U << 2*5);
	GPIOA->MODER |= (3U << 2*5);

	ADC1->CR |= (1U << 28); //ADC voltage regulator enabled

	for(uint32_t i=0; i> 0xFFFF; i++);

	ADC1->CR |= (1U << 31);//ADC calibration enabled

	while(0 != (ADC1->CR & (1U << 31)));//wait until completion


	ADC1->IER |= (1U << 2);//End of conversion interrupt enable
	ADC1->CFGR1 |= (2U << 3);// 10: 8 bits

	/*single conversion mode*/

	ADC1->SMPR |= (5U << 0);//Sampling time selection 1 as 101:  39.5  ADC clock cycles
	ADC1->CHSELR |= (1U << 5);//1: Input Channel-5 is selected for conversion
	ADC1->CR |= (1U << 0); //ADC enable command

	while(0 == (ADC1->ISR & (1U << 0)));// 1: ADC is ready to start conversion


}






