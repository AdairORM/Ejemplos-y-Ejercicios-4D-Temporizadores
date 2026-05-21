/*
 * Funciones.h
 *
 *  Created on: Oct 14, 2025
 *      Author: ignacio
 */

/********************* Constantes de compilador *********************/
#define	bit7 GPIOA,GPIO_ODR_OD11
#define	bit6 GPIOA,GPIO_ODR_OD10
#define	bit5 GPIOA,GPIO_ODR_OD9
#define	bit4 GPIOA,GPIO_ODR_OD8
#define	bit3 GPIOB,GPIO_ODR_OD15
#define	bit2 GPIOB,GPIO_ODR_OD14
#define	bit1 GPIOB,GPIO_ODR_OD13
#define	bit0 GPIOB,GPIO_ODR_OD12

/***************** Prototipos de funciones a utilizar ***************/
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin, uint8_t estado);
uint8_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin);

void MostrarNibble(uint8_t val);
void MostrarByte(uint8_t val);
uint16_t BinToBCD(uint16_t numero);
