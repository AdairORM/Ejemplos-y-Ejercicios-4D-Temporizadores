/*
 * Config_Perif.c
 *
 *  Created on: Oct 14, 2025
 *      Author: ignacio
 */

#include "stm32f4xx.h"
#include "GPIO_Config.h"

/************* Desarrollo de los prototipos de funciones ************/
void GPIOA_Config(void){

}

void GPIOB_Config(void){
	RCC->AHB1ENR = RCC_AHB1ENR_GPIOBEN;
}
