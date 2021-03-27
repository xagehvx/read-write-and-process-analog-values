#include "bsp.h"

uint32_t data;
void BSP_system_init(void){

	__disable_irq();

		init_ADC();
		init_timer2();
	__enable_irq();


}

void init_timer2(){

	RCC->IOPENR |= 7;
	RCC->APBENR1 |= (1U<< 1);// enable time2 module clock

	//setup PA6 as AF2
	GPIOA->MODER &= ~(3U << 2*6);
	GPIOA->MODER |= (2U << 2*6);

	// choose AF2 from mux
	GPIOA->AFR[0] &= ~(0xFU << 4*6);
	GPIOA->AFR[0] |= (1U << 4*6);

	//setup PB0 as AF1
	GPIOB->MODER &= ~(3U << 0);
	GPIOB->MODER |= (2U << 0);

	// choose AF1 from mux
	GPIOB->AFR[0] &= ~(0xFU << 0);
	GPIOB->AFR[0] |= (1U << 0);




	TIM3->CR1=0;// zero out the control register just in case
	TIM3->CR1 |= (1U << 7);	// ARPE
	TIM3->CNT=0;// zero out counter

	/*10 Msecond interrupt	 */

	TIM3->PSC = 10;
	TIM3->ARR = 16000;
	TIM3->DIER |= (1 << 0);// update interrupt enable


//	//PWM FOR PA6 TIM3_CH1
//	TIM3->CCMR1 |=(1 << 3); // output compare preload enable
//	TIM3->CCMR1 &= ~(1U << 16); //0
//	TIM3->CCMR1 &= ~(0xFU << 4);
//	TIM3->CCMR1 |= (0x6U << 4); // mode 1 enable
//	TIM3->CCER |= (1U << 0);
////	TIM3->CCR1	= 8000; //duty cycle

	//PWM FOR PB0 TIM3_CH3
	TIM3->CCMR2 |=(1 << 3); // output compare preload enable
	TIM3->CCMR2 &= ~(1U << 16); //0
	TIM3->CCMR2 &= ~(0xFU << 4);
	TIM3->CCMR2 |= (0x6U << 4); // mode 1 enable
	TIM3->CCER |= (1U << 8);
//	TIM3->CCR3	= 8000; //duty cycle


	TIM3->CR1 |= (1 << 0);// 	tım3 enable

	NVIC_SetPriority(TIM3_IRQn,3);
	NVIC_EnableIRQ(TIM3_IRQn);

}


void TIM3_IRQHandler(void){

	static int i =0;
	i++;
	TIM3->CCR1	= 1000*i;
	if(i==16)i=0;
//	ADC1->CR |= (1U << 2);//Bit 2 ADSTART: ADC start conversion command
//
//	while(0 == (ADC1->ISR & (1U << 2)));
//
	data = ADC1->DR;
//
//	TIM3->CCR1 = data*62;
//	TIM3->CCR3 = 16000 - (data*62);

	TIM3->SR &= ~(1U << 0); //clear update status register

}
