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
	RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;   // Reloj TIM11

	// PB9 -> TIM11_CH1 (AF3)
	GPIOB->MODER &= ~GPIO_MODER_MODER9;
	GPIOB->MODER |=  GPIO_MODER_MODER9_1;  // Modo alterno
	GPIOB->AFR[1] &= GPIO_AFRH_AFSEL9;
	GPIOB->AFR[1] |= (3UL << GPIO_AFRH_AFSEL9_Pos); // AF3 = TIM11

	//Base de tiempo del TIM11
	TIM11->ARR = 5000 - 1; 		// Valor para el tiempo máximo requerido
	TIM11->PSC = 3200 - 1;   	// Prescaler -> 5 kHz -> 5 [tick/ms]

	//Modo captura del TIM11
	// Sin filtro, sin prescaler
	TIM11->CCMR1 &= ~TIM_CCMR1_CC1S;	// Canal 1 como input en TI1
	TIM11->CCMR1 |=  TIM_CCMR1_CC1S_0;  // CC1S = 01 -> IC1 mapeado en TI1
	TIM11->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP); // Rising edge
	TIM11->CCER |= TIM_CCER_CC1E;	// Habilitar captura

	//Interrupciones por TIM11
	TIM11->DIER |= TIM_DIER_CC1IE;	// Habilitar interrupción del canal 1
	NVIC_EnableIRQ(TIM1_TRG_COM_TIM11_IRQn);
	NVIC_SetPriority(TIM1_TRG_COM_TIM11_IRQn, 1);
	TIM11->CR1 |= TIM_CR1_CEN;
}
