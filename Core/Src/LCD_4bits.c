/*
 * LCD_4bits.c
 *
 *  Created on: Oct 16, 2025
 *      Author: ignacio
 */

#include "stm32f4xx.h"
#include "Funciones.h"
#include "LCD_4bits.h"

/************* Desarrollo de los prototipos de funciones ************/
void LCD_PulsoEnable(void){
	GPIO_WritePin(LCD_PIN_EN,1);
	delay_us(1);
	GPIO_WritePin(LCD_PIN_EN,0);
	delay_us(100);
}

void LCD_EnviarNibble(uint8_t nibble){
	GPIO_WritePin(LCD_PIN_D7,((nibble & 0x08) >> 3) & 1U);
	GPIO_WritePin(LCD_PIN_D6,((nibble & 0x04) >> 2) & 1U);
	GPIO_WritePin(LCD_PIN_D5,((nibble & 0x02) >> 1) & 1U);
	GPIO_WritePin(LCD_PIN_D4,((nibble & 0x01) >> 0) & 1U);
	LCD_PulsoEnable();
}

void LCD_EnviarByte(uint8_t byte, uint8_t es_dato){
	if(es_dato) GPIO_WritePin(LCD_PIN_RS,1);
	else 		GPIO_WritePin(LCD_PIN_RS,0);

	LCD_EnviarNibble((byte & 0xF0) >> 4);
	LCD_EnviarNibble(byte & 0x0F);
	delay_us(500);
}

void LCD_PonerCursorRC(uint8_t renglon, uint8_t columna){
	uint8_t offsets[] = {0x00,0x40,0x14,0x54}; //20x4
	LCD_EnviarByte(0x80 | (offsets[renglon] + columna),0);
	delay_ms(5);
}

void LCD_EnviarCaracter(unsigned char c){
	LCD_EnviarByte(c,1);
}

void LCD_EnviarCadena(const char * cadena){
	while(*cadena){
		LCD_EnviarCaracter(*cadena);
		cadena++;
	}
}

void LCD_Inicializar(void){
	delay_ms(50);
	LCD_EnviarNibble(0x03);
	delay_ms(5);
	LCD_EnviarNibble(0x03);
	delay_ms(5);
	LCD_EnviarNibble(0x03);
	delay_ms(1);
	LCD_EnviarNibble(0x02);

	LCD_EnviarByte(0x28,0); //Función: 4-bit, 2 líneas, 5x8
	LCD_EnviarByte(0x0C,0);	//Display ON, cursor OFF
	LCD_EnviarByte(0x06,0);	//Modo entrada
	LCD_Limpiar(); //Clear display
}

void LCD_Limpiar(void){
	LCD_EnviarByte(0x01,0);
	delay_ms(2);
}
