/*
 * LCD_4bits.h
 *
 *  Created on: Oct 16, 2025
 *      Author: ignacio
 */

/********************* Constantes de compilador *********************/
#define	LCD_PIN_RS	GPIOA,GPIO_ODR_OD9
#define	LCD_PIN_EN 	GPIOA,GPIO_ODR_OD8
#define	LCD_PIN_D7 	GPIOB,GPIO_ODR_OD15
#define	LCD_PIN_D6 	GPIOB,GPIO_ODR_OD14
#define	LCD_PIN_D5 	GPIOB,GPIO_ODR_OD13
#define	LCD_PIN_D4 	GPIOB,GPIO_ODR_OD12

/***************** Prototipos de funciones a utilizar ***************/
void LCD_PulsoEnable(void);
void LCD_EnviarNibble(uint8_t nibble);
void LCD_EnviarByte(uint8_t byte, uint8_t es_dato);
void LCD_PonerCursorRC(uint8_t renglon, uint8_t columna);
void LCD_EnviarCaracter(unsigned char c);
void LCD_EnviarCadena(const char * cadena);
void LCD_Inicializar(void);
void LCD_Limpiar(void);
