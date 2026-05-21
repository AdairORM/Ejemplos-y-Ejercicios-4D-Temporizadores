/*********************************************************************
****************************  Encabezado  ****************************
**********************************************************************
* Número del ejercicio	: Ejemplo 4D-6
* Nombre del ejercicio	: Blink por OC
* Autor(es)				: Ignacio Rangel Fuerte
* Asignatura			: Circuitos Digitales
* Grupo					:
* Tema					: Programación de Microcontroladores
* Subtema				: Manejo de temporizadores (Output Compare)
* Fecha de entrega		:

* Descripción:
	Desarrollar un programa en lenguaje C que haga parpadear un LED.
	Deberá pasar 500[ms] encendido y 500[ms] apagado.
	Utilice el temporizador TIM11 en modo comparación para generar el
	retardo por hardware.

* Microcontrolador:
	- Núcleo del microcontrolador	: ARM Cortex M4
	- Matrícula del microcontrolador: STM32F411CEU6
	- Tarjeta de desarrollo			: BlackPill v3.1

* Notas:
	-  OC en B9

====================================================================*/

/*********************************************************************
*****************************  Programa  *****************************
*********************************************************************/

/********************** Bibliotecas a utilizar **********************/
#include "stm32f4xx.h"
#include "GPIO_Config.h"
#include "TIMx_Config.h"

/********************* Constantes de compilador *********************/

/******************* Variables globales de proceso ******************/

/***************** Prototipos de funciones a utilizar ***************/

/************************ Programa principal ************************/
int main(void){
/*------------------ Variables locales de proceso ------------------*/

/*-------------- Configuración de periféricos (SETUP) --------------*/
	GPIOB_Config(); //llamar puerto B
	TIM11_Config(); //activamos timer 11

/*--------------------- Ciclo infinito (LOOP) ----------------------*/
	while(1){

	}
}

/************* Desarrollo de los prototipos de funciones ************/

/************* Desarrollo de las rutinas de interrupción ************/

//====================================================================


