/*********************************************************************
****************************  Encabezado  ****************************
**********************************************************************
* Número del ejercicio	: Ejemplo 4D-11
* Nombre del ejercicio	: Medidor de ciclo de trabajo
* Autor(es)				: Ignacio Rangel Fuerte
* Asignatura			: Circuitos Digitales
* Grupo					:
* Tema					: Programación de Microcontroladores
* Subtema				: Manejo de temporizadores (Input Capture)
* Fecha de entrega		:

* Descripción:
	Desarrollar un programa en lenguaje C con controladores CMSIS que
	mida el ciclo de trabajo de una señal cuadrada que puede variar
	entre 0.2[Hz] y 1[kHz].
	Muestre el valor de la frecuencia en [Hz], la duración del pulso
	en ON en [s] y el valor del ciclo de trabajo en porcentaje usando
	un display LCD 20x4 y con una resolución de centésimas.
	Realizar la medición utilizando el modo captura de un temporizador.

* Microcontrolador:
	- Núcleo del microcontrolador	: ARM Cortex M4
	- Matrícula del microcontrolador: STM32F411CEU6
	- Tarjeta de desarrollo			: BlackPill v3.1

* Notas:
	- TIM2 -> IC en A3
	- Usando CH4 y CH3

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
_Bool BN = 0;
uint32_t val1_on = 0, val2_on = 0, val_up = 0, val_down = 0, DvalF = 0, DvalT = 0;
uint32_t frecEnt = 0, frecFrac = 0, tonEnt = 0, tonFrac = 0;
uint8_t dutyEnt = 0, dutyFrac = 0;
float ton_ms = 0.0f, frec = 0.0f, duty = 0.0f;
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
		if(DvalF != 0){
			frec = 100000.0f / (float)DvalF;
			frecEnt = (uint32_t)frec;
			frecFrac = (uint32_t)((frec - frecEnt)*100);

			ton_ms = (float)DvalT / 100.0f;
			tonEnt = (uint32_t)(ton_ms);
			tonFrac = (uint32_t)((ton_ms - tonEnt)*100);

			duty = ton_ms * frec / 10.0f; //(ton_ms/1000) * frec * 100%
			dutyEnt = (uint8_t)(duty);
			dutyFrac = (uint8_t)((duty - dutyEnt)*100);
		}

		else{
			frecEnt = 0;
			frecFrac = 0;
		}

		sprintf(bufLCD,"Frec: %4lu.%02lu[Hz]",frecEnt,frecFrac);
		LCD_PonerCursorRC(0,0);
		LCD_EnviarCadena(bufLCD);

		sprintf(bufLCD," Ton: %4lu.%02lu[ms] ",tonEnt,tonFrac);
		LCD_PonerCursorRC(1,0);
		LCD_EnviarCadena(bufLCD);

		sprintf(bufLCD,"Duty:  %3u.%02u%%",dutyEnt,dutyFrac);
		LCD_PonerCursorRC(2,0);
		LCD_EnviarCadena(bufLCD);

		delay_ms(5);
	}
}

/************* Desarrollo de los prototipos de funciones ************/

/************* Desarrollo de las rutinas de interrupción ************/
void TIM2_IRQHandler(){
	if(TIM2->SR & TIM_SR_CC4IF){
		if(!BN){
			val1_on = TIM2->CCR4;   // Flanco de subida
			BN = 1;
		}
		else{
			val2_on = TIM2->CCR4;   // 2do flanco de subida
			if (val2_on >= val1_on)	DvalF = val2_on - val1_on;
			else				DvalF = (TIM2->ARR - val1_on) + val2_on;
			BN = 0;       // Listo para la siguiente medición
		}
		TIM2->SR &= ~TIM_SR_CC4IF; // Limpiar bandera de interrupción
	}

	if(TIM2->SR & TIM_SR_CC3IF){
		val_down = TIM2->CCR3;   // Flanco de bajada

		if(BN) val_up = val1_on;
		else   val_up = val2_on;

		if(val_down >= val_up)	DvalT = val_down - val_up;
		else				    DvalT = (TIM2->ARR - val_up) + val_down;

		TIM2->SR &= ~TIM_SR_CC3IF; // Limpiar bandera de interrupción
	}
}
//====================================================================


