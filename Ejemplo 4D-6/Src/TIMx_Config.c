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
	RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;

	// PB9 -> TIM11_CH1 (AF3)
	GPIOB->MODER &= ~GPIO_MODER_MODER9;
	GPIOB->MODER |=  GPIO_MODER_MODER9_1;  // Modo alterno
	GPIOB->AFR[1] &= GPIO_AFRH_AFSEL9;
	GPIOB->AFR[1] |= (3UL << GPIO_AFRH_AFSEL9_Pos);

	//Base de tiempo del TIM11
	TIM11->PSC = 16000 - 1;
	TIM11->ARR = 500 - 1;
	TIM11->CNT = 0; //reinicio del contador

	//Modo compare del TIM11
	TIM11->CCMR1 &= ~TIM_CCMR1_CC1S;
	TIM11->CCMR1 &= ~TIM_CCMR1_OC1M;
	TIM11->CCMR1 |= (3U << TIM_CCMR1_OC1M_Pos);

	TIM11->CCER |= TIM_CCER_CC1E;
	TIM11->CCR1 = 500 - 1; //produce el match
	TIM11->CR1 |= TIM_CR1_CEN; //encender el timer 11
}
