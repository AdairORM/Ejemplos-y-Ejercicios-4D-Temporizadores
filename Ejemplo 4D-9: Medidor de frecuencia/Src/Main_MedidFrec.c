/*********************************************************************
****************************  Encabezado  ****************************
**********************************************************************
* Número del ejercicio	: Ejemplo 4D-9
* Nombre del ejercicio	: Medidor de frecuencia
* Autor(es)				: Ignacio Rangel Fuerte
* Asignatura			: Circuitos Digitales
* Grupo					:
* Tema					: Programación de Microcontroladores
* Subtema				: Manejo de temporizadores (Input Capture)
* Fecha de entrega		:

* Descripción:
	Desarrollar un programa en lenguaje C con controladores CMSIS
	que mida la frecuencia de una señal cuadrada que puede variar
	entre 1 y 100[Hz].
	Muestre el valor de la frecuencia en [Hz] usando un display
	LCD 20x4 y con una resolución de centésimas.
	Realizar la medición utilizando el modo captura de un temporizador.

* Microcontrolador:
	- Núcleo del microcontrolador	: ARM Cortex M4
	- Matrícula del microcontrolador: STM32F411CEU6
	- Tarjeta de desarrollo			: BlackPill v3.1

* Notas:
	-  TIM11 -> IC en B9

====================================================================*/

/*********************************************************************
*****************************  Programa  *****************************
*********************************************************************/

/********************** Bibliotecas a utilizar **********************/
#include "stm32f4xx.h"
#include "GPIO_Config.h"
#include "TIMx_Config.h"
#include "Funciones.h"
#include "LCD_4bits.h"
#include "stdio.h"

/********************* Constantes de compilador *********************/

/******************* Variables globales de proceso ******************/
uint8_t BN = 0;
uint16_t val1 = 0, val2 = 0, Dval = 0, frecEnt = 0, frecFrac = 0;
float frec = 0.0f;
char bufLCD[20];

/***************** Prototipos de funciones a utilizar ***************/

/************************ Programa principal ************************/
int main(void){
/*------------------ Variables locales de proceso ------------------*/

/*-------------- Configuración de periféricos (SETUP) --------------*/
	GPIOA_Config();
	GPIOB_Config();
	TIM11_Config();
	LCD_Inicializar();
	delay_ms(5);

/*--------------------- Ciclo infinito (LOOP) ----------------------*/
	while(1){
		if(Dval != 0){
			frec = 5000.0f / (float)Dval;
			frecEnt = (uint16_t)frec;
			frecFrac = (uint16_t)((frec - frecEnt)*100);
		}
		else{
			frecEnt = 0;
			frecFrac = 0;
		}
		LCD_PonerCursorRC(0,5);
		LCD_EnviarCadena("Frecuencia");
		sprintf(bufLCD,"%3d.%02d[Hz]",frecEnt,frecFrac); //d de decimal que es un entero
		LCD_PonerCursorRC(1,6);
		LCD_EnviarCadena(bufLCD);
		delay_ms(5);
	}
}

/************* Desarrollo de los prototipos de funciones ************/

/************* Desarrollo de las rutinas de interrupción ************/
void TIM1_TRG_COM_TIM11_IRQHandler(){
    if(BN == 0){
        val1 = TIM11->CCR1;   // Primer flanco
        BN = 1;
    }
    else{
        val2 = TIM11->CCR1;   // Segundo flanco
        if (val2 > val1)	Dval = val2 - val1;
        else				Dval = (TIM11->ARR - val1) + val2;
        BN = 0;       // Listo para la siguiente medición
    }
    TIM11->SR &= ~TIM_SR_CC1IF; // Limpiar bandera de interrupción
}
//====================================================================


