/*
 * Config_Perif.c
 *
 *  Created on: Oct 14, 2025
 *      Author: ignacio
 */

#include "stm32f4xx.h"
#include "TIMx_Config.h"

/************* Desarrollo de los prototipos de funciones ************/
void TIM1_Config(void){

}

void TIM2_Config(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

	// PA3 -> TIM2_CH4 (AF1)
	GPIOA->MODER &= ~GPIO_MODER_MODER3;
	GPIOA->MODER |=  GPIO_MODER_MODER3_1;
	GPIOA->AFR[0] &= GPIO_AFRL_AFSEL3;
	GPIOA->AFR[0] |= (1UL << GPIO_AFRL_AFSEL3_Pos);

	//Base de tiempo
	TIM2->ARR = 200000 - 1;
	TIM2->PSC = 160 - 1;
	TIM2->CNT = 0;

	TIM2->CCMR2 &= ~(TIM_CCMR2_CC4S | TIM_CCMR2_CC3S);
	TIM2->CCMR2 |=  TIM_CCMR2_CC4S_0;
	TIM2->CCMR2 |=  TIM_CCMR2_CC3S_1;
	TIM2->CCER &= ~(TIM_CCER_CC4NP | TIM_CCER_CC4P);
	TIM2->CCER &= ~(TIM_CCER_CC3NP | TIM_CCER_CC3P);
	TIM2->CCER |= TIM_CCER_CC3P; //Falling Edge en CC3
	TIM2->CCER |= (TIM_CCER_CC4E | TIM_CCER_CC3E);

	TIM2->DIER |= (TIM_DIER_CC4IE | TIM_DIER_CC3IE);
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn,1);

	TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM3_Config(void){

}

void TIM4_Config(void){

}

void TIM5_Config(void){

}

void TIM9_Config(void){

}

void TIM10_Config(void){

}

void TIM11_Config(void){

}
