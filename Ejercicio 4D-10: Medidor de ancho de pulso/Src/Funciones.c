/*
 * Funciones.c
 *
 *  Created on: Oct 14, 2025
 *      Author: ignacio
 */

#include "stm32f4xx.h"
#include "Funciones.h"

/************* Desarrollo de los prototipos de funciones ************/
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, uint8_t estado)
{
	if(estado) GPIOx->BSRR = GPIO_Pin;
	else GPIOx->BSRR = GPIO_Pin << 16U;
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin){
	return (GPIOx->IDR & GPIO_Pin) ? 1 : 0;
}

void delay_ms(uint32_t ms){
	//SysTick Timer
	SysTick->LOAD = (SystemCoreClock/1000) - 1;//1[ms]
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

	for(uint32_t i = 0; i < ms; i++){
		while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	}

	SysTick->CTRL = 0;
}

void delay_us(uint32_t us){
	//SysTick Timer
	SysTick->LOAD = (SystemCoreClock/1000000) * us - 1;//1[us]
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));

	SysTick->CTRL = 0;
}

void MostrarByte(uint8_t val){
	GPIO_WritePin(bit7,((val & 0x80) >> 7) & 1U);
	GPIO_WritePin(bit6,((val & 0x40) >> 6) & 1U);
	GPIO_WritePin(bit5,((val & 0x20) >> 5) & 1U);
	GPIO_WritePin(bit4,((val & 0x10) >> 4) & 1U);
	GPIO_WritePin(bit3,((val & 0x08) >> 3) & 1U);
	GPIO_WritePin(bit2,((val & 0x04) >> 2) & 1U);
	GPIO_WritePin(bit1,((val & 0x02) >> 1) & 1U);
	GPIO_WritePin(bit0,((val & 0x01) >> 0) & 1U);
}

void MostrarNibble(uint8_t val){
	GPIO_WritePin(bit3,((val & 0x08) >> 3) & 1U);
	GPIO_WritePin(bit2,((val & 0x04) >> 2) & 1U);
	GPIO_WritePin(bit1,((val & 0x02) >> 1) & 1U);
	GPIO_WritePin(bit0,((val & 0x01) >> 0) & 1U);
}

uint16_t BinToBCD(uint16_t numero){
	uint16_t digito = 0, shift = 0, numeroBCD = 0;
	while(numero > 0){
		digito = numero % 10;
		numeroBCD = numeroBCD | (digito << (4 * shift));
		numero = numero/10;
		shift++;
	}
	return numeroBCD;
}
