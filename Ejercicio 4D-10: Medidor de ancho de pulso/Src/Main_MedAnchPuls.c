/*********************************************************************
****************************  Encabezado  ****************************
**********************************************************************
* Número del ejercicio	: Ejemplo 4D-10
* Nombre del ejercicio	: Medidor de ancho de pulso
* Autor(es)				: Ignacio Rangel Fuerte
* Asignatura			: Circuitos Digitales
* Grupo					:
* Tema					: Programación de Microcontroladores
* Subtema				: Manejo de temporizadores (Input Capture)
* Fecha de entrega		:

* Descripción:
	Desarrollar un programa en lenguaje C con controladores CMSIS que
	mida el tiempo que dura en nivel alto una señal cuadrada.
	Considere que la señal podría estar en alto durante máximo 5.0[s]
	y mínimo por 1.0[ms].
	Muestre el valor de la duración del pulso en [ms] usando un
	display LCD 20x4 y con una resolución de milésimas.
	Realizar la medición utilizando el modo captura de un temporizador.

* Microcontrolador:
	- Núcleo del microcontrolador	: ARM Cortex M4
	- Matrícula del microcontrolador: STM32F411CEU6
	- Tarjeta de desarrollo			: BlackPill v3.1

* Notas:
	-  TIM2 -> IC en A3

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
uint32_t val1 = 0, val2 = 0, Dval = 0, tonEnt = 0, tonFrac = 0;
float ton_s = 0.0f;
char bufLCD[20];

/***************** Prototipos de funciones a utilizar ***************/

/************************ Programa principal ************************/
int main(void){
/*------------------ Variables locales de proceso ------------------*/

/*-------------- Configuración de periféricos (SETUP) --------------*/
	GPIOA_Config();
	GPIOB_Config();
	TIM2_Config();
	LCD_Inicializar();
	delay_ms(5);

/*--------------------- Ciclo infinito (LOOP) ----------------------*/
	while(1){
		ton_s = (float)Dval / 100.0f;
		tonEnt = (uint32_t)(ton_s);
		tonFrac = (uint32_t)((ton_s - tonEnt)*1000);
		LCD_PonerCursorRC(0,3);
		LCD_EnviarCadena("Ancho de pulso:");
		sprintf(bufLCD,"%4lu.%03lu[ms] ",tonEnt,tonFrac);
		LCD_PonerCursorRC(1,6);
		LCD_EnviarCadena(bufLCD);
		delay_ms(5);
	}
}

/************* Desarrollo de los prototipos de funciones ************/

/************* Desarrollo de las rutinas de interrupción ************/
void TIM2_IRQHandler(){
    if(BN == 0){
        val1 = TIM2->CCR4;   // Flanco de subida
        BN = 1;
        TIM2->CCER |= TIM_CCER_CC4P; //Cambia a detección flanco de bajada
    }
    else{
        val2 = TIM2->CCR4;   // Flanco de bajada
        if (val2 >= val1)	Dval = val2 - val1;
        else				Dval = (TIM2->ARR - val1) + val2;
        BN = 0;       // Listo para la siguiente medición
        TIM2->CCER &= ~TIM_CCER_CC4P; //Cambia a detección flanco de subida
    }
    TIM2->SR &= ~TIM_SR_CC4IF; // Limpiar bandera de interrupción
}
//====================================================================


