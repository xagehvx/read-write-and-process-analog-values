/*
 * bps.c
 *
 *  Created on: 5 Oca 2021
 *      author:MEHMET AKİF GÜMÜŞ-171024027
 */


#include "bsp.h"

uint32_t data;
volatile int counter = 0;

void BSP_system_init(void){

	__disable_irq();

		init_timer1();
		init_timer3();
		init_ADC();
		init_SSD();
//		displayID_SSD();
		BSP_button_init();

	__enable_irq();


}

void init_timer1(){

	RCC->APBENR2 |= (1U<< 11);// enable time1 module clock

	TIM1->CR1=0;// zero out the control register just in case
	TIM1->CR1 |= (1<<7);	// ARPE
	TIM1->CNT=0;// zero out counter

	/*10 ms interrupt	 */

	TIM1->PSC=10;
	TIM1->ARR=1600;

	TIM1->DIER |= (1 << 0);// update interrupt enable
	TIM1->CR1 |= (1 << 0);// 	tım1 enable

	NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,3);
	NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

}

void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
	ADC1->CR |= (1U << 2);//Bit 2 ADSTART: ADC start conversion command

	while(0 == (ADC1->ISR & (1U << 2)));

	data = ADC1->DR;

	if(data > 243){
		for(uint32_t i=0; i> 0xFFFFFF; i++);
		counter++;
		utility_SSD((float)counter);
	}


	TIM1->SR &= ~(1U<<0); //clear update status register

}

void init_timer3(void){

	RCC->APBENR1 |= (1U<< 1);// enable time3 module clock

	TIM3->CR1=0;// zero out the control register just in case
	TIM3->CR1 |= (1U << 7);	// ARPE
	TIM3->CNT=0;// zero out counter

	/*10 Msecond interrupt	 */

	TIM3->PSC = 10;
	TIM3->ARR = 160;

	TIM3->DIER |= (1 << 0);// update interrupt enable
	TIM3->CR1 |= (1 << 0);// 	tım3 enable

	NVIC_SetPriority(TIM3_IRQn,3);
	NVIC_EnableIRQ(TIM3_IRQn);

}

void TIM3_IRQHandler(void){

	display_SSD();

	TIM3->SR &= ~(1U << 0); //clear update status register
}



void BSP_button_init(void){
		/* Enable GPIOA clock */
    	RCC->IOPENR |= (1U << 0);

	    /* Setup PA1 as input */
	    GPIOA->MODER &= ~(3U << 2*1);
	    GPIOA->PUPDR |= (2U << 2*1); // Pull-down mode

	    /*setup interrrupts for inputs*/
	    EXTI->EXTICR[0] |= (0U << 8*1);//PA1	 EXTI1 mux ta PA1 için EXTICR0'ın 9.biti 0 yapıldı

	    /* MASK*/
	    EXTI->IMR1 |= (1U << 1);

	    /*rising edge*/
	    EXTI->RTSR1 |= (1U << 1);

	    /*NVIC*/
	    NVIC_SetPriority(EXTI0_1_IRQn,0);	// buton interruptı PA1 için EXTI1 in
	    									//içerisinde olduğundan EXTI0_1_IRQn kullanıldı.
	    NVIC_EnableIRQ(EXTI0_1_IRQn);	//nvic enabled
}

void EXTI0_1_IRQHandler(void){
	if (EXTI->RPR1 & (1U << 1)){
	counter=0;
	utility_SSD((float)counter);
	}
	EXTI->RPR1 |= (1U << 1);

	for(uint32_t i=0; i> 0xFFFFFFFF; i++);


}

